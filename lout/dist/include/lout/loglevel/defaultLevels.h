// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "ILogLevel.h"
#include <limits>

namespace lout {
namespace loglevel {


///////////////////////////////////////////////////////////////////////////////
//
// Default log levels provided for convenience
//
///////////////////////////////////////////////////////////////////////////////

class NoLogging : public ILogLevel
{
public:
	NoLogging() : ILogLevel( std::numeric_limits<int>::min(), "NoLogging" ) {}
};

class Info : public ILogLevel
{
public:
	Info() : ILogLevel(10, "Info") {}
};

class Warning : public ILogLevel
{
public:
	Warning() : ILogLevel(20, "Warning") {}
};

class Error : public ILogLevel
{
public:
	Error() : ILogLevel(30, "Error") {}
};

class Verbose : public ILogLevel
{
public:
	Verbose() : ILogLevel(40, "Verbose") {}
};

class Debug : public ILogLevel
{
public:
	Debug() : ILogLevel(50, "Debug") {}
};

}
}