// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once


#include <lout/item/ILogItem.h>
#include <lout/loglevel/ILogLevel.h>
#include <lout/LoutLogger.h>

namespace lout {

class LevelItem : public lout::item::ILogItem
{
public:
	LevelItem(const loglevel::ILogLevel& level) : myLevel(level)
	{ }

	void Log(lout::LoutLogger& l) override;

private:
	loglevel::ILogLevel myLevel;
};

}