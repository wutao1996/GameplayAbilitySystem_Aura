// Copyright Druid Mechanics


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* InTargetActor, TSubclassOf<UGameplayEffect> InGameplayEffectClass)
{
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor))
	{
		FGameplayEffectContextHandle GameplayEffectHandle = TargetASC->MakeEffectContext();
		GameplayEffectHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(InGameplayEffectClass, 1.f, GameplayEffectHandle);
		FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		//�ж�Ч�������Ƿ��ǳ�����
		if (EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
		}
	}
}

void AAuraEffectActor::OnOverlap(AActor* InTarget)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(InTarget, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(InTarget, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(InTarget, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* InTarget)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(InTarget, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(InTarget, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(InTarget, InfiniteGameplayEffectClass);
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTarget);

		TArray<FActiveGameplayEffectHandle> ActivesToRemove;

		for (TPair<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandle : ActiveEffectHandles)
		{
			if (ActiveEffectHandle.Value == TargetASC)
			{
				//ֻ�Ƴ�һ���ѵ���Ч��
				TargetASC->RemoveActiveGameplayEffect(ActiveEffectHandle.Key, 1);
				ActivesToRemove.Add(ActiveEffectHandle.Key);
			}
		}

		for (FActiveGameplayEffectHandle& ActiveEffectHandle : ActivesToRemove)
		{
			ActiveEffectHandles.Remove(ActiveEffectHandle);
		}
	}
}

