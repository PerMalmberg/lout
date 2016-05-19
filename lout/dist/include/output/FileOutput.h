//
// Created by Per Malmberg on 2016-05-17.
//

#pragma once

#include "ILoutOutput.h"
#include <fstream>

namespace com {
namespace codezeal {
namespace logging {
namespace printer {

template<typename TLogLevel>
class FileOutput : public ILoutOutput<TLogLevel>
{
public:
	FileOutput(const std::string& pathToFile);

	~FileOutput();

	void Flush() noexcept override;

	virtual void LogActual(TLogLevel level, const std::string& msg) override;

	virtual void LogWithTagActual(TLogLevel level, const std::string& tag, const std::string& msg) override;

private:
	std::ofstream myFile;
};

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
FileOutput<TLogLevel>::FileOutput(const std::string& pathToFile)
		: ILoutOutput<TLogLevel>( &std::cerr )
{
	// Open for output and append mode
	myFile.open( pathToFile.c_str(), std::ios_base::out | std::ios_base::app );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
FileOutput<TLogLevel>::~FileOutput()
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
template<typename TLogLevel>
void FileOutput<TLogLevel>::Flush() noexcept
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
template<typename TLogLevel>
void FileOutput<TLogLevel>::LogActual(TLogLevel level, const std::string& msg)
{
	if( myFile.is_open() )
	{
		myFile << "[" << static_cast<int>( level ) << "]" << msg << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
void FileOutput<TLogLevel>::LogWithTagActual(TLogLevel level, const std::string& tag, const std::string& msg)
{
	LogActual( level, tag + msg );
}

}
}
}
}