#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <random>
#include "vector3.h"
#include "ray.h"
#include "scene.h"
#include "sphere.h"
#include "camera.h"
#include "lambartian.h"

// Define some convenient constants
const Vector3 color_white = Vector3(1.0, 1.0, 1.0);
const Vector3 color_blue  = Vector3(0.5, 0.7, 1.0);
const Vector3 color_red   = Vector3(1.0, 0.0, 0.0);




// Calculates the color associated with this particular ray.
Vector3 color(const Ray &ray, const Scene& scene, int depth=0) {
    hit_record rec;

    // We only want positive parameters t, i.e. intersection in front of the camera.
    float t_min = 0.0;
    float t_max = MAXFLOAT;
    Vector3 attenuation;
    Ray scattered;

    if (scene.hit(ray, t_min, t_max, rec)) {
        if (depth < 50 && rec.surface_ptr->scatter(ray, rec, attenuation, scattered)){
            return attenuation*color(scattered, scene, depth+1);
        } else { return  Vector3(0.0, 0.0, 0.0);}

    } else {
        // The ray did not hit an object, so simulate a sky, based on the y-coordinate
        // of the rays direction.
        Vector3 unit_direction = unit_vector(ray.direction());
        float t = 0.8*(unit_direction.y() + 1.0); // t is in the range [0,1]
        // Linearly blend between white and blue
        return (1.0-t)*color_white + t*color_blue;
    }
} // color


Scene read_scene_from_file(std::string file_name) {
    Scene         scene;
    Vector3       center;
    float         radius;

    std::ifstream file(file_name);
    while (file >> center >> radius) {
        scene.push_back(new Sphere(center, radius, new lambartian(Vector3(1.0, 1.0, 1.0))));
    }
    return scene;
} // read_scene_from_file


int main() {
    // Size of final image in pixels.
    int nx = 600;
    int ny = 300;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // Number of random samples for each pixel.
    int ns = 300;

    // Holds position of the camera and the viewing screen.
    Camera camera;

    // Define the scene with all the objects
    Scene scene = read_scene_from_file("scene.txt");

    // Loop over all pixels of the image
    for (int y = ny-1; y >= 0; y--) {
        for (int x = 0; x < nx; x++) {

            // Anti-aliasing: Calculate an average over many almost-identical
            // rays.
            Vector3 col(0.0, 0.0, 0.0);
            for (int s=0; s<ns; s++) {

                // Calculate a ray corresponding to random point within this pixel.
                float u = float(x + drand48()) / float(nx);
                float v = float(y + drand48()) / float(ny);
                Ray ray = camera.get_ray(u, v);

                // Calculate the colour of this particular pixel.
                col += color(ray, scene);
            }
            col /= float(ns);

            // Write colour to output.
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
} // main

