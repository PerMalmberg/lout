// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once
#include "ILock.h"

namespace lout::threading
{
	// A class that provides no lock for use in single-threaded applications.
	class NoLock : public ILock
	{
	  public:
		void Acquire() override
		{
		}
		void Release() override
		{
		}
	};

} // namespace lout::threading
