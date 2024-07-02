// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

namespace lout::threading
{

	// Interface for thread synchronization used by Lout
	class ILock
	{
	  public:
		ILock() = default;
		ILock(const ILock&) = delete;
		ILock(ILock&&) = delete;
		ILock& operator=(const ILock&) = delete;
		ILock& operator=(ILock&&) = delete;
		virtual ~ILock() = default;

		virtual void Acquire() = 0;

		virtual void Release() = 0;
	};
} // namespace lout::threading
