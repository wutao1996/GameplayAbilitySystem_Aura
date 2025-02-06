// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UCharacterClassInfo;

/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief ��ɫ�����Ϣ�����ʲ�
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Default")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
