//
// Created by Per Malmberg on 2016-05-25.
//

#pragma once

#include <stdint.h>

namespace lout {
namespace util {

class Bytes {
public:
	Bytes( uint32_t bytes ) : myBytes( bytes ) {}

	uint32_t GetBytes() const { return myBytes; }
private:
	uint32_t myBytes = 0;
};

class KiloBytes : public Bytes
{
public:
	KiloBytes( uint32_t kiloBytes ) : Bytes( kiloBytes * 1024 ) {}
};

class MegaBytes : public KiloBytes
{
	MegaBytes( uint32_t megaBytes ) : KiloBytes( megaBytes * 1024 ) {}
};


}
}