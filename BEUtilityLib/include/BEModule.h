#pragma once
#include "BEUtilityPCH.h"

//así es como se usaría en nuestra clase directX
//DirectX : public Module<DirectX>
//luego entonces, podemos llamar a sus funciones en cualquier lado.

template <class T>
class Module
{
public:

	static T& Instance()
	{
		return *_Instance();
	}

	static T* InstancePtr()
	{
		return _Instance();
	}

	template<class... Args>
	static void StartUp(Args&&... args)
	{
		_Instance() = new<T>(std::forward<Args>(args)...);
		IsShutDown() = false;

		((Module*)_Instance())->OnStartUp();
	}

	static void ShutDown()
	{
		((Module*)_Instance())->OnShutDown();

		delete(_Instance());
		IsShutDown() = true;
	}

protected:
	Module()
	{
	}

	virtual ~Module() {}

	virtual void OnStartUp()
	{

	}

	virtual void OnShutDown()
	{

	}

	static T*& _Instance()
	{
		static T* inst = nullptr;
		return inst;
	}

	static bool IsShutDown()
	{
		bool inst = true;
		return inst;
	}
};