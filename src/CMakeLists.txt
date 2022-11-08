cmake_minimum_required(VERSION 3.22)

add_executable(mtfind
        ${INCLUDE_DIR}/Exception.h
        ${INCLUDE_DIR}/MtFind.h
        ${INCLUDE_DIR}/ThreadPool.h   ## https://github.com/progschj/ThreadPool
        main.cpp
        MtFind.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})