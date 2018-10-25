#ifndef SCENE_LOBBY_H
#define SCENE_LOBBY_H

typedef struct SceneManagerS SceneManagerS;

#include "headers.h"
#include "scene_base.h"
#include "widgets.h"
#include "network.h"
#include "map.h"

typedef struct Scene_Lobby {
    char playerNames[4][32];
    int pingCount;
    WTexture** players;
    WTexture* iniciar;
    WTexture* sair;
    Mix_Music* sound;
} Scene_Lobby;

Scene_Lobby* SceneLobby_new();

void SceneLobby_update(Scene_Lobby* s);

void SceneLobby_Receive(Scene_Lobby* s);

void SceneLobby_Disconnect(Scene_Lobby* s);

void SceneLobby_handleEvent(Scene_Lobby* s, SDL_Event* e);

void SceneLobby_destroy(Scene_Lobby* s);

#endif