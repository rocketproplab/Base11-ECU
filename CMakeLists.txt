cmake_minimum_required(VERSION 3.2)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

#download SCMLib
configure_file(CMakeLists.txt.in
              SCMLib-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/SCMLib-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/SCMLib-download )

add_subdirectory(${CMAKE_BINARY_DIR}/SCMLib-src
              ${CMAKE_BINARY_DIR}/SCMLib-build)

project(Base11-ECU-core)

include_directories(${CMAKE_BINARY_DIR}/SCMLib-src/src)

set(BASE11_ECU_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(BASE11_ECU_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(BASE11_ECU_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(BASE11_ECU_HEADERS_DIR ${PROJECT_SOURCE_DIR})
set(BASE11_ECU_MOCKS_DIR ${PROJECT_SOURCE_DIR}/mocks)

include_directories(${BASE11_ECU_INSTALL_INCLUDE_DIR})
include_directories(${BASE11_ECU_HEADERS_DIR})
include_directories(${BASE11_ECU_MOCKS_DIR})

file(GLOB SOURCE_FILES *.c *.cpp mocks/*.cpp)

add_library(Base11_ECU_lib STATIC ${SOURCE_FILES})
add_subdirectory(test)

add_test (NAME all COMMAND Base11_ECU_tests)
