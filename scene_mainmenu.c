#include "scene_mainmenu.h"

Scene_MainMenu* SceneMainMenu_new() {
    Scene_MainMenu* newScene = malloc(sizeof(Scene_MainMenu));
    //SDL_Surface* textSurface = TTF_RenderUTF8_Blended(gInfo.mainFont, "Testesao", color);
    
    SDL_Surface * textSurface = IMG_Load("BG_Login.png");//BACKGROUND LOGIN

    SDL_Color colorSelect = {255, 156, 0};//CORES INICIAIS DOS BOTÕES
    SDL_Color colorNotSelect = {255,255,255};

    newScene->textTexture = WD_CreateTexture();
    newScene->textLogar = WD_CreateTexture();
    newScene->textModoOff = WD_CreateTexture();
    newScene->textLogarOff = WD_CreateTexture();
    newScene->textModoOffOff = WD_CreateTexture();
    newScene->modoOff = false;
    newScene->seta = WD_CreateTexture();

    WD_TextureLoadFromFile(newScene->seta, "seta.png");
    WD_TextureLoadFromText(newScene->textLogar, "Logar" , gInfo.menuFont, colorSelect);
    WD_TextureLoadFromText(newScene->textLogarOff, "Logar", gInfo.menuFont, colorNotSelect);
    WD_TextureLoadFromText(newScene->textModoOff, "Modo offline", gInfo.menuFont, colorSelect);
    WD_TextureLoadFromText(newScene->textModoOffOff, "Modo offline", gInfo.menuFont, colorNotSelect);

    newScene->seta->h *= 0.5;
    newScene->seta->w *= 0.5;

    newScene->textTexture = SDL_CreateTextureFromSurface(gInfo.renderer, textSurface);
    int w = textSurface->w, h = textSurface->h;
    SDL_FreeSurface(textSurface);
    newScene->renderQuad.x =0;// (SCREEN_WIDTH - w) / 2;
    newScene->renderQuad.y =0;// (SCREEN_HEIGHT - h) / 2;
    newScene->renderQuad.w = w/2;
    newScene->renderQuad.h = h/2;
    return newScene;
}

void SceneMainMenu_update(Scene_MainMenu* s) {
    SDL_SetRenderDrawColor(gInfo.renderer, 0x12, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gInfo.renderer);
    SDL_RenderCopy(gInfo.renderer, s->textTexture, NULL, &s->renderQuad);
    SDL_SetRenderDrawColor(gInfo.renderer, 0x00, 0x00, 0x00, 0x00);
    TTF_SetFontOutline(gInfo.menuFont, 3);
    if (s->modoOff) {
        WD_TextureRender(s->textLogarOff, 325 / 2, 800 / 2);
        WD_TextureRender(s->textModoOff, 800 / 2, 800 / 2);
        WD_TextureRender(s->seta, 720 / 2, 806 / 2);
    }
    else {
        WD_TextureRender(s->textLogar, 325 / 2, 800 / 2);
        WD_TextureRender(s->textModoOffOff, 800 / 2, 800 / 2);
        WD_TextureRender(s->seta, 245 / 2, 806 / 2);
    }
    SDL_SetRenderDrawBlendMode(gInfo.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(gInfo.renderer, 0xFF, 0xFF, 0xFF, 100);
    SDL_Rect rect = {240, 290, 260, 26};
    SDL_RenderFillRect(gInfo.renderer, &rect);
    rect.y += 45;
    SDL_RenderFillRect(gInfo.renderer, &rect);
}

void SceneMainMenu_destroy(Scene_MainMenu* s) {
    SDL_DestroyTexture(s->textTexture);
    SDL_DestroyTexture(s->textLogar);
    SDL_DestroyTexture(s->textLogarOff);
    SDL_DestroyTexture(s->textModoOff);
    SDL_DestroyTexture(s->textModoOffOff);
    free(s);
}

void SceneMainMenu_handleEvent(Scene_MainMenu* s, SDL_Event* e) {
    if(sMng.inTransition)
        return;
    if(e->type == SDL_KEYDOWN) {
        if(e->key.keysym.sym == SDLK_RETURN && s->modoOff) {
            SceneManager_performTransition(DEFAULT_TRANSITION_DURATION, SCENE_SINGLEPLAYER);
        }if(e->key.keysym.sym == SDLK_RIGHT){
            //WD_TextureLoadFromText(newScene->textLogar, "Logar" , gInfo.menuFont, );
            //WD_TextureLoadFromText(newScene->textModoOff, "Modo Offline", gInfo.menuFont, colorOff);
            s->modoOff=true;
        }if(e->key.keysym.sym == SDLK_LEFT){
                //WD_TextureLoadFromText(newScene->textLogar, "Logar" , gInfo.menuFont, colorLogar);
                //WD_TextureLoadFromText(newScene->textModoOff, "Modo Offline", gInfo.menuFont, colorOff);
            s->modoOff=false;
        }
    }
}