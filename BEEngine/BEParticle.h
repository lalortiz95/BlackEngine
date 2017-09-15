#pragma once
#include "BEPrerequisitesEngine.h"
#include "BEModelResource.h"
#include <Vector3D.h>

#include "BETextureResource.h"

namespace BlackEngine
{
	class BE_ENGINE_EXPORT BEParticle
	{
	public:
		/// Default constructor and destructor.
		BEParticle();
		~BEParticle();

		/// Particle's position.
		Vector3D m_Position;
		/// Particle's moving direction.
		Vector3D m_Direction;

		/// The particle's speed;
		float m_Speed;
		/// How long will the particle live.
		float m_SpanTime;

		/// The model that represents the particle.
		BEModelResource m_Model;
		/// Sprite that represents the particle.
		BETextureResource m_Sprite;
	};
}