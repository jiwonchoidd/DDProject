#ifndef __WORLDSOCKETMGR_H
#define __WORLDSOCKETMGR_H

#include "SocketMgr.h"

class WorldSocket;

class TC_GAME_API WorldSocketMgr : public SocketMgr<WorldSocket>
{
	using BaseSocketMgr = SocketMgr<WorldSocket>;

public:
};

#define sWorldSocketMgr WorldSocketMgr::Instance()

#endif