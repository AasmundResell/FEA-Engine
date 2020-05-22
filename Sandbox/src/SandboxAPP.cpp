#include "FEA_Engine.h"


class ExampleLayer : public FEE::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//FEE_INFO("ExampleLayer::Update");
	}
	
	void OnEvent(FEE::Event& event) override
	{
		FEE_TRACE("{0}",event);
	}
};

class Sandbox : public FEE::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer()); 
		PushLayer(new FEE::ImGuiLayer());
	}

	~Sandbox()
	{

	}


};


FEE::Application* FEE::CreateApplication()
{
	//creates the specific instant of this sandbox
	return new Sandbox();

}