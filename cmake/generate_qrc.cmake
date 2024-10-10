# TODO: Try to get rid of the .qrc file at all and add the resources via Cmake qt_add_resources check https://doc.qt.io/qt-6/resources.html

# RUN WITH:
# cmake -P ./cmake/generate_qrc.cmake

#if (DEFINED RESOURCE_DIR)
#    message(STATUS "Resource Directory: ${RESOURCE_DIR}")
#else ()
#    message(FATAL_ERROR "RESOURCE_DIR is not defined.")
#endif ()

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(RESOURCE_QRC "${CMAKE_BINARY_DIR}/res/resources.qrc")

message(STATUS "Creating resource.qrc file")
message(STATUS "Checking inside ${RESOURCE_DIR}")

# Open resources.qrc for writing
file(WRITE ${RESOURCE_QRC} "<!DOCTYPE RCC>\n<RCC version=\"1.0\">\n")
file(APPEND ${RESOURCE_QRC} "<qresource prefix=\"/\">\n")

file(GLOB_RECURSE RESOURCE_FILES_TO_INCLUDE RELATIVE "${RESOURCE_DIR}" "${RESOURCE_DIR}/images/*" "${RESOURCE_DIR}/json/*")

# Temp hardcoded
file(APPEND ${RESOURCE_QRC} "  <file alias=\"AppIcon\">AppIcon.png</file>\n")

# Iterate over all found files and append to the resources.qrc file
foreach (file ${RESOURCE_FILES_TO_INCLUDE})
    if(NOT file MATCHES ".*\\.(DS_Store|jpg)$")
    message(STATUS ${file})
    file(APPEND ${RESOURCE_QRC} "  <file>${file}</file>\n")
    endif()
endforeach ()

# Close the qresource tag
file(APPEND ${RESOURCE_QRC} "</qresource>\n</RCC>\n")

message(STATUS "Finished creating resource.qrc file")