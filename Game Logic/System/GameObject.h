#pragma once
#include "Transform.h"
#include "Renderer.h"
#include "SphereRenderer.h"

class GameObject {
public:
	GameObject();
	Transform* transform;
	Renderer* renderer;
	void Render(Renderer*);
};