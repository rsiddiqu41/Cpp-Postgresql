# CMakeList.txt : CMake project for CDemo, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "C:/path/to/vcpkg.cmake")

# Add this after setting the toolchain file
set(VCPKG_TARGET_TRIPLET "x64-windows")

project ("demo")

find_package(libpqxx CONFIG REQUIRED)

include_directories(".")

# Add source to this project's executable.
add_executable (demo "Database/include/Database.h" "Database/src/Database.cpp")

# TODO: Add tests and install targets if needed.
target_link_libraries(demo PRIVATE libpqxx::pqxx)