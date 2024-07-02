cmake_minimum_required(VERSION 3.28)
project(lout)

set(CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

if (WIN32)
	# Build at warning level 4 on Windows.
	# Treat all warnings as errors
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else ()
	# Build with all warnings
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
	if (NOT UNIX)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
	endif ()
endif ()

# Use CMAKE_CURRENT_LIST_DIR instead of CMAKE_SOURCE_DIR to specify relative to where this CMakeLists.txt is located
# as opposed to where the 'main' CMakeLists.txt file is located.
include_directories("dist/include")
include_directories("src")

set(SOURCE_FILES
		src/Lout.cpp
		src/LoutLogger.cpp
		src/output/IOutput.cpp
		src/output/StdOutput.cpp
		src/output/FileOutput.cpp
		src/output/RollingFile.cpp
		src/loglevel/ILogLevel.cpp
		src/threading/StdLock.cpp
		src/output/DateTimeNameGiver.cpp
		src/formatting/DefaultFormatter.cpp
		src/item/Hex.cpp)

# Create a static library
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
								CXX_STANDARD 17
								CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::filesystem)

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/dist/include/ # for headers when building
				$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>  # for client in install mode
)

# Install the library and its headers
install(TARGETS ${PROJECT_NAME}
		EXPORT ${PROJECT_NAME}_targets
		ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

# Trailing / is important to make file *inside* the lout
# folder end up in the destination, instead of the lout folder itself.
install(DIRECTORY dist/include/lout/ DESTINATION include)

# Generate and install *-targets.cmake
install(EXPORT ${PROJECT_NAME}_targets
		NAMESPACE ${PROJECT_NAME}::
		FILE ${PROJECT_NAME}-targets.cmake
		DESTINATION share/${PROJECT_NAME})

# Generate the config file in the current binary dir (this ensures it's not placed directly in source)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
"include(CMakeFindDependencyMacro)\n"
"find_dependency(Boost::filesystem CONFIG REQUIRED)\n"
"include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-targets.cmake\")\n"
)

# Install the generated config file
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
								DESTINATION share/${PROJECT_NAME})
