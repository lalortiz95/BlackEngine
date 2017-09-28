#pragma once
#include "BEPrerequisitesEngine.h"
#include "BEParticle.h"

#include <Vector3D.h>

namespace BlackEngine
{
	class BE_ENGINE_EXPORT BETransmitter
	{
	public:
		/// Default Constructor and destructor.
		BETransmitter();
		~BETransmitter();

		/// 
		void Initialize(Vector3D pos, Vector3D dir, int32 maxParticles, float emissionStartTime, float emissionEndTime, float v0);
		/// 
		void Destroy();
		/// 
		void Update(float fDelta);

		/// Particle's position.
		Vector3D m_Position;
		/// Particle's moving direction.
		Vector3D m_Direction;
		/// The maximum amount
		int32 m_MaxParticleAmount;
		/// 
		float m_EmissionStartTime;
		/// 
		float m_EmissionEndTime;
		/// The initial speed given to each particle.
		float m_InitialSpeed;
		/// A rotating angle to be applied to the particles.
		float m_RotationAngle;
		/// The gravity affecting the particles.
		float m_Gravity;
		/// 
		int32 m_ParticlesPerFrame;

		/// Where we store the particles from this system.
		Vector<BEParticle> m_Particles;
	};
}