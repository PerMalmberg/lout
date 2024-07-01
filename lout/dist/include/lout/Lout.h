// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "lout/loglevel/ILogLevel.h"
#include "lout/output/IOutput.h"
#include "lout/threading/ILock.h"
#include <memory>
#include <set>
#include <utility>
#include <vector>

namespace lout
{
	class Lout
	{
	  public:
		Lout();

		Lout(Lout&&) = delete;
		Lout& operator=(Lout&&) = delete;
		virtual ~Lout();

		// Resets the logger
		void Reset()
		{
			RemoveAllOutputs();
			SetThreshold(loglevel::NoLogging());
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
		void Log(const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg);

		// Logs using the provided level and category. Only categories that have been activated will be logged.
		void LogWithCategory(const time_t& timestamp,
		                     const loglevel::ILogLevel& level,
		                     const std::string& category,
		                     const std::string& msg);

		// Asks the outputs to clear their logs, if applicable.
		void ClearLog() const;

		// Sets the log level threshold. No level higher than the one set will be allowed.
		void SetThreshold(const loglevel::ILogLevel& newLevel);

		// Sets the locker used by Lout.
		// Note: Must be called before multiple threads uses the Lout instance.
		void SetLocker(std::shared_ptr<threading::ILock> lock)
		{
			myLock = std::move(lock);
		}

		// Activates a category
		void ActivateCategory(const std::string& category);

		// Activates a mandatory category, meaning that any log message with this category will be logged
		// regardless of level threshold.
		void ActivatePriorityCategory(const std::string& category);

		// Overrides the threshold on the specified output with the specified level.
		// The override will be active until Lout::SetThreshold() is called.
		void OverrideThreshold(std::shared_ptr<output::IOutput> output, const loglevel::ILogLevel& level);

		// Returns the number of outputs currently in use
		[[nodiscard]] size_t GetPrinterCount() const
		{
			return myOutput.size();
		}

		Lout(const Lout&) = delete;

		Lout& operator=(Lout&) = delete;

	  protected:
		class Locker
		{
		  public:
			Locker(const Locker&) = delete;
			Locker(Locker&&) = delete;
			Locker& operator=(const Locker&) = delete;
			Locker& operator=(Locker&&) = delete;
			explicit Locker(std::shared_ptr<threading::ILock>);

			~Locker();

		  private:
			std::shared_ptr<threading::ILock> myLock;
		};

	  private:
		std::vector<std::shared_ptr<output::IOutput>> myOutput;
		std::set<std::string> myActiveCategories;
		std::set<std::string> myPriorityCategories;
		std::shared_ptr<threading::ILock> myLock;

		void FlushAll();
	};

} // namespace lout
