#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterData.generated.h"

/**
 * 캐릭터의 데이터 저장용 UObject 클래스 (Temporary 플러그인 소속)
 */
UCLASS(BlueprintType)
class TEMPORARY_API UCharacterData : public UObject
{
	GENERATED_BODY()

public:
	UCharacterData();

	/** 캐릭터 이름 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Stats")
	FString CharacterName;

	/** 체력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Stats")
	int32 Health;

	/** 이동 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Stats")
	float MoveSpeed;
};
