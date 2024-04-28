#include <SDL.h>
#include <iostream>
#include "SDL_image.h"
#include <complex>

#include "Program.h"
#include "Diagram.h"
#include "Font.h"

extern int windowX;
extern int windowY;

Program::Program() {
    window = nullptr;
    renderer = nullptr;
    diagram = nullptr;
    font = nullptr;
    function = nullptr;
}

void Program::CreateFunction(double start, double stop, std::vector<double>& vector, const char color) {
    fun = vector;
    this->start = start;
    this->stop = stop;
    Events();
    function->CreateFunction(fun,color);

}
void Program::Start(int winX, int winY) {
    if (winX > 300 && winX < 4000) {
        windowX = winX;
    }
    if (winY > 300 && winY < 4000) {
        windowY = winY;
    }
    StartProgram();
    SDL_RenderClear(renderer);
}

void Program::Show() {
    Render();
    while (!end)
    {
        Movement();
    }
}

void Program::StartProgram() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowX, windowY, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    font = new Font;
    font->LoadText(40, 29, 29);
    diagram = new Diagram(font, renderer, windowX, windowY);
    function = new Function(font, renderer, windowX, windowY);
    LoadTextures();
}



void Program::LoadTextures() {
    diagram->SetTextureDiagram(load("Textures/point.png", renderer));
    function->SetTexture(load("Textures/fun_point.png", renderer));
    font->SetTexture(load("Textures/font.png", renderer));
}

void Program::Events() {
    diagram->SetUp();
    function->CalcMaxMin(max, min, fun);
}

void Program::Exit(const Uint8* state) {
    if (state[SDL_SCANCODE_ESCAPE]) {
        end = true;
    }
}

void Program::Movement() {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    Exit(state);
}

void Program::Render() {
    diagram->Render();
    diagram->CreateYScale(function->GetMax(),function->GetMin());
    diagram->CreateXScale(start,stop);
    SDL_RenderPresent(renderer);
}

SDL_Texture* Program::load(const char* file, SDL_Renderer* ren) {
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

Program::~Program() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete diagram;
    delete function;
    delete font;
}
