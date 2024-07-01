// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "lout/formatting/IFormatter.h"
#include "lout/loglevel/ILogLevel.h"
#include "lout/loglevel/defaultLevels.h"
#include <memory>
#include <string>

namespace lout
{

	class Lout;

	namespace output
	{
		///////////////////////////////////////////////////////////////////////////////
		//
		// Interface/base class for all Lout outputs.
		// Note the noexcept on the methods - it is imperative that these functions
		// do not leak exceptions. Leaking means std::terminate will be called.
		//
		///////////////////////////////////////////////////////////////////////////////
		class IOutput
		{
		  public:
			// The fallback parameter is as the name implies, a fallback in case the normal output is non-functioning.
			// You may pass in a nullptr if you don't want a fallback stream.
			IOutput(std::shared_ptr<formatting::IFormatter> formatter, std::ostream* fallback)
			    : myFormatter(std::move(formatter)), myFallbackErrorStream(fallback), myThreshold(loglevel::NoLogging())
			{
			}

			virtual ~IOutput() = default;

			IOutput(const IOutput&) = delete;
			IOutput(IOutput&&) = delete;
			IOutput& operator=(const IOutput&) = delete;
			IOutput& operator=(IOutput&&) = delete;

			// Flushes the output, if applicable
			virtual void Flush() = 0;

			// Logs the message using the provided log level
			void Log(const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg);

			// Logs the message using the provided category and log level
			void LogWithCategory(const time_t& timestamp,
			                     const loglevel::ILogLevel& level,
			                     const std::string& category,
			                     const std::string& msg);

			// Clear the log, if applicable for the output type.
			virtual void Clear()
			{
			}

			[[nodiscard]] uint64_t GetMessageCount() const
			{
				return myMessageCount;
			}

			[[nodiscard]] const lout::loglevel::ILogLevel& GetThreshold() const
			{
				return myThreshold;
			}

		  protected:
			virtual void LogActual(const time_t& timestamp,
			                       const loglevel::ILogLevel& level,
			                       const std::string& msg) = 0;

			virtual void LogWithCategoryActual(const time_t& timestamp,
			                                   const loglevel::ILogLevel& level,
			                                   const std::string& category,
			                                   const std::string& msg) = 0;

			void FallbackLog(const time_t& timestamp,
			                 const loglevel::ILogLevel& level,
			                 const std::string& category,
			                 const std::string& msg);

			std::shared_ptr<formatting::IFormatter> myFormatter;

		  private:
			uint64_t myMessageCount = 0;
			std::ostream* myFallbackErrorStream = nullptr;
			loglevel::ILogLevel myThreshold;

			// The method is private because it should only be called from an instance of Lout to ensure threadsafety
			void SetThreshold(const loglevel::ILogLevel& level)
			{
				myThreshold = level;
			}

			bool IsLevelActive(const loglevel::ILogLevel& level)
			{
				return level <= myThreshold;
			}

			// We're best friends with Lout so that it can call SetThreshold in a threadsafe manner.
			friend class lout::Lout;
		};

	} // namespace output
} // namespace lout
