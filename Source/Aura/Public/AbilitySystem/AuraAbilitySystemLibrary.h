// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;

/**
 * 能力系统蓝图函数库
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{ 
	GENERATED_BODY()

public:
	/**
	 * @brief 获取OverlayWidgetController
	 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "InWorldContextObject"), Category = "AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* InWorldContextObject);

	/**
	 * @brief 获取AttributeMenuWidgetController
	 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "InWorldContextObject"), Category = "AuraAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* InWorldContextObject);

	/**
	 * @brief 初始化默认属性
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "InWorldContextObject"), Category = "AuraAbilitySystemLibrary|CharacterClassDefault")
	static void InitializeDefaultAttributes(const UObject* InWorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	/**
	 * @brief 赋予启动能力（敌人）
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "InWorldContextObject"), Category = "AuraAbilitySystemLibrary|Abilities")
	static void GiveStartupAbilities(const UObject* InWorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass);

	/**
	 * @brief 获取角色类别信息
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "InWorldContextObject"), Category = "AuraAbilitySystemLibrary|Abilities")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* InWorldContextObject);

	/**
	 * @brief 是否暴击
	 */
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	/**
	 * @brief 是否格挡
	 */
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	/**
	 * @brief 设置是否暴击
	 */
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	/**
	* @brief 设置是否格挡
	*/
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	/**
	 * @brief 获取半径内玩家
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "InWorldContextObject"), Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject* InWorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& IgnoreActors, float Radius, const FVector& SphereOrigin);

	/**
	 * @brief 是否不是朋友关系
	 */
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);
};