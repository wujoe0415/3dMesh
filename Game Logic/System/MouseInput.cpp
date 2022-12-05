#include "MouseInput.h"
#include <algorithm>

std::vector<MouseInput*> MouseInput::_instances;

MouseInput::MouseInput(std::vector<int> keysToMonitor) : _isEnabled(true) {
	for (int key : keysToMonitor) {
		_keys[key] = false;
	}
	// Add this instance to the list of instances
	MouseInput::_instances.push_back(this);
}

MouseInput::~MouseInput() {
	// Remove this instance from the list of instances
	_instances.erase(std::remove(_instances.begin(), _instances.end(), this), _instances.end());
}
bool MouseInput::getIsMouseUp(int key) {
	bool result = false;
	if (_isEnabled) {
		std::map<int, bool>::iterator it = _keys.find(key);
		if (it != _keys.end()) {
			result = _keys[key];
		}
	}
	return result;
}
bool MouseInput::getIsMouseDown(int key) {
	bool result = false;
	if (_isEnabled) {
		std::map<int, bool>::iterator it = _keys.find(key);
		if (it != _keys.end()) {
			result = _keys[key];
		}
	}
	return result;
}
void MouseInput::setIsMouseDown(int key, bool isDown) {
	std::map<int, bool>::iterator it = _keys.find(key);
	if (it != _keys.end()) {
		_keys[key] = isDown;
	}
}
void MouseInput::setupMouseInputs(Window& window) {
	glfwSetMouseButtonCallback(window.sWindow, MouseInput::callback);
}

void MouseInput::callback(GLFWwindow* window, int button, int action, int mods) {
	// Send key event to all KeyInput instances
	for (MouseInput* mouseInput : _instances) {
		mouseInput->setIsMouseDown(button, action != GLFW_RELEASE);
	}
}