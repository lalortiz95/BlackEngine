#pragma once
#include "BEPrerequisitesGraphics.h"
#include "DirectXData.h"

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	struct ShaderData;

	///Declaration of the shader class. its a base clase for many
	///types of shaders.
	class BE_GRAPHICS_EXPORT BEShader
	{
	public:
		///Default constructor and destructor.
		BEShader();
		virtual ~BEShader();

		///This virtual functions give and release memory from the class' variables.
		virtual bool Initialize() = 0;
		virtual void Destroy() = 0;

		virtual void Reflect() = 0;

		///Creates and compiles the shader.
		virtual bool CreateShader(const GraphicsAPIData* pGraphicData, const String& FileName, const String& Target, const String& EntryPoint) = 0;
	
		///This variable stores the shader data.
		ShaderData* m_ShaderData;
	};
}