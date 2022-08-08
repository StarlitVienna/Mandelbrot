#include "mandelbrot.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <complex>

Mandelbrot::Mandelbrot( long double z_real, long double z_imag, long double c_real, long double c_imag, int base_width, int base_height, SDL_Renderer*& target_render ){

    z_base_real = z_real;
    z_base_imag = z_imag;
    c_base_real = c_real;
    c_base_imag = c_imag;

    z.real(z_real);
    z.imag(z_imag);
    c.real(c_real);
    c.imag(c_imag);

    width = base_width;
    height = base_height;
    
    set_render( target_render );

    if ( !create_texture() ) {
        std::cerr << "Texture was not created" << std::endl;
    }

}

bool Mandelbrot::create_texture() {
    bool success = true;
    texture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height );
    if ( texture == NULL ) {
        std::cerr << "Mandelbrot texture could not be created --> " << SDL_GetError() << std::endl;
        success = false;
    }
    return success;
}

void Mandelbrot::set_cords( int x, int y ) {
    mouse_x = x;
    mouse_y = y;
}

void Mandelbrot::set_render( SDL_Renderer*& target_render ) {
    renderer = target_render;
}

double Mandelbrot::color_map( double value, int max_value ) {
    return (value * 255 / max_value);
}

void Mandelbrot::update_range() {
    real_start = map(mouse_x-(zoom_regulator), 0, width, min_real_range, max_real_range);
    real_end = map(mouse_x+(zoom_regulator), 0, width, min_real_range, max_real_range);

    imag_start = map(mouse_y-(zoom_regulator), 0, height, min_imag_range, max_imag_range);
    imag_end = map(mouse_y+(zoom_regulator), 0, height, min_imag_range, max_imag_range);

    min_real_range = real_start;
    max_real_range = real_end;
    min_imag_range = imag_start;
    max_imag_range = imag_end;

}

long double Mandelbrot::map( long double value, long double old_min, long double old_max, long double new_min, long double new_max) {
    return (((value - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min;
}

void Mandelbrot::calculate_set( double x, double y, int max_iter ){
}

void Mandelbrot::generate( int max_iter ) {
    SDL_SetRenderTarget( renderer, texture );
    SDL_RenderClear( renderer );
    for ( double x = 0; x <= width; ++x ) {
        for ( double y = 0; y <= height; ++y ) {
            c.real(real_start+(x*(real_end-real_start))/width);
            c.imag(imag_start+(y*(imag_end-imag_start))/height);
            z.real(z_base_real);
            z.imag(z_base_imag);
            int i = 0;
            for ( i = 0; i <= max_iter; ++i ) {
                z = z*z+c;
                if ( z.real()*z.real()+z.imag()*z.imag() >= 4 ) {
                    break;
                }
            }
            R = color_map( i, 2*max_iter);
            G = color_map( i, max_iter*10);
            B = color_map( i, .95*max_iter);
            double color = static_cast<double>(i)/max_iter*.69;
            SDL_SetRenderDrawColor( renderer, R, G, B, 255 );
            SDL_RenderDrawPointF( renderer, x, y );
        }
    }
    SDL_SetRenderTarget( renderer, NULL );
    SDL_RenderCopy( renderer, texture, NULL, NULL );
}

