#include <complex>
#include <SDL2/SDL.h>
class Mandelbrot {
    public:
        Mandelbrot( long double z_real, long double z_imag, long double c_real, long double c_imag, int base_width, int base_height );
        void set_render( SDL_Renderer*& render );
        void generate( int max_iter );

    private:
        void calculate_set( long double x, long double y, int max_iter );
        void draw_set( long double x, long double y, int R, int G, int B, int a );
        long double color_map( long double value, long double max_value );
        long double map( long double value, long double old_min, long double old_max);

        long double zoom = 1;

        long double max_range = 2.0;
        long double min_range = -2.0;

        long double c_base_real = 0;
        long double c_base_imag = 0;

        long double z_base_real = 0;
        long double z_base_imag = 0;


        std::complex<long double> z;
        std::complex<long double> c;

        SDL_Renderer* renderer;

        int width = 0;
        int height = 0;
};
