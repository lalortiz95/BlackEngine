#pragma once

namespace BlackEngine
{
	class Rect3D
	{
	public:
		///funciones para acceder a la posición inicial.
		void SetInitPositions(float x, float y, float z) { m_fX1 = x; m_fY1 = y; m_fZ1 = z; }
		void GetInitPositions(float& x, float& y, float& z) { x = m_fX1; y = m_fY1; z = m_fZ1; }

		///funciones para acceder a la posición final.
		void SetFinalPositions(float x, float y, float z) { m_fX2 = x; m_fY2 = y; m_fZ2 = z; }
		void GetFinalPositions(float& x, float& y, float z) { x = m_fX2; y = m_fY2; z = m_fZ2; }

		///función que regresa el ancho y alto
		void GetDimensions(float& width, float& height, float& depth) { width = m_fWidth; height = m_fHeight; depth = m_fDepth; }

	private:
		///posición inicial.
		float m_fX1, m_fY1, m_fZ1;
		///posición final.
		float m_fX2, m_fY2, m_fZ2;
		///ancho y alto.
		float m_fWidth, m_fHeight, m_fDepth;
	};
}