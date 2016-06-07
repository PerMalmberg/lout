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
	// Will use std::cerr as fallback stream
	FileOutput(std::shared_ptr<formatting::IFormatter> formatter, const std::string& pathToFile);

	FileOutput( std::shared_ptr<formatting::IFormatter> formatter, const std::string& pathToFile, std::ostream* fallbackStream );

	~FileOutput();

	long GetCurrentSize() const { return myCurrentSize; }

	void Flush() noexcept override;
	void Close();

	virtual void LogActual(const loglevel::ILogLevel& level, const std::string& msg) override;

	virtual void LogWithCategoryActual(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) override;

	long GetLogSize() const { return myCurrentSize; }

private:
	std::string myFilePath;
	std::ofstream myFile;
	long myCurrentSize = 0;

	std::string FormatForOutput( const loglevel::ILogLevel& level, const std::string& category, const std::string& msg);
	void OpenFile();
	bool Write( const std::string& data);
	void ReadFileSize();
};

}
}
