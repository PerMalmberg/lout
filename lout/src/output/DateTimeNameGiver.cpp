//
// Created by perma on 2016-05-25.
//

#include "output/DateTimeNameGiver.h"

#define __STDC_WANT_LIB_EXT1__ 1 // For localtime_s
#include <time.h>
#include <cstring>

namespace lout {
namespace output {

std::string DateTimeNameGiver::GetNextName() const
{
	time_t now = time( nullptr );
	tm localTime;

	localtime_s( &localTime, &now );

	char buff[40];
	std::memset(buff, 0, sizeof(buff));
	strftime(buff, sizeof(buff)-1, "%Y-%m-%d %H%M%S.log", &localTime);

	return std::string( buff );

}

}
}