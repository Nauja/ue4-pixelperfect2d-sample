// Copyright Epic Games, Inc. All Rights Reserved.

#include "SampleGameViewportClient.h"

void USampleGameViewportClient::Activated(FViewport* InViewport, const FWindowActivateEvent& InActivateEvent)
{
	Super::Activated(InViewport, InActivateEvent);

	// Disable post processing effects when the viewport is activated
	EngineShowFlags.PostProcessing = 0;
}
