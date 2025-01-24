// Copyright Druid Mechanics


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	if (UAuraAttributeSet*  AS = Cast<UAuraAttributeSet>(AttributeSet))
	{
		check(AttributeInfo);

		for (auto& Pair : AS->TagsToAttributes)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		}
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	if (UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet))
	{
		check(AttributeInfo);

		for (auto& Pair : AS->TagsToAttributes)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda
			(
				[this, Pair](const FOnAttributeChangeData& Data)
				{
					BroadcastAttributeInfo(Pair.Key, Pair.Value());
				}
			);

		}
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& InGameplayTag, const FGameplayAttribute& InGameplayAttribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoByTag(InGameplayTag);
	Info.AttributeValue = InGameplayAttribute.GetNumericValue(AttributeSet);
	AttributeInfoSignature.Broadcast(Info);
}
