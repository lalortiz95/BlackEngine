#pragma once
#include "BEMath.h"

namespace BlackEngine
{
	class Vector2DI
	{
		int m_iX;
		int m_iY;

		Vector2DI() : m_iX(0), m_iY(0)
		{

		}

		Vector2DI(int __x, int _y) : m_iX(__x), m_iY(_y)
		{

		}

		int GetMagnitude()
		{
			int Magnitud = (m_iX*m_iX) + (m_iY*m_iY);
			Magnitud = (int)sqrt(Magnitud);
			return Magnitud;
		}

		void CreateVector(Vector2DI Target, Vector2DI Source)
		{
			m_iX = Target.m_iX - Source.m_iX;
			m_iY = Target.m_iY - Source.m_iY;
		}

		void Normalize()
		{
			m_iX /= (int)GetMagnitude();
			m_iY /= (int)GetMagnitude();
		}

		void DotProduct(Vector2DI Target)
		{
			m_iX = m_iX * Target.m_iX;
			m_iY = m_iY * Target.m_iY;
		}

		///Operadores aritmeticos
		Vector2DI operator+(int rhv)
		{
			Vector2DI Result;
			Result.m_iX = m_iX + rhv;
			Result.m_iY = m_iY + rhv;
			return Result;
		}

		Vector2DI operator+(Vector2DI& rhv)
		{
			Vector2DI Result;
			Result.m_iX = m_iX + rhv.m_iX;
			Result.m_iY = m_iY + rhv.m_iY;
			return Result;
		}

		Vector2DI operator-(int rhv)
		{
			Vector2DI Result;
			Result.m_iX = m_iX - rhv;
			Result.m_iY = m_iY - rhv;
			return Result;
		}

		Vector2DI operator-(Vector2DI& rhv)
		{
			Vector2DI Result;
			Result.m_iX = m_iX - rhv.m_iX;
			Result.m_iY = m_iY - rhv.m_iY;
			return Result;
		}

		Vector2DI operator*(int rhv)
		{
			Vector2DI Result;
			Result.m_iX = m_iX * rhv;
			Result.m_iY = m_iY * rhv;
			return Result;
		}

		Vector2DI operator*(Vector2DI& rhv)
		{
			Vector2DI Result;
			Result.m_iX = m_iX * rhv.m_iX;
			Result.m_iY = m_iY * rhv.m_iY;
			return Result;
		}

		Vector2DI operator/(int rhv)
		{
			Vector2DI Result;
			Result.m_iX = m_iX / rhv;
			Result.m_iY = m_iY / rhv;
			return Result;
		}

		Vector2DI operator/(Vector2DI& rhv)
		{
			Vector2DI Result;
			Result.m_iX = m_iX / rhv.m_iX;
			Result.m_iY = m_iY / rhv.m_iY;
			return Result;
		}

		///Operadores aritmeticos de acumulacion
		Vector2DI& operator+=(int rhv)
		{
			m_iX += rhv;
			m_iY += rhv;
			return *this;
		}

		Vector2DI& operator+=(Vector2DI& rhv)
		{
			m_iX += rhv.m_iX;
			m_iY += rhv.m_iY;
			return *this;
		}

		Vector2DI& operator-=(int rhv)
		{
			m_iX -= rhv;
			m_iY -= rhv;
			return *this;
		}

		Vector2DI& operator-=(Vector2DI& rhv)
		{
			m_iX -= rhv.m_iX;
			m_iY -= rhv.m_iY;
			return *this;
		}

		Vector2DI& operator*=(int rhv)
		{
			m_iX *= rhv;
			m_iY *= rhv;
			return *this;
		}

		Vector2DI& operator*=(Vector2DI& rhv)
		{
			m_iX *= rhv.m_iX;
			m_iY *= rhv.m_iY;
			return *this;
		}

		Vector2DI& operator/=(int rhv)
		{
			m_iX /= rhv;
			m_iY /= rhv;
			return *this;
		}

		Vector2DI& operator/=(Vector2DI& rhv)
		{
			m_iX /= rhv.m_iX;
			m_iY /= rhv.m_iY;
			return *this;
		}

		Vector2DI& operator=(int rhv)
		{
			m_iX = rhv;
			m_iY = rhv;
			return *this;
		}

		Vector2DI& operator=(Vector2DI& rhv)
		{
			m_iX = rhv.m_iX;
			m_iY = rhv.m_iY;
			return *this;
		}
		///operadores de relacion
		bool operator<(Vector2DI& rhv)
		{
			if (m_iX < rhv.m_iX && m_iY < rhv.m_iY)
			{
				return true;
			}
			return false;
		}

		bool operator<(int rhv)
		{
			if (m_iX < rhv && m_iY < rhv)
			{
				return true;
			}
			return false;
		}

		bool operator>(Vector2DI& rhv)
		{
			if (m_iX > rhv.m_iX && m_iY > rhv.m_iY)
			{
				return true;
			}
			return false;
		}

		bool operator>(int rhv)
		{
			if (m_iX > rhv && m_iY > rhv)
			{
				return true;
			}
			return false;
		}

		bool operator!=(Vector2DI& rhv)
		{
			if (m_iX != rhv.m_iX && m_iY != rhv.m_iY)
			{
				return true;
			}
			return false;
		}

		bool operator!=(int rhv)
		{
			if (m_iX != rhv && m_iY != rhv)
			{
				return true;
			}
			return false;
		}

		bool operator==(Vector2DI& rhv)
		{
			if (m_iX == rhv.m_iX && m_iY == rhv.m_iY)
			{
				return true;
			}
			return false;
		}

		bool operator==(int rhv)
		{
			if (m_iX == rhv && m_iY == rhv)
			{
				return true;
			}
			return false;
		}
	};
}