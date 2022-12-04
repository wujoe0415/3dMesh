/* The Halfling Project - A Graphics Engine and Projects
 *
 * The Halfling Project is the legal property of Adrian Astley
 * Copyright Adrian Astley 2013 - 2014
 */

#include "Camera.h"

#include <algorithm>


void Camera::Rotate(float dTheta, float dPhi) {
	m_viewNeedsUpdate = true;

	if (m_up > 0.0f)
		m_theta += dTheta;
	else
		m_theta -= dTheta;

	m_phi += dPhi;

	// Keep phi within -2PI to +2PI for easy 'up' comparison
	if (m_phi > 2 * glm::pi<float>()) 
		m_phi -= 2 * glm::pi<float>();
	else if (m_phi < - 2 * glm::pi<float>()) 
		m_phi += 2 * glm::pi<float>();
	

	// If phi is between 0 to PI or -PI to -2PI, make 'up' be positive Y, other wise make it negative Y
	if ((m_phi > 0 && m_phi < glm::pi<float>()) || (m_phi < -glm::pi<float>() && m_phi > - 2 * glm::pi<float>()))
		m_up = 1.0f;
	else
		m_up = -1.0f;
}

void Camera::Zoom(float distance) {
	m_viewNeedsUpdate = true;

	m_radius -= distance;

	// Don't let the radius go negative
	// If it does, re-project our target down the look vector
	/*if (m_radius <= 0.0f) {
		m_radius = 30.0f;
		glm::vec3 look = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(m_target, GetCameraPositionXM()));
		m_target = DirectX::XMVectorAdd(m_target, DirectX::XMVectorScale(look, 30.0f));
	}*/
}

void Camera::Pan(float dx, float dy) {
	m_viewNeedsUpdate = true;
	glm::vec3 look = normalize(ToCartesian());
	glm::vec3 worldUp = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

	glm::vec3 right = glm::cross(look, worldUp);
	glm::vec3 up = glm::cross(look, right);

	m_target = m_target + (right * dx) + (up * dy);
}

void Camera::UpdateViewMatrix() {
	//m_view = DirectX::XMMatrixLookAtLH(GetCameraPositionXM(), m_target, DirectX::XMVectorSet(0.0f, m_up, 0.0f, 0.0f));
}

void Camera::UpdateProjectionMatrix(float clientWidth, float clientHeight, float nearClip, float farClip) {
	//m_proj = DirectX::XMMatrixPerspectiveFovLH(0.25f * DirectX::XM_PI, clientWidth / clientHeight, nearClip, farClip);
}
void Camera::MouseDown() {}
void Camera::MouseMove() {}
void Camera::MouseUp() {}
void Camera::MouseWheel(int zDelta) {
	Zoom((float)zDelta * m_cameraScrollFactor);
}