#include "BEKeyboard.h"

namespace BlackEngine
{
	/// Default constructor.
	BEKeyboard::BEKeyboard()
	{
		//Initialize(NULL);
	}

	/// Default destructor.
	BEKeyboard::~BEKeyboard()
	{
		Destroy();
	}

	/// This Function Initializes and gives memory to the class' variables.
	void BEKeyboard::Initialize(void* pScrHandle, void* pInterface)
	{
		HRESULT hRes;

		IDirectInput8* pInputInterface = reinterpret_cast<IDirectInput8*>(pInterface);

		//Setting up the keyboard:
		hRes = pInputInterface->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
		if (FAILED(hRes))
		{
		}

		hRes = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hRes))
		{
		}

		hRes = m_keyboard->SetCooperativeLevel(reinterpret_cast<HWND>(pScrHandle), DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(hRes))
		{
		}

		hRes = m_keyboard->Acquire();

		if (!FAILED(hRes))
		{
		}
	}

	///Releases memory and deletes memeber variables.
	void BEKeyboard::Destroy()
	{
		if (m_keyboard != nullptr)
		{
			m_keyboard->Unacquire();
			m_keyboard->Release();
		}
	}

	/// Update keyboard state.
	void BEKeyboard::Update()
	{
		HRESULT hRes;
		/// Set the last state.
		memcpy(&m_LastKeyboardState, m_keyboardState, sizeof(m_keyboardState));

		///Get the new state.
		hRes = m_keyboard->GetDeviceState(sizeof(m_keyboardState), &m_keyboardState);
		if (FAILED(hRes))
		{
			/// If the keyboard lost focus or was not acquired then try to get control back.
			if ((hRes == DIERR_INPUTLOST) || (hRes == DIERR_NOTACQUIRED))
			{
				m_keyboard->Acquire();
			}
		}
	}

	/// Function needed to know if a key of the keyboard was pressed.
	bool BEKeyboard::IsPressed(uint8 key)
	{
		return (m_keyboardState[key]);
	}
}