#pragma once
#include "BEPrerequisitesGraphics.h"

///The engine's namespace
namespace BlackEngine
{
	///Forward declarations
	struct GraphicsAPIData;
	struct SamplerData;

	///Declaration of the sampler class.
	class BE_GRAPHICS_EXPORT BESampler
	{
	public:
		///Default constructor and destructor.
		BESampler();
		~BESampler();

		///This functions give and release memory from the class' variables.
		void Initialize();
		void Destroy();

		///Creates the sampler.
		void Create();
	
		///This variable stores the sampler data.
		SamplerData* m_SD;
	};
}