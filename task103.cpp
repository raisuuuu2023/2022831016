#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; 
            int dy = radius - h; 
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

bool checkCollision(int x1, int y1, int x2, int y2, int radius1, int radius2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int distance = sqrt(dx*dx + dy*dy);
    return distance <= (radius1 + radius2);
}

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Collision Detection", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderClear(renderer);

    int radius = 30;    
    int centerY1 = WINDOW_HEIGHT / 2; 
    int centerY2 = radius;   
    int centerX1 = radius;
    int centerX2 = WINDOW_WIDTH / 2; 

    SDL_Color color1 = {255, 105, 180, 255}; 
    SDL_Color color2 = {0, 0, 255, 255};     

    bool quit = false;
    bool collision = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        centerY2 -= 10; 
                        break;
                    case SDLK_DOWN:
                        centerY2 += 10; 
                        break;
                    case SDLK_LEFT:
                        centerX2 -= 10; 
                        break;
                    case SDLK_RIGHT:
                        centerX2 += 10; 
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        SDL_RenderClear(renderer);

        drawCircle(renderer, centerX1, centerY1, radius, color1); 
        drawCircle(renderer, centerX2, centerY2, radius, color2); 

        collision = checkCollision(centerX1, centerY1, centerX2, centerY2, radius, radius);

        if (collision) {
            color2.r = 255; 
            color2.g = 0;
            color2.b = 0;
        } else {

            color2.r = 0; 
            color2.g = 0;
            color2.b = 255;
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}