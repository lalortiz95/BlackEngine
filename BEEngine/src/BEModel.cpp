#include "BEModel.h"
#include "DirectXData.h"
#include "BEVertex.h"
#include "BEResource.h"
#include "BEResourceManager.h"
#include <BEGraphicsAPI.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace BlackEngine
{
	BEModel::BEModel()
	{
		m_Meshes.clear();
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
		//for (SIZE_T i = 0; i < m_IBVector.size(); ++i)
		//{
		//	m_IBVector[i].Destroy();
		//	m_VBVector[i].Destroy();
		//	/*m_IB.Destroy();
		//	m_VB.Destroy();*/
		//}
	}

	bool BEModel::LoadModel(const String& pFile, const GraphicsAPIData * pGraphicData)
	{
		BEResourceManager* RM = new BEResourceManager();
		RM->Initialize();
		RM->m_GA->m_pGraphicsAPIData = const_cast<GraphicsAPIData*>(pGraphicData);
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
			aiProcess_SortByPType |
			aiProcess_FlipUVs |
			aiProcess_FlipWindingOrder
		);

		///revisamos que se haya guardado bien.
		if (!Scene)
		{
			return false;
		}

		///otra revisión para ver que tenga meshes el modelo.
		if (Scene->HasMeshes())
		{
			///reasignamos el tamaño de los vectores de buffers, al numero de meshes que hay.
			m_Meshes.resize(Scene->mNumMeshes);

			for (SIZE_T k = 0; k < Scene->mNumMeshes; ++k)
			{
				///creo e inicializ el mesh con el que voy a llenar el vector de meshes.
				BEMesh* tempMesh = &m_Meshes[k];
				tempMesh->Initialize();
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

					///agregamos el vertice a la lista de vertices.
					tempMesh->m_VB.AddVertex(tempVertex);
				}

				///recorremos las caras que tiene el mesh.
				for (SIZE_T i = 0; i < Mesh->mNumFaces; ++i)
				{
					///la guardamos en una variable local.
					const aiFace& Face = Mesh->mFaces[i];

					///vemos si los indices que tiene son 3.
					if (Face.mNumIndices == 3)
					{
						///los metemos al vector de indices del index buffer.
						tempMesh->m_IB.AddIndex((int16)Face.mIndices[0]);
						tempMesh->m_IB.AddIndex((int16)Face.mIndices[1]);
						tempMesh->m_IB.AddIndex((int16)Face.mIndices[2]);
					}
				}
				
				if (Scene->HasMaterials())
				{
					m_Materials.resize(Scene->mNumMaterials);

					for (SIZE_T i = 0; i < Scene->mNumMaterials; i++)
					{
						BEMaterial* tempMat = &m_Materials[i];
						tempMat->Initialize();
						
						///creamos un material y un string de assimp.
						aiMaterial* material;
						aiString fileAdrr;

						///obtenemos la textura diffuse.
						material = Scene->mMaterials[i];

						for (int ktt = 0; ktt < aiTextureType_UNKNOWN; ++ktt)
						{
							uint32 textCount = material->GetTextureCount(static_cast<aiTextureType>(ktt));

							for (int j = 0; j < textCount; ++j)
							{
								material->GetTexture(static_cast<aiTextureType>(ktt), j, &fileAdrr);
							}

							///TextureName guarda el nombre de la textura que se va a cargar
							///como lo proporciona assimp al leerlo del modelo.
							String TextureName = fileAdrr.C_Str();
							///TextureToLoad almacena la ruta completa donde se encuentra la textura.
							String TextureToLoad = "";

							///veo que tipo de textura se cargo, y lo guardo en el material
							///que corresponde.
							if (TextureName.length() > 0)
							{
								
								TextureToLoad = "C:\\Users\\Lalo\\Documents\\School\\6to cuatrimestre\\Motores\\BlackEngine\\bin\\Resources\\";
								TextureName.erase(0, 3);
								TextureToLoad += TextureName;

								switch (ktt)
								{
								case 1:
									m_Materials[i].m_Diffuse = RM->LoadResourceFromFile(TextureToLoad);
									//m_Materials[i].m_Diffuse->Load(TextureToLoad);
									break;
								case 2:
									m_Materials[i].m_Specular = RM->LoadResourceFromFile(TextureToLoad);
									//m_Materials[i].m_Specular->Load(TextureToLoad);
									break;
								case 3:
									m_Materials[i].m_Ambiental = RM->LoadResourceFromFile(TextureToLoad);
									//m_Materials[i].m_Ambiental->Load(TextureToLoad);
									break;
								case 4:
									m_Materials[i].m_Emisive = RM->LoadResourceFromFile(TextureToLoad);
									//m_Materials[i].m_Emisive->Load(TextureToLoad);
									break;
								case 6:
									m_Materials[i].m_Normal = RM->LoadResourceFromFile(TextureToLoad);
									//m_Materials[i].m_Normal->Load(TextureToLoad);
								default:
									break;
								}
							}
						}
					}
				}//cierre if tiene materiales.
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
		///creamos los index buffers. Uno por cada mesh.
		for (SIZE_T i = 0; i < m_Meshes.size(); ++i)
		{
			m_Meshes[i].m_VB.CreateBuffer(pGraphicData);
		}
	}

	void BEModel::SetVB(const GraphicsAPIData * pGraphicData)
	{
		uint32 stride = sizeof(VERTEX);
		uint32 offset = 0;

		///seteamos todos los vertex buffers que hay.
		for (SIZE_T i = 0; i < m_Meshes.size(); ++i)
		{
			pGraphicData->m_DeviceContext->IASetVertexBuffers
			(
				0, 1, &m_Meshes[i].m_VB.m_BufferData->m_Buffer, &stride, &offset
			);
		}
	}

	void BEModel::CreateIB(const GraphicsAPIData * pGraphicData)
	{
		///creamos los index buffers. Uno por cada mesh.
		for (SIZE_T i = 0; i < m_Meshes.size(); ++i)
		{
			m_Meshes[i].m_IB.CreateBuffer(pGraphicData);
		}
	}

	void BEModel::SetIB(const GraphicsAPIData * pGraphicData)
	{
		///seteamos todos los index buffers. Uno por cada mesh.
		for (SIZE_T i = 0; i < m_Meshes.size(); ++i)
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

		for (SIZE_T i = 0; i < m_Meshes.size(); ++i)
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