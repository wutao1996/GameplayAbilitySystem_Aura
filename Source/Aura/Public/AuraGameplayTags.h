// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * ±æµÿ±Í«©
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

	 FGameplayTag Attributes_Resistance_Fire;
	 FGameplayTag Attributes_Resistance_Lightning;
	 FGameplayTag Attributes_Resistance_Arcane;
	 FGameplayTag Attributes_Resistance_Physical;

	 FGameplayTag Input_LMB;
	 FGameplayTag Input_RMB;
	 FGameplayTag Input_1;
	 FGameplayTag Input_2;
	 FGameplayTag Input_3;
	 FGameplayTag Input_4;

	 FGameplayTag Damage;
	 FGameplayTag Damage_Fire;
	 FGameplayTag Damage_Lightning;
	 FGameplayTag Damage_Arcane;
	 FGameplayTag Damage_Physical;
	 TMap<FGameplayTag, FGameplayTag> DamageTypesToResistance;

	 FGameplayTag Effects_HitReact;

	 //Ability
	 FGameplayTag Ability_Attack;
	 FGameplayTag Ability_Summon;

	 //Socket Tag
	 FGameplayTag CombatSocket_Weapon;
	 FGameplayTag CombatSocket_RightHand;
	 FGameplayTag CombatSocket_LeftHand;
	 FGameplayTag CombatSocket_Tail;

	 //Montage Tag
	 FGameplayTag Montage_Attack_1;
	 FGameplayTag Montage_Attack_2;
	 FGameplayTag Montage_Attack_3;
	 FGameplayTag Montage_Attack_4;

	static const FAttributesGameplayTags& Get() { return GameplayTags; };

	static void InitializeNativeGameplayTags();

 private:
	static FAttributesGameplayTags GameplayTags;
 };