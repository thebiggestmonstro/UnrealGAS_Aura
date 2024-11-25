// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include "UnrealWidgetFwd.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"

// HUD에서 OverlayWidgetController를 가져오는 함수, 이때 가져오는 OverlayWidgetController는 항상 1개를 유지함
UAuraOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AuraOverlayWidgetController == nullptr)
	{
		AuraOverlayWidgetController = NewObject<UAuraOverlayWidgetController>(this, AuraOverlayWidgetControllerClass);
		AuraOverlayWidgetController->SetWidgetControllerParams(WCParams);
	}

	return AuraOverlayWidgetController;
}

// HUD에서 OverlayWidget을 설정하는 함수
void AAuraHUD::InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState, UAbilitySystemComponent* InAbilitySystemComppnent, UAttributeSet* InAttributeSet)
{
	// 우선 OverlayWidget 클래스와 OverlayWidgetController 클래스가 존재하는지 확인
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized, fill out BP_AuraHUD"));
	checkf(AuraOverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass uninitialized, fill out BP_AuraHUD"));

	// 새로운 OverlayWidgetClass를 생성하고 생성된 OverlayWidget이 AuraWUserWidget에서 상속되었는지 확인
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	// OverlayWidgetController를 설정하기 위한 과정 -> 변수를 가져오고 이 변수를 통해 OverlayWidgetController를 생성
	const FWidgetControllerParams WidgetControllerParams(InPlayerController, InPlayerState, InAbilitySystemComppnent, InAttributeSet);
	UAuraOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// 생성한 OverlayWidgetController를 생성한 OverlayWidget에 설정해주고 OverlayWidget을 뷰포트에 생성
	OverlayWidget->SetWidgetController(WidgetController);
	Widget->AddToViewport();
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
}
