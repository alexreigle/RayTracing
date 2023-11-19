#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "color.h"

class ray {
public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    point3 at(double t) const {
        return orig + t * dir;
    }

    bool hit_sphere(const point3& center, double radius, const ray& r) {
        vec3 oc = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto b = 2.0 * dot(oc, r.direction());
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;
        return (discriminant >= 0);
    }

    color ray_color(const ray& r) {
        if (hit_sphere(point3(0, 0, -1), 0.5, r))
            return color(1, 0, 0);

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }

private:
    point3 orig;
    vec3 dir;
};

#endif