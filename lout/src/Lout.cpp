//
// Created by Per Malmberg on 2016-05-21.
//

#include <Lout.h>
#include <c++/iostream>

namespace lout {

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Lout::Lout()
		: myCurrentThreshold( 0, "NoLevel" ),
		  myCurrentLoggingLevel( -1, "NoLevel" ),
		  myActiveTags(),
		  myMandatoryTags()
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
void Lout::ActivateTag(const std::string& tag)
{
	myActiveTags.emplace( tag );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Lout::ActivateMandatoryTag(const std::string& tag)
{
	myMandatoryTags.emplace( tag );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Lout::AddOutput(std::shared_ptr<output::IOutput> output)
{
	if( output )
	{
		myOutput.push_back( std::move( output ) );
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Lout::RemoveAllOutputs()
{
	FlushAll();
	myOutput.erase( myOutput.begin(), myOutput.end() );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Lout::Log(const loglevel::ILogLevel& level, const std::string& msg)
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
void Lout::LogWithTag(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg)
{
	// First check level and normal tags
	bool shallLog = IsLevelActive( level ) && myActiveTags.find( tag ) != myActiveTags.end();
	// Now check mandatory tags
	shallLog |= myMandatoryTags.find( tag ) != myMandatoryTags.end();

	if( shallLog )
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
void Lout::FlushAll()
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

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Lout& Lout::operator<<(const loglevel::ILogLevel& level)
{
	myCurrentLoggingLevel = level;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Lout& Lout::operator<<(const std::string& msg)
{
	Log( myCurrentLoggingLevel, msg );
	return *this;
}

} // END namespace lout