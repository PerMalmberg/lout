// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#define CATCH_CONFIG_MAIN
#include "../externals/Catch/include/catch.hpp"

#include <thread>
#include <lout/output/ColoredStdOutput.h>
#include <lout/output/RollingFile.h>
#include <lout/output/DateTimeNameGiver.h>
#include <lout/LoutLogger.h>
#include <lout/loglevel/defaultLevels.h>
#include <lout/formatting/DefaultFormatter.h>
#include <lout/threading/StdLock.h>
#include <lout/item/Hex.h>
#include "TestItem.h"
#include "../externals/rlutil/rlutil.h"
#include "TestOutput.h"

using namespace lout;
using namespace lout::loglevel;
using namespace lout::output;

#define L Lout::Get()
#define LL LoutLogger()

#define info LoutLogger() << Info()
#define infoc(category) LoutLogger(category) << Info()
#define warn LoutLogger() << Warning()


SCENARIO( "Adding a printer" )
{
	GIVEN( "A clean slate" )
	{
		L.Reset();

		WHEN( "A printer is added" )
		{
			std::shared_ptr<IOutput> p = std::make_shared<TestOutput>();
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
		std::shared_ptr<IOutput> p = std::make_shared<TestOutput>();
		Lout::Get().AddOutput( p );
		Lout::Get().SetThreshold( Info() );

		time_t now;
		time( &now );

		WHEN( "Logging on too high level" )
		{
			Lout::Get().Log( now, Warning(), "Log message" );

			THEN( "No output performed" )
			{
				REQUIRE( p.get()->GetMessageCount() == 0 );
			}
		}
		WHEN( "Logging on correct level" )
		{
			Lout::Get().Log( now, Info(), "Log message" );

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
				L.Log( now, Warning(), s );
				REQUIRE( (*p).GetMessageCount() == 1 );
			}
		}
	}
}

SCENARIO( "Specific log level on output" )
{
	GIVEN( "A logger with a printer" )
	{
		L.Reset();
		std::shared_ptr<IOutput> p = std::make_shared<TestOutput>();
		Lout::Get().AddOutput( p );
		Lout::Get().SetThreshold( Info() );

		time_t now;
		time( &now );

		WHEN( "Logging on too high level" )
		{
			Lout::Get().Log( now, Warning(), "Log message" );

			THEN( "No output performed" )
			{
				REQUIRE( p.get()->GetMessageCount() == 0 );
			}
		}
		WHEN( "Logging on correct level" )
		{
			Lout::Get().Log( now, Info(), "Log message" );

			THEN( "Output performed" )
			{
				REQUIRE( (*p).GetMessageCount() == 1 );
			}
		}
		WHEN( "Setting log level on output specifically" )
		{
			L.OverrideThreshold( p, Warning() );

			THEN( "We can log on that level too" )
			{
				std::string s = "Warning message";
				L.Log( now, Warning(), s );
				REQUIRE( (*p).GetMessageCount() == 1 );
			}
		}
	}
}

SCENARIO( "Logging with category" )
{
	GIVEN( "A logger with a printer" )
	{
		L.Reset();
		std::shared_ptr<IOutput> p = std::make_shared<TestOutput>();
		Lout::Get().AddOutput( p );
		Lout::Get().SetThreshold( Warning() );

		time_t now;
		time( &now );

		WHEN( "Logging called without activating category" )
		{
			Lout::Get().LogWithCategory( now, Info(), "NonActiveTag", "Log message" );

			THEN( "output performed because we allow all categories in that case" )
			{
				REQUIRE( (*p).GetMessageCount() == 1 );
			}
		}
		AND_WHEN( "Category activated" )
		{
			Lout::Get().ActivateCategory( "ActiveTag" );
			Lout::Get().LogWithCategory( now, Info(), "ActiveTag", "Log message" );

			THEN( "Output performed" )
			{
				REQUIRE( (*p).GetMessageCount() == 1 );
			}
		}
		AND_WHEN( "Priority category NOT activated" )
		{
			Lout::Get().SetThreshold( Warning() );
			Lout::Get().LogWithCategory( now, Debug(), "Prio", "Log message" );

			THEN( "Output not performed" )
			{
				REQUIRE( (*p).GetMessageCount() == 0 );
			}
		}
		AND_WHEN( "Priority category activated" )
		{
			Lout::Get().SetThreshold( Warning() );
			Lout::Get().ActivatePriorityCategory( "Prio" );
			Lout::Get().LogWithCategory( now, Debug(), "Prio", "Log message" );

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
		std::shared_ptr<IOutput> p = std::make_shared<FileOutput>( std::make_shared<formatting::DefaultFormatter>(), "output.log" );
		Lout::Get().RemoveAllOutputs();
		Lout::Get().AddOutput( p );
		Lout::Get().SetThreshold( Warning() );

		time_t now;
		time( &now );

		WHEN( "Log with enabled level" )
		{
			for( int i = 0; i < 1000; ++i )
			{
				Lout::Get().Log( now, Info(), "Goes to file" + std::to_string( i ) );
			}
		}
	}
}

SCENARIO( "Using operator to set log level" )
{
	GIVEN( "A newly created Lout" )
	{
		L.Reset();
		std::shared_ptr<IOutput> p = std::make_shared<TestOutput>();
		L.AddOutput( p );

		WHEN( "Level is not set" )
		{
			THEN( "Log level is 0" )
			{
				REQUIRE( p->GetThreshold() == NoLogging() );
			}
		}
		AND_WHEN( "Level is set" )
		{
			L.SetThreshold( Warning() );
			THEN( "Level matches set level" )
			{
				REQUIRE( p->GetThreshold() == Warning() );
			}
			AND_THEN( "Logging to a higher level, doesn't give an output" )
			{
				LL << Error() << "Error message";
				REQUIRE( p->GetMessageCount() == 0 );
			}
			AND_THEN( "We can log to that level" )
			{
				LL << Warning() << "This is logged as a warning message";
				REQUIRE( p->GetMessageCount() == 1 );
			}
		}
		AND_WHEN( "We set log level to Error and log to Verbose" )
		{
			L.SetThreshold( Error() );
			THEN( "nothing is printed" )
			{
				LL << Verbose() << "A verbose message";
				REQUIRE( p->GetMessageCount() == 0 );
			}
		}
		AND_WHEN( "We set log level to verbose" )
		{
			L.SetThreshold( Verbose() );
			THEN( "and log to the same level" )
			{
				LL << Verbose() << "A verbose message";
				REQUIRE( p->GetMessageCount() == 1 );
			}
		}
	}
}

SCENARIO("Logging using custom LogItem")
{
	GIVEN("A logger with one output")
	{
		L.Reset();
		auto p = std::make_shared<TestOutput>();
		L.AddOutput( p );
		L.SetThreshold(Info());

		WHEN("Logging using custom log type")
		{
			auto item = std::make_shared<TestItem>( "Foo", "Bar" );
			LL << Info() << item << Flush();

			THEN( "Output is the two arguments concatenated prefixed by the log level" )
			{
				REQUIRE( p->GetMessageCount() == 1 );
				REQUIRE( strstr( p->GetMsg(0).c_str(), "[Info]FooBar" ) != nullptr );
			}
		}
	}
}

SCENARIO( "Logging using custom Hex item" )
{
	GIVEN( "A logger with one output" )
	{
		L.Reset();
		auto p = std::make_shared<TestOutput>();
		L.AddOutput( p );
		L.SetThreshold( Info() );

		WHEN( "Logging using custom log type" )
		{
			auto item = std::make_shared<lout::item::Hex>( 0x123abc );
			LL << Info() << item << Flush();

			THEN( "Output is the value, as a hex string" )
			{
				REQUIRE( p->GetMessageCount() == 1 );
				REQUIRE( strstr( p->GetMsg( 0 ).c_str(), "[Info]123abc" ) != nullptr );
			}
		}
	}
}

SCENARIO( "Mandatory tags" )
{
	GIVEN( "A logger with one output" )
	{
		L.Reset();
		std::shared_ptr<IOutput> p = std::make_shared<TestOutput>();
		Lout::Get().AddOutput( p );
		L.SetThreshold( Info() );

		time_t now;
		time( &now );

		WHEN( "Log with too high level" )
		{
			LL << Warning() << "Warning message";
			THEN( "No output" )
			{
				REQUIRE( p->GetMessageCount() == 0 );
			}
		}
		AND_WHEN( "A mandatory tag is used" )
		{
			L.ActivatePriorityCategory( "MandatoryTag" );
			THEN( "Message is logged" )
			{
				L.LogWithCategory( now, Verbose(), "MandatoryTag", "Mandatory message" );
				REQUIRE( p->GetMessageCount() == 1 );
			}
		}
	}
}

SCENARIO( "Using operator overloads to log numbers" )
{
	GIVEN( "A logger with one output" )
	{
		L.Reset();
		std::shared_ptr<TestOutput> p = std::make_shared<TestOutput>();
		Lout::Get().AddOutput( p );
		L.SetThreshold( Info() );

		WHEN( "Using operator overload and scoping to force logging to commence" )
		{

			LL << Info() << 1;
			LL << Info() << 1.2F << " " << "This text goes on the same line as \"1.2\"";
			LL << Info() << 13.4L << " This text goes on the same line as \"13.4\"";
			LL << Info() << "Only this text on this line";
			LL << Info() << int8_t( 4 ) << " only a 4 before this text";
			LoutLogger( "A tag" ) << Info() << "This text is logged";
			LL << Warning() << "This text won't be logged";

			THEN( "Output performed" )
			{
				REQUIRE( p->GetMessageCount() == 6 );
				REQUIRE( strstr( p->GetMsg(0).c_str(), "[Info]1" ) != nullptr );
				REQUIRE( strstr( p->GetMsg(1).c_str(), "This text goes on the same line as \"1.2\"" ) != nullptr );
				REQUIRE( strstr( p->GetMsg(2).c_str(), "This text goes on the same line as \"13.4\"" ) != nullptr );
				REQUIRE( strstr( p->GetMsg(3).c_str(), "Only this text on this line" ) != nullptr );
				REQUIRE( strstr( p->GetMsg(4).c_str(), "4 only a 4 before this text" ) != nullptr );
				REQUIRE( strstr( p->GetMsg(5).c_str(), "This text is logged" ) != nullptr );
			}
		}
	}
}

SCENARIO( "Multi threading" )
{
	GIVEN( "A properly setup Lout and multiple threads" )
	{
		L.Reset();
		L.SetLocker( std::make_shared<threading::StdLock>() );
		std::shared_ptr<IOutput> p = std::make_shared<TestOutput>();
		std::shared_ptr<IOutput> p2 = std::make_shared<FileOutput>(std::make_shared<formatting::DefaultFormatter>(), "./thread.log");
		Lout::Get().AddOutput( p );
		Lout::Get().AddOutput(p2);
		L.SetThreshold( Warning() );

		WHEN( "Multiple threads are running" )
		{
			std::vector<std::unique_ptr<std::thread>> threads;

			int iterations = 100;

			auto worker_task = [ & ](int id) {
				for( int i = 0; i < iterations; ++i )
				{
					info << "Thread: " << id << " sample test" << " iteration: " << i;
				}

				warn << "Thread id: " << id << " terminating";
			};

			int threadCount = 50;

			for( int i = 0; i < threadCount; ++i )
			{
				threads.emplace_back( std::make_unique<std::thread>( worker_task, i ) );
			}

			for( auto& thread : threads )
			{
				thread->join();
			}

			THEN( "All outputs accounted for" )
			{
				REQUIRE( p->GetMessageCount() == (threadCount * iterations) + threadCount );
			}
		}
	}
}


SCENARIO( "Using categories" )
{
	GIVEN( "A properly setup Lout" )
	{
		L.Reset();
		L.SetLocker( std::make_shared<threading::StdLock>() );
		std::shared_ptr<TestOutput> p = std::make_shared<TestOutput>();
		Lout::Get().AddOutput( p );
		L.SetThreshold( Warning() );

		WHEN( "Log with category" )
		{
			std::string msg = "Text logged with category and level info";
			infoc( "A category" ) << msg << Flush();

			THEN( "Output performed" )
			{
				REQUIRE( p->GetMessageCount() == 1 );
				REQUIRE( strstr( p->GetMsg( 0 ).c_str(), ("[Info/A category]" + msg).c_str() ) != nullptr );
			}
		}

	}
}

SCENARIO( "Rolling file" )
{
	GIVEN( "A properly setup Lout with a roll over of 10 files" )
	{
		L.Reset();
		std::unique_ptr<DateTimeNameGiver> dt = std::make_unique<DateTimeNameGiver>( "FilePrefix-");
		std::shared_ptr<RollingFile> p = std::make_shared<RollingFile>( ".", std::move( dt ), std::make_shared<formatting::DefaultFormatter>(), util::Bytes( 500 ), 5 );
		Lout::Get().AddOutput( p );
		L.SetThreshold( Warning() );

		WHEN( "Logged enough data to roll ten times" )
		{
			for( int i = 0; i < 10; ++i ) {
				std::string data( 501, static_cast<char>( 'A' + i ) );
				info << data << Flush();
				// We must wait at least 1s so that the next log will get a new name.
				using namespace std::chrono_literals;
				std::this_thread::sleep_for( 1.1s );
			}

			THEN("Five files are found in the current directory")
			{
				REQUIRE( p->GetCurrentLogCount() == 5 );
			}
		}
	}
}

SCENARIO( "Colored output" )
{
	GIVEN( "A properly setup Lout" )
	{
		L.Reset();
		std::shared_ptr<ColoredStdOutput> p = std::make_shared<ColoredStdOutput>(std::make_shared<formatting::DefaultFormatter>());

		L.AddOutput( p );
		L.SetThreshold(Debug());

		WHEN( "Level has a color" )
		{
			p->SetLevelColor(Error(), rlutil::RED);
			p->SetLevelColor(Warning(), rlutil::YELLOW);

			THEN( "Output performed" )
			{
				LL << Warning() << "Warning message in YELLOW";
				LL << Error() << "Error message in RED";
				LL << Debug() << "Debug in normal color";
			}
		}

	}
}