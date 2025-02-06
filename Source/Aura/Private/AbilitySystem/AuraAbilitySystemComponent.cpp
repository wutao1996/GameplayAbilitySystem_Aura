// Copyright Druid Mechanics


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::Client_EffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InGameplayAbilities)
{
	//������ǩ����
	for (TSubclassOf<UGameplayAbility> GameplayAbility : InGameplayAbilities)
	{
		//������Ϸ�����淶
		FGameplayAbilitySpec GameplayAbilitySpec = FGameplayAbilitySpec(GameplayAbility, 1.f);
		if (UAuraGameplayAbility* AuraGameplayAbility = Cast<UAuraGameplayAbility>(GameplayAbilitySpec.Ability))
		{
			//����ǩ��ӵ���̬������ǩ������
			GameplayAbilitySpec.DynamicAbilityTags.AddTag(AuraGameplayAbility->StartupInputTag);
			//��������
			GiveAbility(GameplayAbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InGameplayTag)
{
	if (!InGameplayTag.IsValid()) return;
	//�������е���Ϸ�����淶
	for (FGameplayAbilitySpec GameplayTag : GetActivatableAbilities())
	{
		//�ж��Ƿ������ǩ
		if (GameplayTag.DynamicAbilityTags.HasTagExact(InGameplayTag))
		{	
			//֪ͨGameplayAbility�������ͷ�
			AbilitySpecInputReleased(GameplayTag);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InGameplayTag)
{
	if (!InGameplayTag.IsValid()) return;
	//�������е���Ϸ�����淶
	for (FGameplayAbilitySpec GameplayTag : GetActivatableAbilities())
	{
		//�ж��Ƿ������ǩ
		if (GameplayTag.DynamicAbilityTags.HasTagExact(InGameplayTag))
		{
			//֪ͨGameplayAbility����������
			AbilitySpecInputPressed(GameplayTag);
			//�ж������Ƿ񼤻�
			if (!GameplayTag.IsActive())
			{
				//��������
				TryActivateAbility(GameplayTag.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::Client_EffectApplied_Implementation(UAbilitySystemComponent* InAbilitySystemComponent, const FGameplayEffectSpec& InEffectSpec, FActiveGameplayEffectHandle InActiveEffectHandle)
{
	FGameplayTagContainer GameplayTagContainer;
	InEffectSpec.GetAllAssetTags(GameplayTagContainer);
	OnEffectAssetTags.Broadcast(GameplayTagContainer);
}
