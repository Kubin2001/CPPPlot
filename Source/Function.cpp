#include <iostream>
#include <SDL.h>
#include <string>
#include <math.h>
#include <cstdlib>
#include <complex>
#include "Function.h"
#include "Font.h"

Function::Function(Font *font, SDL_Renderer *renderer, int windowX, int windowY) {
    this->font = font;
    this->renderer = renderer;
    this->windowX = windowX;
    this->windowY = windowY;
}

SDL_Texture* Function::GetTexture() {
    return texture;
}

void Function::SetTexture(SDL_Texture * temptex) {
    texture = temptex;
}

SDL_Rect* Function::GetRectangle() {
    return &rectangle;
}

void Function::CalcMaxMin(double &max, double &min, std::vector<double>& fun) {
    for (int i = 0; i < fun.size(); i++)
    {
        if (fun[i] > yMax) {
            yMax = fun[i];

        }
        if (fun[i] < yMin) {
            yMin = fun[i];

        }
    }
    max = yMax;
    min = yMin;
}

void Function::CreateFunction(std::vector<double>& fun) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect2;
    double scaleX = static_cast<double>(fun.size()) / static_cast<double>(windowX - 100);
    //std::cout << scaleX << "ScaleX\n";
    //std::cout << fun.size() << "ScaleX\n";
    //std::cout << windowX << "ScaleX\n";

    int margin = windowY * 0.1;
    int usableWindowHeight = windowY - 150 - 2 * margin;

    float yRange = yMax - yMin;
    float scaleY = usableWindowHeight / yRange / 1.7;

    int funStart = 100;

    for (int i = funStart; i < windowX; i++)
    {
        GetRectangle()->x = i;
        GetRectangle()->y = ((fun[static_cast<int>((i - funStart) * scaleX)] * -1) * scaleY) + windowY / 2;
        GetRectangle()->w = 1;
        GetRectangle()->h = 1;
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);
        if (i > funStart) {
            SDL_RenderDrawLine(renderer, rect2.x, rect2.y, GetRectangle()->x, GetRectangle()->y);
        }
        //std::cout << GetRectangle()->x << "\n";
        //std::cout << GetRectangle()->y << "\n";
        rect2.x = GetRectangle()->x;
        rect2.y = GetRectangle()->y;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

double Function::GetMax() {
    return yMax;
}

double Function::GetMin() {
    return yMin;
}


