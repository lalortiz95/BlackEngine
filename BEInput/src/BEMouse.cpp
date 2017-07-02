#include "BEMouse.h"

namespace BlackEngine
{
	/// Default constructor.
	BEMouse::BEMouse()
	{

	}

	///Default destructor.
	BEMouse::~BEMouse()
	{
		Destroy();
	}

	/// This Function Initializes and gives memory to the class' variables.
	void BEMouse::Initialize(void* pScrHandle, void* pInterface)
	{
		HRESULT hRes;
		IDirectInput8* pInputInterface = reinterpret_cast<IDirectInput8*>(pInterface);

		/// We create our mouse device.
		hRes = pInputInterface->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
		if (FAILED(hRes))
		{

		}

		/// We set the data format that it'll have.
		hRes = m_mouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(hRes))
		{

		}

		/// Set the cooperative level.
		hRes = m_mouse->SetCooperativeLevel(reinterpret_cast<HWND>(pScrHandle), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(hRes))
		{

		}

		/// We acquire the mouse state.
		hRes = m_mouse->Acquire();
		if (FAILED(hRes))
		{

		}
	}

	/// Releases memory and deletes memeber variables.
	void BEMouse::Destroy()
	{
		if (m_mouse != nullptr)
		{
			m_mouse->Unacquire();
			m_mouse->Release();
		}
	}

	void BEMouse::Update()
	{
		HRESULT hRes;
		memcpy(&m_lastMouseState, &m_mouseState, sizeof(m_mouseState));

		hRes = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState);
		if (FAILED(hRes))
		{
			if ((hRes == DIERR_INPUTLOST) || (hRes == DIERR_NOTACQUIRED))
			{
				m_mouse->Acquire();
			}
		}

		//TODO: llamar a la funcion ispressed con la key que se quiera revisar.
		//ej. Is Pressed(KEY_A);
	}
}