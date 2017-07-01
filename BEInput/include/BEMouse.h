#pragma once
#include "BEPrerequisitesInput.h"

/// The engine's namespace.
namespace BlackEngine
{
	///
	class BE_INPUT_EXPORT BEMouse
	{
		/// Default constructor.
		BEMouse();
		/// Default destructor.
		~BEMouse();

		/// 
		void Initialize();
		/// 
		void Destroy();
	};
}