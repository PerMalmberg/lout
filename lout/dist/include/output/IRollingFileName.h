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

	// Returns true of the file name matches the patterns used to name the log files.
	virtual bool Matches( const std::string& fileName ) = 0;

};

}
}