// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once


namespace lout {

class LoutLogger;

namespace item {

class ILogItem
{
public:
	virtual ~ILogItem() = default;
	virtual void Log( lout::LoutLogger& l ) = 0;
};

}
}
