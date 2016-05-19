//
// Created by Per Malmberg on 2016-05-06.
//

#define CATCH_CONFIG_MAIN

#include "../externals/Catch/include/catch.hpp"
#include "output/FileOutput.h"
#include "lout.h"

using namespace com::codezeal::logging;

enum class MyOwnLogLevel
{
	Info,
	Warning
};

using ILogPrinter = ILoutOutput<MyOwnLogLevel>;
using Logger = Lout<MyOwnLogLevel>;
using FileOutput = com::codezeal::logging::printer::FileOutput<MyOwnLogLevel>;

class StdOutPrinter : public ILogPrinter
{
public:
	StdOutPrinter() :
		ILoutOutput<MyOwnLogLevel>( &std::cerr ) {}

	void LogActual(MyOwnLogLevel level, const std::string& msg) override
	{
		std::cout << "[" << static_cast<int>(level) << "]" << msg << std::endl;
	}

	void LogWithTagActual(MyOwnLogLevel level, const std::string& tag, const std::string& msg) override
	{
		std::cout << "[" << static_cast<int>(level) << "][" << tag << "]" << msg << std::endl;
	}

	void Flush() noexcept override
	{
		std::cout.flush();
	}
};

SCENARIO( "Setting up a logger" )
{
	GIVEN( "A clean slate" )
	{
		auto& a = Logger::Get();

		THEN( "Program compiles" )
		{
			REQUIRE( a.GetLevel() == MyOwnLogLevel::Info );
			a.Log( MyOwnLogLevel::Info, "Goes nowhere" );
		}
		AND_THEN( "Can set log level" )
		{
			a.SetLevel( MyOwnLogLevel::Warning );
			REQUIRE( a.GetLevel() == MyOwnLogLevel::Warning );
		}
	}
}

SCENARIO( "Adding a printer" )
{
	GIVEN( "A clean slate" )
	{
		WHEN("A printer is added")
		{
			std::shared_ptr<ILogPrinter> p = std::make_shared<StdOutPrinter>();
			Logger::Get().AddOutput( p );

			THEN( "Printer count is increased" )
			{
				REQUIRE( Logger::Get().GetPrinterCount() == 1 );
			}
		}
	}
}

SCENARIO("Regular logging")
{
	GIVEN("A logger with a printer")
	{
		std::shared_ptr<ILogPrinter> p = std::make_shared<StdOutPrinter>();
		Logger::Get().AddOutput( p );
		Logger::Get().SetLevel( MyOwnLogLevel::Info );

		WHEN("Logging on too high level") {
			Logger::Get().Log( MyOwnLogLevel::Warning, "Log message");

			THEN( "No output performed") {
				REQUIRE(p.get()->GetMessageCount() == 0 );
			}
		}
		WHEN("Logging on correct level") {
			Logger::Get().Log( MyOwnLogLevel::Info, "Log message");

			THEN("Output performed") {
				REQUIRE((*p).GetMessageCount() == 1 );
			}
		}
		WHEN("Increasing log level") {
			Logger::Get().SetLevel( MyOwnLogLevel::Warning);

			THEN("We can log on that level too") {
				std::string s = "Warning message";
				char buff[50];
				s.append( _itoa( __LINE__, buff, 10 ));

				Logger::Get().Log( MyOwnLogLevel::Warning, s );
				REQUIRE((*p).GetMessageCount() == 1 );
			}
		}
	}
}

SCENARIO("Logging with tag")
{
	GIVEN("A logger with a printer")
	{
		std::shared_ptr<ILogPrinter> p = std::make_shared<StdOutPrinter>();
		Logger::Get().AddOutput( p );
		Logger::Get().SetLevel( MyOwnLogLevel::Warning );

		WHEN("Logging called without activating tag") {
			Logger::Get().LogWithTag( MyOwnLogLevel::Info, "NonActiveTag", "Log message");

			THEN( "No output performed") {
				REQUIRE((*p).GetMessageCount() == 0 );
			}
		}
		AND_WHEN("Tag activated") {
			Logger::Get().ActivateTag( "ActiveTag");
			Logger::Get().LogWithTag( MyOwnLogLevel::Info, "ActiveTag", "Log message");

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
		std::shared_ptr<ILogPrinter> p = std::make_shared<FileOutput>( "output.log" );
		Logger::Get().RemoveAllOutputs();
		Logger::Get().AddOutput( p );
		Logger::Get().SetLevel( MyOwnLogLevel::Warning );

		WHEN("Log with enabled level")
		{
			for( int i = 0; i < 1000; ++i)
			{
				Logger::Get().Log( MyOwnLogLevel::Info, "Goes to file" + std::to_string( i ) );
			}
		}
	}
}