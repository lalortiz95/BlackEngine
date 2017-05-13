#pragma once
#include "BEShader.h"

namespace BlackEngine
{
	struct ShaderData;

	class BE_GRAPHICS_EXPORT BEVertexShader : public BEShader
	{
	public:
		BEVertexShader();
		virtual ~BEVertexShader();

		virtual bool Initialize();
		virtual void Destroy();

		virtual void Reflect();
		virtual bool CreateShader(const GraphicsAPIData* pGraphicData, const String& FileName, const String& Target, const String& EntryPoint);

		VertexShaderData* m_VSData;
	};
}
