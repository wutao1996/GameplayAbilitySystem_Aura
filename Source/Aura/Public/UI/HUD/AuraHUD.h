// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

struct FWidgetControllerParams;
class APlayerState;
class UAttributeSet;
class UAuraUserWidget;
class APlayerController;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;

/**
 * HUD
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;


	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	/*
	* ÊôÐÔ²Ëµ¥UI¿ØÖÆÆ÷
	*/
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

public:
	void InitOverlay(APlayerController* InPC, APlayerState* InPS, UAbilitySystemComponent* InASC, UAttributeSet* InAS);

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& InParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& InParams);
};
