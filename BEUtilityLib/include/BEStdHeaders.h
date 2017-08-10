#pragma once
#include "BEUtilityPlatformDefines.h"

/************************************************************************/
/* Si estamos en un compilador de Borland                               */
/************************************************************************/
#ifdef __BORLANDC__
#define __STD_ALGORITHM
#endif

/************************************************************************/
/* Tipos de objeto C                                                    */
/************************************************************************/
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>

/************************************************************************/
/* Para manejo de memoria                                               */
/************************************************************************/
#include <memory>

/************************************************************************/
/* STL Containers		                                                */
/************************************************************************/
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>
#include <array>

/************************************************************************/
/* Note - not in the original STL, but exists in SGI STL and STLport	*/
/* For GCC 4.3 see http://gcc.gnu.org/gcc-4.3/changes.html				*/
/************************************************************************/
#if (BE_COMPILER == BE_COMPILER_GNUC)
	#if BE_COMP_VER >= 430
		#include <tr1/unordered_map>
		#include <tr1/unordered_set>
	#elif (BE_PLATFORM == BE_PLATFORM_PS4)
		#include <unordered_map>
		#include <unordered_set>
	#else
		#include <ext/hash_map>
		#include <ext/hast_set>
	#endif
#else
	#if (BE_COMPILER == BE_COMPILER_MSVC) && BE_COMP_VER >= 1600 //VC++ 10.0 or higher
		#include <unordered_map>
		#include <unordered_set>
	#else
		#include <hash_set>
		#include <hash_map>
	#endif
#endif

/************************************************************************/
/* STL algorithms & functions                                           */
/************************************************************************/
#include <algorithm>
#include <functional>
#include <limits>

/************************************************************************/
/* C++ Stream stuff                                                     */
/************************************************************************/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#ifdef __BORLANDC__
namespace BEorceSDK
{
	using namespace std;
}
#endif

/************************************************************************/
/* C Types and Stats                                                    */
/************************************************************************/
extern "C"
{
	#include <sys/types.h>
	#include <sys/stat.h>
}

#if BE_COMPILER == BE_COMPILER_MSVC
#	pragma warning(disable : 4251)
#endif

/************************************************************************/
/* Windows specifics                                                    */
/************************************************************************/
#if BE_PLATFORM == BE_PLATFORM_WIN32
//Undefine min & max
#undef min
#undef max

#if !defined(NOMINMAX) && defined(_MSC_VER)
#define NOMINMAX //Required to stop windows.h messing up std::min
#endif
#if defined(__MINGW32__)
#include <unistd.h>
#endif
#endif

/************************************************************************/
/* Linux specifics                                                      */
/************************************************************************/
#if BE_PLATFORM == BE_PLATFORM_LINUX
extern "C"
{
	#include <unistd.h>
	#include <sys/param.h>
	#include <CoreFoundation/CoreFoundation.h>
}
#endif

#if BE_PLATFORM == BE_PLATFORM_OSX
extern "C"
{
	#include <unistd.h>
	#include <sys/param.h>
	#include <CoreFoundation/CoreFoundation.h>
}
#endif

#if BE_PLATFORM == BE_PLATFORM_PS4
extern "C"
{
	#include <unistd.h>
	#include <sys/param.h>
}
#endif

namespace BlackEngine
{
	template<typename T, typename A = std::allocator<T>>
	using Deque = std::deque<T, A>;

	template <typename T, typename A =  std::allocator<T>>
	using Vector = std::vector<T, A>;

	template <typename T, typename A =  std::allocator<T>>
	using List = std::list<T, A>;

	template <typename T, typename A =  std::allocator<T>>
	using Stack = std::stack<T, std::deque<T, A>>;

	template <typename T, typename A =  std::allocator<T>>
	using Queue = std::queue<T, std::deque<T, A>>;

	template <typename T, typename P = std::less<T>, typename A = std::allocator<T>>
	using Set = std::set<T, P, A>;

	template <typename K, typename V, typename P = std::less<K>, typename A = StdAlloc < std::pair<const K, V>>>
	using Map = std::map<K, V, P, A>;

	template <typename K, typename V, typename P = std::less<K>, typename A = StdAlloc < std::pair<const K, V>>>
	using Multimap = std::multimap<K, V, P, A>;

	template <typename T, typename H = std::hash<T>, typename C = std::equal_to<T>, typename A = std::allocator<T>>
	using UnorderedSet = std::unordered_set<T, H, C, A>;

	template <typename  K, typename V, typename H = std::hash<K>, typename C = std::equal_to<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using UnorderedMap = std::unordered_map<K, V, H, C, A>;

	template <typename  K, typename V, typename H = std::hash<K>, typename C = std::equal_to<K>, typename A = StdAlloc<std::pair<const K, V >>>
	using UnorderedMultimap = std::unordered_multimap<K, V, H, C, A>;
}