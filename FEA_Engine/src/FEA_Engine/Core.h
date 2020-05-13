#pragma once


//declspec used only by windows
#ifdef FEE_PLATFORM_WINDOWS
	#ifdef FEE_BUILD_DLL //will activate the dllexport when the FEA_Engine is built
		#define FEE_API __declspec(dllexport)
	#else //this will be active when the sandbox is used
		#define FEE_API __declspec(dllimport)
	#endif
#else
	#error Wrong platform, only windows compatible
#endif