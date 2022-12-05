#pragma once
#include "System/GameObject.h"
#include <vector>
#include <map>
#include "System/Renderer.h"
#include "System/SphereRenderer.h";
#include "System/ObjLoader.h"
#include "System/Window.h"
#include "System/MouseInput.h"
using namespace std;
class Dino : public GameObject {
public:
	Dino();
	void Rotate(float angle, glm::vec3 direction);
	void Draw(Renderer*);
	MouseInput* mouse;
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void InputHandler();
private:
	bool lastMouseisDown = false;
	vector<int> inputList;
	ObjLoader* objLoader;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	void Normalize();

private:
	glm::vec3 lastPos;
	glm::vec3 Projection(int mouseX, int mouseY) {
		float d, a;
		/* project x,y onto a hemisphere centered within width, height ,
	   note z is up here*/
		glm::vec3 v;
		v.x = (2.0 * mouseX - (float)Window::getInstance().getWindowWidth()) / (float)Window::getInstance().getWindowWidth();
		v.y = ((float)Window::getInstance().getWindowHeight() - 2.0F * mouseY) / (float)Window::getInstance().getWindowHeight();
		d = sqrt(v.x * v.x + v.y * v.y);
		v.z = cos((glm::pi<float>() / 2.0) * ((d < 1.0) ? d : 1.0));
		v = glm::normalize(v);
		return v;
	}
	void MouseDown() {
		//cout << "Down";
		//set radous
		float radius = glm::length(glm::vec2(1, 1));
		double x, y;
		glfwGetCursorPos(Window::sWindow, &x, &y);
		this->lastPos = Projection((float)x, (float)y);
	}
	void MouseMove() {
		double x, y;
		glfwGetCursorPos(Window::sWindow, &x, &y);
		float curPos[3],
			dx, dy, dz;
		/* compute position on hemisphere */
		glm::vec3 nextMove = Projection((float)x, (float)y);
		dx = nextMove.x - lastPos.x;
		dy = nextMove.y - lastPos.y;
		dz = nextMove.z - lastPos.z;
		if (dx || dy || dz)
		{
			/* compute theta and cross product */
			float angle = 90.0 * sqrt(dx * dx + dy * dy + dz * dz);
			glm::vec3 axis = glm::normalize(glm::cross(lastPos, nextMove));
			transform->RotateAlong(angle, axis);
			/* update position */
			lastPos = nextMove;
		}
	}
	void MouseUp() {
		//cout << "Release";
	}
};