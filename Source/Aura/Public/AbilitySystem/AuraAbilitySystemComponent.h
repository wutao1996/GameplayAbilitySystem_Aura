// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectAssetTags, const FGameplayTagContainer&);

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	FOnEffectAssetTags OnEffectAssetTags;

	void AbilityActorInfoSet();

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InGameplayAbilities);

	void AbilityInputTagReleased(const FGameplayTag& InGameplayTag);

	void AbilityInputTagHeld(const FGameplayTag& InGameplayTag);
protected:
	void EffectApplied(UAbilitySystemComponent* InAbilitySystemComponent, const FGameplayEffectSpec& InEffectSpec, FActiveGameplayEffectHandle InActiveEffectHandle);
	
};
