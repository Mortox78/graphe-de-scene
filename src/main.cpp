#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <cmath>

#include "Object.hpp"
#include "matrix.h"
#include "matrix4.h"
#include "Vec4.h"

int main()
{
    GLFWwindow* window = init_openGl_and_create_window();

    float x = 0, y = 0, z = -5, angleX = 0, angleY = 0, angleZ = 0, scaleX = 1, scaleY = 1, scaleZ = 1, time = 0;
    // world
    Object world;
    Matrix4 matIdentity = Matrix4::identity(4);
    // sphere
    world.childrens.emplace_back(Object(SPHERE));
    world.childrens[0].color = {0, 0, 1};
    // cube
    world.childrens[0].childrens.emplace_back(Object(CUBE));
    world.childrens[0].childrens[0].pos   = {2, 0, 0};
    world.childrens[0].childrens[0].color = {1, 0, 0};
    // cylinder
    world.childrens[0].childrens[0].childrens.emplace_back(Object(CYLINDER));
    world.childrens[0].childrens[0].childrens[0].pos   = {0, 2, 0};
    world.childrens[0].childrens[0].childrens[0].color = {0, 1, 0};

    while (!glfwWindowShouldClose(window))
    {
		//we look for the time of execution since we initialized SDL
    	float current_time 		= SDL_GetTicks();
		//and here we calculate the time of execution of the loop
    	float deltaTime			= (time > 0) ? ((current_time - time) / 1000.f) : 1.0f / 60.0f;
    	time 					= current_time;
    

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90, SCREEN_WIDTH / SCREEN_HEIGHT, 0.001, 1000);

        glfwPollEvents();

        angleY += 1.f * deltaTime;
        angleX += 1.f * deltaTime;
        angleZ += 1.f * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_UP))
            z -= 10.f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_DOWN))
            z += 10.f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_LEFT))
            x -= 10.f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_RIGHT))
            x += 10.f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_SPACE))
            y += 10.f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
            y -= 10.f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_KP_ADD))
        {
            scaleX += 1.f * deltaTime;
            scaleY += 1.f * deltaTime;
            scaleZ += 1.f * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT))
        {
            scaleX -= 1.f * deltaTime;
            scaleY -= 1.f * deltaTime;
            scaleZ -= 1.f * deltaTime;
        }



        world.childrens[0].rot                           = {0, angleY, 0};
        world.childrens[0].pos                           = {x, y, z};
        world.childrens[0].childrens[0].rot              = {angleX, 0, 0};
        world.childrens[0].childrens[0].scale            = {scaleX, scaleY, scaleZ};
        world.childrens[0].childrens[0].childrens[0].rot = {0, 0, angleZ};
        world.display(world, matIdentity);

        glClearColor(0, 0, 0, 1);
        glFlush();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

