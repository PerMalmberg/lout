// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include "LoutLogger.h"
#include "Flush.h"
#include "LevelItem.h"
#include "Lout.h"
#include "item/ILogItem.h"
#include "item/StringItem.h"
#include <climits>
#include <cstdint>
#include <ctime>
#include <limits>
#include <memory>
#include <string>

namespace lout
{
	using namespace lout::item;

	LoutLogger::LoutLogger() : myCurrentLevel(std::numeric_limits<int>::max(), "NoLevel"), timestamp(time(nullptr))
	{
	}

	LoutLogger::~LoutLogger()
	{
		Flush();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(const loglevel::ILogLevel& level)
	{
		myItems.push_back(std::make_shared<LevelItem>(level));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(const std::string& msg)
	{
		myItems.push_back(std::make_shared<StringItem>(msg));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(int8_t value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(int16_t value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(int32_t value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(int64_t value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(uint8_t value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(uint16_t value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(uint32_t value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(uint64_t value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
#if ULONG_MAX == (0xFFFFFFFFUL) || __APPLE__
	// Don't compile this on 64 bit platforms since it is the same as uint64_t
	LoutLogger& LoutLogger::operator<<(unsigned long value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}
#endif

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(double value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(long double value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(float value)
	{
		myItems.push_back(std::make_shared<StringItem>(std::to_string(value)));
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(const std::shared_ptr<lout::item::ILogItem>& item)
	{
		myItems.push_back(item);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	LoutLogger& LoutLogger::operator<<(const lout::Flush& /*unused*/)
	{
		Flush();
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void LoutLogger::AppendMsg(const std::string& msg)
	{
		myCurrentMessage << msg;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void LoutLogger::SetLevel(const loglevel::ILogLevel& level)
	{
		myCurrentLevel = level;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void LoutLogger::Flush()
	{
		for(auto& item : myItems)
		{
			item->Log(*this);
		}

		myItems.clear();

		const std::string msg = myCurrentMessage.str();

		if(!msg.empty())
		{
			if(myCategory.empty())
			{
				Lout::Get().Log(timestamp, myCurrentLevel, msg);
			}
			else
			{
				Lout::Get().LogWithCategory(timestamp, myCurrentLevel, myCategory, msg);
			}
		}

		myCurrentMessage.str("");
		myCurrentMessage.clear();

		// Set a new time in case this instance is reused.
		(void)time(&timestamp);
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void LevelItem::Log(LoutLogger& log)
	{
		log.SetLevel(myLevel);
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void StringItem::Log(LoutLogger& log)
	{
		log.AppendMsg(myMsg);
	}
} // namespace lout
