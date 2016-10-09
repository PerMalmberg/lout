// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <loglevel/ILogLevel.h>

namespace lout {
namespace formatting {
	class IFormatter {
	public:
		virtual std::string Format(const loglevel::ILogLevel &level, const std::string &category, const std::string &msg) = 0;
		virtual std::string Format(const loglevel::ILogLevel &level, const std::string &msg) = 0;
	};
}
}