#include "GameObject.h"

GameObject::GameObject(){
	transform = new Transform();
	renderer = new Renderer("lightblue", "standard");
}
void GameObject::Render(Renderer* _renderer) {
	renderer->Render(transform->GetGlobalPosition(), transform->GetGlobalRotation(), transform->GetGlobalScale(), glm::vec3(1, 1, 1));
}
