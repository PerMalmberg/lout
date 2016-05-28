//
// Created by Per Malmberg on 2016-05-21.
//

#include <Lout.h>
#include <iostream>
#include <filesystem>
namespace lout {

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Lout::Lout()
		: myCurrentThreshold( 0, "NoLevel" ),
		  myActiveCategories(),
		  myPriorityCategories(),
		  myLock( std::make_shared<threading::NoLock>() )
{
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Lout::~Lout()
{
	RemoveAllOutputs();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Lout::SetThreshold(const loglevel::ILogLevel& newLevel)
{
	myCurrentThreshold = newLevel;
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Lout::ActivateCategory(const std::string& category)
{
	myActiveCategories.emplace( category );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Lout::ActivatePriorityCategory(const std::string& category)
{
	myPriorityCategories.emplace( category );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Lout::AddOutput(std::shared_ptr<output::IOutput> output)
{
	if( output )
	{
		myOutput.push_back( output );
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Lout::RemoveAllOutputs()
{
	FlushAll();
	Locker lock( myLock );
	(void)lock;
	myOutput.erase( myOutput.begin(), myOutput.end() );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Lout::Log(const loglevel::ILogLevel& level, const std::string& msg)
{
	Locker lock( myLock );
	(void)lock; // Just to silence the warning

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
void Lout::LogWithCategory(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg)
{
	Locker lock( myLock );
	(void)lock;

	// First check level and normal categories. If no category is set, all are allowed.
	bool shallLog = IsLevelActive( level )
	                && (myActiveCategories.empty() || myActiveCategories.find( category ) != myActiveCategories.end());

	// Now check mandatory categories
	shallLog |= myPriorityCategories.find( category ) != myPriorityCategories.end();

	if( shallLog )
	{
		for( auto& p : myOutput )
		{
			try
			{
				p.get()->LogWithCategory( level, category, msg );
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
void Lout::FlushAll()
{
	Locker lock( myLock );
	(void)lock;

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


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Lout::Locker::Locker(std::shared_ptr<threading::ILock> lock)
		: myLock( lock )
{
	if( myLock )
	{
		myLock->Acquire();
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Lout::Locker::~Locker()
{
	if( myLock )
	{
		myLock->Release();
	}
}


} // END namespace lout