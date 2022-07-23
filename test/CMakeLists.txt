cmake_minimum_required(VERSION 3.5)

project(
    MO_ELOM
    VERSION 1.0.0
    DESCRIPTION "test uint256 lib"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(m_out main.cxx)

set(CMAKE_PREFIX_PATH "../build")

find_package(UInt256L REQUIRED)

target_link_libraries(m_out uint256_l)
