// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <threading/Lock.h>
/*qqq*/#include <iostream>

namespace lout {
namespace threading {

Lock::Lock()
: myMutex()
{
}

void Lock::Acquire()
{
	myMutex.lock();
}

void Lock::Release()
{
	myMutex.unlock();
}


}
}