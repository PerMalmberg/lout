//
// Created by Per Malmberg on 2016-05-06.
//

#pragma once

#include <ostream>
#include <vector>
#include <exception>
#include "ILoutPrinter.h"

namespace com {
namespace codezeal {
namespace logging {

template<typename TLogLevel>
class Lout
{
public:
	Lout();

	virtual ~Lout();

	static Lout<TLogLevel>& Get()
	{
		static Lout<TLogLevel> instance;
		return instance;
	}

	void AddPrinter(std::shared_ptr<ILoutPrinter<TLogLevel>> printer);

	void Log(TLogLevel level, const std::string& msg);

	void LogWithTag(TLogLevel level, const std::string& tag, const std::string& msg);

	void SetLevel(TLogLevel newLevel);

	TLogLevel GetLevel() const
	{ return myCurrentLevel; }

	void ActivateTag(const std::string& tag);

	size_t GetPrinterCount() const
	{ return myPrinter.size(); }

	Lout<TLogLevel>(const Lout<TLogLevel>&) = delete;

	Lout<TLogLevel>& operator=(Lout<TLogLevel>&) = delete;

private:
	TLogLevel myCurrentLevel;
	std::vector<std::shared_ptr<ILoutPrinter<TLogLevel>>> myPrinter;
	std::set<std::string> myActiveTags;

	bool IsLevelActive(TLogLevel level)
	{
		// We allow logging up to and including the currently set level.
		return level <= myCurrentLevel;
	}
};

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
Lout<TLogLevel>::Lout()
		: myCurrentLevel(), myActiveTags()
{

}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
Lout<TLogLevel>::~Lout()
{
	for( auto& p : myPrinter )
	{
		try
		{
			(*p).Flush();
		}
		catch( std::exception& e )
		{
			std::cerr << e.what() << std::endl;
		}
		catch( ... )
		{
			std::cerr << "Unknown error while flushing" << std::endl;
		}
	}

	myPrinter.erase(myPrinter.begin(), myPrinter.end());
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
void Lout<TLogLevel>::SetLevel(TLogLevel newLevel)
{
	myCurrentLevel = newLevel;
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
void Lout<TLogLevel>::ActivateTag(const std::string& tag)
{
	myActiveTags.emplace(tag);
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
void Lout<TLogLevel>::AddPrinter(std::shared_ptr<ILoutPrinter<TLogLevel>> printer)
{
	if( printer )
	{
		myPrinter.push_back( std::move( printer ) );
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
void Lout<TLogLevel>::Log(TLogLevel level, const std::string& msg)
{
	if( IsLevelActive( level ) )
	{
		for( auto& p : myPrinter )
		{
			try
			{
				p.get()->Log( level, msg );
			}
			catch( std::exception& e )
			{
				std::cerr << e.what() << std::endl;
			}
			catch( ... )
			{
				std::cerr << "Unknown error while logging" << std::endl;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
void Lout<TLogLevel>::LogWithTag(TLogLevel level, const std::string& tag, const std::string& msg)
{
	if( IsLevelActive( level ) && myActiveTags.find( tag ) != myActiveTags.end() )
	{
		for( auto& p : myPrinter )
		{
			try
			{
				p.get()->LogWithTag( level, tag, msg );
			}
			catch( std::exception& e )
			{
				std::cerr << e.what() << std::endl;
			}
			catch( ... )
			{
				std::cerr << "Unknown error while logging" << std::endl;
			}
		}
	}
}

}
}
}