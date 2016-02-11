cmake_minimum_required(VERSION 3.0)

project(RenameMe)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

find_package(Exiv2 REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${EXIV2_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

set(LIBS ${LIBS} ${EXIV2_LIBRARY})

set(${PROJECT_NAME}_CPP
	src/main.cpp
	src/RenameMeMainWindow.cpp
	src/RenameMeSettingsWindow.cpp
	src/RenameMePhotos.cpp
	src/RenameMeSettings.cpp
)

set(${PROJECT_NAME}_H
	src/RenameMeMainWindow.h
	src/RenameMeSettingsWindow.h
	src/RenameMePhotos.h
	src/RenameMeSettings.h
)

add_executable(
	${PROJECT_NAME}
	${${PROJECT_NAME}_CPP}
	${${PROJECT_NAME}_H}
)

target_link_libraries(
	${PROJECT_NAME} 
	${LIBS}
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Qt5Widgets_LIBRARIES}
)
