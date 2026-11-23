cmake_minimum_required(VERSION 3.25)

project(framelog
  VERSION 0.1.0
  DESCRIPTION "A small C++20 CLI for filtering and summarising recorded frame logs"
  HOMEPAGE_URL "https://github.com/firas-khemakhem/framelog"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(FRAMELOG_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)

include(cmake/warnings.cmake)

add_library(framelog_core src/version.cpp)
add_library(framelog::core ALIAS framelog_core)
target_include_directories(framelog_core PUBLIC include)
target_compile_features(framelog_core PUBLIC cxx_std_20)
target_compile_definitions(framelog_core PRIVATE FRAMELOG_VERSION="${PROJECT_VERSION}")
framelog_set_warnings(framelog_core)

add_executable(framelog apps/framelog/main.cpp)
target_link_libraries(framelog PRIVATE framelog::core)
framelog_set_warnings(framelog)

include(CTest)
if(BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
    URL_HASH SHA256=8ad598c73ad796e0d8280b082cebd82a630d73e73cd3c70057938a6501bba5d7
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  add_executable(framelog_tests tests/version_test.cpp)
  target_link_libraries(framelog_tests PRIVATE framelog::core GTest::gtest_main)
  target_compile_definitions(framelog_tests PRIVATE FRAMELOG_EXPECTED_VERSION="${PROJECT_VERSION}")
  include(GoogleTest)
  gtest_discover_tests(framelog_tests)

  add_test(NAME framelog_version COMMAND framelog --version)
  set_tests_properties(framelog_version PROPERTIES
    PASS_REGULAR_EXPRESSION "framelog ${PROJECT_VERSION}")

  add_test(NAME framelog_help COMMAND framelog --help)
  set_tests_properties(framelog_help PROPERTIES
    PASS_REGULAR_EXPRESSION "Usage: framelog")
endif()
