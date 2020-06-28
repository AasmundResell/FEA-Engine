#pragma once

#include "FEA_Engine/Core.h"
#include "FEA_Engine/Events/Event.h"
#include "FEA_Engine/Core/Timestep.h"	

namespace FEE {

class FEE_API Layer
{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		//the naming of layers are only for debug builds
		std::string m_DebugName;
	};


}

