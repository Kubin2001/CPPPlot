#include <iostream>
#include <SDL.h>
#include <string>
#include "Font.h"
#include "Diagram.h"

extern int windowX;
extern int windowY;

Diagram::Diagram(Font* font, SDL_Renderer* renderer, int windowX, int windowY) {
    this->font = font;
    this->renderer = renderer;
    this->windowX = windowX;
    this->windowY = windowY;
}

SDL_Texture* Diagram::GetTextureDiagram() {
    return textureDiagram;
}


void Diagram::SetTextureDiagram(SDL_Texture * temptex) {
    textureDiagram = temptex;
}


SDL_Rect* Diagram::GetRectangleDiagram(int i) {
    return &rectangleDiagram[i];
}

SDL_Rect* Diagram::GetRectangleFunction() {
    return &rectangleFunction;
}

void Diagram::CreateYScale(double yMax, double yMin) {
    std::cout << "MAX: " << yMax<<"\n";
    std::cout << "MIN: " << yMin << "\n";
    double fullScale = (yMax - yMin) /3;
    //std::cout << "FULLSCALE: " << fullScale << "\n";
    double nArray[4];
    nArray[0] = yMin;
    nArray[3] = yMax;
    double temp = yMin +fullScale;
    nArray[1] = temp;
    temp += fullScale;
    nArray[2] = temp;
    int y = windowY - 200;
    for (int i = 0; i < 4; i++)
    {
        std::string str = std::to_string(nArray[i]);
        if (str.length() > 5)
        {
            str = str.substr(0, 6);
        }
        font->RenderText(renderer, str, 0, y, 14, 14, 15);
        y -= windowY / 4;
    }

}

void Diagram::CreateXScale(double start, double stop) {
    std::cout << "START: " << start<<"\n";
    std::cout << "STOP: " << stop << "\n";
    double fullScale = (stop - start) / 3;
    double nArray[4];
    nArray[0] = start;
    nArray[3] = stop;
    double temp = start + fullScale;
    nArray[1] = temp;
    temp += fullScale;
    nArray[2] = temp;
    int x = 120;
    for (int i = 0; i < 4; i++)
    {
        std::string str = std::to_string(nArray[i]);
        if (str.length() > 5)
        {
            str = str.substr(0, 6);
        }
        font->RenderText(renderer, str, x, windowY - 86, 14, 14, 15);
        x += (windowX / 4) + 30;
    }

}

void Diagram::SetUp() {
    GetRectangleDiagram(0)->x = 100;
    GetRectangleDiagram(0)->y = windowY * 0.5;
    GetRectangleDiagram(0)->w = windowX;
    GetRectangleDiagram(0)->h = 2;

    GetRectangleDiagram(1)->x = 600;
    GetRectangleDiagram(1)->y = 0;
    GetRectangleDiagram(1)->w = 2;
    GetRectangleDiagram(1)->h = 8;

    GetRectangleDiagram(2)->x = 100;
    GetRectangleDiagram(2)->y = 0;
    GetRectangleDiagram(2)->w = 2;
    GetRectangleDiagram(2)->h = windowY - 100;

    GetRectangleDiagram(3)->x = 100;
    GetRectangleDiagram(3)->y = windowY -100;
    GetRectangleDiagram(3)->w = windowX;
    GetRectangleDiagram(3)->h = 2;
}

void Diagram::Render() {
    RenderDiagram();
}

void Diagram::RenderDiagram() {
    SDL_RenderCopy(renderer, textureDiagram, NULL, &rectangleDiagram[0]);
    SDL_RenderCopy(renderer, textureDiagram, NULL, &rectangleDiagram[2]);
    SDL_RenderCopy(renderer, textureDiagram, NULL, &rectangleDiagram[3]);
}
