cmake_minimum_required(VERSION 3.18.1)
project("invocation-api")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/lib)
find_library(log-lib log REQUIRED)

add_executable(main "main.c")

add_library(nativehelper SHARED "jni_loader.c")
add_library(sigchain SHARED "jni_loader.c")
add_library(loader STATIC "jni_loader.c")

target_link_libraries(main loader hello-jni) # change the library name in the last section with your own
target_link_libraries(nativehelper loader)
target_link_libraries(loader sigchain)