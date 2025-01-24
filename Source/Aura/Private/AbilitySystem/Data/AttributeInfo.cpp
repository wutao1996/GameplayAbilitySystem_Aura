// Copyright Druid Mechanics


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& InAttributeTag)
{
	for (const FAuraAttributeInfo& AttributeInfo : AttributeInformation)
	{
		if (AttributeInfo.AttributeTag == InAttributeTag)
		{
			return AttributeInfo;
		}
	}
	return FAuraAttributeInfo();
}
