#pragma once
#include "BEPrerequisitesEngine.h"
#include "BETransmitter.h"
#include "BEForce.h"

namespace BlackEngine
{
	class BE_ENGINE_EXPORT BEParticleSystem
	{
	public:
		BEParticleSystem();
		~BEParticleSystem();

		Vector<BETransmitter> m_Transmitters;
		Vector<BEForce> m_Forces;
	};
}