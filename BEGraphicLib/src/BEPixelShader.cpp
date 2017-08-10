#include "BEPixelShader.h"
#include "BEGraphicsAPI.h"
#include <BEUtilityString.h>
#include <BEPrerequisitesUtility.h>
#include <BEFile.h>

namespace BlackEngine
{
#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)
	BEPixelShader::BEPixelShader()
	{
		Initialize();
	}

	BEPixelShader::~BEPixelShader()
	{
	}
	bool BEPixelShader::Initialize()
	{
		m_ShaderData = new ShaderData();
		m_PSData = new PixelShaderData();
		return true;
	}

	void BEPixelShader::Destroy()
	{
		m_PSData->Destroy();
		m_ShaderData->Destroy();
	}

	void BEPixelShader::Reflect()
	{
	}

	bool BEPixelShader::CreateShader(/*const GraphicsAPIData * pGraphicData,*/ const String& FileName, const String& Target, const String& EntryPoint)
	{
		BEFile File;
		HRESULT HRes;
		String FileData;

		ID3D10Blob* ErrorBlob;

		if (Initialize())
		{
			File.Open(FileName.c_str());
			FileData.resize(File.m_Size + 1, 0);
			File.Read(&FileData[0], File.m_Size);
			File.Close();
			///compilo el shader.
			HRes = D3DCompile
			(
				FileData.c_str(), FileData.size(), FileName.c_str(),
				NULL, NULL, EntryPoint.c_str(), Target.c_str(),
				D3DCOMPILE_DEBUG | D3DCOMPILE_ENABLE_STRICTNESS, 0, 
				&m_ShaderData->m_Blob, &ErrorBlob
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

			HRes = g_GraphicsAPI().m_pGraphicsAPIData->m_Device->CreatePixelShader
			(m_ShaderData->m_Blob->GetBufferPointer(), m_ShaderData->m_Blob->GetBufferSize(),
				nullptr, &m_PSData->m_PixelShader);
			//HRes = pGraphicData->m_Device->CreatePixelShader
			//(m_ShaderData->m_Blob->GetBufferPointer(), m_ShaderData->m_Blob->GetBufferSize(),
			//	nullptr, &m_PSData->m_PixelShader);

			if (FAILED(HRes))
			{
				return false;
			}
			return true;
		}
		return false;
	}
}
