// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EGameState.generated.h"

/**
 * ゲームの進行状態
 */
UENUM(BlueprintType)
enum class EGameState : uint8
{
	None,
	Intro,
	InGame,
	GameOver,
	Clear,
	NextLevel,
};
