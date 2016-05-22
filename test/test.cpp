//
// Created by Per Malmberg on 2016-05-06.
//

#define CATCH_CONFIG_MAIN

#include "../externals/Catch/include/catch.hpp"

#include <output/StdOutput.h>
#include <thread>
#include "output/FileOutput.h"
#include "LoutLogger.h"
#include "loglevel/defaultLevels.h"

using namespace lout;
using namespace lout::loglevel;
using namespace lout::output;

#define L Lout::Get()
#define LL LoutLogger()

SCENARIO( "Setting up a logger" )
{
	GIVEN( "A clean slate" )
	{
		L.Reset();
		THEN( "Program compiles" )
		{
			REQUIRE( L.GetThreshold().GetLevel() == 0 );
			L.Log( Verbose(), "Goes nowhere" );
		}
		AND_THEN( "Can set log level" )
		{
			L.SetThreshold( Warning() );
			REQUIRE( L.GetThreshold() == Warning() );
		}
	}
}

SCENARIO( "Adding a printer" )
{
	GIVEN( "A clean slate" )
	{
		L.Reset();

		WHEN( "A printer is added" )
		{
			std::shared_ptr<IOutput> p = std::make_shared<StdOutPrinter>();
			Lout::Get().AddOutput( p );

			THEN( "Printer count is increased" )
			{
				REQUIRE( Lout::Get().GetPrinterCount() == 1 );
			}
		}
	}
}

SCENARIO( "Regular logging" )
{
	GIVEN( "A logger with a printer" )
	{
		L.Reset();
		std::shared_ptr<IOutput> p = std::make_shared<StdOutPrinter>();
		Lout::Get().AddOutput( p );
		Lout::Get().SetThreshold( Info() );

		WHEN( "Logging on too high level" )
		{
			Lout::Get().Log( Warning(), "Log message" );

			THEN( "No output performed" )
			{
				REQUIRE( p.get()->GetMessageCount() == 0 );
			}
		}
		WHEN( "Logging on correct level" )
		{
			Lout::Get().Log( Info(), "Log message" );

			THEN( "Output performed" )
			{
				REQUIRE( (*p).GetMessageCount() == 1 );
			}
		}
		WHEN( "Increasing log level" )
		{
			Lout::Get().SetThreshold( Warning() );

			THEN( "We can log on that level too" )
			{
				std::string s = "Warning message";
				L.Log( Warning(), s );
				REQUIRE( (*p).GetMessageCount() == 1 );
			}
		}
	}
}

SCENARIO( "Logging with tag" )
{
	GIVEN( "A logger with a printer" )
	{
		L.Reset();
		std::shared_ptr<IOutput> p = std::make_shared<StdOutPrinter>();
		Lout::Get().AddOutput( p );
		Lout::Get().SetThreshold( Warning() );

		WHEN( "Logging called without activating tag" )
		{
			Lout::Get().LogWithCategory( Info(), "NonActiveTag", "Log message" );

			THEN( "No output performed" )
			{
				REQUIRE( (*p).GetMessageCount() == 0 );
			}
		}
		AND_WHEN( "Tag activated" )
		{
			Lout::Get().ActivateCategory( "ActiveTag" );
			Lout::Get().LogWithCategory( Info(), "ActiveTag", "Log message" );

			THEN( "Output performed" )
			{
				REQUIRE( (*p).GetMessageCount() == 1 );
			}
		}
	}
}

SCENARIO( "Using FileOutput" )
{
	GIVEN( "A logger with a file output  writer" )
	{
		L.Reset();
		std::shared_ptr<IOutput> p = std::make_shared<FileOutput>( "output.log" );
		Lout::Get().RemoveAllOutputs();
		Lout::Get().AddOutput( p );
		Lout::Get().SetThreshold( Warning() );

		WHEN( "Log with enabled level" )
		{
			for( int i = 0; i < 1000; ++i )
			{
				Lout::Get().Log( Info(), "Goes to file" + std::to_string( i ) );
			}
		}
	}
}

SCENARIO( "Using operator to set log level" )
{
	GIVEN( "A newly created Lout" )
	{
		L.Reset();
		std::shared_ptr<IOutput> p = std::make_shared<StdOutPrinter>();
		L.AddOutput( p );

		WHEN( "Level is not set" )
		{
			THEN( "Log level is 0" )
			{
				REQUIRE( L.GetThreshold().GetLevel() == 0 );
			}
		}
		AND_WHEN( "Level is set" )
		{
			L.SetThreshold( Warning() );
			THEN( "Level matches set level" )
			{
				REQUIRE( L.GetThreshold() == Warning() );
			}
			AND_THEN( "Logging to a higher level, doesn't give an output" )
			{
				L.Log( Error(), "Error message" );
				REQUIRE( p->GetMessageCount() == 0 );
			}
			AND_THEN( "We can log to that level" )
			{
				LL << Warning() << "This is logged as a warning message";
				REQUIRE( p->GetMessageCount() == 1 );
			}
		}
		AND_WHEN("We set log level to Error and log to Verbose" )
		{
			L.SetThreshold( Error() );
			THEN("nothing is printed")
			{
				LL << Verbose() << "A verbose message";
				REQUIRE( p->GetMessageCount() == 0 );
			}
		}
		AND_WHEN( "We set log level to verbose" )
		{
			L.SetThreshold( Verbose() );
			THEN("and log to the same level")
			{
				LL << Verbose() << "A verbose message";
				REQUIRE( p->GetMessageCount() == 1 );
			}
		}
	}
}


SCENARIO("Mandatory tags")
{
	GIVEN( "A logger with one output" )
	{
		L.Reset();
		std::shared_ptr<IOutput> p = std::make_shared<StdOutPrinter>();
		Lout::Get().AddOutput( p );
		L.SetThreshold( Info() );

		WHEN( "Log with too high level")
		{
			LL << Warning()  << "Warning message";
			THEN( "No output")
			{
				REQUIRE(p->GetMessageCount() == 0);
			}
		}
		AND_WHEN("A mandatory tag is used")
		{
			L.ActivatePriorityCategory( "MandatoryTag" );
			THEN("Message is logged")
			{
				L.LogWithCategory(Verbose(), "MandatoryTag", "Mandatory message");
				REQUIRE(p->GetMessageCount() == 1);
			}
		}
	}
}

SCENARIO("Using operator overloads to log numbers")
{
	GIVEN( "A logger with one output" )
	{
		L.Reset();
		std::shared_ptr<IOutput> p = std::make_shared<StdOutPrinter>();
		Lout::Get().AddOutput( p );
		L.SetThreshold( Info() );

		WHEN( "Using operator overload")
		{
			{
				LL << Info() << 1;
				LL << Info() << 1.2F << " " << "This text goes on the same line as \"1.2\"";
				LL << Info() << 13.4L << " This text goes on the same line as \"13.4\"";
				LL << Info() << "Only this text on this line";
				LL << Info() << int8_t( 4 ) << " only a 4 before this text";
			}
			THEN( "Output performed")
			{
				REQUIRE(p->GetMessageCount() == 5);
			}
		}
	}
}

SCENARIO("Multi threading")
{
	GIVEN("A properly setup Lout and multiple threads")
	{
		L.Reset();
		L.SetLocker(std::make_shared<threading::Lock>());
		std::shared_ptr<IOutput> p = std::make_shared<StdOutPrinter>();
		Lout::Get().AddOutput( p );
		L.SetThreshold( Warning() );

		WHEN( "Multiple threads are running")
		{
			std::vector<std::thread> threads;

			int iterations = 100;

			auto worker_task = [ & ](int id) {
				for( int i = 0; i < iterations; ++i )
				{
					LL << Info() << "Thread: " << id << " sample test" << " Iteraton: " << i;
				}

				LL << Warning() << "Thread id: " << id << " terminating";
			};

			int threadCount = 100;

			for( int i = 0; i < threadCount; ++i )
			{
				threads.emplace_back( worker_task, i );
			}

			for( auto& thread : threads )
			{
				thread.join();
			}

			THEN("All outputs accounted for")
			{
				REQUIRE(p->GetMessageCount() == ( threadCount * iterations ) + threadCount);
			}
		}
	}
}