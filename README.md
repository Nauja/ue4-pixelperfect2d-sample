# ue4-pixelperfect2d-sample

![UE4](https://img.shields.io/badge/UE4-4.25+-blue)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/Nauja/ue4-jetpack-sample/master/LICENSE)

Sample of coding a pixel perfect 2D game with Paper2D.

![Preview](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/docs/preview.gif)

The sole purpose of this sample is to compile all the required config and common
pitfalls to avoid to correctly render pixel perfect sprites with Paper2D.

### Pixel perfect sprites

Here is the charset used for Mario:

![Mario](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/Content/Textures/T_Mario.png)

As you can see, the size of one frame is really small (16x32 pixels). If it were displayed as is
in UE4, then all your physics would have to be configured with unrealistic values and placing or moving
Actors in the editor would become complicated due to their small size.

So, the first important point is to configure our sprites with a **pixels per unit** value of **0.5**, which effectively make them scaled by two:

![PixelsPerUnit](https://github.com/Nauja/ue4-chest2d-sample/raw/master/docs/pixelperfect_sprite.png)

Finally, the **SideViewCameraComponent** is configured with an **OrthoWidth** of **1280** pixels in **ASampleCharacter.cpp**:

```cpp
SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
SideViewCameraComponent->OrthoWidth = 1280.0f;
SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
```

### True sprite colors

One common problem is that the colors of rendered sprites are altered by UE4's post processing effects.
By default, many post processing effects are enabled and are causing sprites
not to be rendered correctly. In this sample, all post processing effects are disabled
with this single command:

```cpp
APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
check(Controller);
Controller->ConsoleCommand(TEXT("showflag.postprocessing 0"));
```

Also, in **Project Settings > Engine > Rendering**, make sure to uncheck the **Mobile HDR** option and all post processing options such as **Bloom**, **Auto Exposure**, **Anti-Aliasing**, etc.

### Credits

Sprites are coming from [The Spriters Resource](https://www.spriters-resource.com/).
