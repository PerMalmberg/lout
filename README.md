# Lout
A lightweight logging framework

**Work in progress**

## Features
* Customizable log-levels
  * Active levels can be adjusted at run-time.
* Support for custom output channels (inherit from `lout::output::IOutput`)
* Filtering - log messages can be categorized with a custom string which enables filtering on that category.
  * Priority categories - if a message is tagged with a priority category, it will be logged regardless of active level.
* Operator overloading for short-hand logging.
* Fallback to std::cerr (or custom stream) in case of issues with getting things written to the output.

## Included in the box
* Output handlers for [File](https://github.com/PerMalmberg/lout/blob/master/lout/dist/include/output/FileOutput.h) and [`std::cout`](https://github.com/PerMalmberg/lout/blob/master/lout/dist/include/output/StdOutput.h).
* [Ready-to-use log levels](https://github.com/PerMalmberg/lout/blob/master/lout/dist/include/loglevel/defaultLevels.h) (Info, Warning, Error, Vebose, Debug).
* Customizable [thread synchronization](https://github.com/PerMalmberg/lout/blob/master/lout/dist/include/threading/Lock.h) mechanism

##Usage
Please see the [test project](https://github.com/PerMalmberg/lout/blob/master/test/test.cpp) for examples on how to setup, configure and use Lout.
Here's a hint though: LoutLogger is the class you want to use. Have a look at the top of the [test project](https://github.com/PerMalmberg/lout/blob/master/test/test.cpp) for how you can
use macros to reduce typing and to define 'named' loggers for different log levels and categories.

##Getting the source
The test project uses Catch (https://github.com/philsquared/Catch) for testing so you need that cloned too.

Use `git clone --recursive https://github.com/PerMalmberg/CmdParser4Cpp.git`


## Building
Requires a C++ 11 compliant compiler.

Standard CMakeLists.txt files included, directly usable by CLion etc.
To compile in MSVC on Windows, do:
<pre>
cd &lt;path root of project&gt;
mkdir build
cd build
cmake -G "Visual Studio 14 2015" ..
</pre>
then open the generated solution.

## Building boost
For reference, these are the commands I used to build boost filesystem libraries

### Linux
./b2 --prefix=/usr/local/boost_1_61_0 --with-libraries=filesystem  link=static threading=multi runtime-link=static variant=release

### Windows
b2 --with-filesystem variant=release link=static address-model=64 install