#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include "SDL_image.h"
#include "Font.h"


class Diagram
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture* textureDiagram = nullptr;
        std::vector <SDL_Rect> rectangleDiagram;
        SDL_Rect rectangleFunction;
        Font* font = nullptr;
        
        int windowX = 0;
        int windowY = 0;

    public:
        Diagram(Font* font, SDL_Renderer* renderer, int windowX, int windowY);
        SDL_Texture* GetTextureDiagram();
        void SetTextureDiagram(SDL_Texture* temptex);
        SDL_Rect* GetRectangleDiagram(int i);
        SDL_Rect* GetRectangleFunction();
        void Render();

        void CreateYScale(double yMax, double yMin, double plotMin, double plotMax);

        void CreateXScale(double yMax, double yMin, double plotMin, double plotMax);

        void SetUp();

        void RenderDiagram();
};