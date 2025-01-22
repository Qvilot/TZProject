cmake_minimum_required(VERSION 3.10)
project(network_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# --- Library Configuration ---
set(LIB_NAME lib)
include_directories(lib/include)
file(GLOB LIB_SRC lib/src/*.cpp)
add_library(${LIB_NAME} SHARED ${LIB_SRC})
set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME lib)
# Указываем, куда нужно помещать библиотеку при сборке (в папку build/my_lib)
set_target_properties(${LIB_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


# --- Program 1 Configuration ---
set(PROGRAM1_NAME program1)
include_directories(program1/include)
file(GLOB PROGRAM1_SRC program1/src/*.cpp)
add_executable(${PROGRAM1_NAME} ${PROGRAM1_SRC})
target_link_libraries(${PROGRAM1_NAME} lib)
# Указываем, куда нужно помещать исполняемый файл при сборке (в папку build/program1)
set_target_properties(${PROGRAM1_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/program1")
# Указываем, где искать библиотеку во время выполнения (в папке build/my_lib)
set_target_properties(${PROGRAM1_NAME} PROPERTIES  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


# --- Program 2 Configuration ---
set(PROGRAM2_NAME program2)
include_directories(program2/include)
file(GLOB PROGRAM2_SRC program2/src/*.cpp)
add_executable(${PROGRAM2_NAME} ${PROGRAM2_SRC})
target_link_libraries(${PROGRAM2_NAME} lib)
# Указываем, куда нужно помещать исполняемый файл при сборке (в папку build/program2)
set_target_properties(${PROGRAM2_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/program2")
set_target_properties(${PROGRAM2_NAME} PROPERTIES  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
