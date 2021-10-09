CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)
PROJECT(lib-diurna C)

# CMake modules
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
INCLUDE(LeadingZero)

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
SET(SOURCE_FILES ${SOURCE_FILES}
        src/appender/diurna_appender_console.c
        src/core/diurna_destroy.c
        src/core/diurna_get_version_as_int.c
        src/core/diurna_get_version_as_str.c
        src/core/diurna_initialize.c
        src/core/diurna_log_consumer_thread.c
        src/core/diurna_logger.c
        src/queue/diurna_queue_dequeue.c
        src/queue/diurna_queue_destroy.c
        src/queue/diurna_queue_initialize.c
        src/queue/diurna_queue_queue.c)

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
