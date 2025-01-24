// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){};

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC;

	UPROPERTY()
	AActor* SourceAvatarActor;

	UPROPERTY()
	AController* SourceController;

	UPROPERTY()
	ACharacter* SourceCharacter;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC;

	UPROPERTY()
	AActor* TargetAvatarActor;

	UPROPERTY()
	AController* TargetController;

	UPROPERTY()
	ACharacter* TargetCharacter;
};

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 属性集
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	/*
	* Primary Attributes
	*/

	/**
	 * @brief 力量
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;		
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	/**
	 * @brief 智力
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;	
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	/**
	 * @brief 韧性
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience)
	FGameplayAttributeData Resilience;		
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	/**
	 * @brief 活力
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor)
	FGameplayAttributeData Vigor;		
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	/*
	* Secondary Attributes
	*/

	/**
	 * @brief 护甲
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;			
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	/**
	 * @brief 护甲穿透
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;	
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	/**
	 * @brief 有几率减少阻挡伤害
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

	/**
	 * @brief 暴击几率
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	/**
	 * @brief 暴击伤害
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	/**
	 * @brief 暴击抗性
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	/**
	 * @brief 生命恢复
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	/**
	 * @brief 法力恢复
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

	/**
	 * @brief 最大生命
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	/**
	 * @brief 最大法力
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	/*
	* Vital Attribute
	*/

	/**
	 * @brief 生命
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	/**
	 * @brief 法力
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps( TArray<class FLifetimeProperty> & OutLifetimeProps ) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;

	//Vital

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& InOldHealth);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& InOldMana);

	//Primary

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& InOldStrength);

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& InOldIntelligence);

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& InOldResilience);

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& InOldVigor);

	//Secondary

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& InOldArmor);

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& InOldArmorPenetration);

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& InOldBlockChance);

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& InOldCriticalHitChance);

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& InOldCriticalHitDamage);

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& InOldCriticalHitResistance);

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& InOldHealthRegeneration);

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& InOldManaRegeneration);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& InOldMaxHealth);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& InOldMaxMana);

private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};
