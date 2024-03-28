#pragma once

#define _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "PolyEngine/Core/Log.h"

#ifdef PE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif