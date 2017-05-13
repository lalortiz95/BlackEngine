#include "BELogger.h"

namespace BlackEngine
{
	void Logger::StartLogger(char * szFileName)
	{
		std::fstream File;

		///creamos el archivo, lo truncamos por si ya existe uno con ese nombre lo sobreescriba.
		File.open(szFileName, std::ios::out | std::ios::trunc);
		///guardamos el nombre del archivo en una variable miembra.
		m_FileName = szFileName;
		///crerramos el archivo.
		File.close();
	}

	void Logger::SendMessage(int type, String Msg, int Line)
	{
		std::fstream filePath;
		///abrimos el archivo que ya está creado.
		filePath.open(m_FileName.c_str(), std::ios_base::out | std::ios_base::app);
		///revisamos que haya abierto correctamente.
		if (filePath.is_open())
		{
			///dependiendo de que tipo sea, manda un mensaje distinto.
			switch (type)
			{
			case Logger::BE_GENERAL:
				filePath << "Mensaje general. " << Msg << " In line: " << Line << std::endl;
				break;
			case Logger::BE_WARNING:
				filePath << "Mensaje de warning. " << Msg << " In line: " << Line << std::endl;
				break;
			case Logger::BE_ERROR:
				filePath << "Mensaje de error. " << Msg << " In line: " << Line << std::endl;
				break;
			case Logger::BE_FATALERROR:
				filePath << "Mensaje de error fatal. " << Msg << " In line: " << Line << std::endl;
				break;
			default:
				break;
			}

			///cerramos el archivo.
			filePath.close();
		}
	}
}