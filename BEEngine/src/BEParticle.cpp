#include "BEParticle.h"

namespace BlackEngine
{
	BEParticle::BEParticle()
	{

	}

	BEParticle::~BEParticle()
	{
		Destroy();
	}

	void BEParticle::Initialize(Vector3D pos, Vector3D dir, float speed, float spanTime)
	{
		m_Position = pos;
		m_Direction = dir;
		m_Speed = speed;
		m_SpanTime = spanTime;
	}

	void BEParticle::Destroy()
	{
		m_Position = 0;
		m_Direction = 0;
		m_Speed = 0;
		m_SpanTime = 0;
	}

	void BEParticle::Update(float fDelta)
	{
		//TODO: mover.
	}
}