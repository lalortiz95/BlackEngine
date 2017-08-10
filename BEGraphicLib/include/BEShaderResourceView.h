#pragma once
#include "BEPrerequisitesGraphics.h"
#include "BETexture.h"

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	struct GraphicsAPIData;
	struct ShaderResourceViewData;

	///Declaration of the shader resource view class.
	class BE_GRAPHICS_EXPORT BEShaderResourceView
	{
	public:
		///Default constructor and destructor.
		BEShaderResourceView();
		~BEShaderResourceView();

		///This functions give and release memory from the class' variables.
		bool Initialize();
		void Destroy();

		///Creates the shader resource with the device, upon a given texture.
		bool Create(const BETexture* data);

		///this variable stores the shader resource view data.
		ShaderResourceViewData* m_SRVData;
	};
}