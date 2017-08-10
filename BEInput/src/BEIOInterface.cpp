#include "BEIOInterface.h"

namespace BlackEngine
{
	///Deefault constructor.
	BEIOInterface::BEIOInterface()
	{

	}

	/// Default destructor.
	BEIOInterface::~BEIOInterface()
	{
		Destroy();
	}

	/// This function initializes it's variables.
	void BEIOInterface::Initialize(void* ScrHandle)
	{
		HRESULT hRes;
		HINSTANCE hInstance = ::GetModuleHandleA(NULL);

		/// We create our direct input.
		hRes = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_DirectInput, NULL);
		if (FAILED(hRes))
		{
		}

		/// Set the keyboard input.
		m_Keyboard.Initialize(ScrHandle, m_DirectInput);
		m_Mouse.Initialize(ScrHandle, m_DirectInput);
		m_Controller.Initialize(ScrHandle, m_DirectInput);
	}

	/// Releases memory and deletes memeber variables.
	void BEIOInterface::Destroy()
	{
		m_Controller.Destroy();
		m_Mouse.Destroy();
		m_Keyboard.Destroy();

		if (m_DirectInput != nullptr)
		{
			m_DirectInput->Release();
		}
	}

	void BEIOInterface::Update()
	{
		m_Keyboard.Update();
		m_Mouse.Update();
		m_Controller.Update();
	}
}