cmake_minimum_required(VERSION 3.16)
project(BlockChain)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp lib/sha256.cpp lib/sha256.h BlockChain.cpp BlockChain.h TransactionData.h TransactionData.cpp
        I_Printable.cpp I_Printable.h CryptoHash.cpp CryptoHash.h Helper.h Helper.cpp)
set(SOURCE_FILES_TEST Tests/BlockChainTest.cpp Tests/BlockTest.cpp Tests/CryptoHashTest.cpp)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${SOURCE_FILES_TEST})
target_link_libraries(${PROJECT_NAME} gtest gtest_main gmock gmock_main )



