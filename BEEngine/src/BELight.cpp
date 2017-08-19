#include "BELight.h"

namespace BlackEngine
{
	BELight::BELight()
	{

	}

	BELight::~BELight()
	{

	}

	void BELight::Initialize(Vector3D pos, Vector3D dir, Vector4D lightColor)
	{
		m_Position = pos;
		m_Direction = dir;
		m_LightColor = lightColor;
	}
}