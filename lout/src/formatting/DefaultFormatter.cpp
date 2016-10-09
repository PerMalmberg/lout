// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <lout/formatting/DefaultFormatter.h>
#include <sstream>

namespace lout {
namespace formatting {

std::string
DefaultFormatter::Format(const lout::loglevel::ILogLevel &level, const std::string &msg)
{
	std::stringstream s;
	s << "[" << level << "]" << msg;
	return s.str();
}

std::string
DefaultFormatter::Format(const lout::loglevel::ILogLevel &level, const std::string &category, const std::string &msg)
{
	std::stringstream s;
	s << "[" << level << "/" << category << "]" << msg;
	return s.str();
}

}
}