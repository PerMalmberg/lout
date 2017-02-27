// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <string>
#include "ILogItem.h"

namespace lout {
namespace item {

class StringItem : public ILogItem
{
public:
	StringItem( const std::string& msg ) : myMsg( msg )
	{
	}

	void Log( lout::LoutLogger& l ) override;

private:
	std::string myMsg;
};

}
}