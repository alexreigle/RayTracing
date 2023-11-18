// OneWeekend.cpp : Defines the entry point for the application.
//

#include "OneWeekend.h"
#include <iostream>
#include <fstream>

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
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            img << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    img.close();

    std::clog << "\rDone.                      \n";
}