// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "ILogItem.h"

namespace lout::item
{

	class Hex : public lout::item::ILogItem
	{
	  public:
		explicit Hex(long num) : number(num)
		{
		}

		void Log(lout::LoutLogger& log) override;

	  private:
		long number;
	};

} // namespace lout::item

