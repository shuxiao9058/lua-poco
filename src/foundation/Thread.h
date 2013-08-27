#ifndef LUA_POCO_THREAD_H
#define LUA_POCO_THREAD_H

#include "LuaPoco.h"
#include "Userdata.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"

namespace LuaPoco
{

class ThreadUserdata : public Userdata, public Poco::Runnable
{
public:
	ThreadUserdata();
	virtual ~ThreadUserdata();
	virtual UserdataType getType();
	// register metatable for this class
	static bool registerThread(lua_State* L);
	void run();
	
private:
	// constructor function 
	static int Thread(lua_State* L);
	
	// metamethod infrastructure
	static int metamethod__gc(lua_State* L);
	static int metamethod__tostring(lua_State* L);
	
	// userdata methods
	static int name(lua_State* L);
	static int priority(lua_State* L);
	static int id(lua_State* L);
	static int isRunning(lua_State* L);
	static int join(lua_State* L);
	static int stackSize(lua_State* L);
	static int start(lua_State* L);
	
	Poco::Thread mThread;
	lua_State* mThreadState;
	bool mJoined;
	bool mStarted;
	int mParamCount;
	int mThreadResult;
};

} // LuaPoco

#endif