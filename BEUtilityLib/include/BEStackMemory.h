#pragma once
#include "BEPrerequisitesUtility.h"
#include "BEStdHeaders.h"

namespace BlackEngine
{
	template<class T>
	class BE_UTILITY_EXPORT BEStackMemory
	{
	public:
		BEStackMemory() _NOEXCEPT {};

		typedef T value_type;

		///tamaño de la memoria que se aloja.
		char m_Size[1024 * 1024];
		///variable donde se guarda la posición donde se alcanzó a aalmacenar memoria por última vez.
		value_type m_StartPos;
		///variable donde se va a guardar a continuación, en caso de desalojar memoria esta variable 
		///apunta a la última posición  donde se empezó a alojar. 
		value_type m_ActualPos;
		///end = ptr + size;
		value_type m_EndPos;


		///función que guarda memoria y manda a sobreescribir memoria.
		value_type AllocateMemory()
		{
			return m_StartPos = m_ActualPos;

			m_ActualPos += sizeof(value_type);
			/////agregamos un nuevo lugar al arreglo.
			//Memory[m_MemorySize] = new value_type();
			//
			////TO-DO: hacer que esta variable se guarde sólo la primera vez que entra en la función.
			//m_StartPos = Memory[m_MemorySize];
		}

		void FreeMemory()
		{
			///recorro el apuntador a la última posición donde se alojó memoria.
			m_ActualPos = m_StartPos;
		}
	};
}