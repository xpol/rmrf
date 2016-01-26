#include <lua.h>
#include <lauxlib.h>
#include "rmrf.h"

static int rmrf_rmrf(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    int r = rmrf(path);
    if (r == 0)
        lua_pushboolean(L, 1);
    else
        lua_pushnil(L);
    return 1;
}

static const luaL_Reg apis[] = {
    { "rmrf", rmrf_rmrf },
    { NULL, NULL }
};

static int rmrf_meta_call(lua_State* L)
{
    // args for meta call is: module, arg1, arg2...
    // replace mdoule with rmrf.rmrf
    int nargs = lua_gettop(L) - 1;
    lua_getfield(L, lua_upvalueindex(1), "rmrf");
    lua_replace(L, 1);
    lua_call(L, nargs, LUA_MULTRET);
    return lua_gettop(L);
}


LUALIB_API int luaopen_rmrf(lua_State *L)
{
    lua_createtable(L, 0, sizeof(apis)/sizeof(apis[0]) - 1); // module table

#if LUA_VERSION_NUM >= 502 // LUA 5.2 or above
	luaL_setfuncs(L, apis, 0);
#else
	luaL_register(L, NULL, apis);
#endif

    lua_createtable(L, 0, 1); // metatable

    lua_pushvalue(L, -2); // duplicate the module table.
    lua_pushcclosure(L, rmrf_meta_call, 1);
    lua_setfield(L, -2, "__call");

    lua_setmetatable(L, -2);
    return 1;
}
