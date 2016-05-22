//
// Created by perma on 2016-05-22.
//

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