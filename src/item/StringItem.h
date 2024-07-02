// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "ILogItem.h"
#include <string>
#include <utility>

namespace lout::item
{
	class StringItem : public ILogItem
	{
	  public:
		explicit StringItem(std::string msg) : myMsg(std::move(msg))
		{
		}

		void Log(lout::LoutLogger& log) override;

	  private:
		std::string myMsg;
	};

} // namespace lout::item

