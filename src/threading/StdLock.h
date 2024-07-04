// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once
#include "ILock.h"
#include <mutex>

namespace lout::threading
{
	// A class that provides lock via a mutex for use in multi-threaded applications
	class StdLock : public ILock
	{
	  public:
		void Acquire() override;
		void Release() override;

	  private:
		std::recursive_mutex myMutex;
	};
} // namespace lout::threading
