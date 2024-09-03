#pragma once
#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"

class ISingleton
{
public:
	virtual ~ISingleton() {}

	virtual void Initialize() {}
	virtual void Finalize() {}
	virtual void Tick(float _DeltaTime) {}
};

template<typename TClass>
class DDSingleton : public ISingleton
{
protected:
	static TClass* _pInstance;

public:  
	static TClass* MakeInstance();
	static void    RemoveInstance();
	static TClass* GetInstance();
	static bool    HasInstance();
};

template <typename TClass>
TClass* DDSingleton<TClass>::MakeInstance()
{
	_pInstance = NewObject<TClass>();
	_pInstance->AddToRoot();
	return _pInstance;
}

template <typename TClass>
void DDSingleton<TClass>::RemoveInstance()
{
	if(_pInstance->IsValidLowLevel())
	{
		_pInstance->RemoveFromRoot();
		_pInstance->ConditionalBeginDestroy();
	}
	_pInstance = nullptr;
}

template <typename TClass>
TClass* DDSingleton<TClass>::GetInstance()
{
	return _pInstance;
}

template <typename TClass>
bool DDSingleton<TClass>::HasInstance()
{
	return _pInstance->IsValidLowLevel() ? true : false;
}

template<typename TClass>
TClass* DDSingleton<TClass>::_pInstance = nullptr;