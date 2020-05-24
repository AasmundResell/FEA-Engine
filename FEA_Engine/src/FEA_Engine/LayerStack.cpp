#include "feepch.h"
#include "LayerStack.h"

namespace FEE {

	LayerStack::LayerStack()
	{
	
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayersInsertIndex, layer);
		m_LayersInsertIndex++;
	
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		//puts overlay in the back
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		//removes the given layer
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayersInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		//removes the given overlay
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

}
