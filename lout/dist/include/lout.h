//
// Created by Per Malmberg on 2016-05-06.
//

#pragma once

#include <memory>
#include <vector>
#include <exception>
#include "ILoutOutput.h"

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

	void AddOutput(std::shared_ptr<ILoutOutput < TLogLevel>> output );

	void RemoveAllOutputs();

	void Log(TLogLevel level, const std::string& msg);

	void LogWithTag(TLogLevel level, const std::string& tag, const std::string& msg);

	void SetLevel(TLogLevel newLevel);

	TLogLevel GetLevel() const
	{ return myCurrentLevel; }

	void ActivateTag(const std::string& tag);

	size_t GetPrinterCount() const
	{ return myOutput.size(); }

	Lout<TLogLevel>(const Lout<TLogLevel>&) = delete;

	Lout<TLogLevel>& operator=(Lout<TLogLevel>&) = delete;

private:
	TLogLevel myCurrentLevel;
	std::vector<std::shared_ptr<ILoutOutput < TLogLevel>>> myOutput;
	std::set<std::string> myActiveTags;

	bool IsLevelActive(TLogLevel level)
	{
		// We allow logging up to and including the currently set level.
		return level <= myCurrentLevel;
	}

	void FlushAll();
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
	RemoveAllOutputs();
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
	myActiveTags.emplace( tag );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
void Lout<TLogLevel>::AddOutput(std::shared_ptr< ILoutOutput<TLogLevel> > output) {
	if( output ) {
		myOutput.push_back( std::move(output) );
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
void Lout<TLogLevel>::RemoveAllOutputs()
{
	FlushAll();
	myOutput.erase( myOutput.begin(), myOutput.end() );
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
		for( auto& p : myOutput )
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
		for( auto& p : myOutput )
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

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
void Lout<TLogLevel>::FlushAll()
{
	for( auto& p : myOutput )
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
}

}
}
}