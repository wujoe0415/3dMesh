#include "Dinosaur.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

void AddMouse() {
	auto func = [](GLFWwindow* w, int button, int action, int mods) {
		static_cast<Dino*>(glfwGetWindowUserPointer(w))->mouse_button_callback(w, button, action, mods);
	};
	glfwSetMouseButtonCallback(Window::sWindow, /*mouse_button_callback*/ func);
}
void Dino::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		MouseDown();
	 else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		MouseUp();
}
Dino::Dino() {
	lastMouseisDown = false;
    objLoader = new ObjLoader();
    bool res = objLoader->loadObj("Dino.obj", vertices, uvs, normals);
	if(res)
		renderer->ChangeVertex(vertices, objLoader->vertexIndices);
	Normalize();
	inputList.push_back(GLFW_MOUSE_BUTTON_LEFT);
	mouse = new MouseInput(inputList);
	// Initialize Input callback
}
void Dino::Rotate(float angle, glm::vec3 direction) {
	transform->Rotate(angle * direction.x, angle * direction.y, angle * direction.z);
}
void Dino::Draw(Renderer* renderer) {
	//renderer->Render(transform->GetGlobalPosition(), transform->GetGlobalRotation(), transform->GetGlobalScale(), glm::vec3(1, 1, 1), objLoader->vertexIndices.size());
	this->Render(renderer);
}
void Dino::Normalize()
{
	int max = glm::length(vertices[1] - vertices[0]);
	for (int i = 1; i < vertices.size(); i++)
	{
		int next = glm::length(vertices[i] - vertices[i - 1]);
		if (max < next)
			max = next;
	}
	float scaler = (float)1 / max;
	cout << scaler;
	transform->SetScale(glm::vec3(scaler, scaler, scaler));
} 
void Dino::InputHandler() {
	if (!lastMouseisDown && mouse->getIsMouseDown(GLFW_MOUSE_BUTTON_LEFT)) {
		lastMouseisDown = true;
		MouseDown();
	}
	else if (mouse->getIsMouseDown(GLFW_MOUSE_BUTTON_LEFT))
		MouseMove();
	else if (lastMouseisDown && !mouse->getIsMouseUp(GLFW_MOUSE_BUTTON_LEFT)) {
		lastMouseisDown = false;
		MouseUp();
	}
}
