cmake_minimum_required(VERSION 3.20)
project(katas)
include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#11.0.2")
CPMAddPackage("gh:catchorg/Catch2@3.7.0")
CPMAddPackage("gh:approvals/ApprovalTests.cpp@.10.13.0")

find_package(Catch2 REQUIRED)

add_library(gilded_rose_lib)
target_sources(gilded_rose_lib PRIVATE src/gilded_rose.cxx)
target_include_directories(gilded_rose_lib PUBLIC include)

add_executable(gilded_rose_test)
target_sources(gilded_rose_test PRIVATE test/test_main.cxx test/test_cases.cxx)
target_link_libraries(gilded_rose_test PRIVATE gilded_rose_lib Catch2::Catch2 Catch2::Catch2WithMain ApprovalTests::ApprovalTests)