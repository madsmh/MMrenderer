#include <iostream>
#include "vector3.h"
#include "ray.h"
#include "scene.h"
#include "sphere.h"

// Define some convenient constants
const Vector3 color_white = Vector3(1.0, 1.0, 1.0);
const Vector3 color_blue  = Vector3(0.5, 0.7, 1.0);
const Vector3 color_red   = Vector3(1.0, 0.0, 0.0);

// Calculates the color associated with this particular ray.
Vector3 color(const Ray& ray, const Scene& scene) {
    hit_record rec;

    // We only want positive parameters t, i.e. intersection in front of the camera.
    float t_min = 0.0;
    float t_max = MAXFLOAT;

    if (scene.hit(ray, t_min, t_max, rec)) {
        // The normal vector has all components in the interval [-1, 1]
        // Convert linearly to vector where all components are in the interval [0, 1]
        return 0.5*(rec.normal + Vector3(1.0, 1.0, 1.0));
    } else {
        // The ray did not hit an object, so simulate a sky, based on the y-coordinate
        // of the rays direction.
        Vector3 unit_direction = unit_vector(ray.direction());
        float t = 0.5*(unit_direction.y() + 1.0); // t is in the range [0,1]
        // Linearly blend between white and blue
        return (1.0-t)*color_white + t*color_blue;
    }
} // color


int main() {
    // Size of final image in pixels.
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // Define the viewing screen
    Vector3 lower_left_corner(-2.0, -1.0, -1.0);
    Vector3 horizontal(4.0, 0.0, 0.0);
    Vector3 vertical(0.0, 2.0, 0.0);

    // Defines the position of the camera
    Vector3 camera(0.0, 0.0, 0.0);

    // Define the scene with all the objects
    // Note: Negative values of z correspond to objects in front of the camera, whereas
    // positive z-values are behind the camera.
    // This is because the x,y,z coordinate system must be a regular right-haned coordinate system.
    Scene scene;
    //                                 x       y     z       r
    scene.push_back(new Sphere(Vector3(0.0,    0.0, -1.0),   0.5));
    scene.push_back(new Sphere(Vector3(0.0, -100.5, -1.0), 100.0));

    // Loop over all pixels of the image
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {

            // Calculate a position on the viewing screen.
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Vector3 screen_pos(lower_left_corner + u*horizontal + v*vertical);

            // Calculate a ray from the camera through the position on the viewing screen.
            Ray ray(camera, screen_pos);

            // Calculate the colour of this particular pixel
            Vector3 col = color(ray, scene);

            // Write colour to output.
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
} // main

