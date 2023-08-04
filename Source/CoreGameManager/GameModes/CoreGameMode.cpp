/******************************************************************************
* Project Core - Generic UE Project
* Copyright (c) [2023] [ Joydip chakraborty ]
* This class is part of the ProjectCore open-source project. 
* ******************************************************************************/

#include "CoreGameMode.h"

#include "AssetRegistry/AssetRegistryModule.h"
//#include "UI/CoreHUD.h"
//#include "Player/CorePlayerState.h"

ACoreGameMode::ACoreGameMode(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
		//HUDClass  = ACoreHUD::StaticClass();
    	//PlayerStateClass = ACorePlayerState::StaticClass();
}

void ACoreGameMode::BeginPlay()
{
	Super::BeginPlay();

	//LoadMasterSkeleton();
	// Get the Skeletal Mesh folder path
	//FString SkeletalMeshFolder = TEXT("/Game/Path/To/Your/SkeletalMeshFolder");
	
}

void ACoreGameMode::LoadMasterSkeleton()
{
	// /CorePlayer/Character/Mannequins/Meshes/SK_MasterUE5.SK_MasterUE5
	// /CorePlayer/MasterCharacter/MasterSkeleton/UE4/SK_MasterUE4.SK_MasterUE4
	// /CorePlayer/MasterCharacter/MasterSkeleton/UE5/SK_MasterUE5.SK_MasterUE5
	// /CorePlayer/Character/Mannequins/Meshes/SKM_Manny.SKM_Manny
	// /CorePlayer/MasterCharacter/Animations/UE5
	// /CorePlayer/MasterCharacter/Animations/UE4
	// /CorePlayer/MasterCharacter/SkeletonMeshes/UE5
	// /CorePlayer/MasterCharacter/SkeletalMeshes/UE4
	// /CorePlayer/MasterCharacter/SkeletonMeshes/UE5/Mannequin/SKM_Manny.SKM_Manny
	// /CorePlayer/MasterCharacter/SkeletonMeshes/UE4/Mannequin/SK_Mannequin.SK_Mannequin
	
	FString MasterSkeletonPath_UE5 = FString::Printf(TEXT("/CorePlayer/MasterCharacter/MasterSkeleton/UE5/SK_MasterUE5.SK_MasterUE5"));
	FString MasterSkeletonPath_UE4 = FString::Printf(TEXT("/CorePlayer/MasterCharacter/MasterSkeleton/UE4/SK_MasterUE4.SK_MasterUE4"));
	
	MasterSkeleton_UE5 = Cast<USkeleton>(StaticLoadObject(USkeleton::StaticClass(), nullptr, *MasterSkeletonPath_UE5));
	MasterSkeleton_UE4 = Cast<USkeleton>(StaticLoadObject(USkeleton::StaticClass(), nullptr, *MasterSkeletonPath_UE4));

	FString MannyRefPath_UE5 = FString::Printf(TEXT("/CorePlayer/MasterCharacter/SkeletonMeshes/UE5/Mannequin/SKM_Manny.SKM_Manny"));
	FString MannyRefPath_UE4 = FString::Printf(TEXT("/CorePlayer/MasterCharacter/SkeletonMeshes/UE4/Mannequin/SK_Mannequin.SK_Mannequin"));

	MannyRef_UE5 = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, *MannyRefPath_UE5));
	MannyRef_UE4 = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, *MannyRefPath_UE4));

	if(MasterSkeleton_UE5)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT(" UE5 Master Skeletal found  "));
		}
		
		if(MannyRef_UE5)
		{
			if( MasterSkeleton_UE5->GetPreviewMesh() ==nullptr)
			{
				MasterSkeleton_UE5->SetPreviewMesh(MannyRef_UE5);
			}
			if(MannyRef_UE5 ->GetSkeleton() ==nullptr)
			{
				MannyRef_UE5->SetSkeleton(MasterSkeleton_UE5);
			}
			
			// Save changes to the asset
			//FAssetRegistryModule::AssetCreated(MannyRef_UE5);
			
			
		}

		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
        IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

		
		// Get the Skeletal Mesh folder path
		//FString SkeletalMeshFolder_UE5 = TEXT("/CorePlayer/MasterCharacter/SkeletalMeshes/UE5");
		//FString SkeletalMeshesFolder_UE5 = FString::Printf( TEXT("/CorePlayer/MasterCharacter/SkeletalMeshes/UE5"));
		FString SkeletalMeshesFolder_UE5 = FString::Printf( TEXT("C:/Projects/ProjectCore 5.2/Plugins/CorePlayer/Content/MasterCharacter/SkeletonMeshes"));
		SkeletalMeshArray_UE5 = ScanForSkeletalMesh(SkeletalMeshesFolder_UE5);
		if(!SkeletalMeshArray_UE5.IsEmpty())
		{
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT(" Skeletal Meshes array not empty  "));
			}
			
			for (USkeletalMesh*SKM : SkeletalMeshArray_UE5 )
			{
				if(GEngine)
				{
					FString Text = FString::Printf(TEXT("Skeletal Mesh Name : %s"),*SKM->GetName());
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, Text);
				}
				/*
				if(SKM->GetSkeleton()==nullptr)
				{
					SKM->SetSkeleton(MasterSkeleton_UE5);
				}*/
			}
		}
		/*
		FString AnimationFolder_UE5 = FString::Printf( TEXT("/CorePlayer/MasterCharacter/Animations/UE5"));
		AnimationSequencesArray_UE5 = ScanForAnimationSequences(AnimationFolder_UE5);
		if(!AnimationSequencesArray_UE5.IsEmpty())
		{
			for (UAnimSequence*AS: AnimationSequencesArray_UE5 )
			{
				if(AS->GetSkeleton()==nullptr)
				{
					AS->SetSkeleton(MasterSkeleton_UE5);
				}
			}
		}*/
	}
	/*
	if(MasterSkeleton_UE4)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT(" UE4 Master Skeletal found  "));
		}

		// Get the Skeletal Mesh folder path
		FString SkeletalMeshFolder_UE4 = FString::Printf( TEXT("/CorePlayer/MasterCharacter/Animations/UE4"));
		SkeletalMeshArray_UE4 = ScanForSkeletalMesh(SkeletalMeshFolder_UE4);
		if(!SkeletalMeshArray_UE4.IsEmpty())
		{
			for (USkeletalMesh*SKM : SkeletalMeshArray_UE4 )
			{
				if(SKM->GetSkeleton()==nullptr)
				{
					SKM->SetSkeleton(MasterSkeleton_UE4);
				}
			}
		}
		FString AnimationFolder_UE4 = FString::Printf( TEXT("/CorePlayer/MasterCharacter/Animations/UE4"));
		AnimationSequencesArray_UE4 = ScanForAnimationSequences(AnimationFolder_UE4);
		if(!AnimationSequencesArray_UE4.IsEmpty())
		{
			for (UAnimSequence*AS: AnimationSequencesArray_UE4 )
			{
				if(AS->GetSkeleton()==nullptr)
				{
					AS->SetSkeleton(MasterSkeleton_UE4);
				}
			}
		}
	}*/
	
}

void ACoreGameMode::AssignMasterSkeletalToSkeletalMesh(USkeletalMesh* InSkeletalMesh)
{
	InSkeletalMesh->SetSkeleton(MasterSkeleton_UE5);
	InSkeletalMesh->PostEditChange();
	InSkeletalMesh->Build();
}

TArray<USkeletalMesh*> ACoreGameMode::ScanForSkeletalMesh(FString FolderLocation)
{
	// Create an instance of IFileManager
	IFileManager& FileManager = IFileManager::Get();

	// Find all files in the Skeletal Mesh folder
	TArray<FString>FolderContents;
	TArray<USkeletalMesh*>SKMContainer;
	
	//TCHAR* FileExtension = TEXT("uasset");
	TCHAR* Filter = TEXT("*.uasset");
	
	//FileManager.FindFiles(FolderContents, *FolderLocation, Filter);
	FileManager.FindFilesRecursive(FolderContents,*FolderLocation,Filter,true,true);

	// Iterate over the found files
	for (const FString& FilePath : FolderContents)
	{
		// Load the Skeletal Mesh asset
		USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, *FilePath));
		SKMContainer.Add(SkeletalMesh);
	}
	return SKMContainer;
	
}

TArray<UAnimSequence*> ACoreGameMode::ScanForAnimationSequences(FString FolderLocation)
{
	// Create an instance of IFileManager
	IFileManager& FileManager = IFileManager::Get();

	// Find all files in the Skeletal Mesh folder
	TArray<FString> SkeletalMeshFiles;
	TArray<UAnimSequence*>ASContainer;
	TCHAR* FileExtension = TEXT("uasset"); 
	FileManager.FindFiles(SkeletalMeshFiles, *FolderLocation, FileExtension);

	// Iterate over the found files
	for (const FString& FilePath : SkeletalMeshFiles)
	{
		// Load the Skeletal Mesh asset
		UAnimSequence* AnimSequence = Cast<UAnimSequence>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, *FilePath));
		ASContainer.Add(AnimSequence);
	}
	return ASContainer;
}

