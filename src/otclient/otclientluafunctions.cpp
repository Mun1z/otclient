#include "otclient.h"

#include <framework/luascript/luainterface.h>
#include <otclient/core/game.h>
#include <otclient/core/datmanager.h>
#include <otclient/core/spritemanager.h>
#include <otclient/net/protocollogin.h>
#include <otclient/net/protocolgame.h>

void OTClient::registerLuaFunctions()
{
    g_lua.bindGlobalFunction("exit", std::bind(&OTClient::exit, &g_client));
    g_lua.bindGlobalFunction("setOnClose", std::bind(&OTClient::setOnClose, &g_client, _1));
    g_lua.bindGlobalFunction("importDat", std::bind(&DatManager::load, &g_dat, _1));
    g_lua.bindGlobalFunction("importSpr", std::bind(&SpriteManager::load, &g_sprites, _1));

    g_lua.registerClass<ProtocolLogin, Protocol>();
    g_lua.bindClassStaticFunction<ProtocolLogin>("create", &ProtocolLogin::create);
    g_lua.bindClassMemberFunction("login", &ProtocolLogin::login);
    g_lua.bindClassMemberFunction("cancelLogin", &ProtocolLogin::cancelLogin);

    g_lua.registerClass<ProtocolGame, Protocol>();

    g_lua.registerClass<Game>();
    g_lua.bindClassStaticFunction<Game>("loginWorld", std::bind(&Game::loginWorld, &g_game, _1, _2, _3, _4, _5));
}
