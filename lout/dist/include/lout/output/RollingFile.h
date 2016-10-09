// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <string>
#include <memory>
#include <lout/output/IOutput.h>
#include <lout/output/FileOutput.h>
#include <lout/output/IRollingFileName.h>
#include <lout/util/Sizes.h>

namespace lout {
namespace output {

class RollingFile : public IOutput
{
public:
	RollingFile(const std::string& pathToOutputFolder, std::unique_ptr<IRollingFileName> nameGiver, std::shared_ptr<formatting::IFormatter> formatter, util::Bytes maximumLogSize, int filesToKeep );

	RollingFile(const std::string& pathToOutputFolder, std::unique_ptr<IRollingFileName> nameGiver, std::shared_ptr<formatting::IFormatter> formatter, util::Bytes maximumLogSize, int filesToKeep, std::ostream* fallbackStream);

	~RollingFile();

	size_t GetCurrentLogCount() const;

protected:
	void Flush() noexcept override;

	virtual void LogActual(const loglevel::ILogLevel& level, const std::string& msg) override;

	virtual void LogWithCategoryActual(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) override;
private:
	std::string myPathToOutputFolder;
	std::unique_ptr<FileOutput> myOutput;
	std::unique_ptr<IRollingFileName> myNameGiver;
	util::Bytes myMaximumLogSize;
	const int myFilesToKeep;

	void Roll();
	void Open();
	void Close();
	void CleanOldFiles() const;
	void GetCurrentLogFiles( std::vector<std::string> &target ) const;
};

}
}
