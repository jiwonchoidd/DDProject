#include "DDSoundManager.h"
#include "Components/AudioComponent.h"
#include "DDFundamental/DDFundamentalDefine.h"
#include "DDFundamental/Gameplay/DDFunctionLibrary.h"
#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "Kismet/GameplayStatics.h"

namespace SoundMng
{
    constexpr float DefaultDelayTime = 0.1f;
    constexpr float DefaultDelayCorrection = 1.5f;
}

FDDBgmStack::FDDBgmStack(const FString& _strSOP, float _Volume, float _StartTime, float _FadeInTime, float _FadeOutTime)
{
    Path = _strSOP;
    Volume = _Volume;
    StartTime = _StartTime;
    FadeInTime = _FadeInTime;
    FadeOutTime = _FadeOutTime;
}

void UDDSoundManager::Initialize()
{
    BgmStack.Reset();
    CurPlayingComponent.Reset();
}

void UDDSoundManager::Finalize()
{
    BgmStack.Reset();
    CurPlayingComponent.Reset();
    
    UWorld* pWorld = GDDInstance->GetWorld();
    if (!pWorld)
        return;
    
    if (StartBgmTimerHandle.IsValid())
    {
        pWorld->GetTimerManager().ClearTimer(StartBgmTimerHandle);
    }
}

void UDDSoundManager::Tick(float _DeltaTime)
{
    
}

//-----------------------------------------------------------------------------------------------------------------------------

void UDDSoundManager::Push(const FString& _strSOP, float _Volume, float _StartTime, float _FadeInTime, float _FadeOutTime)
{
    UWorld* pWorld = GDDInstance->GetWorld();
    if(!pWorld)
        return;

    float PlayDelayTime = SoundMng::DefaultDelayTime;
    if (!BgmStack.IsEmpty())
    {
        const FDDBgmStack& OldBgm = BgmStack.Last();
        PlayDelayTime = OldBgm.FadeOutTime * SoundMng::DefaultDelayCorrection;
        Stop(OldBgm);
    }

    const FDDBgmStack NewBgm(_strSOP, _Volume, _StartTime, _FadeInTime, _FadeOutTime);
    BgmStack.Add(NewBgm);

    // 한 틱에서 여러개가 저장될때 오브젝트 생성을 굳이 여러개 생성할 필요가없음 타이머로 개선 
    pWorld->GetTimerManager().SetTimer(StartBgmTimerHandle, FTimerDelegate::CreateWeakLambda(this, [&, _Bgm = NewBgm]()
    {
        if (!BgmStack.IsEmpty())
        {
            const FDDBgmStack& LastBgm = BgmStack.Last();
            Play(LastBgm);
        }
    }), PlayDelayTime, false);
#if WITH_EDITOR
    Print();
#endif
}

void UDDSoundManager::Pop()
{
    UWorld* pWorld = GDDInstance->GetWorld();
    if(!pWorld)
        return;

    float PlayDelayTime = SoundMng::DefaultDelayTime;
    if (!BgmStack.IsEmpty())
    {
        const FDDBgmStack& OldBgm = BgmStack.Pop();
        PlayDelayTime = OldBgm.FadeOutTime * SoundMng::DefaultDelayCorrection;
        Stop(OldBgm);
    }

    pWorld->GetTimerManager().SetTimer(StartBgmTimerHandle, FTimerDelegate::CreateWeakLambda(this, [&]()
    {
        if (!BgmStack.IsEmpty())
        {
            const FDDBgmStack& LastBgm = BgmStack.Last();
            Play(LastBgm);
        }
    }), PlayDelayTime, false);

#if WITH_EDITOR
    Print();
#endif
}

void UDDSoundManager::Clear()
{
    while (!BgmStack.IsEmpty())
    {
        Stop(BgmStack.Pop());
    }
}

//-----------------------------------------------------------------------------------------------------------------------------

void UDDSoundManager::Play(const FDDBgmStack& _Info)
{
    USoundWave* Sound = Cast<USoundWave>(UDDFunctionLibrary::SyncLoadAsset(_Info.Path));
    if(!IsValid(Sound))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load SoundWave from path: %s"), *_Info.Path);
        return;
    }

    UWorld* pWorld = GDDInstance->GetWorld();
    if(!IsValid(pWorld))
        return;
    
    UAudioComponent* AudioComp = UGameplayStatics::CreateSound2D(pWorld, Sound, _Info.Volume, 1.0f, _Info.StartTime);
    if (!AudioComp)
        return;

    AudioComp->Play();
    if(_Info.FadeInTime > 0.0f)
    {
        AudioComp->FadeIn(_Info.FadeInTime, _Info.Volume, _Info.StartTime);
    }
    CurPlayingComponent = AudioComp;
}

void UDDSoundManager::Stop(const FDDBgmStack& _Info)
{
    UWorld* pWorld = GDDInstance->GetWorld();
    if(!IsValid(pWorld))
        return;

    if(!CurPlayingComponent.IsValid())
        return;

    CurPlayingComponent->bAutoDestroy = true;

    if(_Info.FadeOutTime > 0.f)
    {
        CurPlayingComponent->FadeOut(_Info.FadeOutTime, 0);
        FTimerHandle TimerHandle;
        pWorld->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateWeakLambda(this,[_Comp = CurPlayingComponent]()
        {
            if(_Comp.IsValid())
            {
                _Comp->Stop();
            }
        }), _Info.FadeOutTime, false);
        CurPlayingComponent.Reset();
    }
    else
    {
        CurPlayingComponent->Stop();
        CurPlayingComponent.Reset();
    }
}

void UDDSoundManager::OnAudioFinishedPlaying()
{
    Pop();
}

#if WITH_EDITOR
void UDDSoundManager::Print() const
{
    FString Context = TEXT("");
    DD_SCREEN(TEXT("BgmStack %i"), BgmStack.Num());
}
#endif
