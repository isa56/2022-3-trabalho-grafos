cmake_minimum_required (VERSION 3.14)

# Define the project
project(2022-3-trabalho-grafos LANGUAGES CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

# Add definition for libraries
# add_library(nameClass src/name.cpp)


# Add definition for the cmake-tutorial binary
add_executable(main src/main.cpp)
# target_link_libraries(main nameClass)

# Adiciona GoogleTest:
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(ExternalProject)
ExternalProject_Add(googletest
    PREFIX "${CMAKE_BINARY_DIR}/lib"
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "main"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/installed
)

# Prevent build on all targets build
set_target_properties(googletest PROPERTIES EXCLUDE_FROM_ALL TRUE)

# Define ${CMAKE_INSTALL_...} variables
include(GNUInstallDirs)

# Specify where third-party libraries are located
link_directories(${CMAKE_BINARY_DIR}/lib/installed/${CMAKE_INSTALL_LIBDIR})
include_directories(${CMAKE_BINARY_DIR}/lib/installed/${CMAKE_INSTALL_INCLUDEDIR})

# This is required for googletest
find_package(Threads REQUIRED)


enable_testing()

# Test
# add_executable(nameOfTestClass tests/testClass.cpp)
# target_link_libraries(nameOfTestClass PRIVATE classUsed classUsed gtest Threads::Threads)
# add_dependencies(nameOfTestClass googletest)

add_executable(TestSort tests/TestSort.cpp)
target_link_libraries(TestSort PRIVATE SortingMethods gtest Threads::Threads)
add_dependencies(TestSort googletest)
