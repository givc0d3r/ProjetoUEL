#include "scene_mainmenu.h"

Scene_MainMenu* SceneMainMenu_new() {
    Scene_MainMenu* newScene = malloc(sizeof(Scene_MainMenu));
    newScene->enteringFrame = 0;
    newScene->frame = 0;

    SDL_Color colorSelected = {255, 156, 0}; // Cores dos botões quando selecionados
    SDL_Color colorNotSelected = {255,255,255}; // Cores dos botões quando não selecionados

    newScene->backgroundTexture = WD_CreateTexture();
    newScene->textLogar = WD_CreateTexture();
    newScene->textModoOff = WD_CreateTexture();
    newScene->textLogarOff = WD_CreateTexture();
    newScene->textModoOffOff = WD_CreateTexture();
    newScene->seta = WD_CreateTexture();
    newScene->modoOff = false;
    newScene->index=0; // Começar no login

    WD_TextureLoadFromFile(newScene->seta, "seta.png");
    WD_TextureLoadFromText(newScene->textLogar, "Logar" , gInfo.menuFont, colorSelected);
    WD_TextureLoadFromText(newScene->textLogarOff, "Logar", gInfo.menuFont, colorNotSelected);
    WD_TextureLoadFromText(newScene->textModoOff, "Modo offline", gInfo.menuFont, colorSelected);
    WD_TextureLoadFromText(newScene->textModoOffOff, "Modo offline", gInfo.menuFont, colorNotSelected);

    newScene->seta->h *= 0.5;
    newScene->seta->w *= 0.5;

    WD_TextureLoadFromFile(newScene->backgroundTexture, "BG_Login.png");
    int w = newScene->backgroundTexture->w, h = newScene->backgroundTexture->h;
    newScene->renderQuad.x = 0;
    newScene->renderQuad.y = 0;
    newScene->renderQuad.w = w/2;
    newScene->renderQuad.h = h/2;
    SDL_Color black = {0, 0, 0, 255};
    newScene->login = WD_CreateTextBox(240, 290, 260, 26, 30, gInfo.inputFont, black, false);
    newScene->senha = WD_CreateTextBox(240, 335, 260, 26, 30, gInfo.inputFont, black, true);

    SDL_StartTextInput();
    
    return newScene;
}

void SceneMainMenu_update(Scene_MainMenu* s) {
    SDL_SetRenderDrawColor(gInfo.renderer, 0x12, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gInfo.renderer);
    WD_TextureRenderDest(s->backgroundTexture, &s->renderQuad);
    SDL_SetRenderDrawColor(gInfo.renderer, 0x00, 0x00, 0x00, 0x00);

    WD_TextureRender(s->textLogarOff, 325 / 2, 800 / 2); //Começa com os dois botoes brancos
    WD_TextureRender(s->textModoOffOff, 800 / 2, 800 / 2);

    if (s->modoOff && s->index==2) {
        WD_TextureRender(s->textLogarOff, 325 / 2, 800 / 2);
        WD_TextureRender(s->textModoOff, 800 / 2, 800 / 2);
        WD_TextureRender(s->seta, 720 / 2, 806 / 2);
    }
    else if(!s->modoOff && s->index==2) {
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
    if(s->index == 0) {
        s->login->active = true;
    } else {
        s->login->active = false;
    }
    if(s->index == 1) {
        s->senha->active = true;
    } else {
        s->senha->active = false;
    }
    WD_TextBoxRender(s->login, s->frame);
    WD_TextBoxRender(s->senha, s->frame);
    if(s->enteringFrame < 25) {
        SDL_SetRenderDrawColor(gInfo.renderer, 0x00, 0x00, 0x00, 255 - 10 * s->enteringFrame);
        SDL_Rect fillRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderFillRect(gInfo.renderer, &fillRect);
        s->enteringFrame++;
    }
    s->frame++;
    if(s->frame >= 60) {
        s->frame = 0;
    }
}

void SceneMainMenu_destroy(Scene_MainMenu* s) {
    WD_TextureDestroy(s->backgroundTexture);
    WD_TextureDestroy(s->textLogar);
    WD_TextureDestroy(s->textLogarOff);
    WD_TextureDestroy(s->textModoOff);
    WD_TextureDestroy(s->textModoOffOff);
    WD_TextBoxDestroy(s->login);
    WD_TextBoxDestroy(s->senha);
    SDL_StopTextInput();
    free(s);
}

void SceneMainMenu_handleEvent(Scene_MainMenu* s, SDL_Event* e) {
    if(sMng.inTransition)
        return;
    if(e->type == SDL_KEYDOWN) {
        if(e->key.keysym.sym == SDLK_RETURN && s->modoOff && s->index == 2 ) {
            SceneManager_performTransition(DEFAULT_TRANSITION_DURATION, SCENE_SINGLEPLAYER);
        }else if(e->key.keysym.sym == SDLK_RIGHT && s->index == 2 || e->key.keysym.sym == SDLK_LEFT && s->index == 2 ){
            s->modoOff = !s->modoOff;
        }else if((e->key.keysym.sym == SDLK_DOWN || e->key.keysym.sym == SDLK_TAB) && s->index < 2){
            s->index++;
        }else if(e->key.keysym.sym == SDLK_UP && s->index > 0){
            s->index--;
        }
    }
    WD_TextBoxHandleEvent(s->login, e);
    WD_TextBoxHandleEvent(s->senha, e);
}