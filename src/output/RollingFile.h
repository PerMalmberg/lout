// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "output/FileOutput.h"
#include "output/IOutput.h"
#include "output/IRollingFileName.h"
#include "util/Sizes.h"
#include <memory>
#include <string>
#include <vector>

namespace lout::output
{

	class RollingFile : public IOutput
	{
	  public:
		RollingFile(const RollingFile&) = delete;
		RollingFile(RollingFile&&) = delete;
		RollingFile& operator=(const RollingFile&) = delete;
		RollingFile& operator=(RollingFile&&) = delete;

		RollingFile(std::string pathToOutputFolder,
		            std::unique_ptr<IRollingFileName> nameGiver,
		            std::shared_ptr<formatting::IFormatter> formatter,
		            util::Bytes maximumLogSize,
		            int filesToKeep);

		RollingFile(std::string pathToOutputFolder,
		            std::unique_ptr<IRollingFileName> nameGiver,
		            std::shared_ptr<formatting::IFormatter> formatter,
		            util::Bytes maximumLogSize,
		            int filesToKeep,
		            std::ostream* fallbackStream);

		~RollingFile() override;

		[[nodiscard]] size_t GetCurrentLogCount() const;

	  protected:
		void Flush() noexcept override;

		void LogActual(const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg) override;

		void LogWithCategoryActual(const time_t& timestamp,
		                           const loglevel::ILogLevel& level,
		                           const std::string& category,
		                           const std::string& msg) override;

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
		void GetCurrentLogFiles(std::vector<std::string>& target) const;
	};

} // namespace lout::output
