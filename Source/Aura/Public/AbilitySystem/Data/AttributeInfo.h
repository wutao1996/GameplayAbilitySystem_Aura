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
	 * @brief ���Ա�ǩ
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	/**
	 * @brief ������
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();

	/**
	 * @brief ��������
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription = FText();

	/**
	 * @brief ����ֵ
	 */
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 * ������Ϣ
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
	
	/**
	 * @brief �������Ա�ǩ��ȡ������Ϣ
	 * @param InAttributeTag ���Ա�ǩ
	 * @return ������Ϣ
	 */
	FAuraAttributeInfo FindAttributeInfoByTag(const FGameplayTag& InAttributeTag);
};
