// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include "loglevel/ILogLevel.h"
#include <ostream>

std::ostream& operator<<(std::ostream& stream, const lout::loglevel::ILogLevel& level)
{
	stream << level.GetText().c_str();
	return stream;
}
