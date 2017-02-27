// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <string>
#include <lout/item/Hex.h>
#include <lout/LoutLogger.h>

namespace lout {
namespace item {

void Hex::Log( lout::LoutLogger& l )
{
	std::stringstream ss;
	ss << std::hex << number;
	l.AppendMsg( ss.str() );
}

}
}