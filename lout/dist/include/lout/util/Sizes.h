// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <stdint.h>

namespace lout {
namespace util {

class Bytes {
public:
	Bytes( uint64_t bytes ) : myBytes( bytes ) {}

	uint64_t GetBytes() const { return myBytes; }
private:
	uint64_t myBytes = 0;
};

class KiloBytes : public Bytes
{
public:
	KiloBytes( uint64_t kiloBytes ) : Bytes( kiloBytes * 1024 ) {}
};

class MegaBytes : public KiloBytes
{
	MegaBytes( uint64_t megaBytes ) : KiloBytes( megaBytes * 1024 ) {}
};


}
}