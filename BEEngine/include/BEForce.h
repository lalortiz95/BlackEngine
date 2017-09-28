#pragma once
#include "BEPrerequisitesEngine.h"

namespace BlackEngine
{
	class BE_ENGINE_EXPORT BEForce
	{
	public:
		/// Default constructor and destructor.
		BEForce();
		~BEForce();

		/// 
		void Initialize();
		/// 
		void Destroy();
		/// 
		void Update(float fDelta);
	};
}