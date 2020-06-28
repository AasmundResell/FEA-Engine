#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace FEE {

	class FEE_API Log
	{
	public:
		static void init();
		
		//create two loggers, one for the engine(core) and one for the application(client)
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

//these will forward the arguments from the macro(...)?? to the actual function error, warn etc.

//Core Log Macros
#define FEE_CORE_ERROR(...)    ::FEE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FEE_CORE_WARN(...)     ::FEE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FEE_CORE_INFO(...)     ::FEE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FEE_CORE_TRACE(...)    ::FEE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FEE_CORE_FATAL(...)    ::FEE::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define FEE_ERROR(...)         ::FEE::Log::GetClientLogger()->error(__VA_ARGS__)
#define FEE_WARN(...)          ::FEE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FEE_INFO(...)          ::FEE::Log::GetClientLogger()->info(__VA_ARGS__)
#define FEE_TRACE(...)         ::FEE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FEE_FATAL(...)         ::FEE::Log::GetClientLogger()->fatal(__VA_ARGS__)

#define SOLVER_ERROR(...)      ::FEE::Log::GetClientLogger()->error(__VA_ARGS__)
#define SOLVER_WARN(...)       ::FEE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SOLVER_INFO(...)       ::FEE::Log::GetClientLogger()->info(__VA_ARGS__)
#define SOLVER_TRACE(...)      ::FEE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SOLVER_FATAL(...)      ::FEE::Log::GetClientLogger()->fatal(__VA_ARGS__)

