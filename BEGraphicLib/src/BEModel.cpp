#include "BEModel.h"
#include "BEVertexBuffer.h"
#include "BEIndexBuffer.h"
#include "DirectXData.h"
#include "BEVertex.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace BlackEngine
{
	BEModel::BEModel()
	{

	}

	BEModel::~BEModel()
	{
		Destroy();
	}

	void BEModel::Initialize()
	{

	}

	void BEModel::Destroy()
	{
		for (SIZE_T i = 0; i < m_Meshes.size(); ++i)
		{
			m_Meshes[i].Destroy();
		}
	}

	bool BEModel::LoadModel(const String& pFile)
	{
		///importer de assimp.
		Assimp::Importer importer;
		///mesh de assimp
		aiMesh* Mesh;

		///guardamos el modelo que queremos abrir.
		const aiScene* Scene = importer.ReadFile(pFile.c_str(),
			aiProcess_MakeLeftHanded |
			aiProcess_CalcTangentSpace |
			aiProcess_JoinIdenticalVertices |
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_SortByPType);

		///revisamos que se haya guardado bien.
		if (!Scene)
		{
			return false;
		}

		///otra revisión para ver que tenga meshes el modelo.
		if (Scene->HasMeshes())
		{
			///agregamos el mesh temporal al vector de meshes.
			m_Meshes.resize(Scene->mNumMeshes);

			for (SIZE_T k = 0; k < Scene->mNumMeshes; ++k)
			{
				///mesh con el que voy a llenar el vector de meshes.
				BEMesh* TempMesh = &m_Meshes[k];
				///le asignamos memoria a sus variables miembras.
				TempMesh->Initialize();

				///guardamos el mesh de la escena en la variable local de tipo aiMesh.
				Mesh = Scene->mMeshes[k];

				///recorremos los vertices
				for (SIZE_T i = 0; i < Mesh->mNumVertices; ++i)
				{
					VERTEX tempVertex;
					///guardamos las posiciones de los vertices.
					aiVector3D pos = Mesh->mVertices[i];
					tempVertex.Position.X = pos.x;
					tempVertex.Position.Y = pos.y;
					tempVertex.Position.Z = pos.z;

					if (Mesh->GetNumUVChannels() > 0)
					{
						tempVertex.TexCoord.X = Mesh->mTextureCoords[0][i].x;
						tempVertex.TexCoord.Y = Mesh->mTextureCoords[0][i].y;
					}

					///agregamos el vertice a la lista de vertices del mesh.
					TempMesh->m_VB.AddVertex(tempVertex);
				}

				///recorremos las caras que tiene el mesh.
				for (SIZE_T i = 0; i < Mesh->mNumFaces; ++i)
				{
					///la guardamos en una variable local.
					const aiFace& Face = Mesh->mFaces[i];

					///vemos si los indices que tiene son 3.
					if (Face.mNumIndices == 3)
					{
						///los metemos al vector de indices del mesh temporal.
						TempMesh->m_IB.AddIndex((int16)Face.mIndices[0]);
						TempMesh->m_IB.AddIndex((int16)Face.mIndices[1]);
						TempMesh->m_IB.AddIndex((int16)Face.mIndices[2]);
					}
				}

			/*	if (Scene->HasMaterials())
				{
					for (SIZE_T i = 0; i < Scene->mNumMaterials; i++)
					{
						///creamos un material y un string de assimp.
						aiMaterial material;
						aiString fileAdrr;
						///guardamos la direccion del archivo en el string.
						fileAdrr.Set(pFile.c_str());
						///obtenemos la textura diffuse.
						material.GetTexture(aiTextureType_DIFFUSE, i, &fileAdrr);
					}
				}*/
			}
		}
		return true;
	}

	bool BEModel::CreateBuffers(const GraphicsAPIData * pGraphicData)
	{
		///creamos el vertex buffer.
		CreateVB(pGraphicData);

		///creamos el index buffer.
		CreateIB(pGraphicData);

		return true;
	}

	void BEModel::SetBuffers(const GraphicsAPIData * pGraphicData)
	{
		///seteamos vertex buffer.
		SetVB(pGraphicData);
		///seteamos index buffer.
		SetIB(pGraphicData);
	}

	void BEModel::CreateVB(const GraphicsAPIData * pGraphicData)
	{
		for (SIZE_T i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i].m_VB.CreateBuffer(pGraphicData);
		}
	}

	void BEModel::SetVB(const GraphicsAPIData * pGraphicData)
	{
		uint32 stride = sizeof(VERTEX);
		uint32 offset = 0;
		///recorro el vetor de meshes
		for (SIZE_T i = 0; i < m_Meshes.size(); i++)
		{
			///seteo el vertex buffer.
			pGraphicData->m_DeviceContext->IASetVertexBuffers
			(
				0, 1, &m_Meshes[i].m_VB.m_BufferData->m_Buffer,
				&stride, &offset
			);
		}
	}

	void BEModel::CreateIB(const GraphicsAPIData * pGraphicData)
	{
		for (SIZE_T i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i].m_IB.CreateBuffer(pGraphicData);
		}
	}

	void BEModel::SetIB(const GraphicsAPIData * pGraphicData)
	{
		for (SIZE_T i = 0; i < m_Meshes.size(); i++)
		{
			pGraphicData->m_DeviceContext->IASetIndexBuffer
			(
				m_Meshes[i].m_IB.m_BufferData->m_Buffer,
				DXGI_FORMAT_R32_UINT,
				0
			);
		}
	}

	void BEModel::Render(const GraphicsAPIData * pGraphicData)
	{
		uint32 stride = sizeof(VERTEX);
		uint32 offset = 0;

		for (SIZE_T i = 0; i < m_Meshes.size(); i++)
		{
			pGraphicData->m_DeviceContext->IASetIndexBuffer
			(
				m_Meshes[i].m_IB.m_BufferData->m_Buffer,
				DXGI_FORMAT_R32_UINT,
				0
			);

			pGraphicData->m_DeviceContext->IASetVertexBuffers
			(
				0, 1, &m_Meshes[i].m_VB.m_BufferData->m_Buffer,
				&stride, &offset
			);

			pGraphicData->m_DeviceContext->DrawIndexed(m_Meshes[i].m_IB.GetIndicesSize(), 0, 0);
		}
	}
}