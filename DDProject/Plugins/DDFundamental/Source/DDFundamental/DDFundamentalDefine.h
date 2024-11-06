#pragma once
#include "CoreMinimal.h"

DDFUNDAMENTAL_API DECLARE_LOG_CATEGORY_EXTERN(DDLog, Log, All);
DDFUNDAMENTAL_API DECLARE_LOG_CATEGORY_EXTERN(DDWarning, Warning, All);
DDFUNDAMENTAL_API DECLARE_LOG_CATEGORY_EXTERN(DDError, Error, All);

#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define	DD_Log(InFormat, ...)	  UE_LOG(DDLog, Log, InFormat, ##__VA_ARGS__);
#define	DD_WARNING(InFormat, ...) UE_LOG(DDWarning, Warning, InFormat, ##__VA_ARGS__);
#define	DD_ERROR(InFormat, ...)   UE_LOG(DDError, Error, InFormat, ##__VA_ARGS__);

#define	DD_LOG_CALLINFO(InFormat, ...)	  UE_LOG(DDLog, Log, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(InFormat, ##__VA_ARGS__));
#define	DD_WARNING_CALLINFO(InFormat, ...) UE_LOG(DDWarning, Warning, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(InFormat, ##__VA_ARGS__));
#define	DD_ERROR_CALLINFO(InFormat, ...)   UE_LOG(DDError, Error, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(InFormat, ##__VA_ARGS__));

#define	DD_SCREEN(Format, ...)    if(GEngine) {GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *FString::Printf(Format, ##__VA_ARGS__));}

#define DD_CHECK(expr) check(expr);
#define DD_ENSURE(expr) ensure(expr);

#define	DD_New new
#define	DD_Delete delete

#define	DD_NewObject NewObject
#define	DD_DeleteObject(Object){					    \
DD_CHECK(Object != nullptr);				\
(Object->ConditionalBeginDestroy());		\
};
