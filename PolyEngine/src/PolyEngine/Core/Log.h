#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace PolyEngine
{
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core Log macros
#define PE_CORE_TRACE(...)	::PolyEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PE_CORE_INFO(...)	::PolyEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PE_CORE_WARN(...)	::PolyEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PE_CORE_ERROR(...)	::PolyEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PE_CORE_FATAL(...)	::PolyEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros
#define PE_TRACE(...)		::PolyEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PE_INFO(...)		::PolyEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define PE_WARN(...)		::PolyEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PE_ERROR(...)		::PolyEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define PE_FATAL(...)		::PolyEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
