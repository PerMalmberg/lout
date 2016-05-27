//
// Created by Pamlmberg on 2016-05-25.
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
	RollingFile(const std::string& pathToOutputFolder, std::unique_ptr<IRollingFileName> nameGiver, util::Bytes maximumLogSize );

	RollingFile(const std::string& pathToOutputFolder, std::unique_ptr<IRollingFileName> nameGiver, util::Bytes maximumLogSize, std::ostream* fallbackStream);

	~RollingFile();

protected:
	void Flush() noexcept override;

	virtual void LogActual(const loglevel::ILogLevel& level, const std::string& msg) override;

	virtual void LogWithCategoryActual(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) override;
private:
	std::string myPathToOutputFolder;
	std::unique_ptr<FileOutput> myOutput;
	std::unique_ptr<IRollingFileName> myNameGiver;
	util::Bytes myMaximumLogSize;

	void Roll();
	void Open();
	std::string PathCombine( const std::string& p1, const std::string& p2);
};

}
}
