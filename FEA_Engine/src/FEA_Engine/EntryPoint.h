#pragma once

#ifdef FEE_PLATFORM_WINDOWS

//extern specifies that the symbol has external linkage
//this pointer lets us call CreateApplication from an application

extern FEE::Application* FEE::CreateApplication();

//main loop	
int main(int argc, char** argv)
{
	printf("FEA Engine\n");
	auto app = FEE::CreateApplication();
	//Heap allocated because the sandbox can be very large, need to have control over its lifetime	
	app->run();
	delete app;
}

#endif 