// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "IOutput.h"
#include <fstream>

namespace lout::output
{

	class FileOutput : public IOutput
	{
	  public:
		// Will use std::cerr as fallback stream
		FileOutput(std::shared_ptr<formatting::IFormatter> formatter, const std::string& pathToFile);

		FileOutput(std::shared_ptr<formatting::IFormatter> formatter,
		           const std::string& pathToFile,
		           std::ostream* fallbackStream);

		~FileOutput() override;

		FileOutput(const FileOutput&) = delete;
		FileOutput(FileOutput&&) = delete;
		FileOutput& operator=(const FileOutput&) = delete;
		FileOutput& operator=(FileOutput&&) = delete;

		long GetCurrentSize() const
		{
			return myCurrentSize;
		}

		void Flush() noexcept override;
		void Close();

		void LogActual(const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg) override;

		void LogWithCategoryActual(const time_t& timestamp,
		                           const loglevel::ILogLevel& level,
		                           const std::string& category,
		                           const std::string& msg) override;

		long GetLogSize() const
		{
			return myCurrentSize;
		}

	  private:
		std::string myFilePath;
		std::ofstream myFile;
		long myCurrentSize = 0;

		void OpenFile();
		bool Write(const std::string& data);
		void ReadFileSize();
	};

} // namespace lout::output
