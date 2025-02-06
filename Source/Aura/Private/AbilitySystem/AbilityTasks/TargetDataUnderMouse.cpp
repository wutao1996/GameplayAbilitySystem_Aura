// Copyright Druid Mechanics


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* TargetDataUnderMouse = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return TargetDataUnderMouse;
}

void UTargetDataUnderMouse::Activate()
{
	//�Ƿ��ڿͻ���
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		//����Ǳ�����Ҫ�����ݷ��͵�������
		SendMouseCursorData();
	}
	else
	{
		//��ί�У������������յ����ݺ�����ص������ᱻ������
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		//�ж������ί���Ƿ��Ѿ�������
		const bool bCalledDelegate =AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey());
		if (!bCalledDelegate)
		{
			//�ȴ���������ϴ�
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	//�����µ�Ԥ���
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());

	if (APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get())
	{
		FHitResult Hit;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		//����Ŀ������
		FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
		Data->HitResult = Hit;

		//�������ݾ������������
		FGameplayAbilityTargetDataHandle DataHandle;
		DataHandle.Add(Data);

		//����Ŀ�����ݵ�������
		AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

		//�жϵ�ǰGameplayAbility�Ƿ��ڼ���״̬
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			ValidData.Broadcast(DataHandle);
		}
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	//֪ͨ�ͻ��� ���������Ѿ����ղ������˴ӿͻ��˸��Ƶ�Ŀ�����ݣ�����������TargetDataӦ�õ��ͻ��ˣ�����������棩
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	//�жϵ�ǰGameplayAbility�Ƿ��ڼ���״̬
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
