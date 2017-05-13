#include "BEVertexBuffer.h"
#include "DirectXData.h"
#include "BEVertex.h"
#include <Vector2D.h>
#include <Vector3D.h>
#include <Vector4D.h>
#include <Matrix4D.h>

namespace BlackEngine
{
	BEVertexBuffer::BEVertexBuffer()
	{
		m_BufferData = nullptr;
	}

	BEVertexBuffer::~BEVertexBuffer()
	{
		Destroy();
	}

	void BEVertexBuffer::Destroy()
	{
		if (m_BufferData != nullptr)
		{
			delete m_BufferData;
			m_BufferData = nullptr;
		}
	}

	bool BEVertexBuffer::CreateBuffer(const GraphicsAPIData * pGraphicData)
	{
		Destroy();
		m_BufferData = new BufferData();

		D3D11_BUFFER_DESC bufferDesc = { 0 };
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(VERTEX) * m_Vertices.size();
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA srd = { 0 };
		srd.pSysMem = &m_Vertices[0];

		HRESULT hRes = pGraphicData->m_Device->CreateBuffer
		(&bufferDesc, &srd, &m_BufferData->m_Buffer);

		if (FAILED(hRes))
		{
			return false;
		}
		return true;
	}

	void BEVertexBuffer::AddVertex(VERTEX v)
	{
		m_Vertices.push_back(v);
	}

	//void BEVertexBuffer::Rotate(Vector4D angle)
	//{
	//	Matrix4D M;
	//	Vector4D TempVect;
	//	M.Zero();

	//	for (int i = 0; i < m_Vertices.size(); i++)
	//	{
	//		TempVect =
	//			(Vector4D(m_Vertices[i].Position.X, m_Vertices[i].Position.Y,
	//				m_Vertices[i].Position.Z, 1.0f));
	//		TempVect = M.Rotate(angle) * TempVect;
	//	}
	//}

	//void BEVertexBuffer::Scale(Vector4D scale)
	//{
	//	Matrix4D M;
	//	Vector4D V(scale.X, scale.Y, scale.Z, 1);
	//	Vector4D TempVect;
	//	M.Zero();

	//	for (int i = 0; i < m_Vertices.size(); i ++)
	//	{
	//		TempVect =
	//			(Vector4D(m_Vertices[i].Position.X, m_Vertices[i].Position.Y,
	//				m_Vertices[i].Position.Z, 1.0f));
	//		
	//		TempVect = M.Scale(V) * TempVect;
	//	}
	//}

	//void BEVertexBuffer::Translate(Vector4D position)
	//{
	//	Matrix4D M;
	//	Vector4D TempVect;
	//	Vector4D V(position.X, position.Y, position.Z, 1.0f);

	//	for (int i = 0; i < m_Vertices.size(); i++)
	//	{
	//		///vector de 4 dimensiones done almacenamos la posición del
	//		///vertice y un 1 en la última posición.
	//		TempVect = 
	//			(Vector4D(	m_Vertices[i].Position.X, m_Vertices[i].Position.Y,
	//						m_Vertices[i].Position.Z, 1.0f));
	//		///hacemos la matriz de transformación con la posición que se recibe
	//		///como parametro, y la multiplicamos por el vector temporal. Para
	//		///tener la posición correcta de cada vertice.
	//		TempVect = M.Translate(V) * TempVect;
	//		///cambiamos la posición del vertice.
	//		//m_Vertices[i].Position.X = TempVect.X;
	//		//m_Vertices[i].Position.Y = TempVect.Y;
	//		//m_Vertices[i].Position.Z = TempVect.Z;
	//	}
	//}
}