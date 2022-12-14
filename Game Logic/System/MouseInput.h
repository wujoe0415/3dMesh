#pragma once
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include "Window.h"

using namespace std;


class MouseInput {
	// Main KeyInput functionality
public:
	// Takes a list of which keys to keep state for
	MouseInput(std::vector<int> keysToMonitor);
	~MouseInput();
	// If this KeyInput is enabled and the given key is monitored,
	// returns pressed state.  Else returns false.
	bool getIsMouseDown(int key);
	bool getIsMouseUp(int key);
	// See _isEnabled for details
	bool getIsEnabled() { return _isEnabled; }
	void setIsEnabled(bool value) { _isEnabled = value; }
private:
	// Used internally to update key states.  Called by the GLFW callback.
	void setIsMouseDown(int key, bool isDown);
	// Map from monitored keyes to their pressed states
	std::map<int, bool> _keys;
	// If disabled, KeyInput.getIsKeyDown always returns false
	bool _isEnabled;

	// Workaround for C++ class using a c-style-callback
public:
	// Must be called before any KeyInput instances will work
	static void setupMouseInputs(Window&);
private:
	// The GLFW callback for key events.  Sends events to all KeyInput instances
	static void callback(GLFWwindow* window, int button, int action, int mods);
	// Keep a list of all KeyInput instances and notify them all of key events
	static std::vector<MouseInput*> _instances;
};