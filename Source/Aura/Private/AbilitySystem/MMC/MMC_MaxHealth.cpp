// Copyright Druid Mechanics


#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//��ʼ����Ҫ����Ľṹ����Ϣ
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	//��ӵ�������
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//��ȡ��ǩ
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TaregetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	//���ۺ�������
	FAggregatorEvaluateParameters Parameters;
	Parameters.SourceTags = SourceTags;
	Parameters.TargetTags = TaregetTags;

	//��ȡ�����ֵ
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, Parameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	//��ȡPlayerLevel
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	//���ؼ�����
	return 80 + 2.5f * Vigor + 10 * PlayerLevel;
}
