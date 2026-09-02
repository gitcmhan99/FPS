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
    MYLOG("Start PreInitializeComponents()");

    Super::PreInitializeComponents();

    MYLOG("End PreInitializeComponents()");
}

void AFPSGameModeBase::PostInitializeComponents()
{
    MYLOG("Start AFPSGameModeBase PostInitializeComponents()");

    Super::PostInitializeComponents();

    MYLOG("End AFPSGameModeBase PostInitializeComponents()");
}

void AFPSGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    MYLOG("Start PreLogin() Options: %s, Address: %s, ErrorMessage: %s", *Options, *Address, *ErrorMessage);

    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

    MYLOG("End PreLogin() Options: %s, Address: %s, ErrorMessage: %s", *Options, *Address, *ErrorMessage);
}

APlayerController* AFPSGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    MYLOG("Start Login() NewPlayer: %s, InRemoteRole: %d, Portal: %s, Options: %s, ErrorMessage: %s", *NewPlayer->GetName(), InRemoteRole, *Portal, *Options, *ErrorMessage);

    APlayerController* PlayerController = Super::Login(
        NewPlayer,
        InRemoteRole,
        Portal,
        Options,
        UniqueId,
        ErrorMessage
    );

    MYLOG("End Login() NewPlayer: %s, InRemoteRole: %d, Portal: %s, Options: %s, ErrorMessage: %s", *NewPlayer->GetName(), InRemoteRole, *Portal, *Options, *ErrorMessage);

    return PlayerController;
}

void AFPSGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    MYLOG("Start PostLogin() NewPlayer: %s", *NewPlayer->GetName());

    Super::PostLogin(NewPlayer);

    MYLOG("End PostLogin() NewPlayer: %s", *NewPlayer->GetName());
}
