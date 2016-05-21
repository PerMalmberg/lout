//
// Created by Per Malmberg on 2016-05-17.
//

#pragma once

#include "IOutput.h"
#include <fstream>

namespace lout {
namespace output {

class FileOutput : public IOutput
{
public:
	FileOutput(const std::string& pathToFile);

	~FileOutput();

	void Flush() noexcept override;

	virtual void LogActual(const loglevel::ILogLevel& level, const std::string& msg) override;

	virtual void LogWithTagActual(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg) override;

private:
	std::ofstream myFile;
};

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
	if( myFile.is_open() )
	{
		myFile << "[" << level << "]" << msg << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void FileOutput::LogWithTagActual(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg)
{
	LogActual( level, tag + msg );
}

}
}
