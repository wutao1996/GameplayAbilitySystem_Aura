// Copyright Druid Mechanics


#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//初始化需要捕获的结构体信息
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	//添加到数组中
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//获取标签
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TaregetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	//填充聚合器参数
	FAggregatorEvaluateParameters Parameters;
	Parameters.SourceTags = SourceTags;
	Parameters.TargetTags = TaregetTags;

	//获取捕获的值
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, Parameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	//获取PlayerLevel
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	//返回计算结果
	return 80 + 2.5f * Vigor + 10 * PlayerLevel;
}
