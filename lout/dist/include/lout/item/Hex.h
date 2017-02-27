// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <string>
#include "ILogItem.h"

namespace lout {
namespace item {

class Hex : public lout::item::ILogItem
{
public:
	explicit Hex( long num ) : number( num ) {}

	virtual void Log( lout::LoutLogger& l );
private:
	long number;
};

}
}