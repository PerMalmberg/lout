// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <ostream>
#include <utility>

namespace lout::loglevel
{

	///////////////////////////////////////////////////////////////////////////////
	//
	// Base class for log levels used by Lout. Inherit from this to provide custom levels
	//
	///////////////////////////////////////////////////////////////////////////////
	class ILogLevel
	{
	  public:
		ILogLevel(int level, std::string levelAsText) : myLevel(level), myLevelAsText(std::move(levelAsText))
		{
		}

		bool operator<=(const ILogLevel& rhs) const
		{
			return myLevel <= rhs.myLevel;
		}

		bool operator==(const ILogLevel& rhs) const
		{
			return myLevel == rhs.GetLevel();
		}

		[[nodiscard]] int GetLevel() const
		{
			return myLevel;
		}

		[[nodiscard]] const std::string& GetText() const
		{
			return myLevelAsText;
		}

	  private:
		int myLevel;
		std::string myLevelAsText;
	};
} // namespace lout::loglevel

std::ostream& operator<<(std::ostream& stream, const lout::loglevel::ILogLevel&);
