// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "SampleGameViewportClient.generated.h"

/**
 * Custom viewport used to override the EngineShowFlags.
 */
UCLASS(minimalapi)
class USampleGameViewportClient : public UGameViewportClient
{
    GENERATED_BODY()
public:
    void Activated(FViewport* InViewport, const FWindowActivateEvent& InActivateEvent) override;
};
