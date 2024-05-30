#pragma once
#include <SDL.h>
#include "Diagram.h"
#include "Function.h"
#include "Font.h"

class Plot {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Diagram* diagram;
        Function* function;
        Font* font;
        std::vector<double> fun;
        bool end = false;
        int windowX = 1000;
        int windowY = 1000;
        double max = 0;
        double min = 0;
        double plotMax = 0;
        double plotMin = 0;
        double start = 0;
        double stop = 0;

        void StartProgram();

        void LoadTextures();

        void Events();

        void Render();

        SDL_Texture* load(const char* file, SDL_Renderer* ren);

        void Exit(const Uint8* state);


    public:
        Plot();

        void Tittle(std::string tittle);

        void CreateFunction(double start, double stop, std::vector<double> &vector, char color);

        void CreatePoints(double start, double stop, std::vector<double>& vector, const char color,const int size);

        void Movement();

        void Start(int winX, int winY);

        void Show();

        ~Plot();
};
