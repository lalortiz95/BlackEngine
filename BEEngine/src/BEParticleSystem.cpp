#include "BEParticleSystem.h"

namespace BlackEngine
{
	BEParticleSystem::BEParticleSystem()
	{
	
	}

	BEParticleSystem::~BEParticleSystem()
	{

	}

	void BEParticleSystem::Initialize()
	{

	}

	void BEParticleSystem::Destroy()
	{
	
	}

	void BEParticleSystem::Update(float fDelta)
	{
		for (int32 i  = 0; i < m_Transmitters.size(); ++i)
		{
			m_Transmitters[i].Update(fDelta);
		}

		for (int32 i = 0; i < m_Forces.size(); ++i)
		{
			m_Forces[i].Update(fDelta);
		}
	}
}