// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once
#include <mutex>
#include "ILock.h"

namespace lout {
namespace threading {

// A class that provides lock via a mutex for use in multi-threaded applications
class StdLock : public ILock
{
public:
	StdLock();
	void Acquire() override;
	void Release() override;
private:
	std::recursive_mutex myMutex;
};

}
}
