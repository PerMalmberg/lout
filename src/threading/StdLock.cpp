// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include "threading/StdLock.h"

namespace lout::threading
{
	void StdLock::Acquire()
	{
		myMutex.lock();
	}

	void StdLock::Release()
	{
		myMutex.unlock();
	}

} // namespace lout::threading
