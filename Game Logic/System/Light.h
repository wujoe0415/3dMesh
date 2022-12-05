#pragma once
#include "Transform.h"
#include "Renderer.h"

class Light {
public:
	Light() {
		transform = new Transform();
		renderer = new Renderer("lightblue", "light");
	}
	Transform* transform;
	Renderer* renderer;
	void Render(Renderer* render) {
		renderer->Render(transform->GetGlobalPosition(), transform->GetGlobalRotation(), transform->GetGlobalScale(), glm::vec3(1, 1, 1));
	}
};