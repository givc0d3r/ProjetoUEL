#include "headers.h"
#include "scene_base.h"
#include "network.h"

GameInfo gInfo;
SceneManager sMng;

// Tentar inicializar a biblioteca SDL e suas funcionalidades
bool initialize() {
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Falha ao inicializar o SDL! Erro: %s\n", SDL_GetError());
        success = false;
    } else {
        Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
        SDL_DisplayMode current;
        SDL_GetCurrentDisplayMode(0, &current);
        if (current.w >= 1920) {
            gInfo.screenMulti = 0.8;
        }
        else {
            gInfo.screenMulti = 0.5;
        }
        gInfo.screenWidth = 1440 * gInfo.screenMulti;
        gInfo.screenHeight = 1080 * gInfo.screenMulti;
        gInfo.window = SDL_CreateWindow("Projeto UEL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gInfo.screenWidth, gInfo.screenHeight, SDL_WINDOW_SHOWN);
        if(gInfo.window == NULL) {
            printf("Falha ao criar a janela! Erro: %s\n", SDL_GetError());
            success = false;
        } else {
            //SDL_SetWindowFullscreen(gInfo.window, SDL_WINDOW_FULLSCREEN);
            gInfo.renderer = SDL_CreateRenderer(gInfo.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gInfo.renderer == NULL) {
                printf("Falha ao criar o renderer! Erro: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(gInfo.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("Falha ao inicializar o SDL_image! Erro: %s\n", IMG_GetError());
                    success = false;
                }
                if(TTF_Init() == -1) {
                    printf("Falha ao inicializar o SDL_ttf! Erro: %s\n", TTF_GetError());
                    success = false;
                }
                if(!Network_InitSockets()) {
                    printf("Falha ao inicializar os módulos de conexão!\n");
                    success = false;
                }
            }
        }
    }
    return success;
}

// Destruir os elementos do SDL
void destroy() {
    SDL_DestroyRenderer(gInfo.renderer);
    gInfo.renderer = NULL;
    SDL_DestroyWindow(gInfo.window);
    gInfo.window = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    Network_ShutdownSockets();
}

int main(int argc, char* argv[]) {
    if(!initialize()) {
        printf("Falha ao inicializar!\n");
    } else {
        bool quit = false;
        gInfo.mainFont = TTF_OpenFont("content/Fipps-Regular.ttf", 36 * gInfo.screenMulti);
        gInfo.menuFont = TTF_OpenFont("content/Minecraft.ttf", 72 * gInfo.screenMulti);
        gInfo.inputFont = TTF_OpenFont("content/Minecraft.ttf", 46 * gInfo.screenMulti);
        SDL_RenderPresent(gInfo.renderer);
        sMng.currentScene = SCENE_MAINMENU;
        sMng.sMainMenu = SceneMainMenu_new();
        SDL_Event e;
        while(!quit) {
            while(SDL_PollEvent(&e) != 0) {
                if(e.type == SDL_QUIT) {
                    quit = true;
                } else {
                    SceneManager_handleEvent(&e);
                }
            }
            SceneManager_updateScene();
            SDL_RenderPresent(gInfo.renderer);
        }
        TTF_CloseFont(gInfo.mainFont);
        TTF_CloseFont(gInfo.menuFont);
        TTF_CloseFont(gInfo.inputFont);
        gInfo.mainFont = NULL;
        SceneManager_changeScene(SCENE_UNDEFINED);
    }
    destroy();
    return 0;
}