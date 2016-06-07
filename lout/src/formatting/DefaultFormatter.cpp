//
// Created by perm on 2016-06-07.
//

#include <formatting/DefaultFormatter.h>
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