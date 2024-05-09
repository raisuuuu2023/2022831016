#include <SDL.h>
#include <cmath>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CIRCLE_RADIUS = 10;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Moving Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return 1;
    }

    SDL_Event event;
    bool quit = false;
    float angle = 0.0f;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Calculate circle position
        int x = SCREEN_WIDTH / 2 + static_cast<int>(50 * cos(angle));
        int y = SCREEN_HEIGHT / 2 + static_cast<int>(50 * sin(angle));

        // Draw the circle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = -CIRCLE_RADIUS; i <= CIRCLE_RADIUS; ++i) {
            for (int j = -CIRCLE_RADIUS; j <= CIRCLE_RADIUS; ++j) {
                if (i * i + j * j <= CIRCLE_RADIUS * CIRCLE_RADIUS) {
                    SDL_RenderDrawPoint(renderer, x + i, y + j);
                }
            }
        }

        // Update angle
        angle += 0.02f;

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}