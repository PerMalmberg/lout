//
// Created by Per Malmberg on 2016-05-21.
//

#include <c++/iostream>
#include "output/Stdoutput.h"


namespace lout {
namespace output {

StdOutPrinter::StdOutPrinter() :
		ILoutOutput( &std::cerr )
{ }

void StdOutPrinter::LogActual(const loglevel::ILogLevel& level, const std::string& msg)
{
	std::cout << "[" << level << "]" << msg << std::endl;
}

void StdOutPrinter::LogWithTagActual(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg)
{
	std::cout << "[" << level << "][" << tag << "]" << msg << std::endl;
}

void StdOutPrinter::Flush() noexcept
{
	std::cout.flush();
}

}
}