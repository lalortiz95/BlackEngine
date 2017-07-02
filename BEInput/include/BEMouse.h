#pragma once
#include "BEPrerequisitesInput.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

/// The engine's namespace.
namespace BlackEngine
{
	/// Definition of the mouse class.
	class BE_INPUT_EXPORT BEMouse
	{
	public:
		/// Default constructor.
		BEMouse();
		/// Default destructor.
		~BEMouse();

		/// This Function Initializes and gives memory to the class' variables.
		void Initialize(void* pScrHandle, void* pInterface);
		/// Releases memory and deletes memeber variables.
		void Destroy();
		/// Update mouse state.
		void Update();

		/// Input where we store our mouse.
		IDirectInputDevice8* m_mouse;
		/// In this variable we store the mouse state.
		DIMOUSESTATE m_mouseState;
		/// Previous mouse state.
		DIMOUSESTATE m_lastMouseState;
	};
}