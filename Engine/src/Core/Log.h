#pragma once

#include <spdlog/spdlog.h>

namespace Engine {

	class Log
	{
	public:
		
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return EngineCoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger; }
		
	private:
		static std::shared_ptr<spdlog::logger> EngineCoreLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;
	};

}


#define CORE_TRACE(...) Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_WARN(...) Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_INFO(...) Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_ERROR(...) Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define CLIENT_TRACE(...) Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_WARN(...) Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_INFO(...) Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_ERROR(...) Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_CRITICAL(...) Engine::Log::GetClientLogger()->critical(__VA_ARGS__)

#define CORE_ASSERT(x, ...) {if (!(x)) { CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();}}
