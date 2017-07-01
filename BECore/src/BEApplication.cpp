#include "BEApplication.h"
#include <Vector4D.h>
#include <DirectXData.h>

#include <exception>

#define WIN32_LEAN_AND_MEAN //la versión más vacia de windows
#include <Windows.h>

#include <FreeImage.h>

using std::exception;

namespace BlackEngine
{
	const char* g_szClassName = "ENGINE_WND_CLASS";
	BEApplication* g_AppBase = NULL;

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_SIZE:
			g_AppBase->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
			break;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
			{
				DestroyWindow(hwnd);
			}
			if (wParam == 0x57)
			{
				///W key.
				//g_AppBase->MoveForward(1);
			}
			if (wParam == 0x53)
			{
				///S key.
				g_AppBase->MoveForward(-1);
			}
			if (wParam == 0x41)
			{
				///A key.
				g_AppBase->MoveRight(-1);
			}
			if (wParam == 0x44)
			{
				///D key.
				g_AppBase->MoveRight(1);
			}
			if (wParam == VK_SHIFT)
			{
				g_AppBase->MoveUp(1);
			}
			if (wParam == VK_CONTROL)
			{
				g_AppBase->MoveUp(-1);
			}
			return 0;

		case WM_KEYUP:
			if (wParam == 0x57)
			{
				///W key.
				//TODO: llamar funcion dejar de mover.
			}
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	struct ApplicationData
	{
#if BE_PLATFORM == BE_PLATFORM_WIN32
		HWND hwnd;
		LPCTSTR WndClassName;
#else
#	error "Sistema no definido"
#endif
	};

	BEApplication::BEApplication()
	{
		g_AppBase = this;
		m_szTitle = "Black Engine Window";
		m_ScrHandle = 0;
		m_Width = 1024;
		m_Height = 768;
	}

	BEApplication::~BEApplication()
	{
	}

	bool BEApplication::Initialize()
	{
		///aqui inicializo todos los sistemas del motor.
		///graphics, audio, input, physics, managers, etc...
		m_AppData = new ApplicationData();
		m_GraphicsAPI = new BEGraphicsAPI((int)m_ScrHandle, m_Width, m_Height,
			false, DXGI_FORMAT_R8G8B8A8_UNORM, 1, true);

		///inicializamos la libreria de free image.
		FreeImage_Initialise(false);

		m_GraphicsAPI->Initialize(m_ScrHandle, m_Width, m_Height, 1, true);

		OnInitialize();
		return true;
	}

	void BEApplication::Destroy()
	{
		//esto va antes de liberar toda la memoria.
		OnPreDestroy();
		FreeImage_DeInitialise();
	}

	int BEApplication::Run()
	{

		OnPreInitialize();
		if (!InitializeWindow(m_Width, m_Height, true))
		{
			throw exception("falló al inicializar la ventana.");
		}
		if (!Initialize())
		{
			throw exception("falló al inicializar la app.");
		}
		OnPostInitialize();

		messageloop();

		///uninitalizwGameSystems();
		return 0;
	}

	void BEApplication::OnPreInitialize()
	{
	}

	void BEApplication::OnInitialize()
	{
	}

	void BEApplication::OnPostInitialize()
	{
	}

	void BEApplication::OnPreDestroy()
	{
	}

	void BEApplication::OnDestroy()
	{
	}

	void BEApplication::OnSize(int32 /*request*/, int32 /*width*/, int32 /*height*/)
	{

	}

	void BEApplication::MoveForward(float z)
	{
		//TODO: el valor que reciba, positivo o negativo. va a depender si se mueve para adelante o para
		//Atrás. En el override de esta función, se multiplica el valor del parametro por la velocidad
		//por el tiempo.
	}

	void BEApplication::MoveRight(float x)
	{

	}

	void BEApplication::MoveUp(float y)
	{

	}

	bool BEApplication::InitializeWindow(int width, int height, bool windowed)
	{
		HINSTANCE hInstance = ::GetModuleHandleA(NULL);
		WNDCLASSEXA wc;
		memset(&wc, 0, sizeof(WNDCLASSEXA));
		wc.cbSize = sizeof(WNDCLASSEXA);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = NULL;
		wc.cbWndExtra = NULL;
		wc.hInstance = hInstance;
		wc.hIcon = 0;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = 0;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = g_szClassName;
		wc.hIconSm = 0;

		if (RegisterClassEx(&wc) == 0)
		{
			throw exception("falló al registrar la clase de ventana.");
		}

		HWND hwnd;

		if (windowed)
		{
			///creamos la ventana
			hwnd = CreateWindowA
			(
				g_szClassName,			//nombre de la clase
				m_szTitle.c_str(),		//nombre de la ventana
				WS_OVERLAPPEDWINDOW,	//estilode la ventana
				CW_USEDEFAULT,			//posición en X
				CW_USEDEFAULT,			//posicicón en Y
				width,					//width
				height,					//height
				nullptr,				//parent
				nullptr,				//menu
				::GetModuleHandle(NULL),//instancia
				nullptr					//parametros extra
			);
		}
		else
		{
			hwnd = CreateWindowA
			(
				g_szClassName,			//nombre de la clase
				m_szTitle.c_str(),		//nombre de la ventana
				WS_MAXIMIZE,			//estilode la ventana
				CW_USEDEFAULT,			//posición en X
				CW_USEDEFAULT,			//posicicón en Y
				width,					//width
				height,					//height
				nullptr,				//parent
				nullptr,				//menu
				::GetModuleHandle(NULL),//instancia
				nullptr					//parametros extra
			);
		}

		if (!hwnd)
		{
			throw exception("falló al crear la ventana.");
			return false;
		}

		m_ScrHandle = reinterpret_cast<int>(hwnd);

		ShowWindow(reinterpret_cast<HWND>(m_ScrHandle), SW_SHOW);
		UpdateWindow(reinterpret_cast<HWND>(m_ScrHandle));

		return true;
	}

	int BEApplication::messageloop()
	{
		LARGE_INTEGER frequency;
		LARGE_INTEGER counter;
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&counter);

		MSG msg;
		memset(&msg, 0, sizeof(MSG));
		float startTime = static_cast<float>(counter.QuadPart / frequency.QuadPart);
		float endTime = 0;

		while (msg.message != WM_QUIT)
		{
			endTime = startTime;
			startTime = static_cast<float>(counter.QuadPart / frequency.QuadPart);

			while (PeekMessage(&msg, NULL, 0, 0, 1))
			{
				DispatchMessage(&msg);
			}

			double deltaTime = (double)startTime - (double)endTime / (double)frequency.QuadPart;

			Update(startTime - endTime);
			Render();
		}

		OnPreDestroy();
		Destroy();

		return msg.wParam;
	}
}
