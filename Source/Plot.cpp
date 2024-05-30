#include <SDL.h>
#include <iostream>
#include "SDL_image.h"
#include <complex>

#include "Plot.h"
#include "Diagram.h"
#include "Font.h"

Plot::Plot() {
    window = nullptr;
    renderer = nullptr;
    diagram = nullptr;
    font = nullptr;
    function = nullptr;
}

void Plot::Tittle(std::string tittle) {
    int fontSize = 20;
    int xPos = (windowX *0.5) - ((tittle.length() * fontSize) *0.5);
    font->RenderText(renderer, tittle, xPos, 10, fontSize, fontSize, fontSize);
}

void Plot::CreateFunction(double start, double stop, std::vector<double>& vector, const char color) {
    fun = vector;
    this->start = start;
    this->stop = stop;
    Events();
    function->CreateFunction(fun,color);

}
void Plot::CreatePoints(double start, double stop, std::vector<double>& vector, const char color, const int size) {
    fun = vector;
    this->start = start;
    this->stop = stop;
    Events();
    function->CreatePoints(fun, color,size);

}

void Plot::Start(int winX, int winY) {
    if (winX > 300 && winX < 4000) {
        windowX = winX;
    }
    if (winY > 300 && winY < 4000) {
        windowY = winY;
    }
    StartProgram();
    SDL_RenderClear(renderer);
}

void Plot::Show() {
    Render();
    while (!end)
    {
        Movement();
    }
}

void Plot::StartProgram() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowX, windowY, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    font = new Font;
    font->LoadText(29, 29);
    diagram = new Diagram(font, renderer, windowX, windowY);
    function = new Function(font, renderer, windowX, windowY);
    LoadTextures();
}



void Plot::LoadTextures() {
    diagram->SetTextureDiagram(load("Textures/point.png", renderer));
    function->SetTexture(load("Textures/fun_point.png", renderer));
    font->SetTexture(load("Textures/font.png", renderer));
}

void Plot::Events() {
    diagram->SetUp();
    function->CalcMaxMin(max, min, plotMax, plotMin, fun);
}

void Plot::Exit(const Uint8* state) {
    if (state[SDL_SCANCODE_ESCAPE]) {
        end = true;
    }
}

void Plot::Movement() {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    Exit(state);
}

void Plot::Render() {
    diagram->Render();
    diagram->CreateYScale(function->GetMax(),function->GetMin(),plotMin,plotMax);
    diagram->CreateXScale(start,stop,100,windowX -200);
    SDL_RenderPresent(renderer);
}

SDL_Texture* Plot::load(const char* file, SDL_Renderer* ren) {
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

Plot::~Plot() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete diagram;
    delete function;
    delete font;
}
