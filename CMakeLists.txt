cmake_minimum_required(VERSION 3.10.0)
project(multiplex-streams VERSION 0.1.0 LANGUAGES C)

add_definitions(-D__STDC_CONSTANT_MACROS)

find_package(PkgConfig REQUIRED)


# Find GStreamer and base plugins
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GST_APP REQUIRED gstreamer-app-1.0)
pkg_check_modules(GST_VIDEO REQUIRED gstreamer-video-1.0)

# Check for FFmpeg components
pkg_check_modules(AVCODEC REQUIRED IMPORTED_TARGET libavcodec)
pkg_check_modules(AVFORMAT REQUIRED IMPORTED_TARGET libavformat)
pkg_check_modules(AVUTIL REQUIRED IMPORTED_TARGET libavutil)
pkg_check_modules(SWSCALE REQUIRED IMPORTED_TARGET libswscale)

# Include directories for GStreamer
include_directories(
    ${GSTREAMER_INCLUDE_DIRS}
    ${GST_APP_INCLUDE_DIRS}
    ${GST_VIDEO_INCLUDE_DIRS}
)

# Include directories for ffmpeg
include_directories(
    ${AVFORMAT_INCLUDE_DIRS}
    ${AVCODEC_INCLUDE_DIRS}
    ${SWSCALE_INCLUDE_DIRS}
    ${AVUTIL_INCLUDE_DIRS}
)

add_executable(multiplex-streams main.c)

# Link libraries
target_link_libraries(multiplex-streams
    PkgConfig::AVCODEC
    PkgConfig::AVFORMAT
    PkgConfig::AVUTIL
    PkgConfig::SWSCALE
)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
