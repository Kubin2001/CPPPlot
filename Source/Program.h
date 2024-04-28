#pragma once
#include <SDL.h>
#include <complex>
#include "Diagram.h"
#include "Function.h"
#include "Font.h"

class Program {
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
        double start = 0;
        double stop = 0;


    public:
        Program();

        void StartProgram();

        void CreateFunction(double start, double stop, std::vector<double> &vector, char color);

        void LoadTextures();

        void Events();

        void Exit(const Uint8* state);

        void Movement();

        void Render();

        void Start(int winX, int winY);

        void Show();

        SDL_Texture* load(const char* file, SDL_Renderer* ren);

        ~Program();
};
