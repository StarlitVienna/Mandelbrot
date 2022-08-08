#include <complex>
#include <SDL2/SDL.h>
class Mandelbrot {
    public:
        Mandelbrot( long double z_real, long double z_imag, long double c_real, long double c_imag, int base_width, int base_height, SDL_Renderer*& target_render );
        void set_render( SDL_Renderer*& target_render );
        void generate( int max_iter );
        void update_range();
        void set_cords(int x, int y);
        bool create_texture();
        float zoom = 1;
        float zoom_regulator = (100/zoom);

    private:
        void calculate_set( double x, double y, int max_iter );
        double color_map( double value, int max_value );
        long double map( long double value, long double old_min, long double old_max, long double new_min, long double new_max);

        int width = 0;
        int height = 0;
        
        bool zoom_mode = false;

        long double max_real_range = 2.0;
        long double min_real_range = -2.0;
        long double max_imag_range = 2.0;
        long double min_imag_range = -2.0;

        long double c_base_real = 0;
        long double c_base_imag = 0;

        long double real_start = -2;
        long double real_end = 2;
        long double imag_start = -2;
        long double imag_end = 2;

        double z_base_real = 0;
        double z_base_imag = 0;

        double R = 0;
        double G = 0;
        double B = 0;

        int mouse_x = 0;
        int mouse_y = 0;

        std::complex<long double> z;
        std::complex<long double> c;

        SDL_Renderer* renderer = NULL;
        SDL_Texture* texture = NULL;

};
