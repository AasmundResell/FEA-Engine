#pragma once

#include <memory>


#ifdef FEE_PLATFORM_WINDOWS
#if FEE_DYNAMIC_LINK
	#ifdef FEE_BUILD_DLL //will activate the dllexport when the FEA_Engine is built
		#define FEE_API __declspec(dllexport)
	#else //this will be active when the sandbox is used
		#define FEE_API __declspec(dllimport)
	#endif
#else
	#define FEE_API
#endif

#else
	#error Wrong platform, only windows compatible
#endif

#ifdef FEE_DEBUG
	#define FEE_ENABLE_ASSERTS
#endif

#ifdef FEE_ENABLE_ASSERTS
	#define FEE_ASSERT(x, ...) {if(!(x)) { FEE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FEE_CORE_ASSERT(x, ...) {if(!(x)) { FEE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FEE_ASSERT(x, ...) 
	#define FEE_CORE_ASSERT(x, ...)
#endif

#define FEE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

//defines 1 shifted by x-places, ie. BIT(1) is 1
//Uses this to define several category types for each instance
#define BIT(x) (1 << x) 

namespace FEE {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>

	using Ref = std::shared_ptr<T>;

}