// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ModuleAndPluginCameraManager.generated.h"

/**
 *  Basic First Person camera manager.
 *  Limits min/max look pitch.
 */
UCLASS()
class AModuleAndPluginCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	/** Constructor */
	AModuleAndPluginCameraManager();
};
