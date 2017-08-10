#include "BEController.h"

namespace BlackEngine
{
	BEController::BEController()
	{

	}

	BEController::~BEController()
	{
		Destroy();
	}

	void BEController::Initialize(void * pScrHandle, void * pInterface)
	{
		HRESULT hRes;

		IDirectInput8* pInputInterface = reinterpret_cast<IDirectInput8*>(pInterface);

		//Setting up the keyboard:
		hRes = pInputInterface->CreateDevice(GUID_SysKeyboard, &m_controller, NULL);
		if (FAILED(hRes))
		{
		}

		hRes = m_controller->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hRes))
		{
		}

		hRes = m_controller->SetCooperativeLevel(reinterpret_cast<HWND>(pScrHandle), DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(hRes))
		{
		}

		hRes = m_controller->Acquire();

		if (!FAILED(hRes))
		{
		}
	}

	void BEController::Destroy()
	{
		if (nullptr != m_controller)
		{
			m_controller->Unacquire();
			m_controller->Release();
		}
	}

	void BEController::Update()
	{
		HRESULT hRes;
		/// Set the last state.
		memcpy(&m_lastControllerState, &m_ControllerState, sizeof(m_ControllerState));

		///Get the new state.
		hRes = m_controller->GetDeviceState(sizeof(m_ControllerState), &m_ControllerState);
		if (FAILED(hRes))
		{
			/// If the keyboard lost focus or was not acquired then try to get control back.
			if ((hRes == DIERR_INPUTLOST) || (hRes == DIERR_NOTACQUIRED))
			{
				m_controller->Acquire();
			}
		}
	}

	bool BEController::IsPressed(uint8 key)
	{
		//TODO: implementar
		return false;
		//return (m_ControllerState.rgbButtons[key] & 0x80);
	}
}