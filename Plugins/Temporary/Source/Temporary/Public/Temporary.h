#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FTemporaryModule : public IModuleInterface
{
public:
	/** 모듈이 메모리에 로드될 때 호출됨 */
	virtual void StartupModule() override;

	/** 모듈이 언로드될 때(에디터 종료 등) 호출됨 */
	virtual void ShutdownModule() override;
};
