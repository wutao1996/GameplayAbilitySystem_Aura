// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	/**
	 * @brief 属性标签
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	/**
	 * @brief 属性名
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();

	/**
	 * @brief 属性描述
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription = FText();

	/**
	 * @brief 属性值
	 */
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 * 属性信息
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
	
	/**
	 * @brief 根据属性标签获取属性信息
	 * @param InAttributeTag 属性标签
	 * @return 属性信息
	 */
	FAuraAttributeInfo FindAttributeInfoByTag(const FGameplayTag& InAttributeTag);
};
