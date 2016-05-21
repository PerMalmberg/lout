//
// Created by perma on 2016-05-21.
//

#include <ostream>
#include <loglevel/ILogLevel.h>


std::ostream& operator<<(std::ostream& stream, const lout::loglevel::ILogLevel& level)
{
	stream << level.GetText().c_str();
	return stream;
}