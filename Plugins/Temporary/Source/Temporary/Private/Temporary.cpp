#include "Temporary.h"

#define LOCTEXT_NAMESPACE "FTemporaryModule"

void FTemporaryModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT(">>> Temporary Plugin Started!"));
}

void FTemporaryModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT(">>> Temporary Plugin Shutdown!"));
}

#undef LOCTEXT_NAMESPACE

// 전역에 단 한 번. DLL에 InitializeModule 진입점을 심어줌 → 엔진이 모듈을 초기화할 수 있게 됨
IMPLEMENT_MODULE(FTemporaryModule, Temporary)
