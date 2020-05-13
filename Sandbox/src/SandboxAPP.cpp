#include "FEA_Engine.h"

class Sandbox : public FEE::Application
{
public: 
	Sandbox()
	{

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