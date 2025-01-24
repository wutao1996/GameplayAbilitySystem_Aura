// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

struct FGameplayTag;
struct FGameplayAttribute;
class UAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, AttributeInfo);

/**
 *  Ù–‘≤Àµ•WidgetController
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FAttributeInfoSignature AttributeInfoSignature;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

private:
	void BroadcastAttributeInfo(const FGameplayTag& InGameplayTag, const FGameplayAttribute& InGameplayAttribute) const;
};
