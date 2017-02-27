// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <lout/threading/StdLock.h>

namespace lout {
namespace threading {

StdLock::StdLock()
: myMutex()
{
}

void StdLock::Acquire()
{
	myMutex.lock();
}

void StdLock::Release()
{
	myMutex.unlock();
}


}
}