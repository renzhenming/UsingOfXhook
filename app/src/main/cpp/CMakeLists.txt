# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Declares and names the project.

project("myxhook")


find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/xhook)

add_library(
        xhook
        SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/xhook/xh_core.c
        ${CMAKE_CURRENT_SOURCE_DIR}/xhook/xh_elf.c
        ${CMAKE_CURRENT_SOURCE_DIR}/xhook/xh_jni.c
        ${CMAKE_CURRENT_SOURCE_DIR}/xhook/xh_log.c
        ${CMAKE_CURRENT_SOURCE_DIR}/xhook/xh_util.c
        ${CMAKE_CURRENT_SOURCE_DIR}/xhook/xh_version.c
        ${CMAKE_CURRENT_SOURCE_DIR}/xhook/xhook.c
        native-lib.cpp
)


target_link_libraries( # Specifies the target library.
        xhook
        ${log-lib} )
