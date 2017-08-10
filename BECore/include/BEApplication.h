#pragma once

#include "BEPrerequisitesCore.h"
#include <BEGraphicsAPI.h>
#include <BETexture.h>
#include <BEIOInterface.h>

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

		void* GetScrHandle() { return m_ScrHandle; }
		int32 GetWidth() { return m_Width; }
		int32 GetHeight() { return m_Height; }

		///The render function.
		virtual void OnUpdate(float delta) {};
		virtual void OnRender() {};

	protected:
		String m_szTitle;
		void* m_ScrHandle;
		int32 m_Width;
		int32 m_Height;

		/// The interface to handle the inputs.
		BEIOInterface m_InputInterface;

	private:
		bool Initialize();
		void Destroy();
		bool InitializeWindow(int width, int height, bool windowed);
		int messageloop();
		///Updates EveryFrame.
		void Update(float delta);
		void Render();
		ApplicationData* m_AppData;
	};
}