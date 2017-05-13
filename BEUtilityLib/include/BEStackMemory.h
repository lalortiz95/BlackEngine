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

		///tama�o de la memoria que se aloja.
		char m_Size[1024 * 1024];
		///variable donde se guarda la posici�n donde se alcanz� a aalmacenar memoria por �ltima vez.
		value_type m_StartPos;
		///variable donde se va a guardar a continuaci�n, en caso de desalojar memoria esta variable 
		///apunta a la �ltima posici�n  donde se empez� a alojar. 
		value_type m_ActualPos;
		///end = ptr + size;
		value_type m_EndPos;


		///funci�n que guarda memoria y manda a sobreescribir memoria.
		value_type AllocateMemory()
		{
			return m_StartPos = m_ActualPos;

			m_ActualPos += sizeof(value_type);
			/////agregamos un nuevo lugar al arreglo.
			//Memory[m_MemorySize] = new value_type();
			//
			////TO-DO: hacer que esta variable se guarde s�lo la primera vez que entra en la funci�n.
			//m_StartPos = Memory[m_MemorySize];
		}

		void FreeMemory()
		{
			///recorro el apuntador a la �ltima posici�n donde se aloj� memoria.
			m_ActualPos = m_StartPos;
		}
	};
}