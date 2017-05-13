#pragma once
#include "BEPrerequisitesUtility.h"

namespace BlackEngine
{
	class BE_UTILITY_EXPORT BETime
	{
	public:
		BETime();
		~BETime();

		///empieza a contar el timer, esto va antes del game loop.
		void SetStartTime();
		///deja de contar el timer, eto va después del loop.
		void SetEndTime();
		///esta función se utiliza cuando se quiere saber cuantos segundos han pasado.
		float ConvertToSeconds();
		/////funcion que regresa el tiempo que ha pasado.
		//float Delta();

		int64 m_ClockFrequency;
		int64 m_StartTime;
		int64 m_EndTime;
	};
}
