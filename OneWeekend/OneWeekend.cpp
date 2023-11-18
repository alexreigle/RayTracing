// OneWeekend.cpp : Defines the entry point for the application.
//

#include "OneWeekend.h"
#include "color.h"
#include "vec3.h"

int main() {

    std::ofstream img;
    img.open("../../../images/image.ppm", std::ios::in|std::ios::out);
    if (!img.is_open())
    {
        std::cout << "Error: Invalid File" << std::endl;
        return 1;
    }

    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    img << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        // Progress Bar
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i) {
            auto pixel_color = color(double(i)/ (image_width - 1), double(j) / (image_height - 1), 0);
            //write_color(std::cout, pixel_color);
        }
    }

    img.close();

    std::clog << "\rDone.                      \n";
}