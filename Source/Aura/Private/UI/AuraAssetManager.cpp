// Copyright Druid Mechanics


#include "UI/AuraAssetManager.h"
#include "UI/AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAttributesGameplayTags::InitializeNativeGameplayTags();
}
