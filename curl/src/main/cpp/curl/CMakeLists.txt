cmake_minimum_required(VERSION 3.4.1)

project(net LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ../
        .
        ${event-dir}/include
        ${curl-dir}/include
        ${zlib-dir}/include
        ${openssl-dir}/include)

link_directories(
        ${event-dir}/${ANDROID_ABI}
        ${curl-dir}/${ANDROID_ABI}
        ${openssl-dir}/${ANDROID_ABI}
        ${zlib-dir}/${ANDROID_ABI}
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} NET-SRC)

add_library(net-lib SHARED ${NET-SRC})

target_link_libraries(net-lib z log curl event crypto ssl)
