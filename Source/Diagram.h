#pragma once
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include "Font.h"


class Diagram
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture* textureDiagram = nullptr;
        SDL_Rect rectangleDiagram[4];
        SDL_Rect rectangleFunction;
        Font* font = nullptr;
        
        int windowX = 1000;
        int windowY = 1000;

    public:
        Diagram(Font* font, SDL_Renderer* renderer, int windowX, int windowY);
        SDL_Texture* GetTextureDiagram();
        void SetTextureDiagram(SDL_Texture* temptex);
        SDL_Rect* GetRectangleDiagram(int i);
        SDL_Rect* GetRectangleFunction();
        void Render();

        void CreateYScale(double yMax, double yMin);

        void CreateXScale(double start, double stop);

        void SetUp();

        void RenderDiagram();
};