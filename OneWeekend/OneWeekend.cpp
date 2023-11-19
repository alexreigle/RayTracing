// OneWeekend.cpp : Defines the entry point for the application.
//

#include "OneWeekend.h"

int main() {

    std::ofstream img;
    img.open("../../../images/image.ppm", std::ios::in|std::ios::out);
    if (!img.is_open())
    {
        std::cout << "Error: Invalid File" << std::endl;
        return 1;
    }

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int  image_width = 400;
    //int  image_height = 256;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;   // Ensure image height is at least 1
    
    // Camera
    auto focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);

    // Viewport 
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2; // This is the intersection of the upper and right EDGES of the image
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // This is the centroid of the first pixel

    // Render

    img << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        // Progress Bar
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = r.ray_color(r);  // NOTE: I've moved the `ray_color` function into the ray class and therefore have to access it via the ray object "r", above.
                                                 
            //auto pixel_color = color(double(i)/ (image_width - 1), double(j) / (image_height - 1), 0);
            //write_color(std::cout, pixel_color);
        }
    }

    img.close();

    std::clog << "\rDone.                      \n";
}