#pragma once

namespace BlackEngine
{
	class Rect2DI
	{
	public:
		///funciones para acceder a la posici�n inicial.
		void SetInitPositions(int x, int y) { m_iX1 = x; m_iY1 = y; }
		void GetInitPositions(int& x, int& y) { x = m_iX1; y = m_iY1; }

		///funciones para acceder a la posici�n final.
		void SetFinalPositions(int x, int y) { m_iX2 = x; m_iY2 = y; }
		void GetFinalPositions(int& x, int& y) { x = m_iX2; y = m_iY2; }

		///funci�n que regresa el ancho y alto
		void GetDimensions(int& width, int& height) { width = m_iWidth; height = m_iHeight; }

	private:
		///posici�n inicial.
		int m_iX1, m_iY1;
		///posici�n final.
		int m_iX2, m_iY2;
		///ancho y alto.
		int m_iWidth, m_iHeight;
	};
}