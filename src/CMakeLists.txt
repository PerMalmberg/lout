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

set(SOURCE_FILES
		Lout.cpp
		LoutLogger.cpp
		output/IOutput.cpp
		output/StdOutput.cpp
		output/FileOutput.cpp
		output/RollingFile.cpp
		loglevel/ILogLevel.cpp
		threading/StdLock.cpp
		output/DateTimeNameGiver.cpp
		formatting/DefaultFormatter.cpp
		item/Hex.cpp)

# Create a static library
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
								CXX_STANDARD 17
								CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::filesystem)

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
				$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>  # for client in install mode
)

# Install the library and its headers
install(TARGETS ${PROJECT_NAME}
		EXPORT ${PROJECT_NAME}_targets
		ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

install(DIRECTORY src/ DESTINATION include/lout FILES_MATCHING PATTERN "*.h")

# Generate and install *-targets.cmake
install(EXPORT ${PROJECT_NAME}_targets
		NAMESPACE ${PROJECT_NAME}::
		FILE ${PROJECT_NAME}-targets.cmake
		DESTINATION share/${PROJECT_NAME})

# Generate the config file in the current binary dir (this ensures it's not placed directly in source)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
"include(CMakeFindDependencyMacro)\n"
"find_dependency(Boost REQUIRED COMPONENTS filesystem)\n"
"include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-targets.cmake\")\n"
)

# Install the generated config file
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
								DESTINATION share/${PROJECT_NAME})
