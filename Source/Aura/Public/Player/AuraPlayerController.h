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

	/* ������ƶ� */
	/**
	 * @brief Ŀ��λ��
	 */
	FVector CachedDestination = FVector::ZeroVector;
	/**
	* @brief ��갴�³���ʱ��
	*/
	float FollowTime = 0.f;
	/**
	* @brief �̰���ֵ
	 */
	float ShortPressThreshold = 0.5f;
	/**
	 * @brief �Ƿ��Զ��ƶ�
	 */
	bool bAutoRunning = false;
	/**
	 * @brief �Ƿ���Ŀ�����
	 */
	bool bTargeting = false;
	/**
	 * @brief �Զ��ƶ����հ뾶���ƶ���Ŀ��λ�ð뾶��ֹͣ�ƶ���
	 */
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	/**
	 * @brief ����������Ŀ��λ��֮�����ƽ�����ƶ�·��
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	/**
	 * @brief �˺��ı�����ࣨ������ʾ�յ����˺���
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
