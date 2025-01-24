// Copyright Druid Mechanics


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "UI/AuraGameplayTags.h"
#include "AbilitySystem/GameplayAbility/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InGameplayAbilities)
{
	//遍历标签集合
	for (TSubclassOf<UGameplayAbility> GameplayAbility : InGameplayAbilities)
	{
		//构建游戏能力规范
		FGameplayAbilitySpec GameplayAbilitySpec = FGameplayAbilitySpec(GameplayAbility, 1.f);
		if (UAuraGameplayAbility* AuraGameplayAbility = Cast<UAuraGameplayAbility>(GameplayAbilitySpec.Ability))
		{
			//将标签添加到动态能力标签集合中
			GameplayAbilitySpec.DynamicAbilityTags.AddTag(AuraGameplayAbility->StartupInputTag);
			//给与能力
			GiveAbility(GameplayAbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InGameplayTag)
{
	if (!InGameplayTag.IsValid()) return;
	//遍历所有的游戏能力规范
	for (FGameplayAbilitySpec GameplayTag : GetActivatableAbilities())
	{
		//判断是否包含标签
		if (GameplayTag.DynamicAbilityTags.HasTagExact(InGameplayTag))
		{	
			//通知GameplayAbility按键被释放
			AbilitySpecInputReleased(GameplayTag);
			//判断能力是否激活
			if (!GameplayTag.IsActive())
			{
				//激活能力
				TryActivateAbility(GameplayTag.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InGameplayTag)
{
	if (!InGameplayTag.IsValid()) return;
	//遍历所有的游戏能力规范
	for (FGameplayAbilitySpec GameplayTag : GetActivatableAbilities())
	{
		//判断是否包含标签
		if (GameplayTag.DynamicAbilityTags.HasTagExact(InGameplayTag))
		{
			//通知GameplayAbility按键被按下
			AbilitySpecInputPressed(GameplayTag);
			//判断能力是否激活
			if (!GameplayTag.IsActive())
			{
				//激活能力
				TryActivateAbility(GameplayTag.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* InAbilitySystemComponent, const FGameplayEffectSpec& InEffectSpec, FActiveGameplayEffectHandle InActiveEffectHandle)
{
	FGameplayTagContainer GameplayTagContainer;
	InEffectSpec.GetAllAssetTags(GameplayTagContainer);
	OnEffectAssetTags.Broadcast(GameplayTagContainer);
}
