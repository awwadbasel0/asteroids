cmake_minimum_required(VERSION 3.15)
project(asteroids)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
	include(FetchContent)
	FetchContent_Declare(
		raylib
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
		URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
		)
		FetchContent_GetProperties(raylib)
		if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
			set(FETCHCONTENT_QUIET NO)
			FetchContent_MakeAvailable(raylib)
		endif()
endif()

#find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

#set(CMAKE_C_STANDARD 11) # Requires C11 standard

add_executable(${PROJECT_NAME} src/main.cpp src/Player.cpp src/Asteroids.cpp)

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
	    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
	        target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
		    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
