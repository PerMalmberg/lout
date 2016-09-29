cmake_minimum_required(VERSION 3.4)
project(lout)
include( ../externals/CMakeUtils/CMakeUtils.txt)

set(CMAKE_CXX_STANDARD 14)

if( IS_WINDOWS )
	# Build at warning level 4 on Windows.
	# Treat all warnings as errors
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
	# Setup path for boost headers
    include_directories("C:/Boost/include/boost-1_61")
else()
	# Build with all warnings
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread")
    # Setup path for boost headers
    include_directories("/usr/local/boost/include/")
endif()

# Use CMAKE_CURRENT_LIST_DIR instead of CMAKE_SOURCE_DIR to specify relative to where this CMakeLists.txt is located
# as opposed to where the 'main' CMakeLists.txt file is located.
include_directories("${CMAKE_CURRENT_LIST_DIR}/../lout/dist/include")

include_directories("${CMAKE_CURRENT_LIST_DIR}/dist/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../externals")


set(SOURCE_FILES
		src/Lout.cpp
		src/LoutLogger.cpp
		src/output/IOutput.cpp
		src/output/StdOutput.cpp
		src/output/FileOutput.cpp
		src/output/RollingFile.cpp
		src/loglevel/ILogLevel.cpp
		src/threading/Lock.cpp
		src/output/DateTimeNameGiver.cpp
		src/formatting/DefaultFormatter.cpp
        src/output/ColoredStdOutput.cpp)

# Create a static library
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Tell linker to link against boost. Note that this doesn't actually take effect until the main executable is linked
# and thus that target needs to know where to fine the libraries (set via link_directories() )
if(${CMAKE_MAKE_PROGRAM} MATCHES ".*(MSBuild|msdev|devenv|nmake).*")
	target_link_libraries( ${PROJECT_NAME} libboost_filesystem-vc140-mt-1_61 libboost_system-vc140-mt-1_61)
else()
	target_link_libraries( ${PROJECT_NAME} boost_filesystem boost_system)
	
endif()

# Note if you build your binary using -static in CMAKE_CXX_FLAGS, you must make sure that the entire pthread archive is linked
# to our target. See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52590#c4
# In short, the internet says 'don't use static linking'.
#target_link_libraries( ${PROJECT_NAME} -Wl,--whole-archive -lpthread -Wl,--no-whole-archive)

# Output final binaries in the dist folder so they easily can be distributed together with the header files.
set_target_properties(${PROJECT_NAME}
		PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/dist/bin/${CMAKE_BUILD_TYPE}"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/dist/bin/${CMAKE_BUILD_TYPE}"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/dist/bin/${CMAKE_BUILD_TYPE}"
		)