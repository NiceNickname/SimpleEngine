#include "pch.h"

#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Engine {

	std::shared_ptr<spdlog::logger> Log::EngineCoreLogger;
	std::shared_ptr<spdlog::logger> Log::ClientLogger;


	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		EngineCoreLogger = spdlog::stdout_color_mt("ENGINE");
		EngineCoreLogger->set_level(spdlog::level::trace);

		ClientLogger = spdlog::stdout_color_mt("GAME");
		ClientLogger->set_level(spdlog::level::trace);
	}

}