cmake_minimum_required(VERSION 3.19.6)
project(CuckooTrie)
set(CMAKE_BUILD_TYPE Release)

aux_source_directory(./ DIR_LIB_SRCS)

list(FILTER DIR_LIB_SRCS EXCLUDE REGEX ".*benchmark\\.c$")
list(FILTER DIR_LIB_SRCS EXCLUDE REGEX ".*test\\.c$")
list(FILTER DIR_LIB_SRCS EXCLUDE REGEX ".*dataset\\.c$")
list(FILTER DIR_LIB_SRCS EXCLUDE REGEX ".*random_dist\\.c$")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(./)
add_compile_options(--std=gnu18 -O3 -flto -fno-strict-aliasing -march=haswell -Wreturn-type -Wuninitialized -Wunused-parameter -DNDEBUG)

add_library(cuckoo SHARED ${DIR_LIB_SRCS})