cmake_minimum_required(VERSION 3.16)

project(LearnOpenGL)

# Build glad
add_library(glad lib/glad/glad.c)

file(GLOB SRC "src/*.cpp")

# Build program
add_executable(learn-gl ${SRC})

# Link target and glad
target_link_libraries(learn-gl glad GL glfw3 dl X11 pthread)