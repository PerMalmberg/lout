// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "LoutLogger.h"
#include "item/ILogItem.h"
#include <string>
#include <utility>

class TestItem : public lout::item::ILogItem
{
  public:
	TestItem(std::string foo, std::string bar) : value1(std::move(foo)), value2(std::move(bar))
	{
	}

	virtual void Log(lout::LoutLogger& log)
	{
		log.AppendMsg(value1);
		log.AppendMsg(value2);
	}

  private:
	std::string value1;
	std::string value2;
};
