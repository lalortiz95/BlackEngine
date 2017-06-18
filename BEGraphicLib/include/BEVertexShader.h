#pragma once
#include "BEShader.h"

///The eingine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	struct ShaderData;

	///Declaration of BEVertexShaderClass that inherits from BEShader
	class BE_GRAPHICS_EXPORT BEVertexShader : public BEShader
	{
	public:
		///Default constructor and destructor.
		BEVertexShader();
		virtual ~BEVertexShader();

		///This functions give and release memory from the class' variables.
		virtual bool Initialize();
		virtual void Destroy();

		virtual void Reflect();
		///Function that creates a VertexShader.
		virtual bool CreateShader(const GraphicsAPIData* pGraphicData, const String& FileName, const String& Target, const String& EntryPoint);

	private:
		///Variable where we store the vertex shader data
		VertexShaderData* m_VSData;
	};
}
