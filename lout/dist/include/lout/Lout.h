// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <memory>
#include <vector>
#include <exception>
#include <set>
#include "lout/output/IOutput.h"
#include "lout/loglevel/ILogLevel.h"
#include "lout/threading/Lock.h"

namespace lout {

class Lout
{
public:
	Lout();

	virtual ~Lout();

	// Resets the logger
	void Reset()
	{
		RemoveAllOutputs();
		SetThreshold( loglevel::ILogLevel( 0, "NoLevel" ) );
		myActiveCategories.clear();
		myPriorityCategories.clear();
	}

	// Gets the singleton instance
	static Lout& Get()
	{
		// This is thread safe in C++11, §6.7 - 4
		// Page 137, http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2011/n3242.pdf
		static Lout instance;
		return instance;
	}

	// Adds an output to the logger
	void AddOutput(std::shared_ptr<output::IOutput> output);

	// Removes all outputs
	void RemoveAllOutputs();

	// Logs using the provided level
	void Log(const loglevel::ILogLevel& level, const std::string& msg);

	// Logs using the provided level and category. Only categories that have been activated will be logged.
	void LogWithCategory(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg);

	// Sets the log level threshold. No level higher than the one set will be allowed.
	void SetThreshold(const loglevel::ILogLevel& newLevel);

	// Sets the locker used by Lout.
	// Note: Must be called before multiple threads uses the Lout instance.
	void SetLocker( std::shared_ptr<threading::ILock> lock ) {
		myLock = lock;
	}

	// Gets the current threshold level
	const loglevel::ILogLevel& GetThreshold() const
	{
		return myCurrentThreshold;
	}

	// Activates a category
	void ActivateCategory(const std::string& category);

	// Activates a mandatory category, meaning that any log message with this category will be logged
	// regardless of level threshold.
	void ActivatePriorityCategory(const std::string& category);

	// Returns the number of outputs currently in use
	size_t GetPrinterCount() const
	{
		return myOutput.size();
	}

	Lout(const Lout&) = delete;

	Lout& operator=(Lout&) = delete;

protected:
	class Locker
	{
	public:
		Locker(std::shared_ptr<threading::ILock>);

		~Locker();
	private:
		std::shared_ptr<threading::ILock> myLock;
	};

private:
	loglevel::ILogLevel myCurrentThreshold;
	std::vector<std::shared_ptr<output::IOutput>> myOutput;
	std::set<std::string> myActiveCategories;
	std::set<std::string> myPriorityCategories;
	std::shared_ptr<threading::ILock> myLock;

	bool IsLevelActive(const loglevel::ILogLevel& level)
	{
		// We allow logging up to and including the currently set level.
		return level <= myCurrentThreshold;
	}

	void FlushAll();
};


}