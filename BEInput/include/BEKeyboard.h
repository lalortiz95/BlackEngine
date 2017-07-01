#pragma once
#include "BEPrerequisitesInput.h"

/// The engine's namespace.
namespace BlackEngine
{
	/// Definition of Keyboard class. It'll handle keyboard input events.
	class BE_INPUT_EXPORT BEKeyboard
	{
	public:
		///Default constructor and destructor.
		BEKeyboard();
		~BEKeyboard();

		/// This Function Initializes and gives memory to the class' variables.
		void Initialize();
		///Releases memory and deletes memeber variables.
		void Destroy();
	};
}