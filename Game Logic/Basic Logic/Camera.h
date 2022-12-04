#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
class Camera {
public:
	Camera()
		: m_theta(0.0f),
		m_phi(0.0f),
		m_radius(0.0f),
		m_up(1.0f),
		/*m_target(DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)),
		m_view(DirectX::XMMatrixIdentity()),
		m_proj(DirectX::XMMatrixIdentity()),*/
		m_viewNeedsUpdate(true) {
	}
	Camera(float theta, float phi, float radius)
		: m_theta(theta),
		m_phi(phi),
		m_radius(radius),
		m_up(1.0f),
		/*m_target(DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)),
		m_view(DirectX::XMMatrixIdentity()),
		m_proj(DirectX::XMMatrixIdentity()),*/
		m_viewNeedsUpdate(true) {
	}

private:
	float m_theta;
	float m_phi;
	float m_radius;
	float m_up;
	
	float m_cameraScrollFactor;

	glm::vec3 m_target;

	glm::vec4 m_view;
	glm::vec4 m_proj;

	bool m_viewNeedsUpdate;

public:
	void Rotate(float dTheta, float dPhi);
	void Zoom(float distance);
	void Pan(float dx, float dy);

	/**
	 * Re-creates the internal projection matrix based on the input parameters
	 *
	 * @param clientWidth     The width of the client window
	 * @param clientHeight    The height of the client window
	 * @param nearClip        The distance to the near clip plane
	 * @param farClip         The distance to the far clip plane
	 */
	void UpdateProjectionMatrix(float clientWidth, float clientHeight, float nearClip, float farClip);

	/**
	 * Returns the position of the camera in Cartesian coordinates
	 *
	 * @return    The position of the camera
	 */
	/*inline DirectX::XMFLOAT3 GetCameraPosition() const {
		DirectX::XMFLOAT3 temp;
		DirectX::XMStoreFloat3(&temp, GetCameraPositionXM());

		return temp;
	}*/
	/**
	 * Returns the position of the camera in Cartesian coordinates
	 *
	 * @return    The position of the camera
	 */
	/*inline DirectX::XMVECTOR GetCameraPositionXM() const {
		return DirectX::XMVectorAdd(m_target, ToCartesian());
	}*/

	/**
	 * Returns the view matrix represented by the camera
	 *
	 * @return    The view matrix
	 */
	/*inline DirectX::XMMATRIX GetView() {
		if (m_viewNeedsUpdate) {
			UpdateViewMatrix();
			m_viewNeedsUpdate = false;
		}

		return m_view;
	}*/
	/**
	 * Returns the internal projection matrix
	 *
	 * @return    The projection matrix
	 */
	//inline DirectX::XMMATRIX GetProj() { return m_proj; }

private:
	void UpdateViewMatrix();
	void MouseDown();
	void MouseMove();
	void MouseUp();
	void MouseWheel(int zDelta);
	glm::vec4 ToCartesian() const {
		float x = m_radius * sinf(m_phi) * sinf(m_theta);
		float y = m_radius * cosf(m_phi);
		float z = m_radius * sinf(m_phi) * cosf(m_theta);
		float w = 1.0f;

		return glm::vec4(x, y, z, w);
	}
};
