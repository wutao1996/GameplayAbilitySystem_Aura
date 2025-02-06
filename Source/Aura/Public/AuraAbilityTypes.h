// Copyright Druid Mechanics

#pragma once
#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"


/**
 * @brief �Զ�����ϷЧ��������
 */

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY();

public:
	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit() const { return bIsBlockedHit; }

	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FAuraGameplayEffectContext* Duplicate() const
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:
	UPROPERTY()
	bool bIsCriticalHit = false;		//�Ƿ񱩻�
	UPROPERTY()
	bool bIsBlockedHit = false;			//�Ƿ��

};

/**
 * @brief �ṹ������
 */
template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum 
	{
		WithNetSerializer = true,	//�������������л����ܣ�����ڶ�����Ϸ����Ҫ������ͻ��˺ͷ�����֮��ͬ������ϷЧ����˵�Ǳز����ٵ�
		WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};