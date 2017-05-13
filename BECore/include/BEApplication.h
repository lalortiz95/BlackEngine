#pragma once

#include "BEPrerequisitesCore.h"
#include <BEGraphicsAPI.h>
#include <BETexture.h>

namespace BlackEngine
{
	struct ApplicationData;
	struct BufferData;

	class BE_CORE_EXPORT BEApplication
	{
	public:
		BEApplication();
		virtual ~BEApplication();

		virtual void Update(float /*delta*/) {};

		int Run();
		virtual void OnPreInitialize();
		virtual void OnInitialize();
		virtual void OnPostInitialize(); //also called as OnInitialized.

		virtual void OnPreDestroy();
		virtual void OnDestroy();

		virtual void OnSize(int32 request, int32 width, int32 height);

		int GetScrHandle() { return m_ScrHandle; }
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }

		virtual void Render() {};

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