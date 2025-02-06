// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class IEnemyInterface;
class UAuraInputConfig;
class USplineComponent;
class UDamageTextComponent;
class UAuraAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraInputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Shift;

private:
	bool bShiftKeyDown = false;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
	FHitResult HitResult;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> AuraInputConfig;

	TObjectPtr<UAuraAbilitySystemComponent> AuraASC;

	/* 鼠标点击移动 */
	/**
	 * @brief 目标位置
	 */
	FVector CachedDestination = FVector::ZeroVector;
	/**
	* @brief 鼠标按下持续时间
	*/
	float FollowTime = 0.f;
	/**
	* @brief 短按阈值
	 */
	float ShortPressThreshold = 0.5f;
	/**
	 * @brief 是否自动移动
	 */
	bool bAutoRunning = false;
	/**
	 * @brief 是否有目标对象
	 */
	bool bTargeting = false;
	/**
	 * @brief 自动移动接收半径（移动到目标位置半径内停止移动）
	 */
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	/**
	 * @brief 用于生成与目标位置之间相对平滑的移动路径
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	/**
	 * @brief 伤害文本组件类（用于显示收到的伤害）
	 */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InInputActionValue);

	void ShiftPressed();

	void ShiftReleased();

	void CursorTrace();

	void AbilityInputTagPressed(FGameplayTag InGameplayTag);

	void AbilityInputTagReleased(FGameplayTag InGameplayTag);

	void AbilityInputTagHeld(FGameplayTag InGameplayTag);

	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();

	void AutoRun();

public:
	UFUNCTION(Client, Reliable)
	void Client_ShowDamageNumber(float Damage, ACharacter* TargetCharacter, bool bCriticalHit, bool bBlockedHit);
};
