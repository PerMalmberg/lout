// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once
#include <mutex>

namespace lout {
namespace threading {

// Interface for thread synchronization used by Lout
class ILock
{
public:
	virtual ~ILock() = default;

	virtual void Acquire() = 0;

	virtual void Release() = 0;
};

}
}
