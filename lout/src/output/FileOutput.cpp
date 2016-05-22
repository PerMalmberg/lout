//
// Created by Per Malmberg on 2016-05-17.
//


#include "output/FileOutput.h"
#include <iostream>
#include <sstream>


namespace lout {
namespace output {


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
FileOutput::FileOutput(const std::string& pathToFile)
		: IOutput( &std::cerr )
{
	// Open for output and append mode
	myFile.open( pathToFile.c_str(), std::ios_base::out | std::ios_base::app );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
FileOutput::~FileOutput()
{
	try
	{
		if( myFile.is_open() )
		{
			myFile.close();
		}
	}
	catch( ... )
	{ }
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void FileOutput::Flush() noexcept
{
	try
	{
		if( myFile.is_open() )
		{
			myFile.flush();
		}
	}
	catch( ... )
	{ }
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void FileOutput::LogActual(const loglevel::ILogLevel& level, const std::string& msg)
{
	Write( FormatForOutput( level, "", msg ) );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void FileOutput::LogWithCategoryActual(const loglevel::ILogLevel& level, const std::string& category,
                                       const std::string& msg)
{
	Write( FormatForOutput( level, category, msg ) );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void FileOutput::Write(const std::string& data)
{
	if( myFile.is_open() )
	{
		myFile << data << std::endl;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
std::string FileOutput::FormatForOutput(const loglevel::ILogLevel& level, const std::string& category,
                                        const std::string& msg)
{
	std::stringstream s;

	s << "[" << level;

	if( !category.empty() )
	{
		s << "/" << category;
	}

	s << "]" << msg;

	return s.str();
}

}
}