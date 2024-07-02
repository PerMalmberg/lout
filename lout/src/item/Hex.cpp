// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <ios>
#include <lout/LoutLogger.h>
#include <lout/item/Hex.h>
#include <sstream>

namespace lout::item
{
	void Hex::Log(lout::LoutLogger& log)
	{
		std::stringstream sstr;
		sstr << std::hex << number;
		log.AppendMsg(sstr.str());
	}
} // namespace lout::item

