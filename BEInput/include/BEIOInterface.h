#pragma once
#include "BEPrerequisitesInput.h"
#include "BEMouse.h"
#include "BEKeyboard.h"
#include "BEController.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

/// The engine's namespace.
namespace BlackEngine
{
	/// Declaration of the input/output interface class.
	class BE_INPUT_EXPORT BEIOInterface
	{
	public:
		///Default constructor and destructor.
		BEIOInterface();
		~BEIOInterface();

		/// This function initializes it's variables.
		void Initialize(void* scrHandle);
		/// Releases memory and deletes memeber variables.
		void Destroy();
		/// Calls it's member's updates.
		void Update();

		///Where we store our inputs.
		IDirectInput8 *m_DirectInput;
		/// Stores our mouse input.
		BEMouse m_Mouse;
		/// Stores our keyboard input.
		BEKeyboard m_Keyboard;
		/// Stores our joystick input.
		BEController m_Controller;
	};
}