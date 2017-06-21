#pragma once

#include "BEPrerequisitesCore.h"
#include <BEGraphicsAPI.h>
#include <BETexture.h>

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	struct ApplicationData;
	struct BufferData;

	///Declaration of the application class.
	class BE_CORE_EXPORT BEApplication
	{
	public:
		///Default constructor and destructor.
		BEApplication();
		virtual ~BEApplication();

		///Updates EveryFrame.
		virtual void Update(float /*delta*/) {};

		///Ests función llama a todas las necesarias para crear una ventana, inicializar el pipeline grafico
		///Y dejar toda al app lista.
		int Run();
		///When overwritten, this function initializes variables right before ending this class'
		///Initialize function.
		virtual void OnPreInitialize();
		virtual void OnInitialize();
		virtual void OnPostInitialize(); //also called as OnInitialized.

		virtual void OnPreDestroy();
		virtual void OnDestroy();

		virtual void OnSize(int32 request, int32 width, int32 height);

		int GetScrHandle() { return m_ScrHandle; }
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }

		///The render function.
		virtual void Render() {};

		///This funcion will move the camera forward
		virtual void MoveViewForward();
		virtual void MoveViewBack();
		virtual void MoveViewLeft();
		virtual void MoveViewRight();
		virtual void MoveViewUp();
		virtual void MoveViewDown();

	protected:
		BEGraphicsAPI* m_GraphicsAPI;
		String m_szTitle;
		int32 m_ScrHandle;
		int32 m_Width;
		int32 m_Height;

	private:
		bool Initialize();
		void Destroy();
		bool InitializeWindow(int width, int height, bool windowed);
		int messageloop();

		ApplicationData* m_AppData;
	};
}