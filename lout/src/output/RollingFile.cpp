//
// Created by Per Malmberg on 2016-05-25.
//

#include <iostream>
#include <util/Sizes.h>
#include "output/RollingFile.h"


namespace lout {
namespace output {

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
RollingFile::RollingFile(const std::string& pathToOutputFolder, std::unique_ptr<IRollingFileName> nameGiver,
                         util::Bytes maximumLogSize)
		: RollingFile( pathToOutputFolder, std::move( nameGiver ), maximumLogSize, &std::cerr )
{

}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
RollingFile::RollingFile(const std::string& pathToOutputFolder, std::unique_ptr<IRollingFileName> nameGiver,
                         util::Bytes maximumLogSize, std::ostream* fallbackStream)
		: IOutput( fallbackStream ), myPathToOutputFolder(pathToOutputFolder), myOutput(), myNameGiver( std::move( nameGiver ) ),
		  myMaximumLogSize( maximumLogSize )
{

}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
RollingFile::~RollingFile()
{

}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void RollingFile::Flush() noexcept
{
	if( myOutput ) {
		myOutput->Flush();
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void RollingFile::LogActual(const loglevel::ILogLevel& level, const std::string& msg)
{
	Open();

	if( myOutput ) {
		myOutput->Log(level, msg );
	}

	Roll();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void RollingFile::LogWithCategoryActual(const loglevel::ILogLevel& level, const std::string& category,
                                        const std::string& msg)
{
	Open();

	if( myOutput ) {
		myOutput->LogWithCategory(level, category, msg );
	}

	Roll();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void RollingFile::Roll()
{
	if( myOutput && myOutput->GetCurrentSize() > myMaximumLogSize.GetBytes()) {
		myOutput->Close();
		myOutput.reset( nullptr);
		Open();
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void RollingFile::Open()
{
	if( !myOutput)
	{
		myOutput = std::make_unique<FileOutput>( PathCombine( myPathToOutputFolder, myNameGiver->GetNextName() ) );
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
std::string RollingFile::PathCombine( const std::string& p1, const std::string& p2)
{
#if defined( _WIN32 ) || defined( __CYGWIN__ )
	const char pathSeparator = '\\';
#else
	const char pathSeparator = '/';
#endif

	std::string path = p1;

	if( path.length() > 0) {
		if( path.at( p1.length()-1 ) != pathSeparator) {
			path += pathSeparator;
		}
	}

	path += p2;

	return path;
}


}
}