#include "BECamera.h"
#include "Matrix3D.h"
#include "Vector3D.h"
#include "Vector4D.h"


namespace BlackEngine
{
	BECamera::BECamera()
	{
	}

	BECamera::BECamera(Vector4D pos, Vector4D front, Vector4D up)
	{
		m_position = pos;
		m_Direction = front;
		m_Up = up;
		Initialize();
	}


	BECamera::~BECamera()
	{
		Destroy();
	}

	void BECamera::Initialize()
	{
		m_Dirty = false;
	}

	void BECamera::Destroy()
	{
		
	}

	void BECamera::Update(float delta)
	{
		///Reviso que hayan habido cambios.
		if (m_Dirty)
		{
			//TODO: mover la camara, con una velocidad, el tiempo y la dirección en la que se movio.
			///calculamos de nuevo el look at, con la nueva posición, y rotación de la cámara.
			m_ViewMat = m_ViewMat.LookAtLH(m_position, m_Direction, m_Up);
			///Seteo la bandera de cambios a falso.
			m_Dirty = false;
		}
	}

	void BECamera::LookAt(Vector4D target)
	{
		///hago que la cámara voltee a el nuevo target.
		m_ViewMat.LookAtLH(m_position, target, m_Up);

		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::Move(Vector4D position)
	{
		m_position += position;

		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::Pan(Vector4D direction)
	{
		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::SetPosition(Vector4D pos)
	{
		m_position = pos;
	}

	void BECamera::SetTarget(Vector4D target)
	{
		m_Direction = target;
	}

	void BECamera::SetUp(Vector4D up)
	{
		m_Up = up;
	}

	void BECamera::Rotate(Vector3D axis)
	{
		///Almaceno en un vector 4D los axis que recibe la función. 
		Vector4D anglesToRotate = {axis.X, axis.Y, axis.Z, 0};
		///Llamo a la función rotar de la matriz, que recibe un vector4D.
		m_ViewMat.Rotate(anglesToRotate);

		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::Orbitate(Vector3D axis)
	{

		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::Pitch(float x)
	{
		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::Yaw(float y)
	{
		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}

	void BECamera::Roll(float z)
	{
		///Seteamos la bandera de que han habido cambios.
		m_Dirty = true;
	}
}