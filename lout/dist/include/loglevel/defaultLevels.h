//
// Created by Per Malmberg on 2016-05-21.
//

#pragma once

#include "ILogLevel.h"


namespace lout {
namespace loglevel {


///////////////////////////////////////////////////////////////////////////////
//
// Default log levels provided for convenience
//
///////////////////////////////////////////////////////////////////////////////

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