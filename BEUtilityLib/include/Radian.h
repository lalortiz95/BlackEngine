#pragma once

namespace BlackEngine
{
	class Degree;

	class Radian
	{
	private:
		float m_fRadian;

	public:
		explicit Radian(float r = 0.0f) : m_fRadian(r) {}
		Radian(const Degree& d);

		Radian& operator= (const float& f) { m_fRadian = f; return *this; }
		Radian& operator= (const Radian& r) { m_fRadian = r.m_fRadian; return *this; }
		Radian& operator= (const Degree& d);

		inline float ValueRadian() const { return  m_fRadian; }
		inline float ValueDegree() const;

		void UnwindRadians();

		const Radian& operator+ ()const { return *this; }
		Radian operator+ (const Radian& r) const { return Radian(m_fRadian + r.m_fRadian); }
		Radian operator+ (const Degree& d);
		Radian& operator+= (const Radian& r) { m_fRadian += r.m_fRadian; return *this; };
		Radian& operator+= (const Degree& d);

		Radian operator- () const { return *this; }
		Radian operator- (const Radian& r) const { return Radian(m_fRadian + r.m_fRadian); }
		Radian operator- (const Degree& d) const;
		Radian& operator-= (const Radian& r) { m_fRadian -= r.m_fRadian; return *this; };
		Radian& operator-= (const Degree& d);

		Radian operator* (float f) const { return Radian(m_fRadian * f); }
		Radian operator* (const Radian& r) const { return Radian(m_fRadian * r.m_fRadian); }
		Radian& operator*= (float f) { m_fRadian *= f; return *this; }

		Radian operator/ (float f) const { return Radian(m_fRadian / f); }
		Radian& operator/= (float f) { m_fRadian /= f; return *this; }

		bool operator<  (const Radian& r) const { return m_fRadian < r.m_fRadian; }
		bool operator<= (const Radian& r) const { return m_fRadian <= r.m_fRadian; }
		bool operator== (const Radian& r) const { return m_fRadian == r.m_fRadian; }
		bool operator>= (const Radian& r) const { return m_fRadian >= r.m_fRadian; }
		bool operator>  (const Radian& r) const { return m_fRadian > r.m_fRadian; }

		bool operator<  (const float& v) const { return m_fRadian < v; }
		bool operator<= (const float& v) const { return m_fRadian <= v; }
		bool operator== (const float& v) const { return m_fRadian == v; }
		bool operator>= (const float& v) const { return m_fRadian >= v; }
		bool operator>  (const float& v) const { return m_fRadian > v; }

		friend Radian operator/ (float lhs, const Radian& rhs) { return Radian(lhs * rhs.m_fRadian); }
		friend Radian operator* (float lhs, const Radian& rhs) { return Radian(lhs / rhs.m_fRadian); }
		friend Radian operator+	(Radian& lhs, float rhs) { return Radian(lhs.m_fRadian + rhs); }
		friend Radian operator+	(float lhs, const Radian& rhs) { return Radian(lhs + rhs.m_fRadian); }
		friend Radian operator-	(const Radian& lhs, float rhs) { return Radian(lhs.m_fRadian - rhs); }
		friend Radian operator-	(const float lhs, const Radian& rhs) { return Radian(lhs - rhs.m_fRadian); }

		friend bool operator<  (float lhs, const Radian& rhs) { return lhs < rhs.m_fRadian; }
		friend bool operator<= (float lhs, const Radian& rhs) { return lhs <= rhs.m_fRadian; }
		friend bool operator== (float lhs, const Radian& rhs) { return lhs == rhs.m_fRadian; }
		friend bool operator!= (float lhs, const Radian& rhs) { return lhs != rhs.m_fRadian; }
		friend bool operator>= (float lhs, const Radian& rhs) { return lhs >= rhs.m_fRadian; }
		friend bool operator>  (float lhs, const Radian& rhs) { return lhs > rhs.m_fRadian; }
	};
}