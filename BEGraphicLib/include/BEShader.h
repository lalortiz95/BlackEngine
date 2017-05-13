#pragma once
#include "BEPrerequisitesGraphics.h"
#include "DirectXData.h"

namespace BlackEngine
{
	struct ShaderData;

	class BE_GRAPHICS_EXPORT BEShader
	{
	public:
		BEShader();
		virtual ~BEShader();

		///funci�n de inicializar virtual.
		virtual bool Initialize() = 0;
		virtual void Destroy() = 0;

		virtual void Reflect() = 0;
		///funci�n que crea y compila el shader.
		virtual bool CreateShader(const GraphicsAPIData* pGraphicData, const String& FileName, const String& Target, const String& EntryPoint) = 0;

		ShaderData* m_ShaderData;
	};
}