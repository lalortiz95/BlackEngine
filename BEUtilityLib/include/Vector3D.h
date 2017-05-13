#pragma once
#include "BEMath.h"

namespace BlackEngine
{
	class Vector3D
	{
	public:
		float X;
		float Y;
		float Z;

		Vector3D() : X(0), Y(0), Z(0)
		{

		}

		Vector3D(float __x, float _y, float __z) : X(__x), Y(_y), Z(__z)
		{

		}

		float GetMagnitude()
		{
			///eleva al cuadrado los miembros.
			float Magnitud = (X*X) + (Y*Y) + (Z*Z);
			///saca la raiz cuadrada.
			Magnitud = sqrt(Magnitud);
			return Magnitud;
		}

		void CreateVector(Vector3D Target, Vector3D Source)
		{
			X = Target.X - Source.X;
			Y = Target.Y - Source.Y;
			Z = Target.Z - Source.Z;
		}

		void Normalize()
		{
			X /= GetMagnitude();
			Y /= GetMagnitude();
			Z /= GetMagnitude();
		}

		void DotProduct(Vector3D Target)
		{
			X = X * Target.X;
			Y = Y * Target.Y;
			Z = Z * Target.Z;
		}

		Vector3D CrossProduct(const Vector3D& V)
		{
			return Vector3D
			(
				Y * V.Z - Z * V.Y,
				Z * V.X - X * V.Z,
				X * V.Y - Y * V.X
			);
		}

		///Operadores aritmeticos
		Vector3D operator^(const Vector3D& V)
		{
			return CrossProduct(V);
		}

		Vector3D operator+(float rhv)
		{
			Vector3D Result;
			Result.X = X + rhv;
			Result.Y = Y + rhv;
			Result.Z = Z + rhv;
			return Result;
		}

		Vector3D operator+(const Vector3D& rhv)
		{
			Vector3D Result;
			Result.X = X + rhv.X;
			Result.Y = Y + rhv.Y;
			Result.Z = Z + rhv.Z;
			return Result;
		}

		Vector3D operator-(float rhv)
		{
			Vector3D Result;
			Result.X = X - rhv;
			Result.Y = Y - rhv;
			Result.Z = Z - rhv;
			return Result;
		}

		Vector3D operator-(const Vector3D& rhv)
		{
			Vector3D Result;
			Result.X = X - rhv.X;
			Result.Y = Y - rhv.Y;
			Result.Z = Z - rhv.Z;
			return Result;
		}

		Vector3D operator*(float rhv)
		{
			Vector3D Result;
			Result.X = X * rhv;
			Result.Y = Y * rhv;
			Result.Z = Z * rhv;
			return Result;
		}

		Vector3D operator*(const Vector3D& rhv)
		{
			Vector3D Result;
			Result.X = X * rhv.X;
			Result.Y = Y * rhv.Y;
			Result.Z = Z * rhv.Z;
			return Result;
		}

		Vector3D operator/(float rhv)
		{
			Vector3D Result;
			Result.X = X / rhv;
			Result.Y = Y / rhv;
			Result.Z = Z / rhv;
			return Result;
		}

		Vector3D operator/(const Vector3D& rhv)
		{
			Vector3D Result;
			Result.X = X / rhv.X;
			Result.Y = Y / rhv.Y;
			Result.Z = Z / rhv.Z;
			return Result;
		}

		///Operadores aritmeticos de acumulacion
		Vector3D& operator+=(float rhv)
		{
			X += rhv;
			Y += rhv;
			Z += rhv;
			return *this;
		}

		Vector3D& operator+=(const Vector3D& rhv)
		{
			X += rhv.X;
			Y += rhv.Y;
			Z += rhv.Z;
			return *this;
		}

		Vector3D& operator-=(float rhv)
		{
			X -= rhv;
			Y -= rhv;
			Z -= rhv;
			return *this;
		}

		Vector3D& operator-=(const Vector3D& rhv)
		{
			X -= rhv.X;
			Y -= rhv.Y;
			Z -= rhv.Z;
			return *this;
		}

		Vector3D& operator*=(float rhv)
		{
			X *= rhv;
			Y *= rhv;
			Z *= rhv;
			return *this;
		}

		Vector3D& operator*=(const Vector3D& rhv)
		{
			X *= rhv.X;
			Y *= rhv.Y;
			Z *= rhv.Z;
			return *this;
		}

		Vector3D& operator/=(float rhv)
		{
			X /= rhv;
			Y /= rhv;
			Z /= rhv;
			return *this;
		}

		Vector3D& operator/=(Vector3D& rhv)
		{
			X /= rhv.X;
			Y /= rhv.Y;
			Z /= rhv.Z;
			return *this;
		}

		Vector3D& operator=(float rhv)
		{
			X = rhv;
			Y = rhv;
			Z = rhv;
			return *this;
		}

		Vector3D& operator=(const Vector3D& rhv)
		{
			X = rhv.X;
			Y = rhv.Y;
			Z = rhv.Z;
			return *this;
		}
		///operadores de relacion
		bool operator<(const Vector3D& rhv)
		{
			if (X < rhv.X && Y < rhv.Y && Z < rhv.Z)
			{
				return true;
			}
			return false;
		}

		bool operator<(float rhv)
		{
			if (X < rhv && Y < rhv && Z < rhv)
			{
				return true;
			}
			return false;
		}

		bool operator>(const Vector3D& rhv)
		{
			if (X > rhv.X && Y > rhv.Y && Z > rhv.Z)
			{
				return true;
			}
			return false;
		}

		bool operator>(float rhv)
		{
			if (X > rhv && Y > rhv && Z > rhv)
			{
				return true;
			}
			return false;
		}

		bool operator!=(const Vector3D& rhv)
		{
			if (X != rhv.X && Y != rhv.Y && Z != rhv.Z)
			{
				return true;
			}
			return false;
		}

		bool operator!=(float rhv)
		{
			if (X != rhv && Y != rhv && Z != rhv)
			{
				return true;
			}
			return false;
		}

		bool operator==(const Vector3D& rhv)
		{
			if (X == rhv.X && Y == rhv.Y && Z == rhv.Z)
			{
				return true;
			}
			return false;
		}

		bool operator==(float rhv)
		{
			if (X == rhv && Y == rhv && Z == rhv)
			{
				return true;
			}
			return false;
		}
	};
}