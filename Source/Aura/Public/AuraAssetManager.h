// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * �ʲ�����
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UAuraAssetManager& Get();

	virtual void StartInitialLoading() override;
private:
	static UAuraAssetManager AssetManager;

};
