project(LineAndArrow)
cmake_minimum_required(VERSION 3.10)
enable_language(CXX)
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_GNUtoMS_VCVARS TRUE)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BUILD_SHARED_LIBS OFF)

# ~ Complie Flags
## ~ CPP
set(CMAKE_CXX_FLAGS "-std=c++2a -g -fPIC -Wall -Wno-unused-const-variable" ${CMAKE_CXX_FLAGS})
# add_definitions(-g)
## ~ C
set(CMAKE_C_FLAGS "-std=c18 -g -fPIC -Wall -Wno-unused-const-variable" ${CMAKE_C_FLAGS})

# ~ Globe Library Path
## ~ 1
set(CMAKE_LIBRARY_PATH "C:/msys64/mingw64/bin" ${CMAKE_LIBRARY_PATH})
set(CMAKE_LIBRARY_PATH "C:/msys64/mingw64/lib" ${CMAKE_LIBRARY_PATH})
set(CMAKE_INCLUDE_PATH "C:/msys64/mingw64/include" ${CMAKE_INCLUDE_PATH})

INCLUDE_DIRECTORIES("include" ${CMAKE_INCLUDE_PATH})
INCLUDE_DIRECTORIES("src" ${CMAKE_INCLUDE_PATH})

add_subdirectory(src)