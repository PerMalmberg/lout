// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <iostream>
#include <lout/output/StdOutput.h>


namespace lout {
namespace output {

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
StdOutput::StdOutput( std::shared_ptr<formatting::IFormatter> formatter) :
		IOutput( formatter, &std::cerr )
{ }

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
StdOutput::StdOutput( std::shared_ptr<formatting::IFormatter> formatter, std::ostream* fallbackStream ) :
		IOutput( formatter, fallbackStream )
{ }

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void StdOutput::LogActual( const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg)
{
	std::cout << myFormatter->Format( timestamp, level, msg ) << std::endl;
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void StdOutput::LogWithCategoryActual( const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& category,
                                          const std::string& msg){
	std::cout << myFormatter->Format(timestamp, level, category, msg ) << std::endl;
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void StdOutput::Flush() noexcept
{
	std::cout.flush();
}

}
}