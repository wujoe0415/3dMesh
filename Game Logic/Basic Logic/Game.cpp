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
	ResourceManager::LoadTexture("Resources/lightblue.png", false, "lightblue");
	ResourceManager::GetShader("standard").Use().SetInteger("standard", 0);
	InitGame();
}
void Game::InitGame() {
	dino = new Dino();
	totalTime = 0;
	glfwSetTime(0);
}
void Game::Draw() {
	dino->Draw(renderer);
}
void Game::GameLoop() {
	float deltaTime = glfwGetTime() - totalTime;
	totalTime = glfwGetTime();

}