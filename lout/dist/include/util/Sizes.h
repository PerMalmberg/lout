// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <stdint.h>

namespace lout {
namespace util {

class Bytes {
public:
	Bytes( long bytes ) : myBytes( bytes ) {}

	long GetBytes() const { return myBytes; }
private:
	long myBytes = 0;
};

class KiloBytes : public Bytes
{
public:
	KiloBytes( long kiloBytes ) : Bytes( kiloBytes * 1024 ) {}
};

class MegaBytes : public KiloBytes
{
	MegaBytes( long megaBytes ) : KiloBytes( megaBytes * 1024 ) {}
};


}
}