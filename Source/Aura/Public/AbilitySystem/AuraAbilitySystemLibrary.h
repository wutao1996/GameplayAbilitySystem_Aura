// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
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
};