// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include "lout/output/RollingFile.h"
#include "lout/formatting/IFormatter.h"
#include "lout/output/IOutput.h"
#include "lout/output/IRollingFileName.h"
#include "lout/util/Sizes.h"
#include <algorithm>
#include <boost/filesystem.hpp>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace fs = boost::filesystem;

namespace lout::output
{

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	RollingFile::RollingFile(std::string pathToOutputFolder,
	                         std::unique_ptr<IRollingFileName> nameGiver,
	                         std::shared_ptr<formatting::IFormatter> formatter,
	                         util::Bytes maximumLogSize,
	                         int filesToKeep)
	    : RollingFile(std::move(pathToOutputFolder),
	                  std::move(nameGiver),
	                  std::move(formatter),
	                  maximumLogSize,
	                  filesToKeep,
	                  &std::cerr)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	RollingFile::RollingFile(std::string pathToOutputFolder,
	                         std::unique_ptr<IRollingFileName> nameGiver,
	                         std::shared_ptr<formatting::IFormatter> formatter,
	                         util::Bytes maximumLogSize,
	                         int filesToKeep,
	                         std::ostream* fallbackStream)
	    : IOutput(std::move(formatter), fallbackStream),
	      myPathToOutputFolder(std::move(pathToOutputFolder)),
	      myNameGiver(std::move(nameGiver)),
	      myMaximumLogSize(maximumLogSize),
	      myFilesToKeep(filesToKeep)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	RollingFile::~RollingFile()
	{
		Close();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	size_t RollingFile::GetCurrentLogCount() const
	{
		std::vector<std::string> currentLogs;
		GetCurrentLogFiles(currentLogs);
		return currentLogs.size();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void RollingFile::GetCurrentLogFiles(std::vector<std::string>& target) const
	{
		try
		{
			fs::directory_iterator dir(myPathToOutputFolder);
			const fs::directory_iterator end = fs::directory_iterator();

			while(dir != end)
			{
				auto& entry = *dir;
				if(fs::is_regular_file(entry.path()))
				{
					const fs::path& path = entry.path();
					const std::string fileName = path.filename().string();
					if(myNameGiver->Matches(fileName))
					{
						target.push_back(path.string());
					}
				}
				++dir;
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
	void RollingFile::Flush() noexcept
	{
		if(myOutput)
		{
			myOutput->Flush();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void RollingFile::LogActual(const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg)
	{
		Open();

		if(myOutput)
		{
			myOutput->Log(timestamp, level, msg);
		}

		Roll();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void RollingFile::LogWithCategoryActual(const time_t& timestamp,
	                                        const loglevel::ILogLevel& level,
	                                        const std::string& category,
	                                        const std::string& msg)
	{
		Open();

		if(myOutput)
		{
			myOutput->LogWithCategory(timestamp, level, category, msg);
		}

		Roll();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void RollingFile::Roll()
	{
		if(myOutput && myOutput->GetCurrentSize() > myMaximumLogSize.GetBytes())
		{
			Close();
			CleanOldFiles();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void RollingFile::Open()
	{
		if(!myOutput)
		{
			fs::path file(myPathToOutputFolder);
			file /= myNameGiver->GetNextName();

			myOutput = std::make_unique<FileOutput>(myFormatter, file.string());
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void RollingFile::Close()
	{
		if(myOutput)
		{
			myOutput->Close();
			myOutput.reset(nullptr);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	class AgeSorter
	{
	  public:
		bool operator()(const fs::path& lhs, const fs::path& rhs)
		{
			auto timeA = fs::last_write_time(lhs);
			auto timeB = fs::last_write_time(rhs);
			return timeA < timeB;
		}
	};

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void RollingFile::CleanOldFiles() const
	{
		try
		{
			std::vector<std::string> allFiles;
			GetCurrentLogFiles(allFiles);

			// Sort in decending age order
			std::sort(allFiles.begin(), allFiles.end(), AgeSorter());
			// Remove from back until we have removed as many as we want to save
			if(static_cast<int>(allFiles.size()) > myFilesToKeep)
			{
				// Remove newest files from the list - we're keeping those.
				for(int i = 0; i < myFilesToKeep; ++i)
				{
					allFiles.pop_back();
				}

				// Now delete the files remaining in our list
				for(const auto& fullPath : allFiles)
				{
					try
					{
						fs::remove(fs::path(fullPath));
					}
					catch(...)
					{
						// If we can't delete it, there is nothing we can do.
					}
				}
			}
		}
		catch(...)
		{
		}
	}
} // namespace lout::output

