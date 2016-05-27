//
// Created by Per Malmberg on 2016-05-25.
//

#pragma once
#include <string>

namespace lout {
namespace output {

class IRollingFileName
{
public:
	virtual ~IRollingFileName() {}

	// Returns the next log name to use
	virtual std::string GetNextName() const = 0;

};

}
}