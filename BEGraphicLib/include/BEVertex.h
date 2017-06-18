#pragma once
#include <Vector2D.h>
#include <Vector3D.h>

///Engine's namespace.
namespace BlackEngine
{
	///Struct that is a vertex in a 3D space, it's got a position, and a 
	///TexCoord, pretty gnarly huh?
	struct VERTEX
	{
		/// Position.
		Vector3D Position;
		/// Texturee coordinate.
		Vector2D TexCoord;

		///Operator to equal a vertex with another vertex.
		VERTEX& operator=(const VERTEX& v1)
		{
			Position = v1.Position;
			TexCoord = v1.TexCoord;
			return *this;
		}
	};
}