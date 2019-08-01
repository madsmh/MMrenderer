// The complete Gosu library.
#include <Gosu/Gosu.hpp>

#include <fstream>

#include "ray.h"
#include "camera.h"
#include "scene.h"
#include "vector3.h"
#include "sphere.h"

// Define some convenient constants
const Vector3 color_white = Vector3(1.0, 1.0, 1.0);
const Vector3 color_blue  = Vector3(0.5, 0.7, 1.0);
const Vector3 color_red   = Vector3(1.0, 0.0, 0.0);

// Define image size
const int c_width  = 400;
const int c_height = 200;


class MMrenderer : public Gosu::Window
{
public:
    MMrenderer()
    : Window(c_width, c_height),
      m_bitmap(c_width, c_height)
    {
        set_caption("MMrenderer");
    }

    // Load scene from file
    void load(std::string file_name) {
        Vector3 center;
        float   radius;

        std::ifstream file(file_name);
        while (file >> center >> radius) {
            m_scene.push_back(new Sphere(center, radius));
        }

        std::cout << "Loaded " << m_scene.size() << " spheres" << std::endl;
    } // load


    // Check keyboard
    void button_down(Gosu::Button button) override
    {
        if (button == Gosu::KB_ESCAPE) {
            close();
        } else {
            Window::button_down(button);
        }
    } // button_down


    // Called 60 times each second
    void update() override
    {
        // Show frame rate
        set_caption("FPS: " + std::to_string(Gosu::fps()) + ", Camera: " + m_camera.to_string());

        // Loop over all pixels on screen
        for (int x=0; x<c_width/2; ++x) {
            for (int y=0; y<c_height/2; ++y) {
                float u     = float(x)/float(c_width/2);
                float v     = 1.0-float(y)/float(c_height/2);
                Ray ray     = m_camera.get_ray(u, v);
                Vector3 col = color(ray);

                Gosu::Color gosu_col(255.99*col[0], 255.99*col[1], 255.99*col[2]);
                // Set four pixels at a time, to make image larger.
                m_bitmap.set_pixel(2*x,   2*y,   gosu_col);
                m_bitmap.set_pixel(2*x,   2*y+1, gosu_col);
                m_bitmap.set_pixel(2*x+1, 2*y,   gosu_col);
                m_bitmap.set_pixel(2*x+1, 2*y+1, gosu_col);
            }
        }

        // Check for camera movement
        if (Gosu::Input::down(Gosu::KB_LEFT) || Gosu::Input::down(Gosu::GP_LEFT)) {
            m_camera.move(Vector3(-0.01, 0.0, 0.0));
        }
        if (Gosu::Input::down(Gosu::KB_RIGHT) || Gosu::Input::down(Gosu::GP_RIGHT)) {
            m_camera.move(Vector3(0.01, 0.0, 0.0));
        }
        if (Gosu::Input::down(Gosu::KB_UP) || Gosu::Input::down(Gosu::GP_UP)) {
            m_camera.move(Vector3(0.0, 0.01, 0.0));
        }
        if (Gosu::Input::down(Gosu::KB_DOWN) || Gosu::Input::down(Gosu::GP_DOWN)) {
            m_camera.move(Vector3(0.0, -0.01, 0.0));
        }
    } // update


    // Called after update
    void draw() override
    {
        Gosu::Image image(m_bitmap);
        image.draw(0, 0, 1);
    } // draw

private:

    // Calculates the color associated with this particular ray.
    Vector3 color(const Ray& ray) const {
        hit_record rec;

        // We only want positive parameters t, i.e. intersection in front of the camera.
        float t_min = 0.001;
        float t_max = MAXFLOAT;

        if (m_scene.hit(ray, t_min, t_max, rec)) {
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
        
    Gosu::Bitmap m_bitmap;
    Camera       m_camera;
    Scene        m_scene;
}; // class MMrenderer

int main()
{
    MMrenderer window;
    window.load("scene.txt");
    window.show();
} // main

