cmake_minimum_required(VERSION 3.10.0)
project(multiplex-streams VERSION 0.1.0 LANGUAGES C CXX)

add_definitions(-D__STDC_CONSTANT_MACROS)

find_package(PkgConfig REQUIRED)

# Check for FFmpeg components
pkg_check_modules(AVCODEC REQUIRED IMPORTED_TARGET libavcodec)
pkg_check_modules(AVFORMAT REQUIRED IMPORTED_TARGET libavformat)
pkg_check_modules(AVUTIL REQUIRED IMPORTED_TARGET libavutil)
pkg_check_modules(SWSCALE REQUIRED IMPORTED_TARGET libswscale)

# Check for GStreamer components
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GST_APP REQUIRED gstreamer-app-1.0)
pkg_check_modules(GST_VIDEO REQUIRED gstreamer-video-1.0)
pkg_check_modules(GST_RTSP_SERVER REQUIRED gstreamer-rtsp-server-1.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)

# Add the cJSON library as a remote subdirectory
add_subdirectory(contrib/cJSON)

# Add src folder as a library
add_library(single_stream src/single_stream.c)
add_library(parse_config src/parse_config.c)

include_directories(
    # Include directories for ffmpeg
    ${AVFORMAT_INCLUDE_DIRS}
    ${AVCODEC_INCLUDE_DIRS}
    ${SWSCALE_INCLUDE_DIRS}
    ${AVUTIL_INCLUDE_DIRS}
    # Include directories for GStreamer
    ${GSTREAMER_INCLUDE_DIRS}
    ${GST_APP_INCLUDE_DIRS}
    ${GST_VIDEO_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${GST_RTSP_SERVER_INCLUDE_DIRS}
    # Include directories for cJSON
    contrib/cJSON
    # Local project include directories
    include
)

add_executable(multiplex-streams main.c)

# Linking above libraries statically
target_link_libraries(multiplex-streams
    PkgConfig::AVCODEC
    PkgConfig::AVFORMAT
    PkgConfig::AVUTIL
    PkgConfig::SWSCALE
    ${GSTREAMER_LIBRARIES}
    ${GST_APP_LIBRARIES}
    ${GST_VIDEO_LIBRARIES}
    ${GLIB_LIBRARIES}
    ${GST_RTSP_SERVER_LIBRARIES}
    cjson
    single_stream
    parse_config
)


include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
