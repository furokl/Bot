cmake_minimum_required (VERSION 3.5)

set(PROJECT_NAME CastawaysBot)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES 
	src/main.cpp 
	src/Constants.h)

project(${PROJECT_NAME} CXX)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)

find_package( OpenCV REQUIRED )
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})                         
include_directories( ${OpenCV_INCLUDE_DIRS} )
