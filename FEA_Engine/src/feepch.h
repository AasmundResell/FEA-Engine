#pragma once

//common stuff
#include <iostream>
#include <memory> //includes smart pointers
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>

//Data structures
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "FEA_Engine\Log.h" 

//for windows specific files
#ifdef FEE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif