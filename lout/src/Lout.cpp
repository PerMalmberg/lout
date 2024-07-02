// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include "lout/Lout.h"
#include "lout/loglevel/ILogLevel.h"
#include "lout/output/IOutput.h"
#include "lout/threading/ILock.h"
#include "lout/threading/NoLock.h"
#include <ctime>
#include <memory>
#include <string>
#include <utility>

namespace lout
{

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	Lout::Lout() : myLock(std::make_shared<threading::NoLock>())
	{
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	Lout::~Lout()
	{
		RemoveAllOutputs();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Lout::SetThreshold(const loglevel::ILogLevel& newLevel)
	{
		const Locker lock(myLock);
		(void)lock;

		for(const auto& out : myOutput)
		{
			out->SetThreshold(newLevel);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Lout::OverrideThreshold(const std::shared_ptr<output::IOutput>& output, const loglevel::ILogLevel& level)
	{
		const Locker lock(myLock);
		(void)lock;
		output->SetThreshold(level);
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Lout::ActivateCategory(const std::string& category)
	{
		const Locker lock(myLock);
		(void)lock;

		myActiveCategories.emplace(category);
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Lout::ActivatePriorityCategory(const std::string& category)
	{
		const Locker lock(myLock);
		(void)lock;

		myPriorityCategories.emplace(category);
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Lout::AddOutput(const std::shared_ptr<output::IOutput>& output)
	{
		const Locker lock(myLock);
		(void)lock;

		if(output)
		{
			myOutput.push_back(output);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Lout::RemoveAllOutputs()
	{
		FlushAll();
		const Locker lock(myLock);
		(void)lock;
		myOutput.erase(myOutput.begin(), myOutput.end());
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Lout::Log(const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg)
	{
		const Locker lock(myLock);
		(void)lock;

		for(auto& out : myOutput)
		{
			if(out->IsLevelActive(level))
			{
				out->Log(timestamp, level, msg);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Lout::LogWithCategory(const time_t& timestamp,
	                           const loglevel::ILogLevel& level,
	                           const std::string& category,
	                           const std::string& msg)
	{
		const Locker lock(myLock);
		(void)lock;

		// First check normal categories. If no category is set, all are allowed.
		const bool shallLog =
		myActiveCategories.empty() || myActiveCategories.find(category) != myActiveCategories.end();

		// Now check priority categories
		const bool priority = myPriorityCategories.find(category) != myPriorityCategories.end();

		if(shallLog || priority)
		{
			for(auto& out : myOutput)
			{
				// The message should be logged if a priority category is used, or if the output has the level active.
				if(priority || out->IsLevelActive(level))
				{
					out->LogWithCategory(timestamp, level, category, msg);
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Lout::ClearLog() const
	{
		const Locker lock(myLock);
		(void)lock;

		for(const auto& out : myOutput)
		{
			out->Clear();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Lout::FlushAll()
	{
		const Locker lock(myLock);
		(void)lock;

		for(auto& out : myOutput)
		{
			(*out).Flush();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	Lout::Locker::Locker(std::shared_ptr<threading::ILock> lock) : myLock(std::move(lock))
	{
		if(myLock)
		{
			myLock->Acquire();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	Lout::Locker::~Locker()
	{
		if(myLock)
		{
			myLock->Release();
		}
	}
} // END namespace lout
