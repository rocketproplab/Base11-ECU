cmake_minimum_required(VERSION 3.2)
project(Base11_ECU_tests)

include_directories(${BASE11_ECU_HEADERS_DIR} ${PROJECT_SOURCE_DIR}/test/)

set(SOURCE_FILES TestMain.cpp)

add_executable(Base11_ECU_tests ${SOURCE_FILES})

set_target_properties (Base11_ECU_tests PROPERTIES LINK_FLAGS "-Wall")

target_link_libraries(Base11_ECU_tests Base11_ECU_lib)
