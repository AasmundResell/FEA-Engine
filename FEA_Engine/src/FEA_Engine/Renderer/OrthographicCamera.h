#pragma once

#include <glm/glm.hpp>

namespace FEE {

	class OrthoGraphicCamera
	{
	public:
		OrthoGraphicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		glm::vec3& GetPosition() { return m_Position; }
		float GetRotation() { return m_Rotation; }

		void SetPosition(const glm::vec3& position) {
			m_Position = position; RecalculateViewMatrix();	}
		void SetRotation(float rotation) {
			m_Rotation = rotation; RecalculateViewMatrix();	}
		 

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		//only need rotation to rotate along the z-axis because its a 2D engine
		float m_Rotation = 0.0f;
	};

}
