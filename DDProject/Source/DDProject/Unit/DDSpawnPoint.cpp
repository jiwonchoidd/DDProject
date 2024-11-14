// Fill out your copyright notice in the Description page of Project Settings.


#include "DDSpawnPoint.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "DDFundamental/Manangers/DDTableManager.h"
#include "DDFundamental/Manangers/DDUnitManager.h"
#include "DDFundamental/Unit/DDBaseCharacter.h"
#include "DDProject/GamePlay/GameDefine.h"
#include "DDProject/Table/RowHeader/BPResource.h"


struct FBPResource;

ADDSpawnPoint::ADDSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	AddOwnedComponent(SceneRootComponent);
	SetRootComponent(SceneRootComponent);
	SceneRootComponent->SetMobility(EComponentMobility::Movable);

#if WITH_EDITORONLY_DATA
	struct FConstructorStatics
	{
		//Find UTexture2D object in the resource
		ConstructorHelpers::FObjectFinderOptional<UTexture2D> TextureFinder;

		FConstructorStatics()
			:TextureFinder(TEXT("Texture2D'/Game/NeverCook/kirbo.kirbo'"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	SpriteComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));
	if (SpriteComponent)
	{
		SpriteComponent->Sprite = ConstructorStatics.TextureFinder.Get();
		SpriteComponent->SetupAttachment(RootComponent);
		SpriteComponent->SetRelativeScale3D_Direct(FVector(0.5f, 0.5f, 0.5f));
		SpriteComponent->bHiddenInGame = true;
		SpriteComponent->bIsScreenSizeScaled = true;
		SpriteComponent->bReceivesDecals = false;
	}

	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent0"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(255, 0, 128);

		ArrowComponent->ArrowSize = 1.5f;
		ArrowComponent->bHiddenInGame = true;
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetupAttachment(RootComponent);
		ArrowComponent->SetUsingAbsoluteScale(true);
	}
#endif
}

void ADDSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

bool ADDSpawnPoint::SpawnUnit() const
{
	if(SpawnOption.UnitTableId == 0)
		return false;
	
	if(const FBPResource* pResource = gTableMng.GetRowData<FBPResource>(ETableType::BPResource, SpawnOption.UnitTableId))
	{
		FDDSpawnCommand Command;
		Command.Pos = GetActorLocation();
		Command.Rot = GetActorRotation();
		Command.BPPath = pResource->Blueprint.ToSoftObjectPath();
		
		DDHandle SpawnIndex = gUnitMng.CreateActor(Command);

		TWeakObjectPtr<ADDBaseCharacter> Actor = gUnitMng.GetUnitActor(SpawnIndex);
#if WITH_EDITOR
		UE_LOG(LogTemp, Log, TEXT("Spawn Point : %d"), SpawnIndex);
#endif

		return true;
	}
	return false;
}
