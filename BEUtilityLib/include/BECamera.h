#pragma once
#include "BEPrerequisitesUtility.h"
#include "Matrix4D.h"

///Engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	class Vector3D;
	class Vector4D;
	class Matrix3D;

	///Declaration of BECamera class.
	class BE_UTILITY_EXPORT BECamera
	{
	public:
		///Default constructor
		BECamera();
		///Parameter constructor.
		BECamera(Vector4D pos, Vector4D target, Vector4D up);
		///Default destructor.
		~BECamera();
		
		///Initializes it's variables.
		void Initialize();
		///Releases memory and deletes memory.
		void Destroy();
		///Updates every frame.
		void Update(float delta);

		///Calculates the camera direction with a given target position.
		void LookAt(Vector4D target);
		///Moves the camera to a given position
		void Move(Vector4D position);
		///Moves the camera and the target to a given direction.
		void Pan(Vector4D direction);

		///Sets the position of the camera with a given vector4D.
		void SetPosition(Vector4D pos);
		///Sets where the camera will be looking at.
		void SetTarget(Vector4D target);
		///Sets where's the camera up.
		void SetUp(Vector4D up);
		///Sets the projection matrix.
		void SetProjectionMatrix(Matrix4D proj) { m_ProjectionMat = proj; }
		///Sets the view matrix.
		void SetViewMatrix(Matrix4D view) { m_ViewMat = view; }

		///Returns the view matrix.
		Matrix4D GetViewMatrix() { return m_ViewMat; }
		///Returns the project matrix.
		Matrix4D GetProjectionMatrix() { return m_ProjectionMat; }

		///Rotates the camera with a given rotation.
		void Rotate(Vector3D axis);
		///Given a given axes, X, Y, and Z. Calculates the camera rotation.
		void Orbitate(Vector3D axis);

		///Rotates only upon the x axis
		void Pitch(float x);
		///Rotates only upon the Y axis
		void Yaw(float y);
		///Rotates only upon the Z axis
		void Roll(float z);

		///The camera's speed. Used when needing to move it.
		float m_Speed;

	private:
		///Flag that tells us if any changes where made.
		bool m_Dirty;
		///Member variables.
		Vector4D m_Position;
		///Where the camera is looking at, it's front.
		Vector4D m_Direction;
		///The up direction from the camera.
		Vector4D m_Up;
		///Member view matrix
		Matrix4D m_ViewMat;
		///Member projection matrix
		Matrix4D m_ProjectionMat;
	};
}