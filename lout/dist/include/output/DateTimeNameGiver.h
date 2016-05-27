//
// Created by Per Malmberg on 2016-05-25.
//

#pragma once
#include <string>
#include "output/IRollingFileName.h"

namespace lout {
namespace output {

class DateTimeNameGiver : public IRollingFileName
{
	// Returns the next log name to use
	std::string GetNextName() const override;
};

}
}