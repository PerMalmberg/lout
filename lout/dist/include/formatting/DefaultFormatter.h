//
// Created by perm on 2016-06-07.
//

#pragma once

#include <formatting/IFormatter.h>

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
