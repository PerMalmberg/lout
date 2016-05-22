//
// Created by Per Malmberg on 2016-05-22.
//

#pragma once
#include <mutex>

namespace lout {
namespace threading {

// Interface for thread synchronization used by Lout
class ILock
{
public:
	virtual void Acquire() = 0;

	virtual void Release() = 0;
};

// A class that provides no lock for use in single-threaded applications.
class NoLock : public ILock
{
public:
	void Acquire() override {}
	void Release() override {}
};

// A class that provides lock via a mutex for use in multi-threaded applications
class Lock : public ILock
{
public:
	Lock();
	void Acquire() override;
	void Release() override;
private:
	std::recursive_mutex myMutex;
};

}
}
