// Copyright Druid Mechanics


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "InputActionValue.h"
#include "Interaction/EnemyInterface.h"
#include "Input/AuraInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "UI/AuraGameplayTags.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("SplieComponent");
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(AuraInputContext, 0);
	}

	SetShowMouseCursor(true);
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeGameAndUI);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	AutoRun();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UAuraInputComponent* AuraInputComponent = Cast<UAuraInputComponent>(InputComponent))
	{
		AuraInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
		AuraInputComponent->BindAbilityActions(AuraInputConfig, this, &AAuraPlayerController::AbilityInputTagPressed, &AAuraPlayerController::AbilityInputTagReleased, &AAuraPlayerController::AbilityInputTagHeld);
	}
}

void AAuraPlayerController::Move(const FInputActionValue& InInputActionValue)
{
	const FVector2D InputAxisVector = InInputActionValue.Get<FVector2D>();
	const FRotator YawRotator = FRotator(0.f, GetControlRotation().Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = Cast<APawn>(GetPawn()))
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (!HitResult.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(HitResult.GetActor());

	if (LastActor != nullptr)
	{
		if (ThisActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else if (LastActor != ThisActor)
		{
			LastActor->UnHighlightActor();
			ThisActor->HighlightActor();
		}
	}
	else
	{
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InGameplayTag)
{
	if (InGameplayTag.MatchesTagExact(FAttributesGameplayTags::Get().Input_LMB))
	{
		bTargeting = ThisActor != nullptr ? true : false;
		bAutoRunning = false;
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InGameplayTag)
{
	if (!InGameplayTag.MatchesTagExact(FAttributesGameplayTags::Get().Input_LMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InGameplayTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InGameplayTag);
		}
	}
	else
	{
		APawn* ControllerPawn = GetPawn<APawn>();
		if (ControllerPawn && FollowTime <= ShortPressThreshold)
		{
			//查找路径
			if (UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControllerPawn->GetActorLocation(), CachedDestination))
			{
				for (const FVector& PathLocation : NavigationPath->PathPoints)
				{
					Spline->AddSplinePoint(PathLocation, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PathLocation, 10.f, 10, FColor::Green, false, 10.f);
				}
				//将查找到的最后一个路径点设置为目标位置
				CachedDestination = NavigationPath->PathPoints[NavigationPath->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InGameplayTag)
{
	if (!InGameplayTag.MatchesTagExact(FAttributesGameplayTags::Get().Input_LMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InGameplayTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InGameplayTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		/**
		 * 获取鼠标点击的位置
		 */
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}
		//移动Pawn
		if (APawn* ControllerPawn = GetPawn<APawn>())
		{
			const FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
			ControllerPawn->AddMovementInput(WorldDirection);
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (AuraASC == nullptr)
	{
		AuraASC = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraASC;
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);

		ControllerPawn->AddMovementInput(Direction);

		//如果接近目标停止自动移动
		if ((LocationOnSpline - CachedDestination).Length() <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
