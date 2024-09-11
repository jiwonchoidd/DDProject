// Fill out your copyright notice in the Description page of Project Settings.


#include "DDSpawnPoint.h"

#include "DDUnitBase.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "DDFundamental/Manangers/DDUnitManager.h"


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
#endif // WITH_EDITORONLY_DATA
}

void ADDSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	FDDSpawnCommand SC;
	SC.Pos = GetActorLocation();
	SC.Rot = GetActorRotation();
	SC.AssetPath = TEXT("/Script/Engine.Blueprint'/Game/Unit/BP_CharBase.BP_CharBase'");
	
	if(const UDDUnitBase* UnitBase = gUnitMng.CreateUnit(UDDUnitBase::StaticClass(), SC))
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Log, TEXT("Spawn Point : %d"), UnitBase->GetUnitHandle());
#endif
	}
}

void ADDSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

