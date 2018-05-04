cmake_minimum_required(VERSION 3.4)
project(lout)
include(../externals/CMakeUtils/CMakeUtils.txt)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DBOOST_ALL_NO_LIB)

if (IS_WINDOWS)
	# Build at warning level 4 on Windows.
	# Treat all warnings as errors
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else ()
	# Build with all warnings
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
	if (NOT IS_OSX)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
	endif ()
endif ()

# Defined in top-level project?
if( NOT BOOST_LOCATION )
	if( ${IS_WINDOWS} OR ${MINGW})
		# Setup path for boost headers
        include_directories("C:/Boost/include/boost-1_61")
	else()
		include_directories("/usr/local/boost/include/")
	endif()
else()
	include_directories(${BOOST_LOCATION})
endif()

# Use CMAKE_CURRENT_LIST_DIR instead of CMAKE_SOURCE_DIR to specify relative to where this CMakeLists.txt is located
# as opposed to where the 'main' CMakeLists.txt file is located.
include_directories("dist/include")
include_directories("src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../externals")


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
		src/output/ColoredStdOutput.cpp
		src/item/Hex.cpp)

# Create a static library
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Tell your linker to link against boost.

# Output final binaries in the dist folder so they easily can be distributed together with the header files.
set_target_properties(${PROJECT_NAME}
		PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/dist/bin/${CMAKE_BUILD_TYPE}"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/dist/bin/${CMAKE_BUILD_TYPE}"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/dist/bin/${CMAKE_BUILD_TYPE}"
		)
