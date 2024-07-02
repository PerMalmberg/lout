// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <ctime>
#include <iostream>
#include <lout/formatting/IFormatter.h>
#include <lout/loglevel/ILogLevel.h>
#include <lout/output/FileOutput.h>
#include <lout/output/IOutput.h>
#include <memory>
#include <string>
#include <utility>

namespace lout::output
{

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	FileOutput::FileOutput(std::shared_ptr<formatting::IFormatter> formatter, std::string pathToFile)
	    : FileOutput(std::move(formatter), std::move(pathToFile), &std::cerr)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	FileOutput::FileOutput(std::shared_ptr<formatting::IFormatter> formatter,
	                       std::string pathToFile,
	                       std::ostream* fallbackStream)
	    : IOutput(std::move(formatter), fallbackStream), myFilePath(std::move(pathToFile))
	{
		// Open for output and append mode
		OpenFile();
		ReadFileSize();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	FileOutput::~FileOutput()
	{
		Close();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void FileOutput::Close()
	{
		try
		{
			if(myFile.is_open())
			{
				myFile.close();
			}
		}
		catch(...)
		{
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void FileOutput::Flush() noexcept
	{
		try
		{
			if(myFile.is_open())
			{
				myFile.flush();
			}
		}
		catch(...)
		{
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void FileOutput::LogActual(const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg)
	{
		if(!Write(myFormatter->Format(timestamp, level, msg)))
		{
			FallbackLog(timestamp, level, "", msg);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void FileOutput::LogWithCategoryActual(const time_t& timestamp,
	                                       const loglevel::ILogLevel& level,
	                                       const std::string& category,
	                                       const std::string& msg)
	{
		if(!Write(myFormatter->Format(timestamp, level, category, msg)))
		{
			FallbackLog(timestamp, level, category, msg);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void FileOutput::OpenFile()
	{
		if(!myFile.is_open())
		{
			myFile.open(myFilePath, std::ios_base::out | std::ios_base::app);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	bool FileOutput::Write(const std::string& data)
	{
		bool res = false;

		OpenFile();

		if(myFile.is_open())
		{
			myFile << data << std::endl;
			ReadFileSize();
			res = true;
		}

		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void FileOutput::ReadFileSize()
	{
		if(myFile.good() && myFile.is_open())
		{
			// Seek output to end of file
			myFile.seekp(0, std::ios_base::end);
			myCurrentSize = static_cast<long>(myFile.tellp());
		}
	}

} // namespace lout::output
