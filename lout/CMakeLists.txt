cmake_minimum_required(VERSION 3.4)
project(lout)

set(CMAKE_CXX_STANDARD 14)

if(${CMAKE_MAKE_PROGRAM} MATCHES ".*(MSBuild|msdev|devenv|nmake).*")
	# Build at warning level 4 on Windows.
	# Treat all warnings as errors
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /wd4711 /wd4702")
else()
	# Build with all warnings
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -static-libgcc -static-libstdc++ -static -lpthread")
endif()

# Use CMAKE_CURRENT_LIST_DIR instead of CMAKE_SOURCE_DIR to specify relative to where this CMakeLists.txt is located
# as opposed to where the 'main' CMakeLists.txt file is located.
include_directories("${CMAKE_CURRENT_LIST_DIR}/../lout/dist/include")

include_directories("${CMAKE_CURRENT_LIST_DIR}/dist/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/src")


set(SOURCE_FILES
		ILoutPrinter.cpp
		)

# Create a static library
#add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Output final binaries in the dist folder so they easily can be distributed together with the header files.
#set_target_properties(${PROJECT_NAME}
#		PROPERTIES
#		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/dist/bin/${CMAKE_BUILD_TYPE}"
#		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/dist/bin/${CMAKE_BUILD_TYPE}"
#		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/dist/bin/${CMAKE_BUILD_TYPE}"
#		)