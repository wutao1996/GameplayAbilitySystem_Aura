// Copyright Druid Mechanics


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	if (UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
		OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
		OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	}
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	if (UAuraAbilitySystemComponent* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
		{
			//注册属性值变化
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda
			(
				[this](const FOnAttributeChangeData& InData)
				{
					OnHealthChanged.Broadcast(InData.NewValue);
				}
			);
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda
			(
				[this](const FOnAttributeChangeData& InData)
				{
					OnMaxHealthChanged.Broadcast(InData.NewValue);
				}
			);
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda
			(
				[this](const FOnAttributeChangeData& InData)
				{
					OnManaChanged.Broadcast(InData.NewValue);
				}
			);
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda
			(
				[this](const FOnAttributeChangeData& InData)
				{
					OnMaxManaChanged.Broadcast(InData.NewValue);
				}
			);

			AuraAbilitySystemComponent->OnEffectAssetTags.AddLambda(
				[this](const FGameplayTagContainer& InGameplayTagContainer)
				{
					for (const FGameplayTag& Tag : InGameplayTagContainer)
					{
						//如果是消息标签，广播给绑定的UI
						FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag("Message");
						if (Tag.MatchesTag(MessageTag))
						{
							const FUIWidgetRow* UIWidgetRow = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
							if (UIWidgetRow)
							{
								MessageWidgetRowSignature.Broadcast(*UIWidgetRow);
							}
						}
					}	
				}
			);
		}
	}
}