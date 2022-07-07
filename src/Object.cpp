#include <iostream>
#include "Object.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>
#include <assert.h>
#include "matrix.h"
#include "matrix4.h"

Object::Object()
{
    this->primitiveType = -1;
    name  = "World";
    pos   = {0, 0, 0};
    rot   = {0, 0, 0};
    scale = {1, 1, 1};
    color = {0, 0, 0};
}

Object::Object(const Object& copyObj)
{
    this->primitiveType = copyObj.primitiveType;
    this->pos           = copyObj.pos;
    this->rot           = copyObj.rot;
    this->scale         = copyObj.scale;
    this->color         = copyObj.color;
    this->childrens     = copyObj.childrens;
    
    if (primitiveType == 0)
    {
        name = "Box";
        init_cube();
    }
    else if (primitiveType == 1)
    {
        name = "Sphere";
        init_sphere(32, 32);
    }
    else if (primitiveType == 2)
    {
        name = "Cylinder";
        init_cylinder();
    }
}



Object::Object(const int& primitiveType)
{
    assert(primitiveType >= 0 && primitiveType <= 2);

    this->primitiveType = primitiveType;
    pos   = {0, 0, 0};
    rot   = {0, 0, 0};
    scale = {1, 1, 1};
    color = {1, 1, 1};

    if (primitiveType == 0)
        init_cube();
    else if (primitiveType == 1)
        init_sphere(32, 32);
    else if (primitiveType == 2)
        init_cylinder();

    
}

void Object::draw_sphere(Matrix4& matTRS)
{
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(color.x, color.y, color.z);

    for (unsigned int i = 0; i < sphereIndices.size(); ++i)
    {
        // apply transformation
        Vec3 vertex = matTRS * Vec4(sphereVertices[sphereIndices[i]]);
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }

    glEnd();
}

void Object::draw_cube(Matrix4& matTRS)
{
    glBegin(GL_TRIANGLES);
    glColor3f(color.x, color.y, color.z);

    for (unsigned int i = 0; i < cubeIndices.size(); ++i)
    {
        // apply transformation
        Vec3 vertex = matTRS * Vec4(cubeVertices[cubeIndices[i]]);
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }
    glEnd();
}


void Object::draw_cylinder(Matrix4& matTRS)
{
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(color.x, color.y, color.z);
    for (unsigned int i = 0; i < cylinderVertices.size(); ++i)
    {
        for (unsigned int j = 0; j < cylinderIndexes.size(); ++j)
        {
            if (cylinderIndexes[j] == i)
            {
                glEnd();
                glBegin(GL_TRIANGLE_FAN);
            }
        }
        // apply transformation
        Vec3 vertex = matTRS * Vec4(cylinderVertices[i]);
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }

    glEnd();
}

void Object::init_cube()
{ 
    // +x || +z
    cubeVertices.emplace_back(Vec3(0.5f,     0.5f,       0.5f));          // 0
    cubeVertices.emplace_back(Vec3(0.5f,     -0.5f,      0.5f));          // 1
    // -x || +z                                                           //
    cubeVertices.emplace_back(Vec3(-0.5f,    0.5f,       0.5f));          // 2
    cubeVertices.emplace_back(Vec3(-0.5f,    -0.5f,      0.5f));          // 3
    // -x || -z                                                           //
    cubeVertices.emplace_back(Vec3(-0.5f,    0.5f,       -0.5f));         // 4
    cubeVertices.emplace_back(Vec3(-0.5f,    -0.5f,      -0.5f));         // 5
    // +x || -z                                                           //
    cubeVertices.emplace_back(Vec3(0.5f,     0.5f,       -0.5f));         // 6
    cubeVertices.emplace_back(Vec3(0.5f,     -0.5f,      -0.5f));         // 7

    // Faces
    pushBackCube_triangleIndices(1, 0, 2);
    pushBackCube_triangleIndices(1, 2, 3);

    pushBackCube_triangleIndices(3, 2, 4);
    pushBackCube_triangleIndices(3, 4, 5);

    pushBackCube_triangleIndices(5, 4, 6);
    pushBackCube_triangleIndices(5, 6, 7);

    pushBackCube_triangleIndices(7, 6, 0);
    pushBackCube_triangleIndices(7, 0, 1);

    // Top and bottom
    pushBackCube_triangleIndices(6, 4, 0);
    pushBackCube_triangleIndices(0, 4, 2);

    pushBackCube_triangleIndices(5, 7, 1);
    pushBackCube_triangleIndices(5, 1, 3);
}

void Object::init_cylinder()
{
    unsigned int size = 64;

    // faces of the shape
    for (unsigned int i = 0; i < size; ++i)
    {
        cylinderVertices.emplace_back(Vec3(cos(i * 2.f * M_PI / size) * SCALE / SCREEN_WIDTH, 0.0f, sin(i * 2.f * M_PI / size) * SCALE / SCREEN_WIDTH));
        cylinderVertices.emplace_back(Vec3(cos(i * 2.f * M_PI / size) * SCALE / SCREEN_WIDTH, 1.0f, sin(i * 2.f * M_PI / size) * SCALE / SCREEN_WIDTH));
    }

    // the previous "for" can't init the last face because we're using triangle strip, so we init the last face manually
    cylinderVertices.emplace_back(Vec3(cos(0) * SCALE / SCREEN_WIDTH, 0.0f, sin(0) * SCALE / SCREEN_WIDTH));
    cylinderVertices.emplace_back(Vec3(cos(0) * SCALE / SCREEN_WIDTH, 1.0f, sin(0) * SCALE / SCREEN_WIDTH));

    cylinderIndexes.push_back(cylinderVertices.size());

    // bottom of the shape
    for (unsigned int i = 0; i < size; ++i)
    {
        cylinderVertices.emplace_back(Vec3(cos(i * 2.f * M_PI / size) * SCALE / SCREEN_WIDTH, 0.0f, sin(i * 2.f * M_PI / size) * SCALE / SCREEN_WIDTH));
    }

    cylinderIndexes.push_back(cylinderVertices.size());

    // draw the top of the shape
    for (unsigned int i = 0; i < size; ++i)
    {
        cylinderVertices.emplace_back(Vec3(cos(i * 2.f * M_PI / size) * SCALE / SCREEN_WIDTH, 1.0f, sin(i * 2.f * M_PI / size) * SCALE / SCREEN_WIDTH));
    }
}

void Object::init_sphere(const int& latitude, const int& longitude)
{
    init_sphere_vertices(latitude, longitude);
    init_sphere_indices(latitude, longitude);
}


void Object::pushBackCube_triangleIndices(const unsigned int& index1, const unsigned int& index2, const unsigned int& index3)
{
    cubeIndices.push_back(index1);
    cubeIndices.push_back(index2);
    cubeIndices.push_back(index3);
}

void Object::pushBackSphere_triangleIndices(const unsigned int& index1, const unsigned int& index2, const unsigned int& index3)
{
    sphereIndices.push_back(index1);
    sphereIndices.push_back(index2);
    sphereIndices.push_back(index3);
}


void Object::display(const Object& parentObject, Matrix4& parentMatTRS)
{
    Matrix4 newMatTRS;
    Object  newThis(*this);

    // world.display(world OR object)
    if (this->primitiveType < 0 || this->primitiveType > 2)
    {
        newMatTRS = Matrix4::identity(4);
    }
    else
    {
        // object.display(world)
        if (parentObject.primitiveType < 0 || parentObject.primitiveType > 2)
        {
            newMatTRS = Matrix4::identity(4);
        }
        // object.display(CUBE OR SPHERE OR CYLINDER)
        else
        {
            newMatTRS = Matrix4::CreateTRSMatrix(parentObject.scale, parentObject.rot, parentObject.pos);
        }
        
        Matrix4 matThisObject = Matrix4::CreateTRSMatrix(this->scale, this->rot, this->pos);
        newMatTRS             = parentMatTRS * matThisObject;
    }
    
    // display our object   
    if (this->primitiveType == 0)
        draw_cube(newMatTRS);
    else if (this->primitiveType == 1)
        draw_sphere(newMatTRS);
    else if (this->primitiveType == 2)
        draw_cylinder(newMatTRS);

    // display our object's childrens
    for (std::vector<Object>::iterator it = childrens.begin() ; it != childrens.end(); ++it)
    {
        it->display(newThis, newMatTRS);
    }
}


void Object::init_sphere_vertices(const int& latitude, const int& longitude)
{
	float PI_2 = 2 * M_PI;
	
    sphereVertices.emplace_back(Vec3(0.f, 1.f, 0.f));

	for (int i = 0; i < latitude - 1; i++)
	{
		float cospolar = cosf(M_PI * (float)(i + 1) / (float)latitude);
		float sinpolar = sinf(M_PI * (float)(i + 1) / (float)latitude);

		for (int j = 0; j < longitude; j++)
		{
			float cosazimuth = cosf(PI_2 * (float)j / (float)longitude);
			float sinazimuth = sinf(PI_2 * (float)j / (float)longitude);

			float x = sinpolar * cosazimuth;
			float y = cospolar;
			float z = sinpolar * sinazimuth;
            sphereVertices.emplace_back(Vec3(x, y, z));
		}
	}
    sphereVertices.emplace_back(Vec3(0.0f,-1.0f,0.0f));
}

void Object::init_sphere_indices(const int& latitude, const int& longitude)
{
	for (int j = 0; j < longitude; j++)
    {
        pushBackSphere_triangleIndices(0, (j + 1) % longitude + 1, j + 1);
    }

	for (int i = 0; i < latitude - 2; i++)
	{
		int aStart = i *  longitude+ 1;
		int bStart = (i + 1) * longitude + 1;

		for (int j = 0; j < longitude; j++)
		{
			int a = aStart + j;
			int b = aStart + (j + 1) % longitude;
			int c = bStart + j;
			int d = bStart + (j + 1) % longitude;
            pushBackSphere_triangleIndices(a, b, c);
            pushBackSphere_triangleIndices(c, b, d);
		}
	}

	int max = sphereVertices.size() - 1;
	
	for (int i = 0; i < longitude; i++)
	{
        pushBackSphere_triangleIndices(max, i + longitude * (latitude - 2) + 1, (i + 1) % longitude + longitude * (latitude - 2) + 1);
	}
}

GLFWwindow* init_openGl_and_create_window()
{
    if (!glfwInit()) 
    {
        fprintf(stderr, "glfwInit Failed.\n");
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphe de scène", NULL, NULL);
    if (!window) 
    {
        fprintf(stderr, "glfwCreateWindow failed.\n");
        glfwTerminate();
        return nullptr;
    }


    glfwSwapInterval(1);
    glfwMakeContextCurrent(window);
    if (!gladLoadGL())
    {
        fprintf(stderr, "gladLoadGL failed.\n");
        glfwTerminate();
        return nullptr;
    }

    return window;
}