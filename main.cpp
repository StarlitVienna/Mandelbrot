#include <SDL2/SDL_render.h>
#include <iostream>
#include <complex>
#include <numeric>
#include <SDL2/SDL.h>
#include "mandelbrot.hpp"

const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 700;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

bool init();
void close();

int main( int argc, char* args[] ) {
    std::complex<long double> c(0.0, 0.0);
    std::complex<long double> z(0.0, 0.0);

    if ( !init() ) {
        std::cerr << "Initialization failed" << std::endl;
    } else {
        bool quit = false;
        SDL_Event event;
        SDL_RenderSetLogicalSize( renderer, WINDOW_WIDTH, WINDOW_HEIGHT );
        Mandelbrot fractal( z.real(), z.imag(), c.real(), c.imag(), WINDOW_WIDTH, WINDOW_HEIGHT, renderer );
        fractal.set_render( renderer );

        int mouse_x = 0;
        int mouse_y = 0;

        int max_iter = 20;
        int iter_increase = 1;
        fractal.generate( max_iter );

        while ( !quit ) {
            while ( SDL_PollEvent ( &event ) != 0 ) {
                if ( event.type == SDL_QUIT ) {
                    quit = true;
                } else if ( event.type == SDL_KEYDOWN ) {
                    switch( event.key.keysym.sym ) {

                        case SDLK_q:
                            max_iter+=iter_increase;
                            fractal.generate( max_iter );
                            std::cout << max_iter << std::endl;
                            break;

                        case SDLK_UP:
                            ++max_iter;
                            fractal.generate( max_iter );
                            std::cout << "Iter increase --> " << iter_increase << std::endl;
                            break;

                        case SDLK_DOWN:
                            --max_iter;
                            fractal.generate( max_iter );
                            std::cout << "Iter increase --> " << iter_increase << std::endl;
                            break;
                    }

                } else if ( event.type == SDL_MOUSEBUTTONDOWN ) {
                    switch ( event.button.button ) {
                        case SDL_BUTTON_LEFT:
                            SDL_GetMouseState( &mouse_x, &mouse_y );
                            fractal.set_cords(mouse_x, mouse_y);
                            fractal.update_range();
                            fractal.generate( max_iter );
                            max_iter+=20;
                            //std::cout << "Worok" << std::endl;
                            break;
                    }
                }
            }
            SDL_RenderPresent( renderer );
        }
    }

    return 0;
}

bool init() {
    bool success = true;
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 ) {
        std::cerr << "SDL could not be initialized --> " << SDL_GetError() << std::endl;
        success = false;
    } else {
        window = SDL_CreateWindow( "Starlust", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if ( window == NULL ) {
            std::cerr << "Window was not created --> " << SDL_GetError() << std::endl;
            success = false;
        } else {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if ( renderer == NULL ) {
                std::cerr << "Something went wrong while creating the renderer --> " << SDL_GetError() << std::endl;
                success = false;
            } else {
                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                SDL_RenderClear( renderer );
                SDL_RenderPresent( renderer );
            }
        }
    }
    return success;
}

void close() {
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );

    renderer = NULL;
    window = NULL;

    SDL_Quit();
}
