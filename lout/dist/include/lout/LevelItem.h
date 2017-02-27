// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once


#include "LogItem.h"
#include "loglevel/ILogLevel.h"

namespace lout {

class LevelItem : public LogItem
{
public:
	LevelItem(const loglevel::ILogLevel& level) : myLevel(level)
	{ }

	void Log(LoutLogger& l) override;

private:
	loglevel::ILogLevel myLevel;
};

}