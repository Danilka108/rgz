cmake_minimum_required(VERSION 3.20)
project(rgz)

set(CMAKE_CXX_STANDARD 14)

set(
        PROJECT_HEADERS
        src/num/num.hpp
        src/str/str.hpp
        src/translate/translate.hpp
        src/io/io.hpp
        src/operations/sum.hpp
        src/operations/multiply.hpp
        src/operations/choose_operation.hpp
        src/operations/divide.hpp
)

set(
        PROJECT_SOURCES
        main.cpp
        src/num/num.cpp
        src/str/str.cpp
        src/translate/translate.cpp
        src/io/io.cpp
        src/operations/sum.cpp
        src/operations/multiply.cpp
        src/operations/choose_operation.cpp
        src/operations/divide.cpp
)

add_executable(
        rgz
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
)
