/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/


#include "LoadingScreenGameMode.h"
#include "CoreGameManager/Pawn/UIPawn.h"
#include "CoreGameManager/Player/UIPlayerController.h"

ALoadingScreenGameMode::ALoadingScreenGameMode(const FObjectInitializer& ObjectInitializer)
{
	DefaultPawnClass=AUIPawn::StaticClass();
	PlayerControllerClass= AUIPlayerController::StaticClass();
}

void ALoadingScreenGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ALoadingScreenGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
