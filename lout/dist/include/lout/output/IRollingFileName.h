// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once
#include <string>

namespace lout {
namespace output {

class IRollingFileName
{
public:
	virtual ~IRollingFileName() {}

	// Returns the next log name to use
	virtual std::string GetNextName() = 0;

	// Returns true of the file name matches the patterns used to name the log files.
	virtual bool Matches( const std::string& fileName ) = 0;

};

}
}