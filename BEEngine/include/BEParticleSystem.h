#pragma once
#include "BEPrerequisitesEngine.h"
#include "BETransmitter.h"
#include "BEForce.h"

namespace BlackEngine
{
	class BE_ENGINE_EXPORT BEParticleSystem
	{
	public:
		/// Default constructor and destructor.
		BEParticleSystem();
		~BEParticleSystem();

		/// 
		void Initialize();
		/// 
		void Destroy();
		/// 
		void Update(float fDelta);

		/// 
		Vector<BETransmitter> m_Transmitters;
		Vector<BEForce> m_Forces;
	};
}