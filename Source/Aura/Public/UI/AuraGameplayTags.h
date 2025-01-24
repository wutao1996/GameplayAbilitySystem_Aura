// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * ���ر�ǩ
 */

 struct FAttributesGameplayTags 
 {
 public:
	 FGameplayTag Attributes_Primary_Strength;
	 FGameplayTag Attributes_Primary_Intelligence;
	 FGameplayTag Attributes_Primary_Resilience;
	 FGameplayTag Attributes_Primary_Vigor;


	 FGameplayTag Attributes_Secondary_Armor;
	 FGameplayTag Attributes_Secondary_ArmorPenetration;
	 FGameplayTag Attributes_Secondary_BlockChance;
	 FGameplayTag Attributes_Secondary_CriticalHitChance;
	 FGameplayTag Attributes_Secondary_CriticalHitDamage;
	 FGameplayTag Attributes_Secondary_CriticalHitResistance;
	 FGameplayTag Attributes_Secondary_HealthRegeneration;
	 FGameplayTag Attributes_Secondary_ManaRegeneration;
	 FGameplayTag Attributes_Secondary_MaxHealth;
	 FGameplayTag Attributes_Secondary_MaxMana;

	 FGameplayTag Input_LMB;
	 FGameplayTag Input_RMB;
	 FGameplayTag Input_1;
	 FGameplayTag Input_2;
	 FGameplayTag Input_3;
	 FGameplayTag Input_4;

	static const FAttributesGameplayTags& Get() { return GameplayTags; };

	static void InitializeNativeGameplayTags();

 protected:

 private:
	static FAttributesGameplayTags GameplayTags;
 };