//
// Created by Per Malmberg on 2016-05-25.
//

#pragma once

#include <string>
#include <memory>
#include <output/IOutput.h>
#include <output/FileOutput.h>
#include <output/IRollingFileName.h>
#include <util/Sizes.h>

namespace lout {
namespace output {

class RollingFile : public IOutput
{
public:
	RollingFile(const std::string& pathToOutputFolder, std::unique_ptr<IRollingFileName> nameGiver, util::Bytes maximumLogSize, int filesToKeep );

	RollingFile(const std::string& pathToOutputFolder, std::unique_ptr<IRollingFileName> nameGiver, util::Bytes maximumLogSize, int filesToKeep, std::ostream* fallbackStream);

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
	//std::string PathCombine( const std::string& p1, const std::string& p2);
	void CleanOldFiles() const;
	void GetCurrentLogFiles( std::vector<std::string> &target ) const;
};

}
}
