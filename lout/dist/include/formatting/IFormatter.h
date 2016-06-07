//
// Created by perm on 2016-06-07.
//

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