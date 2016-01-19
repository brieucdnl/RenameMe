cmake_minimum_required(VERSION 3.0)

project(RenameMe)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(LibRaw REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${LibRaw_INCLUDE_DIRS})

set(LIBS ${LIBS} ${LibRaw_LIBRARIES})

set(${PROJECT_NAME}_CPP
	src/main.cpp
)

set(${PROJECT_NAME}_H
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
)
