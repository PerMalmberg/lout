// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

namespace lout::util
{
	class Bytes
	{
	  public:
		explicit Bytes(long bytes) : myBytes(bytes)
		{
		}

		[[nodiscard]] long GetBytes() const
		{
			return myBytes;
		}

	  protected:
		static constexpr int multiplier = 1024;

	  private:
		long myBytes = 0;
	};

	class KiloBytes : public Bytes
	{
	  public:
		explicit KiloBytes(long kiloBytes) : Bytes(kiloBytes * multiplier)
		{
		}
	};

	class MegaBytes : public KiloBytes
	{
		explicit MegaBytes(long megaBytes) : KiloBytes(megaBytes * multiplier)
		{
		}
	};

} // namespace lout::util

