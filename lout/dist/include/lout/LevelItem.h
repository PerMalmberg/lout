// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <lout/LoutLogger.h>
#include <lout/item/ILogItem.h>
#include <lout/loglevel/ILogLevel.h>

#include <utility>

namespace lout
{

	class LevelItem : public lout::item::ILogItem
	{
	  public:
		explicit LevelItem(loglevel::ILogLevel level) : myLevel(std::move(level))
		{
		}

		void Log(lout::LoutLogger& log) override;

	  private:
		loglevel::ILogLevel myLevel;
	};

} // namespace lout
