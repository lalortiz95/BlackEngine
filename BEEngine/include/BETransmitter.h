#pragma once
#include "BEPrerequisitesEngine.h"
#include <Vector3D.h>

namespace BlackEngine
{
	class BE_ENGINE_EXPORT BETransmitter
	{
	public:
		/// Default Constructor and destructor.
		BETransmitter();
		~BETransmitter();

		/// Particle's position.
		Vector3D m_Position;
		/// Particle's moving direction.
		Vector3D m_Direction;
		/// The maximum amount
		int32 m_MaxParticleAmount;
		float m_EmissionStartTime;
		float m_EmissionEndTime;
		float m_EmissionTime;
		float m_InitialSpeed;
		//TODO: giro?
		float m_Gravity;
	};
}