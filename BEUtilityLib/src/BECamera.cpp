#include "BECamera.h"
#include "Matrix3D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "BEMath.h"
#include "Quaternion.h"

namespace BlackEngine
{
	BECamera::BECamera()
	{
	}

	BECamera::BECamera(Vector4D pos, Vector4D front, Vector4D up)
	{
		m_Position = pos;
		m_Direction = front;
		m_Up = up;
		SetTarget(front);
		Initialize();
	}


	BECamera::~BECamera()
	{
		Destroy();
	}

	void BECamera::Initialize()
	{
		m_Dirty = false;
		m_Speed = 0;
		m_Up = { 0, 1, 0, 0 };
	}

	void BECamera::Destroy()
	{
		m_Dirty = false;
		m_Speed = 0;
	}

	void BECamera::Update(float delta)
	{
		///Reviso que hayan habido cambios.
		if (m_Dirty)
		{
			///calculamos de nuevo el look at, con la nueva posición, y rotación de la cámara.
			m_ViewMat = m_ViewMat.LookAtLH(m_Position, m_Target, m_Up);
			///Seteo la bandera de cambios a falso.
			m_Dirty = false;
		}
	}

	void BECamera::LookAt(Vector4D target)
	{
		///hago que la cámara voltee a el nuevo target.
		m_ViewMat.LookAtLH(m_Position, target, m_Up);

		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::Move(Vector4D position)
	{
		m_Position += position;

		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::Pan(Vector4D direction)
	{
		//TODO: con una velocidad dada, la dirección, y el tiempo. Calcular cuantas unidades
		//por segundo van a avanzar el target de la cámara, y la misma.
		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::SetPosition(Vector4D pos)
	{
		m_Position = pos;

		m_Dirty = true;
	}

	void BECamera::SetTarget(Vector4D target)
	{
		m_Direction = target - m_Position;
		m_Direction.Normalize();
		m_Target = target;
		m_Dirty = false;
	}

	void BECamera::SetUp(Vector4D up)
	{
		m_Up = up;
	}

	void BECamera::Rotate(Vector3D axis, float RotateAmount)
	{
		Quaternion RotatedQuaternion;
		///Almaceno en un vector 4D los axis que recibe la función. 
		Vector3D anglesToRotate = { axis.X, axis.Y, axis.Z };

		RotatedQuaternion.RotateLocal(anglesToRotate, RotateAmount);
		RotatedQuaternion.Normalize();
		Matrix4D RotationMatrix = RotatedQuaternion.ConvertToMatrix();
		///Llamo a la función rotar de la matriz, que recibe un vector4D.
		//Matrix4D RotationMatrix = Matrix4D::RotateY(anglesToRotate.Y);

		Vector4D OriginalPosition = m_Position;
		m_Target -= m_Position;
		m_Target *= RotationMatrix;
		m_Target += m_Position;
		
		m_Direction = m_Target - m_Position;
		m_Direction.Normalize();

		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::Orbitate(Vector3D axis)
	{
		Vector4D AxisToRotate(axis.X, axis.Y, axis.Z, 0);
		m_ViewMat.Rotate(AxisToRotate);
		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::Pitch(float x)
	{
		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
		///We rotate the matrix on the X axe only.
		m_ViewMat.RotateX(x);
	}

	void BECamera::Yaw(float y)
	{
		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
		///We rotate the matrix on the Y axe only.
		m_ViewMat.RotateY(y);
	}

	void BECamera::Roll(float z)
	{
		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
		///We rotate the matrix on the Z axe only.
		m_ViewMat.RotateZ(z);
	}
}