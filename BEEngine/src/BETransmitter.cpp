#include "BETransmitter.h"

namespace BlackEngine
{
	BETransmitter::BETransmitter()
	{
		/// Set member variables as default.
		m_Position = 0;
		m_Direction = 0;
		m_MaxParticleAmount = 0;
		m_EmissionStartTime = 0;
		m_EmissionEndTime = 0;
		m_InitialSpeed = 0;
		m_RotationAngle = 0;
	}

	BETransmitter::~BETransmitter()
	{

	}

	void BETransmitter::Initialize(Vector3D pos, Vector3D dir, int32 maxParticles, float emissionStartTime, float emissionEndTime, float v0)
	{
		/// Initialize variables.
		m_Position = pos;
		m_Direction = dir;
		m_MaxParticleAmount = maxParticles;
		m_EmissionStartTime = emissionStartTime;
		m_EmissionEndTime = emissionEndTime;
		m_InitialSpeed = v0;
		m_RotationAngle = 0;

		/// base particle.
		BEParticle newParticle;

		/// initialize the new particles.
		newParticle.Initialize(m_Position, m_Direction, m_InitialSpeed, m_EmissionStartTime);
		///Creates the particles.
		for (int32 i = 0; i < m_MaxParticleAmount; ++i)
		{
			/// Adds the particles to the vector.
			m_Particles.push_back(newParticle);
		}
	}

	void BETransmitter::Destroy()
	{
		/// Change to default.
		m_Position = 0;
		m_Direction = 0;
		m_MaxParticleAmount = 0;
		m_EmissionStartTime = 0;
		m_EmissionEndTime = 0;
		m_InitialSpeed = 0;
		m_RotationAngle = 0;
	}

	void BETransmitter::Update(float fDelta)
	{
		/// Updates every particle.
		for (int32 i = 0; i < m_ParticlesPerFrame; ++i)
		{
			m_Particles[i].m_SpanTime -= fDelta;
			m_Particles[i].m_Position += m_Particles[i].m_Speed * fDelta;

			if (m_Particles[i].m_SpanTime <= 0 + Math::DELTA)
			{
				m_Particles[i].Destroy();
			}
		}
	}
}