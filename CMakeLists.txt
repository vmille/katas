cmake_minimum_required(VERSION 3.20)
project(katas)
include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#11.0.2")
CPMAddPackage("gh:catchorg/Catch2@3.7.0")
CPMAddPackage("gh:approvals/ApprovalTests.cpp@.10.13.0")

find_package(Catch2 REQUIRED)

add_subdirectory(gilded_rose)