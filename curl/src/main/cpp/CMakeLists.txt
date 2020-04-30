cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 17)

#libevent-2.1.8
set(event-dir ../../../../../third_party/libevent)
set(curl-dir ../../../../../third_party/curl)
set(openssl-dir ../../../../../third_party/openssl)
set(zlib-dir ../../../../../third_party/zlib)

add_subdirectory(curl)