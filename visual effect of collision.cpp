#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Function to draw a circle
void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

// Function to check collision between two circles
bool checkCollision(int x1, int y1, int x2, int y2, int radius1, int radius2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int distance = sqrt(dx*dx + dy*dy);
    return distance <= (radius1 + radius2);
}

int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Colliding Circles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Clear the window
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    SDL_RenderClear(renderer);

    // Initial values for the circles
    int centerY1 = 300; // Y-coordinate of the first circle's center
    int centerY2 = 0;   // Y-coordinate of the second circle's center
    int radius = 50;    // Radius of the circles
    int centerX1 = 200; // X-coordinate of the first circle's center
    int centerX2 = 400; // X-coordinate of the second circle's center

    // Color for the circles
    SDL_Color color1 = {255, 105, 180, 255}; // Pink color for the first circle
    SDL_Color color2 = {0, 0, 255, 255};     // Blue color for the second circle
    bool collided = false; // Flag to track collision state

    // Main loop
    int quit = 0;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            // Handle keyboard events
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        centerY2 -= 10; // Move the second circle up
                        break;
                    case SDLK_DOWN:
                        centerY2 += 10; // Move the second circle down
                        break;
                    case SDLK_LEFT:
                        centerX2 -= 10; // Move the second circle left
                        break;
                    case SDLK_RIGHT:
                        centerX2 += 10; // Move the second circle right
                        break;
                }
            }
        }

        // Clear the window
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        SDL_RenderClear(renderer);

        // Check collision between the circles
        bool collision = checkCollision(centerX1, centerY1, centerX2, centerY2, radius, radius);

        // Draw the circles
        drawCircle(renderer, centerX1, centerY1, radius, color1); // First circle

        // If collision detected, change color and increase size of the second circle
        if (collision && !collided) {
            color2.r = 255; // Change color to red
            color2.g = 0;
            color2.b = 0;
            radius += 10; // Increase radius temporarily
            collided = true; // Set collided flag
        } else if (!collision && collided) {
            // Reset color and size of the second circle
            color2.r = 0; // Reset color to blue
            color2.g = 0;
            color2.b = 255;
            radius = 50; // Reset radius
            collided = false; // Reset collided flag
        }
        drawCircle(renderer, centerX2, centerY2, radius, color2); // Second circle

        // Render the circles
        SDL_RenderPresent(renderer);

        // Delay to control animation speed
        SDL_Delay(10);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
