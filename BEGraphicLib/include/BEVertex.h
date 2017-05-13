#pragma once
#include <Vector2D.h>
#include <Vector3D.h>

namespace BlackEngine
{
	struct VERTEX
	{
		/// posición
		Vector3D Position;
		/// color
		Vector2D TexCoord;

		VERTEX& operator=(const VERTEX& v1)
		{
			Position = v1.Position;
			TexCoord = v1.TexCoord;
			return *this;
		}


	};
}