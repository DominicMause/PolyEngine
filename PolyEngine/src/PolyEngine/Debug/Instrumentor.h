#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <thread>

namespace PolyEngine
{
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string Name;
		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	public:
		Instrumentor()
			: m_CurrentSession(nullptr)
		{}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				if (Log::GetCoreLogger())
				{
					PE_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
				}
				InternalEndSession();
			}
			m_OutputStream.open(filepath);
			if (m_OutputStream.is_open())
			{
				m_CurrentSession = new InstrumentationSession{ name };
				WriteHeader();
			}
			else
			{
				if (Log::GetCoreLogger())
				{
					PE_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
				}
			}
		}

		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)
		{

			std::stringstream json;

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			json << std::setprecision(3) << std::fixed;
			json << "{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}

	private:
		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		void InternalEndSession()
		{
			if (m_CurrentSession)
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::steady_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() 
				- std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}

#define PE_PROFILE 0
#if PE_PROFILE
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define PE_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define PE_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define PE_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define PE_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define PE_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define PE_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define PE_FUNC_SIG __func__
	#else
		#define PE_FUNC_SIG "PE_FUNC_SIG unknown!"
	#endif
#define PE_PROFILE_BEGIN_SESSION(name, filepath) ::PolyEngine::Instrumentor::Get().BeginSession(name, filepath)
#define PE_PROFILE_END_SESSION() ::PolyEngine::Instrumentor::Get().EndSession()
#define PE_PROFILE_SCOPE(name) ::PolyEngine::InstrumentationTimer timer##__LINE__(name);
#define PE_PROFILE_FUNCTION() PE_PROFILE_SCOPE(PE_FUNC_SIG)
#else
#define PE_PROFILE_BEGIN_SESSION(name, filepath)
#define PE_PROFILE_END_SESSION()
#define PE_PROFILE_SCOPE(name)
#define PE_PROFILE_FUNCTION()
#endif