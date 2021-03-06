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

# "LEADING_ZERO" function
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
INCLUDE(LeadingZero)

# Configure version.h file
SET(LIBDIURNA_VERSION_MAJOR "1")
SET(LIBDIURNA_VERSION_MINOR "0")
SET(LIBDIURNA_VERSION_PATCH "0")
SET(LIBDIURNA_VERSION_STRING "${LIBDIURNA_VERSION_MAJOR}.${LIBDIURNA_VERSION_MINOR}.${LIBDIURNA_VERSION_PATCH}")

LEADING_ZERO(PADDED_VERSION_MINOR 3 ${LIBDIURNA_VERSION_MINOR})
LEADING_ZERO(PADDED_VERSION_PATCH 3 ${LIBDIURNA_VERSION_PATCH})

SET(LIBDIURNA_VERSION_NUMBER "${LIBDIURNA_VERSION_MAJOR}${PADDED_VERSION_MINOR}${PADDED_VERSION_PATCH}")
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/res/version.h.template ${CMAKE_SOURCE_DIR}/inc/version.h)

# Display build type
IF (NOT CMAKE_BUILD_TYPE)
    MESSAGE(STATUS "Build type: -")
ELSE (NOT CMAKE_BUILD_TYPE)
    MESSAGE(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
ENDIF (NOT CMAKE_BUILD_TYPE)

# Thread
FIND_PACKAGE(Threads REQUIRED)
IF (CMAKE_USE_PTHREADS_INIT)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSE_PTHREAD=1")
ELSEIF (CMAKE_USE_WIN32_THREADS_INIT)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSE_WINTHREAD=1")
ENDIF (CMAKE_USE_PTHREADS_INIT)

# Header directories
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/inc")

# Source Files
IF (WIN32)
    LIST(
            APPEND
            WINDOWS_FILES
            src/windows/win_nanosleep.c)
ENDIF (WIN32)

IF (NOT WIN32)
    ADD_DEFINITIONS("-DHAVE_SYSLOG=1")
    LIST(
            APPEND
            APPENDER_SYSLOG_FILES
            src/appender/diurna_appender_syslog_create.c
            src/appender/diurna_appender_syslog_write.c)
ENDIF (NOT WIN32)

SET(SOURCE_FILES ${SOURCE_FILES}
        src/appender/diurna_appender_console_create.c
        src/appender/diurna_appender_console_write.c
        src/appender/diurna_appender_file_create.c
        src/appender/diurna_appender_file_destroy.c
        src/appender/diurna_appender_file_write.c
        ${APPENDER_SYSLOG_FILES}
        src/core/diurna_cfg_appender_register.c
        src/core/diurna_cfg_appender_unregister_all.c
        src/core/diurna_cfg_loglevel_set.c
        src/core/diurna_destroy.c
        src/core/diurna_initialize.c
        src/core/diurna_initialize_ex.c
        src/core/diurna_log_consumer_thread.c
        src/core/diurna_logger.c
        src/core/diurna_version_as_int.c
        src/core/diurna_version_as_str.c
        src/queue/diurna_queue_dequeue.c
        src/queue/diurna_queue_destroy.c
        src/queue/diurna_queue_initialize.c
        src/queue/diurna_queue_queue.c
        ${WINDOWS_FILES})

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

IF (WIN32)
    TARGET_LINK_LIBRARIES(lib-diurna-test Threads::Threads)
ELSE (WIN32)
    TARGET_LINK_LIBRARIES(lib-diurna-test Threads::Threads)
ENDIF (WIN32)

# Install
IF (NOT MSVC)
    INSTALL(TARGETS lib-diurna-static ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
ENDIF (NOT MSVC)
INSTALL(TARGETS lib-diurna-shared ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/inc/diurna.h DESTINATION include)
IF (NOT WIN32)
    INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/man-pages/ DESTINATION share/man/man3 FILES_MATCHING PATTERN "*.3*")
ENDIF (NOT WIN32)

# Current architecture/operating system
IF (NOT DEFINED ARCHITECTURE)
    EXEC_PROGRAM("uname -m" OUTPUT_VARIABLE ARCHITECTURE)
ENDIF (NOT DEFINED ARCHITECTURE)

IF (APPLE)
    EXEC_PROGRAM("sw_vers -productVersion" OUTPUT_VARIABLE OPERATING_SYSTEM_VERSION)
    SET(OPERATING_SYSTEM "macos_${OPERATING_SYSTEM_VERSION}")
ELSE ()
    IF (WIN32)
        SET(OPERATING_SYSTEM "windows")
    ELSE ()
        EXEC_PROGRAM("awk -F= '$1==\"ID\" { print $2 ;}' /etc/os-release" OUTPUT_VARIABLE OPERATING_SYSTEM)
        EXEC_PROGRAM("awk -F= '$1==\"VERSION_ID\" { print $2 ;}' /etc/os-release" OUTPUT_VARIABLE OPERATING_SYSTEM_VERSION)

        STRING(CONCAT OPERATING_SYSTEM ${OPERATING_SYSTEM} "_" ${OPERATING_SYSTEM_VERSION})
        STRING(REPLACE "\"" "" OPERATING_SYSTEM ${OPERATING_SYSTEM})
    ENDIF (WIN32)
ENDIF (APPLE)

MESSAGE(STATUS "Architecture: ${ARCHITECTURE}")
MESSAGE(STATUS "Operating System: ${OPERATING_SYSTEM}")

# Packaging
SET(CPACK_PACKAGE_VERSION "${LIBDIURNA_VERSION_STRING}")
SET(CPACK_PACKAGE_VERSION_MAJOR "${LIBDIURNA_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${LIBDIURNA_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${LIBDIURNA_VERSION_PATCH}")
SET(CPACK_PACKAGE_NAME "libdiurna")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/res/package-description.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple, fast, and portable logging library for C applications")

SET(PACKAGE_IGNORED_FILES "${CMAKE_CURRENT_BINARY_DIR}/;/.git/;.gitignore;~$;${CPACK_SOURCE_IGNORE_FILES}")

SET(CPACK_GENERATOR "TGZ")
SET(CPACK_ARCHIVE_FILE_NAME
        "libdiurna_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}\
_${OPERATING_SYSTEM}_${ARCHITECTURE}")

OPTION(BUILD_RPM "Build a RPM package" OFF)
IF (BUILD_RPM)
    SET(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
    SET(CPACK_RPM_PACKAGE_VENDOR "Thibault Meyer")
    SET(CPACK_RPM_PACKAGE_LICENSE "MIT")
    SET(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
    SET(CPACK_RPM_PACKAGE_URL "https://github.com/thibaultmeyer/libdiurna")
    SET(CPACK_RPM_FILE_NAME
            "libdiurna_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}\
_${OPERATING_SYSTEM}_${ARCHITECTURE}.rpm")
ENDIF (BUILD_RPM)

OPTION(BUILD_DEB "Build a DEB package" OFF)
IF (BUILD_DEB)
    SET(CPACK_GENERATOR "${CPACK_GENERATOR};DEB")
    SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Thibault Meyer")
    SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
    SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/thibaultmeyer/libdiurna")
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.4)")
    SET(CPACK_DEBIAN_FILE_NAME
            "libdiurna_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}\
_${OPERATING_SYSTEM}_${ARCHITECTURE}.deb")
ENDIF (BUILD_DEB)

SET(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME})
SET(CPACK_SOURCE_IGNORE_FILES ${PACKAGE_IGNORED_FILES})
MESSAGE(STATUS "Generator: ${CPACK_GENERATOR}")

INCLUDE(CPack)
