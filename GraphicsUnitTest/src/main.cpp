#include <BEGraphicsAPI.h>

#include <Windows.h>
#include <iostream>

#include "GraphicsUnitTest.h"

using namespace BlackEngine;

GraphicsUnitTest* pApp;

int main()
{
	pApp = new GraphicsUnitTest();
	pApp->Run();
	
	delete(pApp);
	return 0;
}