cmake_minimum_required(VERSION 3.6)

project(SimplestQueue)

find_package( Boost 1.40 COMPONENTS program_options REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
find_package(Folly COMPONENTS program_options REQUIRED )
find_package(Wangle COMPONENTS program_options REQUIRED )
find_package(Fizz COMPONENTS program_options REQUIRED )

set(CMAKE_CXX_STANDARD 17)
set(LINKER_FLAGS1 "-lwangle  -lfizz -lfolly -lfollybenchmark -liberty -pthread -lglog -lgflags -ldl -ldouble-conversion -lcrypto -lssl")
set(LINKER_FLAGS2 "-lboost_filesystem -lboost_system -lboost_regex -lboost_coroutine -lboost_context -levent -lsodium -lboost_program_options")

add_executable(WangleSender WangleClient.cpp )

add_executable(SimpleReceiver Client.c )

target_link_libraries(WangleSender ${LINKER_FLAGS1} ${LINKER_FLAGS2})
