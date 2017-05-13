#pragma once
#include "BEShader.h"

namespace BlackEngine
{
	struct ShaderData;

	class BE_GRAPHICS_EXPORT BEPixelShader : public BEShader
	{
	public:
		BEPixelShader();
		virtual ~BEPixelShader();

		virtual bool Initialize();
		virtual void Destroy();

		virtual void Reflect();
		virtual bool CreateShader(const GraphicsAPIData* pGraphicData, const String& FileName, const String& Target = "ps_5_0", const String& EntryPoint = "PS");
	
		PixelShaderData* m_PSData;
	};
}

