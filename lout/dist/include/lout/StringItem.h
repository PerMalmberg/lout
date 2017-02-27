// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <string>
#include "LogItem.h"

namespace lout {

class StringItem : public LogItem
{
public:
	StringItem(const std::string& msg) : myMsg(msg)
	{ }

	void Log(LoutLogger& l) override;

private:
	std::string myMsg;
};

}