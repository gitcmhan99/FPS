// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameModeBase.h"
#include "FPSPlayerControllerBase.h"
#include "FPSPawnBase.h"
#include "FPS/FPS.h"

AFPSGameModeBase::AFPSGameModeBase()
{
    MYLOG("Start AFPSGameModeBase()");

    //TSubclassOf<APlayerController>
    PlayerControllerClass = AFPSPlayerControllerBase::StaticClass();
    //TSubclassOf<APawn>
    DefaultPawnClass = AFPSPawnBase::StaticClass();

    MYLOG("End AFPSGameModeBase()");
}

void AFPSGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    MYLOG("Start InitGame MapName: %s, Options: %s", *MapName, *Options);

    Super::InitGame(MapName, Options, ErrorMessage);

    MYLOG("End InitGame");
}

void AFPSGameModeBase::InitGameState()
{
    MYLOG("Start InitGameState()");

    Super::InitGameState();

    MYLOG("End InitGameState()");
}

void AFPSGameModeBase::PreInitializeComponents()
{
    Super::PreInitializeComponents();
}

void AFPSGameModeBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}



void AFPSGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

APlayerController* AFPSGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    APlayerController* PlayerController = Super::Login(
        NewPlayer,
        InRemoteRole,
        Portal,
        Options,
        UniqueId,
        ErrorMessage
    );

    return PlayerController;
}

void AFPSGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
}
