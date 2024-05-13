#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <cmath>
#include <complex>
#include "Font.h"

class Function
{
    private:
        SDL_Renderer* renderer;
        std::vector<double> fun;
        SDL_Texture * texture = nullptr;
        SDL_Rect rectangle;
        Font* font;
        int windowX = 1000;
        int windowY = 1000;
        double yMax = 0;
        double yMin = 0;

    public:
        Function(Font* font, SDL_Renderer* renderer, int windowX, int windowY);

        SDL_Texture *GetTexture();
        void SetTexture(SDL_Texture* temptex);
        SDL_Rect* GetRectangle();

        void CreateFunction(std::vector<double>& fun, const char color);

        void CreatePoints(std::vector<double>& fun, const char color, const int size);

        void CalcMaxMin(double& max, double& min, std::vector<double>& fun);

        double GetMax();

        double GetMin();

};
