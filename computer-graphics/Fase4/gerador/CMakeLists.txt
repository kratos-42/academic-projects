cmake_minimum_required(VERSION 2.8)

# Project Name
PROJECT(gerador)

if (NOT APPLE)
	if (WIN32)
		set(TOOLKITS_FOLDER "" CACHE PATH "Path to toolkits folder")
		include_directories(
			${TOOLKITS_FOLDER}/glew
			${TOOLKITS_FOLDER}/glut)
		link_directories(
			${TOOLKITS_FOLDER}/glew
			${TOOLKITS_FOLDER}/glut)
	else(WIN32)
		find_package(GLEW REQUIRED)
		include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
	endif(WIN32)
endif(NOT APPLE)

if (NOT WIN32)
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
endif(NOT WIN32)	
	
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS} -fpermissive)
link_directories(${OpenGL_LIBRARY_DIRS} -fpermissive)
add_definitions(${OpenGL_DEFINITIONS} -fpermissive)

add_executable(${PROJECT_NAME} gerador.cpp Ponto.cpp Patch.cpp)


if (WIN32)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glut32 glew32)
	file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
	file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})

else(WIN32)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif (WIN32)


