CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)
PROJECT(lib-diurna C)

# Settings
SET(CMAKE_C_STANDARD 99)
IF (MSVC)
    SET(CMAKE_C_FLAGS "-Wall")
ELSE (MSVC)
    SET(CMAKE_C_FLAGS "-Wall -Werror -pedantic -fPIC")
ENDIF (MSVC)
SET(CMAKE_CXX_FLAGS_DEBUG "-g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Configure version.h file
SET(LIBDIURNA_VERSION_STRING "1.0.0")
SET(LIBDIURNA_VERSION_NUMBER "10000")
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/res/version.h.template ${CMAKE_SOURCE_DIR}/src/version.h)

# Display build type
IF (NOT CMAKE_BUILD_TYPE)
    MESSAGE(STATUS "Build type: -")
ELSE (NOT CMAKE_BUILD_TYPE)
    MESSAGE(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
ENDIF (NOT CMAKE_BUILD_TYPE)

# Source Files
SET(SOURCE_FILES ${SOURCE_FILES}
        src/diurna_appender_console.c
        src/diurna_destroy.c
        src/diurna_get_version_as_int.c
        src/diurna_get_version_as_str.c
        src/diurna_initialize.c
        src/diurna_logger.c)

# Test Files
SET(TEST_FILES ${TEST_FILES}
        test/test_main.c)

# Library
ADD_LIBRARY(lib-diurna-obj OBJECT ${SOURCE_FILES})
ADD_LIBRARY(lib-diurna-static STATIC $<TARGET_OBJECTS:lib-diurna-obj>)
ADD_LIBRARY(lib-diurna-shared SHARED $<TARGET_OBJECTS:lib-diurna-obj>)
IF (NOT MSVC)
    SET_TARGET_PROPERTIES(lib-diurna-static PROPERTIES OUTPUT_NAME "diurna")
ENDIF (NOT MSVC)
SET_TARGET_PROPERTIES(lib-diurna-shared PROPERTIES OUTPUT_NAME "diurna")

# Binary (Unit Tests)
ADD_EXECUTABLE(lib-diurna-test $<TARGET_OBJECTS:lib-diurna-obj> ${TEST_FILES})

# Install
IF (NOT MSVC)
    INSTALL(TARGETS lib-diurna-static ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
ENDIF (NOT MSVC)
INSTALL(TARGETS lib-diurna-shared ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/src/ DESTINATION include FILES_MATCHING PATTERN "*.h*")
