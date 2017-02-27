// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <string>
#include <lout/item/ILogItem.h>
#include <lout/LoutLogger.h>

class TestItem : public lout::item::ILogItem
{
public:
	TestItem(const std::string& foo, const std::string& bar)
		: value1(foo), value2(bar)
	{}

	virtual void Log(lout::LoutLogger& l)
	{
		l.AppendMsg( value1 );
		l.AppendMsg( value2 );
	}

private:
	std::string value1;
	std::string value2;

};
