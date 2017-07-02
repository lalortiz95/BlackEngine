#pragma once
#include "BEPrerequisitesInput.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

/// The engine's namespace.
namespace BlackEngine
{
	/// A const to the fine the size of the buffer where we store the keyboard state.
	static const uint32 BUFFER_SIZE = 256;

	/// Definition of Keyboard class. It'll handle keyboard input events.
	class BE_INPUT_EXPORT BEKeyboard
	{
	public:
		/// Default constructor and destructor.
		BEKeyboard();
		~BEKeyboard();

		/// This Function Initializes and gives memory to the class' variables.
		void Initialize(void* pScrHandle, void* pInterface);
		/// Releases memory and deletes memeber variables.
		void Destroy();
		/// Update keyboard state.
		void Update();

		/// Function needed to know if a key of the keyboard was pressed.
		bool IsPressed(uint8 key);

		///Direct input device where we store de keyboard.
		IDirectInputDevice8* m_keyboard;
		///Stores which keys ares being pressed.
		uint8 m_keyboardState[BUFFER_SIZE];
		/// Copy of the last state.
		uint8 m_LastKeyboardState[BUFFER_SIZE];
	};
}