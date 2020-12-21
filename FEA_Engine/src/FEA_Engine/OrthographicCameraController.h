#pragma once

#include "Renderer/OrthographicCamera.h"
#include "FEA_Engine/Core/Timestep.h"

#include "FEA_Engine/Events/ApplicationEvent.h"
#include "FEA_Engine/Events/MouseEvent.h"

namespace FEE {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false); // aspectratio * 2 units

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthoGraphicCamera& GetCamera() { return m_Camera; }	
		const OrthoGraphicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

 	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowsResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		//These to floats has to be above m_Camera because they are used to initialize the camera
		OrthoGraphicCamera m_Camera;
		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}