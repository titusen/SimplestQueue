cmake_minimum_required(VERSION 3.6)

project(SimplestQueue)

find_package( Boost 1.40 COMPONENTS program_options REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_STANDARD 17)
set(LINKER_FLAGS1 "-lwangle  -lfizz -lfolly -lfollybenchmark -pthread -lglog -lgflags -ldl -ldouble-conversion -lcrypto -lssl")
set(LINKER_FLAGS2 "-lboost_filesystem -lboost_system -lboost_regex -lboost_coroutine -lboost_context -levent -lsodium -lboost_program_options")

include_directories(inc)

file(GLOB DEPS src/*.cpp)

add_executable(SimplestQueue SimplestQueue.cpp ${DEPS})

target_link_libraries(SimplestQueue ${LINKER_FLAGS1} ${LINKER_FLAGS2})
