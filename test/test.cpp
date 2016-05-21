//
// Created by Per Malmberg on 2016-05-06.
//

#define CATCH_CONFIG_MAIN

#include <output/StdOutput.h>
#include "../externals/Catch/include/catch.hpp"
#include "output/FileOutput.h"
#include "lout.h"
#include "loglevel/defaultLevels.h"

using namespace lout;
using namespace lout::loglevel;
using namespace lout::output;

using FileOutput = lout::output::FileOutput;

SCENARIO( "Setting up a logger" )
{
	GIVEN( "A clean slate" )
	{
		Lout& a = Lout::Get();

		THEN( "Program compiles" )
		{
			REQUIRE( a.GetLevel().GetLevel() == 0 );
			a.Log( Verbose(), "Goes nowhere" );
		}
		AND_THEN( "Can set log level" )
		{
			a.SetLevel( Warning() );
			REQUIRE( a.GetLevel() == Warning() );
		}
	}
}

SCENARIO( "Adding a printer" )
{
	GIVEN( "A clean slate" )
	{
		WHEN("A printer is added")
		{
			std::shared_ptr<ILoutOutput> p = std::make_shared<StdOutPrinter>();
			Lout::Get().AddOutput( p );

			THEN( "Printer count is increased" )
			{
				REQUIRE( Lout::Get().GetPrinterCount() == 1 );
			}
		}
	}
}

SCENARIO("Regular logging")
{
	GIVEN("A logger with a printer")
	{
		std::shared_ptr<ILoutOutput> p = std::make_shared<StdOutPrinter>();
		Lout::Get().AddOutput( p );
		Lout::Get().SetLevel( Info() );

		WHEN("Logging on too high level") {
			Lout::Get().Log( Warning(), "Log message");

			THEN( "No output performed") {
				REQUIRE(p.get()->GetMessageCount() == 0 );
			}
		}
		WHEN("Logging on correct level") {
			Lout::Get().Log( Info(), "Log message");

			THEN("Output performed") {
				REQUIRE((*p).GetMessageCount() == 1 );
			}
		}
		WHEN("Increasing log level") {
			Lout::Get().SetLevel( Warning() );

			THEN("We can log on that level too") {
				std::string s = "Warning message";
				char buff[50];
				s.append( _itoa( __LINE__, buff, 10 ));

				Lout::Get().Log( Warning(), s );
				REQUIRE((*p).GetMessageCount() == 1 );
			}
		}
	}
}

SCENARIO("Logging with tag")
{
	GIVEN("A logger with a printer")
	{
		std::shared_ptr<ILoutOutput> p = std::make_shared<StdOutPrinter>();
		Lout::Get().AddOutput( p );
		Lout::Get().SetLevel( Warning() );

		WHEN("Logging called without activating tag") {
			Lout::Get().LogWithTag( Info(), "NonActiveTag", "Log message");

			THEN( "No output performed") {
				REQUIRE((*p).GetMessageCount() == 0 );
			}
		}
		AND_WHEN("Tag activated") {
			Lout::Get().ActivateTag( "ActiveTag");
			Lout::Get().LogWithTag( Info(), "ActiveTag", "Log message");

			THEN("Output performed") {
				REQUIRE((*p).GetMessageCount() == 1 );
			}
		}
	}
}

SCENARIO("Using FileOutput")
{
	GIVEN("A logger with a file output  writer")
	{
		std::shared_ptr<ILoutOutput> p = std::make_shared<FileOutput>( "output.log" );
		Lout::Get().RemoveAllOutputs();
		Lout::Get().AddOutput( p );
		Lout::Get().SetLevel( Warning() );

		WHEN("Log with enabled level")
		{
			for( int i = 0; i < 1000; ++i)
			{
				Lout::Get().Log( Info(), "Goes to file" + std::to_string( i ) );
			}
		}
	}
}