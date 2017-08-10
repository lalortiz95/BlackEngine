#include "BEVertexShader.h"
#include "BEGraphicsAPI.h"

#include <BEUtilityString.h>
#include <BEPrerequisitesUtility.h>
#include <BEFile.h>

namespace BlackEngine
{
#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)
	BEVertexShader::BEVertexShader()
	{
		Initialize();
	}


	BEVertexShader::~BEVertexShader()
	{
	}

	bool BEVertexShader::Initialize()
	{
		m_ShaderData = new ShaderData();
		m_VSData = new VertexShaderData();
		return true;
	}

	void BEVertexShader::Destroy()
	{
		m_VSData->Destroy();
		m_ShaderData->Destroy();
	}

	void BEVertexShader::Reflect()
	{

	}

	bool BEVertexShader::CreateShader(const String& FileName, const String& Target, const String& EntryPoint)
	{
		BEFile File;
		String FileData;
		HRESULT HRes;

		ID3D10Blob* ErrorBlob = nullptr;

		if (Initialize())
		{
			File.Open(FileName.c_str());
			FileData.resize(File.m_Size + 1, 0);
			File.Read(&FileData[0], File.m_Size);
			File.Close();

			///compilo el shader.
			HRes = D3DCompile
			(
				FileData.c_str(), FileData.size(), FileName.c_str(), NULL, NULL,
				EntryPoint.c_str(), Target.c_str(),
				D3DCOMPILE_DEBUG | D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_ShaderData->m_Blob,
				&ErrorBlob
			);

			if (FAILED(HRes))
			{
				if ((ErrorBlob))
				{
					String Error = (char*)ErrorBlob->GetBufferPointer();
					ErrorBlob->Release();
				}
				return false;
			}

			///se crea el vertex shader con el praphic api data.
			HRes = g_GraphicsAPI().m_pGraphicsAPIData->m_Device->CreateVertexShader
			(m_ShaderData->m_Blob->GetBufferPointer(), m_ShaderData->m_Blob->GetBufferSize(),
				nullptr, &m_VSData->m_VertexShader);

			///veo que se haya hecho bien.
			if (FAILED(HRes))
			{
				return false;
			}
			return true;
		}
		return false;
	}
}
