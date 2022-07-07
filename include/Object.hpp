#pragma once

#include <iostream>
#include <vector>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "../snmath/Vec3.h"
#include "matrix4.h"

#define SCREEN_WIDTH  1024.f
#define SCREEN_HEIGHT 768.f
#define SCALE         250.f

enum
{
    NONE      = -1,
    CUBE      = 0,
    SPHERE    = 1,
    CYLINDER  = 2,
};

class Object
{
    private:
        std::vector<Vec3>            sphereVertices;
        std::vector<Vec3>            cubeVertices;
        std::vector<Vec3>            cylinderVertices;
        std::vector<unsigned int>    sphereIndices;
        std::vector<unsigned int>    cubeIndices;
        std::vector<unsigned int>    cylinderIndexes;

        void init_sphere(const int& latitude, const int& longitude);
        void init_sphere_vertices(const int& latitude, const int& longitude);
        void init_sphere_indices(const int& latitude, const int& longitude);
        void init_cube();
        void init_cylinder();
        void pushBackCube_triangleIndices(const unsigned int& index1, const unsigned int& index2, const unsigned int& index3);
        void pushBackSphere_triangleIndices(const unsigned int& index1, const unsigned int& index2, const unsigned int& index3);
        void draw_sphere(Matrix4& matTRS);
        void draw_cube(Matrix4& matTRS);
        void draw_cylinder(Matrix4& matTRS);


    public:
        Object();
        Object(const Object& copyObj);
        Object(const int& primitiveType);
        ~Object(){}

        std::string            name;
        Vec3                   pos;
        Vec3                   rot;
        Vec3                   scale;
        Vec3                   color;
        int                    primitiveType;
        std::vector<Object>    childrens;

        void display(const Object& parentObject, Matrix4& matTRS);
};

GLFWwindow* init_openGl_and_create_window();