#include "Degree.h"

namespace BlackEngine
{
	Degree::Degree(const Radian& /*r*/)
	{

	}

	Degree Degree::operator=(const Radian & r)
	{
		Degree R;
		R.m_fDegree = r.ValueRadian();
		return R;
	}

	inline float Degree::ValueRadian(float D) const
	{
		return D * Math::PI / 180;
	}

	void Degree::UnwindDegrees()
	{
		//TODO: agregar implementación.
	}

	Degree Degree::operator+(const Radian & r)
	{
		Degree R;
		R.m_fDegree = m_fDegree + r.ValueRadian();
		return R;
	}

	Degree & Degree::operator+=(const Radian & r)
	{
		m_fDegree += r.ValueRadian();
		return *this;
	}

	Degree Degree::operator-(const Radian & r) const
	{
		Degree R;
		R.m_fDegree = m_fDegree - r.ValueRadian();
		return R;
	}

	Degree & Degree::operator-=(const Radian & r)
	{
		m_fDegree -= r.ValueRadian();
		return *this;
	}
}