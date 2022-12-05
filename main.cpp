#define _CRT_SECURE_NO_WARNINGS
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Basic Logic/Game.h"
#include "System/Window.h"
#include "System/KeyInput.h"
#include "System/MouseInput.h"

using namespace std;
void CloseWindow()
{
    glfwSetWindowShouldClose(Window::getInstance().sWindow, GLFW_TRUE);
}
int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    Window* window = &Window::getInstance();
    window->CreateWindow(960, 960);
    //ObjLoader* modelLoader = new ObjLoader();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Game* game = new Game();
    vector<int> inputList{ GLFW_KEY_ESCAPE };
    KeyInput* keyinputs = new KeyInput(inputList);
    // Initialize Input callback*/
    KeyInput::setupKeyInputs(*window);
    MouseInput::setupMouseInputs(*window);
    glEnable(GL_DEPTH_TEST);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window->sWindow))
    {
        game->GameLoop();

        /* Poll for and process events */
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game->Draw();
        /* Swap front and back buffers */
        glfwSwapBuffers(window->sWindow);
    }

    glfwTerminate();
    return 0;
}