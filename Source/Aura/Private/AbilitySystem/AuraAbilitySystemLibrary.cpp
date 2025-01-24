// Copyright Druid Mechanics


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/AuraHUD.h"
#include "Player/AuraPlayerState.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* InWorldContextObject)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(InWorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* PlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PlayerState->GetAbilitySystemComponent();
			UAttributeSet* AS = PlayerState->GetAuraAttributeSet();
			return AuraHUD->GetOverlayWidgetController(FWidgetControllerParams(PlayerController, PlayerState, ASC, AS));
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* InWorldContextObject)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(InWorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* PS = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAuraAttributeSet();
			return AuraHUD->GetAttributeMenuWidgetController(FWidgetControllerParams(PlayerController, PS, ASC, AS));
		}
	}
	return nullptr;
}
