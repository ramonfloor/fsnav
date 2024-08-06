cmake_minimum_required(VERSION 3.24)

project(fsnav)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "src/*.c")
file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "include/*.h")

# Add a static library target
add_executable(${PROJECT_NAME} ${SOURCE_LIST} ${HEADER_LIST})

# expose the include directory to dependent projects/targets
target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

