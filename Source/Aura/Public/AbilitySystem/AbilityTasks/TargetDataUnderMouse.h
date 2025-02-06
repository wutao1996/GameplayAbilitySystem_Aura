// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, Data);

/**
 * ����µ�Ŀ������
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:
	/**
	* @brief ͨ������ķ�ʽ��Ϊ�ڵ���������
	*/
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataUnderMouse", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = true))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

protected:
	virtual void Activate() override;

private:
	/**
	 * @brief ��������
	 */
	void SendMouseCursorData();

	/**
	 * @brief Ŀ�����ݸ��ƻص�
	 * @param DataHandle Ŀ�����ݾ��
	 * @param ActivationTag ��ǩ
	 */
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
