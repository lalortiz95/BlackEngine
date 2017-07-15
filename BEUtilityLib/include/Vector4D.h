#pragma once
#include "BEMath.h"

namespace BlackEngine
{
	class Matrix4D;

	class BE_UTILITY_EXPORT Vector4D
	{
	public:
		float X;
		float Y;
		float Z;
		float W;

		Vector4D() : X(0), Y(0), Z(0), W(0)
		{

		}

		Vector4D(float __x, float _y, float __z, float __w) : X(__x), Y(_y), Z(__z), W(__w)
		{

		}

		float GetMagnitude()
		{
			///eleva al cuadrado los miembros.
			float Magnitud = (X*X) + (Y*Y) + (Z*Z) + (W*W);
			///saca la raiz cuadrada.
			Magnitud = sqrt(Magnitud);
			return Magnitud;
		}

		//void CreateVector(Vector4D Target, Vector4D Source)
		//{
		//	X = Target.X - Source.X;
		//	Y = Target.Y - Source.Y;
		//	Z = Target.Z - Source.Z;
		//	W = Target.W - Source.W;
		//}

		void Normalize()
		{
			float invmag = 1.0f / GetMagnitude();
			X *= invmag;
			Y *= invmag;
			Z *= invmag;
			W *= invmag;
		}

		float DotProduct(Vector4D Target)
		{
			Vector4D Res;
			Res.X = X * Target.X;
			Res.Y = Y * Target.Y;
			Res.Z = Z * Target.Z;
			Res.W = W * Target.W;

			float escalar = Res.X + Res.Y + Res.Z + Res.W;
			if (escalar <= Math::DELTA && escalar >= 0 - Math::DELTA)
			{
				escalar = 0;
			}
			return escalar;
		}

		float DotProductBetweenTwoVectos(Vector4D V1, Vector4D V2)
		{
			Vector4D Res;
			Res.X = V1.X * V2.X;
			Res.Y = V1.Y * V2.Y;
			Res.Z = V1.Z * V2.Z;
			Res.W = V1.W * V2.W;
			
			return (Res.X + Res.Y + Res.Z + Res.W);
		}

		void CrossProduct(Vector4D V1, Vector4D V2)
		{
			X = (V1.Y * V2.Z) - (V1.Z * V2.Y);
			Y = (V1.Z * V2.X) - (V1.X * V2.Z);
			Z = (V1.X * V2.Y) - (V1.Y * V2.X);
			W = 0;
		}

		void VectorNegate()
		{
			X *= -1;
			Y *= -1;
			Z *= -1;
			W *= -1;
		}

		///Operadores aritmeticos
		Vector4D operator+(float rhv)
		{
			Vector4D Result;
			Result.X = X + rhv;
			Result.Y = Y + rhv;
			Result.Z = Z + rhv;
			Result.W = W + rhv;
			return Result;
		}

		Vector4D operator+(const Vector4D& rhv)
		{
			Vector4D Result;
			Result.X = X + rhv.X;
			Result.Y = Y + rhv.Y;
			Result.Z = Z + rhv.Z;
			Result.W = W + rhv.W;
			return Result;
		}

		Vector4D operator-(float rhv)
		{
			Vector4D Result;
			Result.X = X - rhv;
			Result.Y = Y - rhv;
			Result.Z = Z - rhv;
			Result.W = W - rhv;
			return Result;
		}

		Vector4D operator-(const Vector4D& rhv)
		{
			Vector4D Result;
			Result.X = X - rhv.X;
			Result.Y = Y - rhv.Y;
			Result.Z = Z - rhv.Z;
			Result.W = W - rhv.W;
			return Result;
		}

		Vector4D operator*(float rhv)
		{
			Vector4D Result;
			Result.X = X * rhv;
			Result.Y = Y * rhv;
			Result.Z = Z * rhv;
			Result.W = W * rhv;
			return Result;
		}

		Vector4D operator*(const Vector4D& rhv)
		{
			Vector4D Result;
			Result.X = X * rhv.X;
			Result.Y = Y * rhv.Y;
			Result.Z = Z * rhv.Z;
			Result.W = W * rhv.W;
			return Result;
		}

		Vector4D operator*(const Matrix4D& M);

		Vector4D operator/(float rhv)
		{
			Vector4D Result;
			Result.X = X / rhv;
			Result.Y = Y / rhv;
			Result.Z = Z / rhv;
			Result.W = W / rhv;
			return Result;
		}

		Vector4D operator/(const Vector4D& rhv)
		{
			Vector4D Result;
			Result.X = X / rhv.X;
			Result.Y = Y / rhv.Y;
			Result.Z = Z / rhv.Z;
			Result.W = W / rhv.W;
			return Result;
		}

		///Operadores aritmeticos de acumulacion
		Vector4D& operator+=(float rhv)
		{
			X += rhv;
			Y += rhv;
			Z += rhv;
			W += rhv;
			return *this;
		}

		Vector4D& operator+=(const Vector4D& rhv)
		{
			X += rhv.X;
			Y += rhv.Y;
			Z += rhv.Z;
			W += rhv.W;
			return *this;
		}

		Vector4D& operator-=(float rhv)
		{
			X -= rhv;
			Y -= rhv;
			Z -= rhv;
			W -= rhv;
			return *this;
		}

		Vector4D& operator-=(const Vector4D& rhv)
		{
			X -= rhv.X;
			Y -= rhv.Y;
			Z -= rhv.Z;
			W -= rhv.W;
			return *this;
		}

		Vector4D& operator*=(float rhv)
		{
			X *= rhv;
			Y *= rhv;
			Z *= rhv;
			W *= rhv;
			return *this;
		}

		Vector4D& operator*=(const Vector4D& rhv)
		{
			X *= rhv.X;
			Y *= rhv.Y;
			Z *= rhv.Z;
			W *= rhv.W;
			return *this;
		}

		Vector4D& operator*=(const Matrix4D& M)
		{
			return *this = *this * M;
		}

		Vector4D& operator/=(float rhv)
		{
			X /= rhv;
			Y /= rhv;
			Z /= rhv;
			W /= rhv;
			return *this;
		}

		Vector4D& operator/=(const Vector4D& rhv)
		{
			X /= rhv.X;
			Y /= rhv.Y;
			Z /= rhv.Z;
			W /= rhv.W;
			return *this;
		}

		Vector4D& operator=(float rhv)
		{
			X = rhv;
			Y = rhv;
			Z = rhv;
			W = rhv;
			return *this;
		}

		Vector4D& operator=(const Vector4D& rhv)
		{
			X = rhv.X;
			Y = rhv.Y;
			Z = rhv.Z;
			W = rhv.W;
			return *this;
		}

		///operadores de relacion
		bool operator<(const Vector4D& rhv)
		{
			if (X < rhv.X && Y < rhv.Y && Z < rhv.Z && W < rhv.W)
			{
				return true;
			}
			return false;
		}

		bool operator<(float rhv)
		{
			if (X < rhv && Y < rhv && Z < rhv && W < rhv)
			{
				return true;
			}
			return false;
		}

		bool operator>(const Vector4D& rhv)
		{
			if (X > rhv.X && Y > rhv.Y && Z > rhv.Z && W > rhv.W)
			{
				return true;
			}
			return false;
		}

		bool operator>(float rhv)
		{
			if (X > rhv && Y > rhv && Z > rhv && W > rhv)
			{
				return true;
			}
			return false;
		}

		bool operator!=(const Vector4D& rhv)
		{
			if (X != rhv.X && Y != rhv.Y && Z != rhv.Z && W != rhv.W)
			{
				return true;
			}
			return false;
		}

		bool operator!=(float rhv)
		{
			if (X != rhv && Y != rhv && Z != rhv && W != rhv)
			{
				return true;
			}
			return false;
		}

		bool operator==(const Vector4D& rhv)
		{
			if (X == rhv.X && Y == rhv.Y && Z == rhv.Z && W == rhv.W)
			{
				return true;
			}
			return false;
		}

		bool operator==(float rhv)
		{
			if (X == rhv && Y == rhv && Z == rhv && W == rhv)
			{
				return true;
			}
			return false;
		}
	};
}