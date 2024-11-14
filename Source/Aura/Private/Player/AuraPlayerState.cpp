// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	// 서버가 클라이언트를 업데이트하는 주기
	NetUpdateFrequency = 100.f;
}
