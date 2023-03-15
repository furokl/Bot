cmake_minimum_required (VERSION 3.26)

set(PROJECT_NAME CastawaysBot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SUBSYSTEM_LINKER_OPTIONS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/app.rc")

set(SOURCES 
	src/main.cpp 
	src/Constants.h 
	src/Detector.h 
	src/Detector.cpp 
	src/Fullscreen.h 
	src/Fullscreen.cpp 
	src/Keyboard.h 
	src/Keyboard.cpp)

project(${PROJECT_NAME} CXX)
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${APP_ICON_RESOURCE_WINDOWS})

find_package( OpenCV REQUIRED )
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})                         
include_directories( ${OpenCV_INCLUDE_DIRS} )
