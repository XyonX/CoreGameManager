/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CoreGameMode.generated.h"

/**
 * 
 */
UCLASS()
class COREGAMEMANAGER_API ACoreGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	ACoreGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	void LoadMasterSkeleton ();
	void  AssignMasterSkeletalToSkeletalMesh(USkeletalMesh*InSkeletalMesh);
	TArray<USkeletalMesh*> ScanForSkeletalMesh (FString FolderLocation);
	TArray<UAnimSequence*> ScanForAnimationSequences (FString FolderLocation);

	
protected:

	/**
	* Base Skeleton Reference of this project.
	* WARNING: Do not modify this variable!
	* Modifying it may break the game's animation and character system.
	* This variable is used to hold the shared Skeleton for all Skeletal Meshes in the game.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Data")
	USkeleton* MasterSkeleton_UE5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Data")
	USkeleton* MasterSkeleton_UE4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Data")
	USkeletalMesh* MannyRef_UE5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Data")
	USkeletalMesh* MannyRef_UE4;
	
	UPROPERTY()
	TArray<USkeletalMesh*>SkeletalMeshArray_UE5;
	UPROPERTY()
	TArray<USkeletalMesh*>SkeletalMeshArray_UE4;

	UPROPERTY()
	TArray<UAnimSequence*>AnimationSequencesArray_UE5;
	UPROPERTY()
	TArray<UAnimSequence*>AnimationSequencesArray_UE4;

	
};
