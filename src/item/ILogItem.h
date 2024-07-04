// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

namespace lout
{
	class LoutLogger;

	namespace item
	{
		class ILogItem
		{
		  public:
			ILogItem() = default;
			ILogItem(const ILogItem&) = delete;
			ILogItem(ILogItem&&) = delete;
			ILogItem& operator=(const ILogItem&) = delete;
			ILogItem& operator=(ILogItem&&) = delete;
			virtual ~ILogItem() = default;

			virtual void Log(lout::LoutLogger& log) = 0;
		};

	} // namespace item
} // namespace lout
