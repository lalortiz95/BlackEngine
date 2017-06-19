#pragma once
#include "BEShader.h"

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	struct ShaderData;

	///Declaration of the pixel shader class.
	///we set it so that it gets exported to the library.
	class BE_GRAPHICS_EXPORT BEPixelShader : public BEShader
	{
	public:
		///Default Constructor and destructor.
		BEPixelShader();
		virtual ~BEPixelShader();

		///This functions give and release memory from the class' variables.
		virtual bool Initialize();
		virtual void Destroy();

		virtual void Reflect();
		///Creates the pixel shader, and if succeded, returns true.
		virtual bool CreateShader(const GraphicsAPIData* pGraphicData, const String& FileName, const String& Target = "ps_5_0", const String& EntryPoint = "PS");

		///Variable where we store the PixelShader API data.
		PixelShaderData* m_PSData;
	};
}

