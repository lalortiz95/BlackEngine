#pragma once
#include "BEMath.h"
#include "Radian.h"

namespace BlackEngine
{
	class Degree
	{
	private:
		float m_fDegree;

	public:
		explicit Degree(float d = 0.0f) : m_fDegree(d) {}
		Degree(const Radian& r);

		Degree operator= (const float& f) { m_fDegree = f; return *this; }
		Degree operator= (const Degree& d) { m_fDegree = d.m_fDegree; return *this; }
		Degree operator= (const Radian& r);

		inline float ValueDegree() const { return m_fDegree; };
		inline float ValueRadian(float d) const;

		void UnwindDegrees();

		const Degree& operator+ ()const { return *this; }
		Degree operator+ (const Degree& d) const { return Degree(m_fDegree + d.m_fDegree); }
		Degree operator+ (const Radian& r);
		Degree& operator+= (const Degree& d) { m_fDegree += d.m_fDegree; return *this; };
		Degree& operator+= (const Radian& r);

		Degree operator- () const { return *this; }
		Degree operator- (const Degree& d) const { return Degree(m_fDegree + d.m_fDegree); }
		Degree operator- (const Radian& r) const;
		Degree& operator-= (const Degree& d) { m_fDegree -= d.m_fDegree; return *this; };
		Degree& operator-= (const Radian& r);

		Degree operator* (float f) const { return Degree(m_fDegree * f); }
		Degree operator* (const Degree& d) const { return Degree(m_fDegree * d.m_fDegree); }
		Degree& operator*= (float f) { m_fDegree *= f; return *this; }

		Degree operator/ (float f) const { return Degree(m_fDegree / f); }
		Degree& operator/= (float f) { m_fDegree /= f; return *this; }

		bool operator<  (const Degree& d) const { return m_fDegree < d.m_fDegree; }
		bool operator<= (const Degree& d) const { return m_fDegree <= d.m_fDegree; }
		bool operator== (const Degree& d) const { return m_fDegree == d.m_fDegree; }
		bool operator>= (const Degree& d) const { return m_fDegree >= d.m_fDegree; }
		bool operator>  (const Degree& d) const { return m_fDegree > d.m_fDegree; }

		bool operator<  (const float& v) const { return m_fDegree < v; }
		bool operator<= (const float& v) const { return m_fDegree <= v; }
		bool operator== (const float& v) const { return m_fDegree == v; }
		bool operator>= (const float& v) const { return m_fDegree >= v; }
		bool operator>  (const float& v) const { return m_fDegree > v; }

		friend Degree operator/ (float lhs, const Degree& rhs) { return Degree(lhs * rhs.m_fDegree); }
		friend Degree operator* (float lhs, const Degree& rhs) { return Degree(lhs / rhs.m_fDegree); }
		friend Degree operator+	(Degree& lhs, float rhs) { return Degree(lhs.m_fDegree + rhs); }
		friend Degree operator+	(float lhs, const Degree& rhs) { return Degree(lhs + rhs.m_fDegree); }
		friend Degree operator-	(const Degree& lhs, float rhs) { return Degree(lhs.m_fDegree - rhs); }
		friend Degree operator-	(const float lhs, const Degree& rhs) { return Degree(lhs - rhs.m_fDegree); }

		friend bool operator< (float lhs, const Degree& rhs) { return lhs < rhs.m_fDegree; }
		friend bool operator<= (float lhs, const Degree& rhs) { return lhs <= rhs.m_fDegree; }
		friend bool operator== (float lhs, const Degree& rhs) { return lhs == rhs.m_fDegree; }
		friend bool operator!= (float lhs, const Degree& rhs) { return lhs != rhs.m_fDegree; }
		friend bool operator>= (float lhs, const Degree& rhs) { return lhs >= rhs.m_fDegree; }
		//friend bool operator> (float lhs, const Degree& rhs) { return lhs > rhs.m_fDegree; }
	};
}