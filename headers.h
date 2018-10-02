#ifndef HEADERS_H
#define HEADERS_H

#define PLATFORM_WINDOWS 1
#define PLATFORM_MAC     2
#define PLATFORM_UNIX    3

#if defined(_WIN32)
    #define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define PLATFORM PLATFORM_MAC
#else
    #define PLATFORM PLATFORM_UNIX
#endif

#if PLATFORM == PLATFORM_WINDOWS
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Duração padrao da transiçao (em frames)
#define DEFAULT_TRANSITION_DURATION 10
// Número de camadas do mapa
#define MAP_LAYERS 2
// Tamanho (em pixels) de cada tile (quadrado)
#define TILE_SIZE 32
// Comprimento da imagem do Tileset
#define TILESET_WIDTH 256
// Tickrate do servidor (por segundo)
#define SERVER_TICKRATE 120
// Quantidade de partes que o os tiles serão divididos para movimentação dos personagens
#define MOVEMENT_PARTS 4

typedef struct Address Address;

// Estrutura que carrega os elementos globais do programa
typedef struct GameInfo {
    // Janela global
    SDL_Window* window;
    // Superfície global
    SDL_Surface* screenSurface;
    // Renderizador global
    SDL_Renderer* renderer;
    // Comprimento da tela
    int screenWidth;
    // Altura da tela
    int screenHeight;
    // Taxa de atualização da tela
    int screenFreq;
    // Controle da resolução e escalonamento
    double screenMulti;
    // Fonte principal
    TTF_Font* mainFont;
    // Fonte telaLogin
    TTF_Font* telaLogin;
    // Fonte de entrada de texto
    TTF_Font* inputFont;
    // Fonte mainmenu
    TTF_Font* mainMenu;
    // Fonte mainmenu - botoes
    TTF_Font* mainMenu_botoes;
    // Fontes lobby
    TTF_Font* lobbyFonte;
    TTF_Font* lobbyName;
    TTF_Font* lobbyFontd;
    // Modo debug
    bool debug;

    TTF_Font* rank;

    bool connectedToServer;
    bool serverHost;
    Address* serverAddress;

    int sockFd;
} GameInfo;

typedef struct SceneManager SceneManager;

extern GameInfo gInfo;
extern SceneManager sMng;

#endif