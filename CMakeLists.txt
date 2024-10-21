PROJECT(STRUCTURE)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_FILES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build_cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

########### cmake configuration and compiler flags ###########
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_C_FLAGS_DEBUG " -Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG " -Wall -g")
SET(CMAKE_C_FLAGS_RELEASE " -Wall")
SET(CMAKE_CXX_FLAGS_RELEASE " -Wall")
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib) #static libraries
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) #executables
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) #dynamic libraries (plugins)

#ADD_EXECUTABLE(param_config
#  ${PROJECT_SOURCE_DIR}/src/prog_opt/param_config.cpp
#)

#target_link_libraries(param_config)

include_directories(${PROJECT_SOURCE_DIR}/include/KDTree)

ADD_EXECUTABLE(kdtree
  ${PROJECT_SOURCE_DIR}/src/KDTree/kdtree.cpp
  ${PROJECT_SOURCE_DIR}/src/KDTree/main.cpp
)