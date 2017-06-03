#include "BETime.h"

#if BE_COMPILER == BE_COMPILER_MSVC
	#include <Windows.h>
#endif


namespace BlackEngine
{
	BETime::BETime()
	{
	}


	BETime::~BETime()
	{
	}

	void BETime::SetStartTime()
	{
		LARGE_INTEGER Frequency;
		LARGE_INTEGER StartTime;
		///guardamos la frecuencia en un Large Integer
		QueryPerformanceFrequency(&Frequency);
		///guardamos el Tiempo de inicio en un Large Integer.
		QueryPerformanceCounter(&StartTime);

		///los almacenamos en las variables miembras de clase int64.
		m_ClockFrequency = Frequency.QuadPart;
		m_StartTime = StartTime.QuadPart;
	}

	void BETime::SetEndTime()
	{
		LARGE_INTEGER endtime;
		///guardamos el tiempo final en un large integer.
		QueryPerformanceCounter(&endtime);
		///lo pasamos a la variable miembra de clase int64.
		m_EndTime = endtime.QuadPart;
	}

	float BETime::ConvertToSeconds()
	{
		LARGE_INTEGER delta;
		///restamos el endtime, menos el start time para ver cuantos ciclos han pasado.
		delta.QuadPart = m_EndTime - m_StartTime;
		///los convertimos a segundos, y regresamos el tiempo que ha pasado.
		return ((float)delta.QuadPart) / ((float)m_ClockFrequency);
	}

	//float BETime::Delta()
	//{
	//	LARGE_INTEGER delta;
	//	LARGE_INTEGER EndTime;
	//	///guardamos el Tiempo final en un Large Integer.
	//	QueryPerformanceCounter(&EndTime);
	//	///restamos el endtime, menos el start time para ver cuantos ciclos han pasado.
	//	delta.QuadPart = EndTime.QuadPart - m_StartTime;
	//	return ((float)delta.QuadPart) / m_ClockFrequency;
	//}
}
