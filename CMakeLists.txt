cmake_minimum_required(VERSION 3.20)
project(rgz)

set(CMAKE_CXX_STANDARD 14)

set(
        PROJECT_HEADERS
        main.h
        src/num/num.h
        src/str/str.h
        src/translate/translate.h
        src/io/io.h
        src/operations/sum.h
        src/operations/multiply.h
        src/operations/operations.h
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
        src/operations/operations.cpp
)

add_executable(
        rgz
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
)
