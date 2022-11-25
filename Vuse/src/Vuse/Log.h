#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Vuse {

	class Log {
	public:
		static void Init();
	
		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; };

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
	

}

// core log macros
#define VUSE_CORE_ERROR(...) ::Vuse::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VUSE_CORE_WARN(...)  ::Vuse::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VUSE_CORE_INFO(...)  ::Vuse::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VUSE_CORE_TRACE(...) ::Vuse::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VUSE_CORE_CRITICAL(...) ::Vuse::Log::GetCoreLogger()->critical(__VA_ARGS__)

// client log macros
#define VUSE_ERROR(...)  ::Vuse::Log::GetClientLogger()->error(__VA_ARGS__)
#define VUSE_WARN(...)   ::Vuse::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VUSE_INFO(...)   ::Vuse::Log::GetClientLogger()->info(__VA_ARGS__)
#define VUSE_TRACE(...)  ::Vuse::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VUSE_CRITICAL(...)  ::Vuse::Log::GetClientLogger()->critical(__VA_ARGS__)