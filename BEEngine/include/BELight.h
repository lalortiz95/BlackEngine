#pragma once
#include "BEPrerequisitesEngine.h"
#include <Vector3D.h>
#include <Vector4D.h>

namespace BlackEngine
{
	class BE_ENGINE_EXPORT BELight
	{
	public:
		BELight();
		~BELight();

		void Initialize();
		void Initialize(Vector3D pos, Vector3D dir, Vector4D lightColor);
		void Destroy();

		///
		Vector3D m_Position;
		Vector3D m_Direction;

		///
		Vector4D m_LightColor;
		Vector4D m_SpecularColor;

		/// The light's intensity.
		float m_Intensity;

		/// The type of light that we're using.
		uint32 m_Type;
	};
}