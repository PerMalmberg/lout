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

	virtual void LogWithCategoryActual(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) override;

private:
	std::ofstream myFile;

	std::string FormatForOutput( const loglevel::ILogLevel& level, const std::string& category, const std::string& msg);
	void Write( const std::string& data);
};

}
}
