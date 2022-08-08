#include "mandelbrot.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <complex>

Mandelbrot::Mandelbrot( long double z_real, long double z_imag, long double c_real, long double c_imag, int base_width, int base_height ){
    std::cout << "/////////////////" << std::endl;
    std::cout << " Initial values " << std::endl;
    std::cout << "z = (" << z_real << ", " << z_imag << ")" << std::endl;
    std::cout << "c = (" << c_real << ", " << c_imag << ")" << std::endl;
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
}

void Mandelbrot::set_render( SDL_Renderer*& render ) {
    renderer = render;
}

long double Mandelbrot::color_map( long double value, long double max_value ) {
    return (((value - 0) * (255 - 0)) / (max_value - 0)) + 0;
}

long double Mandelbrot::map( long double value, long double old_min, long double old_max) {
    return (((value - old_min) * (max_range - min_range)) / (old_max - old_min)) + min_range;
}

void Mandelbrot::calculate_set( long double x, long double y, int max_iter ) {
    long double x_scaled = map( x, 0, width );
    long double y_scaled = map( y, 0, height );
    c.real(x_scaled);
    c.imag(y_scaled);
    z.real(z_base_real);
    z.imag(z_base_imag);
    int i = 0;
    for ( i = 0; i < max_iter; ++i ) {
        z = z*z+c;
        if ( z.real()*z.real()+z.imag()*z.imag() >= 4 ) {
            break;
        }
    }
    long double color = color_map( static_cast<long double> (i), max_iter);
    SDL_SetRenderDrawColor( renderer, color, color, color, 255 );
    SDL_RenderDrawPointF( renderer, x, y );
}

void Mandelbrot::generate( int max_iter ) {
    for ( long double x = 0; x <= width; ++x ) {
        for ( long double y = 0; y <= height; ++y ) {
            calculate_set(x, y, max_iter);
        }
    }
}
