// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <output/IOutput.h>
#include <sstream>
#include <formatting/DefaultFormatter.h>
#include <vector>

class TestOutput : public lout::output::IOutput
{
public:
    TestOutput();

    void Flush() noexcept override
    { }

    void LogActual(const lout::loglevel::ILogLevel& level, const std::string& msg) override;

    void LogWithCategoryActual(const lout::loglevel::ILogLevel& level, const std::string& category,
                                       const std::string& msg) override;

    std::string GetMsg(size_t ix);

private:
    std::vector<std::string> myOutput;
};
