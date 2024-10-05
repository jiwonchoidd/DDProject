#include "DDSoundManager.h"
#include "Components/AudioComponent.h"
#include "DDFundamental/Gameplay/DDFunctionLibrary.h"
#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "Kismet/GameplayStatics.h"

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

}

void UDDSoundManager::Finalize()
{
 
}

void UDDSoundManager::Tick(float _DeltaTime)
{
    
}

//-----------------------------------------------------------------------------------------------------------------------------

void UDDSoundManager::Push(const FString& _strSOP, float _Volume, float _StartTime, float _FadeInTime, float _FadeOutTime)
{
    if (!BgmStack.IsEmpty())
    {
        const FDDBgmStack& OldBgm = BgmStack.Last();
        Stop(OldBgm);
    }

    const FDDBgmStack NewBgm(_strSOP, _Volume, _StartTime, _FadeInTime, _FadeOutTime);
    Play(NewBgm);
    BgmStack.Add(NewBgm);
}

void UDDSoundManager::Pop()
{
    if (!BgmStack.IsEmpty())
    {
        Stop(BgmStack.Pop());
    }

    if (!BgmStack.IsEmpty())
    {
        const FDDBgmStack& LastBgm = BgmStack.Last();
        Play(LastBgm);
    }
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
    USoundBase* Sound = Cast<USoundBase>(UDDFunctionLibrary::SyncLoadAsset(_Info.Path));
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
    }
    else
    {
        CurPlayingComponent->Stop();
    }
}

void UDDSoundManager::OnAudioFinishedPlaying()
{
    
}

#if WITH_EDITOR
void UDDSoundManager::Print()
{
    FString Context = TEXT("");
    for (const auto& Bgm : BgmStack)
    {
        //Bgm.GetPath();
    }
}
#endif
