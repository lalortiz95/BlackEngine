#pragma once
#include "BEMath.h"

namespace BlackEngine
{
	class Vector2D
	{
	public:
		float X;
		float Y;

		Vector2D() : X(0), Y(0)
		{

		}

		Vector2D(float __x, float _y) : X(__x), Y(_y)
		{

		}

		float GetMagnitude()
		{
			float Magnitud = (X*X) + (Y*Y);
			Magnitud = sqrt(Magnitud);
			return Magnitud;
		}

		void CreateVector(Vector2D Target, Vector2D Source)
		{
			X = Target.X - Source.X;
			Y = Target.Y - Source.Y;
		}

		void Normalize()
		{
			X /= GetMagnitude();
			Y /= GetMagnitude();
		}

		void DotProduct(Vector2D Target)
		{
			X = X * Target.X;
			Y = Y * Target.Y;
		}

		///cambia al valor de X a negativo, producto cruz para dommies.
		void CrossProduct()
		{
			X = -X;
		}

		///Operadores aritmeticos
		Vector2D operator+(float rhv)
		{
			Vector2D Result;
			Result.X = X + rhv;
			Result.Y = Y + rhv;
			return Result;
		}

		Vector2D operator+(const Vector2D& rhv)
		{
			Vector2D Result;
			Result.X = X + rhv.X;
			Result.Y = Y + rhv.Y;
			return Result;
		}

		Vector2D operator-(float rhv)
		{
			Vector2D Result;
			Result.X = X - rhv;
			Result.Y = Y - rhv;
			return Result;
		}

		Vector2D operator-(const Vector2D& rhv)
		{
			Vector2D Result;
			Result.X = X - rhv.X;
			Result.Y = Y - rhv.Y;
			return Result;
		}

		Vector2D operator*(float rhv)
		{
			Vector2D Result;
			Result.X = X * rhv;
			Result.Y = Y * rhv;
			return Result;
		}

		Vector2D operator*(const Vector2D& rhv)
		{
			Vector2D Result;
			Result.X = X * rhv.X;
			Result.Y = Y * rhv.Y;
			return Result;
		}

		Vector2D operator/(float rhv)
		{
			Vector2D Result;
			Result.X = X / rhv;
			Result.Y = Y / rhv;
			return Result;
		}

		Vector2D operator/(const Vector2D& rhv)
		{
			Vector2D Result;
			Result.X = X / rhv.X;
			Result.Y = Y / rhv.Y;
			return Result;
		}

		///Operadores aritmeticos de acumulacion
		Vector2D& operator+=(float rhv)
		{
			X += rhv;
			Y += rhv;
			return *this;
		}

		Vector2D& operator+=(const Vector2D& rhv)
		{
			X += rhv.X;
			Y += rhv.Y;
			return *this;
		}

		Vector2D& operator-=(float rhv)
		{
			X -= rhv;
			Y -= rhv;
			return *this;
		}

		Vector2D& operator-=(const Vector2D& rhv)
		{
			X -= rhv.X;
			Y -= rhv.Y;
			return *this;
		}

		Vector2D& operator*=(float rhv)
		{
			X *= rhv;
			Y *= rhv;
			return *this;
		}

		Vector2D& operator*=(const Vector2D& rhv)
		{
			X *= rhv.X;
			Y *= rhv.Y;
			return *this;
		}

		Vector2D& operator/=(float rhv)
		{
			X /= rhv;
			Y /= rhv;
			return *this;
		}

		Vector2D& operator/=(const Vector2D& rhv)
		{
			X /= rhv.X;
			Y /= rhv.Y;
			return *this;
		}

		Vector2D& operator=(float rhv)
		{
			X = rhv;
			Y = rhv;
			return *this;
		}

		Vector2D& operator=(const Vector2D& rhv)
		{
			X = rhv.X;
			Y = rhv.Y;
			return *this;
		}

		///operadores de relacion
		bool operator<(const Vector2D& rhv)
		{
			if (X < rhv.X && Y < rhv.Y)
			{
				return true;
			}
			return false;
		}

		bool operator<(float rhv)
		{
			if (X < rhv && Y < rhv)
			{
				return true;
			}
			return false;
		}

		bool operator>(const Vector2D& rhv)
		{
			if (X > rhv.X && Y > rhv.Y)
			{
				return true;
			}
			return false;
		}

		bool operator>(float rhv)
		{
			if (X > rhv && Y > rhv)
			{
				return true;
			}
			return false;
		}

		bool operator!=(const Vector2D& rhv)
		{
			if (X != rhv.X && Y != rhv.Y)
			{
				return true;
			}
			return false;
		}

		bool operator!=(float rhv)
		{
			if (X != rhv && Y != rhv)
			{
				return true;
			}
			return false;
		}

		bool operator==(const Vector2D& rhv)
		{
			if (X == rhv.X && Y == rhv.Y)
			{
				return true;
			}
			return false;
		}

		bool operator==(float rhv)
		{
			if (X == rhv && Y == rhv)
			{
				return true;
			}
			return false;
		}
	};
}