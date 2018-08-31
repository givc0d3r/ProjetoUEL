#ifndef SCENE_MAINMENU_H
#define SCENE_MAINMENU_H

typedef struct SceneManager SceneManager;

#include "headers.h"
#include "scene_base.h"
#include "widgets.h"

typedef struct Scene_MainMenu {
    SDL_Texture* textTexture;
    SDL_Texture* textLogar;
    SDL_Texture* textModoOff;
	SDL_Rect renderQuad;
	SDL_Texture* textLogarOff;
	SDL_Texture* textModoOffOff;
	WTexture* seta;
    bool modoOff;
} Scene_MainMenu;

Scene_MainMenu* SceneMainMenu_new();

void SceneMainMenu_update(Scene_MainMenu* s);

void SceneMainMenu_handleEvent(Scene_MainMenu* s, SDL_Event* e);

void SceneMainMenu_destroy(Scene_MainMenu* s);

#endif