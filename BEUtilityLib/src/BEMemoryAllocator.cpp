#include "BEPrerequisitesUtility.h"

namespace BlackEngine
{
	BE_THREADLOCAL uint64 MemoryCounter::m_Allocs = 0;
	BE_THREADLOCAL uint64 MemoryCounter::m_Frees = 0;
}