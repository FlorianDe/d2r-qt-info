function(get_version_from_git)
    set(UNKNOWN_PLACEHOLDER "unknown")
    set(GIT_VARIABLE_UNKNOWN_PLACEHOLDER ${UNKNOWN_PLACEHOLDER} PARENT_SCOPE)

    # Check if Git is available
    find_program(GIT_EXECUTABLE git)
    if (NOT GIT_EXECUTABLE)
        message(FATAL_ERROR "Git not found")
        return()
    endif ()

    # Get the latest commit hash (not necessarily of the tag)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
            OUTPUT_VARIABLE git_hash
            ERROR_VARIABLE commit_git_error
            RESULT_VARIABLE commit_result
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_STRIP_TRAILING_WHITESPACE
    )
    if (NOT commit_result EQUAL 0)
        message(FATAL_ERROR "Git execution error (get commit): ${commit_git_error}")
        set(GIT_HASH ${UNKNOWN_PLACEHOLDER} PARENT_SCOPE)
        set(GIT_HASH_SHORT ${UNKNOWN_PLACEHOLDER} PARENT_SCOPE)
    else ()
        set(GIT_HASH "${git_hash}" PARENT_SCOPE)
        string(SUBSTRING "${git_hash}" 0 10 git_hash_short)
        set(GIT_HASH_SHORT "${git_hash_short}" PARENT_SCOPE)
    endif ()

    # Get the latest tag
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
            OUTPUT_VARIABLE git_tag
            ERROR_VARIABLE git_error
            RESULT_VARIABLE result
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_STRIP_TRAILING_WHITESPACE
    )
    if (NOT result EQUAL 0)
        message(AUTHOR_WARNING "No tags found: ${git_error}")
        set(GIT_TAG ${UNKNOWN_PLACEHOLDER} PARENT_SCOPE)
        set(VERSION ${UNKNOWN_PLACEHOLDER} PARENT_SCOPE)
        set(VERSION_MAJOR ${UNKNOWN_PLACEHOLDER} PARENT_SCOPE)
        set(VERSION_MINOR ${UNKNOWN_PLACEHOLDER} PARENT_SCOPE)
        set(VERSION_PATCH ${UNKNOWN_PLACEHOLDER} PARENT_SCOPE)
        set(VERSION_SUFFIX ${UNKNOWN_PLACEHOLDER} PARENT_SCOPE)
        set(SEMVER ${UNKNOWN_PLACEHOLDER} PARENT_SCOPE)
    else()
        # Regex for SemVer with optional suffix
        set(semver_regex "^v?(0|[1-9][0-9]*)[.](0|[1-9][0-9]*)[.](0|[1-9][0-9]*)(-[.0-9A-Za-z-]+)?([+][.0-9A-Za-z-]+)?$")

        if ("${git_tag}" MATCHES "${semver_regex}")
            set(VERSION_MAJOR "${CMAKE_MATCH_1}")
            set(VERSION_MINOR "${CMAKE_MATCH_2}")
            set(VERSION_PATCH "${CMAKE_MATCH_3}")
            set(VERSION_SUFFIX "${CMAKE_MATCH_4}")

            set(SEMVER "${git_tag}" PARENT_SCOPE)
            string(REGEX REPLACE "^v" "" VERSION "${git_tag}")
            set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" PARENT_SCOPE)

            if (VERSION_SUFFIX)
                string(APPEND VERSION "${VERSION_SUFFIX}")
            endif ()

            set(VERSION_MAJOR ${VERSION_MAJOR} PARENT_SCOPE)
            set(VERSION_MINOR ${VERSION_MINOR} PARENT_SCOPE)
            set(VERSION_PATCH ${VERSION_PATCH} PARENT_SCOPE)
            set(VERSION_SUFFIX ${VERSION_SUFFIX} PARENT_SCOPE)

            message(STATUS "Parsed SemVer: ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}${VERSION_SUFFIX}")
        else ()
            message(STATUS "Git tag '${git_tag}' is not a valid SemVer")
            set(GIT_TAG "${git_tag}" PARENT_SCOPE)
        endif ()
    endif ()
endfunction()

#get_version_from_git()
#message(STATUS "GIT_HASH: ${GIT_HASH}")
#message(STATUS "GIT_HASH_SHORT: ${GIT_HASH_SHORT}")
#message(STATUS "GIT_TAG: ${GIT_TAG}")
#message(STATUS "VERSION: ${VERSION}")
#message(STATUS "VERSION_MAJOR: ${VERSION_MAJOR}")
#message(STATUS "VERSION_MINOR: ${VERSION_MINOR}")
#message(STATUS "VERSION_PATCH: ${VERSION_PATCH}")
#message(STATUS "VERSION_SUFFIX: ${VERSION_SUFFIX}")