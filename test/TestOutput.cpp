// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <memory>
#include "TestOutput.h"

TestOutput::TestOutput() :
        IOutput( std::make_shared<lout::formatting::DefaultFormatter>(),  nullptr ),
        myOutput()
{ }


void TestOutput::LogActual(const lout::loglevel::ILogLevel& level, const std::string& msg)
{
    std::stringstream s;
    s << "[" << level << "]" << msg;
    myOutput.push_back( s.str() );
}

void TestOutput::LogWithCategoryActual(const lout::loglevel::ILogLevel& level, const std::string& category,
                                   const std::string& msg)
{
    std::stringstream s;
    s << "[" << level << "/" << category << "]" << msg;
    myOutput.push_back( s.str() );
}

std::string TestOutput::GetMsg(size_t ix)
{
    return myOutput.at( ix );
}

