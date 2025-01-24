// Copyright Druid Mechanics


#include "Input/AuraInputConfig.h"
#include "InputAction.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionByTag(const FGameplayTag& InGameplayTag) const
{
	for (FAuraInputAction AuraInputAction : AbilityInputActions)
	{
		if (AuraInputAction.InputAction && AuraInputAction.InputTag == InGameplayTag)
		{
			return AuraInputAction.InputAction;
		}
	}
	return nullptr;
}
