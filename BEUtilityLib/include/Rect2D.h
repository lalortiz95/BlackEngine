#pragma once

namespace BlackEngine
{
	class Rect2D
	{
	public:
		///funciones para acceder a la posici�n inicial.
		void SetInitPositions(float x, float y) { m_fX1 = x; m_fY1 = y; }
		void GetInitPositions(float& x, float& y) { x = m_fX1; y = m_fY1; }

		///funciones para acceder a la posici�n final.
		void SetFinalPositions(float x, float y) { m_fX2 = x; m_fY2 = y; }
		void GetFinalPositions(float& x, float& y) { x = m_fX2; y = m_fY2; }

		///funci�n que regresa el ancho y alto
		void GetDimensions(float& width, float& height) { width = m_fWidth; height = m_fHeight; }

	private:
		///posici�n inicial.
		float m_fX1, m_fY1;
		///posici�n final.
		float m_fX2, m_fY2;
		///ancho y alto.
		float m_fWidth, m_fHeight;
	};
}