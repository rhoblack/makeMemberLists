cmake_minimum_required(VERSION 3.0.0)

project(memberListFile)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_compile_options (${PROJECT_NAME} PUBLIC
    -Wall
)