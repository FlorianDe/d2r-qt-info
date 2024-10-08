cmake_minimum_required(VERSION 3.21.1)
# CMAKE_POLICY(SET CMP0020 NEW)

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")
    #set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64") # universal build
    #set(CMAKE_OSX_ARCHITECTURES "x86_64") # arm build
endif(APPLE)

project(D2R-Qt-Info LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(get_version_from_git)
get_version_from_git()

# Project 
set(PROJECT_COMPANY "FlorianDe")
set(PROJECT_COPYRIGHT "Copyright (c) FlorianDe. All rights reserved.")
#set(PROJECT_DOMAIN "de.floriande.d2r-info")
set(PROJECT_VERSION ${SEMVER})
set(PROJECT_BUNDLE_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Add FetchContent module
include(FetchContent)

# Download and include nlohmann/json
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(json)

# Qt
# Set this to your Qt installation
set(ICON_NAME AppIcon)
set(CMAKE_AUTOMOC ON) # For meta object compiler 
set(CMAKE_AUTOUIC ON) # Resource files
set(CMAKE_AUTORCC ON) # UI Files


find_package(Qt6 REQUIRED COMPONENTS Widgets )

# Set platform-specific variables
if (APPLE)
    message(STATUS "Building for macOS")
    set(APP_ICON "res/${ICON_NAME}.icns")  # macOS-specific icon
elseif (WIN32)
    message(STATUS "Building for Windows")
    set(APP_ICON "res/${ICON_NAME}.ico")  # Windows-specific icon resource
    set(CMAKE_RC_COMPILER_INIT windres)
    set(WINDOWS_EXECUTABLE TRUE)
    set(MACOSX_BUNDLE FALSE)  # Ensure this is not treated as a macOS bundle

endif ()

set(RESOURCE_FILES
        res/resources.qrc
        res/${ICON_NAME}.png
        ${APP_ICON}
)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR})

# source files
file(GLOB_RECURSE SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/*.h
)

# executable
add_executable(${PROJECT_NAME}
#        ${OS_BUNDLE}
        ${SOURCE_FILES}
        ${RESOURCE_FILES}
        ${APP_ICON}
)

# expose values to c++ files
target_compile_definitions(${PROJECT_NAME} PRIVATE
        CMAKE_DEF_PROJECT_VERSION="${PROJECT_VERSION}"
        CMAKE_DEF_COMMIT_HASH_VERSION="${GIT_HASH_SHORT}"
        CMAKE_DEF_APP_NAME="${PROJECT_BUNDLE_NAME}"
        CMAKE_DEF_ORG_COMPANY="${PROJECT_COMPANY}"
        CMAKE_DEF_ORG_DOMAIN="${PROJECT_DOMAIN}"
)

# Link Libs
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets nlohmann_json::nlohmann_json)

# # Define platform-specific configurations

# Set macOS-specific properties (Bundle settings, Info.plist, etc.)
if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE TRUE
#            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist # Could use a file or just set the Options below MACOSX_BUNDLE_XXX
            RESOURCE "${RESOURCE_FILES}"
            OUTPUT_NAME "${PROJECT_BUNDLE_NAME}"
    )
    ## macOS cBundle building
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(OS_BUNDLE "MACOSX_BUNDLE")
        set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_BUNDLE_NAME})
        set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
        set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION})
        set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION})
        set(MACOSX_BUNDLE_COPYRIGHT ${PROJECT_COPYRIGHT})
        set(MACOSX_BUNDLE_GUI_IDENTIFIER ${PROJECT_DOMAIN})
        set(MACOSX_BUNDLE_ICON_FILE ${ICON_NAME}.icns)
    else()
        set(CMAKE_BUILD_TYPE "Debug")
    endif ()
elseif (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE
            RESOURCE ${RESOURCE_FILES}
    )
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)
else ()
    message(FATAL_ERROR "Unsupported platform. This project only supports macOS and Windows currently.")
endif ()

## Copy the platform-specific Qt libraries after building (optional, for deployment)
#if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
#    # macOS: Use macdeployqt after build
#    add_custom_command(TARGET MyApp POST_BUILD
#            COMMAND /path/to/Qt6/bin/macdeployqt ${CMAKE_BINARY_DIR}/MyApp.app
#    )
#elseif(WIN32)
#    # Windows: Use windeployqt after build
#    add_custom_command(TARGET MyApp POST_BUILD
#            COMMAND ${Qt6_DIR}/bin/windeployqt --release $<TARGET_FILE:MyApp>
#    )
#endif()

# # Define platform-specific configurations
# if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
#     # Windows-specific settings
#     target_link_libraries(MyQtApp PRIVATE Qt6::WinExtras)
#     # Set output directory
#     set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
#     # macOS-specific settings
#     set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/MyQtApp.app/Contents/MacOS)
#     # Add macOS bundle setup
#     set_target_properties(MyQtApp PROPERTIES MACOSX_BUNDLE TRUE)
# endif