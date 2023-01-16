#include "Game.h"
#include <time.h>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "System/stb_image.h"

Game::Game() {
	window = &Window::getInstance();
	// Inititialize Render Data
	ResourceManager::LoadShader("3d.vert", "3d.frag", nullptr, "standard");
	ResourceManager::LoadShader("light.vert", "light.frag", nullptr, "light");
	ResourceManager::LoadTexture("Resources/lightblue.png", false, "lightblue");
	ResourceManager::GetShader("standard").Use().SetInteger("standard", 0);
	ResourceManager::GetShader("light").Use().SetInteger("light", 1);
	InitGame();
}
void Game::InitGame() {
	dino = new Dino();
	lights.push_back(new Light());
	lights.push_back(new Light());
	lights.push_back(new Light());
	lights[0]->transform->SetPosition(glm::vec3(0.5f, 0.5f, 0.5f));
	lights[1]->transform->SetPosition(glm::vec3(1.0f, 0.4f, -0.5f));
	lights[2]->transform->SetPosition(glm::vec3(-0.6f, 1.8f, 1.0f));
	lights[0]->transform->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	lights[1]->transform->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	lights[2]->transform->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	totalTime = 0;
	glfwSetTime(0);
}
void Game::Draw() {
	dino->Draw(renderer);
	/*for (auto light : lights)
		light->Render(renderer);*/
}
void Game::GameLoop() {
	float deltaTime = glfwGetTime() - totalTime;
	totalTime = glfwGetTime();
	dino->InputHandler();
}