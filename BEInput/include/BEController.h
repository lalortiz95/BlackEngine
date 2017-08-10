#pragma once
#include "BEPrerequisitesInput.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

/// The engine's namespace.
namespace BlackEngine
{
	/// Declaration of the Controller input class.
	class BE_INPUT_EXPORT BEController
	{
	public:
		///Default constructor and destructor.
		BEController();
		~BEController();

		/// This Function Initializes and gives memory to the class' variables.
		void Initialize(void* pScrHandle, void* pInterface);
		/// Releases memory and deletes memeber variables.
		void Destroy();
		/// Update mouse state.
		void Update();

		/// Function needed to know if a key of the mouse was pressed.
		bool IsPressed(uint8 key);

		/// Input where we store our controller.
		IDirectInputDevice8* m_controller;
		/// In this variable we store the controller state.
		DIJOYSTATE m_ControllerState;
		/// Previous controller state.
		DIJOYSTATE m_lastControllerState;
	};
}