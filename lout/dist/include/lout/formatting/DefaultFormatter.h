// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "IFormatter.h"

namespace lout {
namespace formatting {

class DefaultFormatter : public IFormatter
{
public:
	std::string Format(const loglevel::ILogLevel &level, const std::string &msg) override;
	std::string Format(const loglevel::ILogLevel &level, const std::string &category, const std::string &msg) override;
};

}
}
