// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase , public IEnemyInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level = 1;
	
public:
	AAuraEnemy();

	//~ Begin IEnemyInterface Interface.
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//~ End IEnemyInterface Interface.

	virtual int32 GetPlayerLevel() override;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
};
