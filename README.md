# ue4-pixelperfect2d-sample

![UE5](https://img.shields.io/badge/UE5-5.2+-blue)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/Nauja/ue4-pixelperfect2d-sample/master/LICENSE)

Sample of coding a pixel perfect 2D game in Unreal Engine 5 with Paper2D.

![Preview](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media4.25/preview.gif)

The sole purpose of this sample is to compile all the config required, and common
pitfalls to avoid, to correctly render pixel perfect sprites with Paper2D.

For an Unreal Engine 4 version, check the branch [ue4.25](https://github.com/Nauja/ue4-pixelperfect2d-sample/tree/ue4.25).

Go further:

  * [Climb System 2D Sample](https://github.com/Nauja/ue4-climb2d-sample)
  * [Interactable Chest 2D Sample](https://github.com/Nauja/ue4-chest2d-sample)

## Table of contents:

- [Importing textures](#importing-textures)
- [Scaling up sprites](#scaling-up-sprites)
- [True sprite colors](#true-sprite-colors)
- [Pixelated font](#pixelated-font)
- [Snap pixels to grid](#snap-pixels-to-grid)
- [Orthographic camera](#orthographic-camera)

## Importing textures

When importing new textures, check that the **Texture Group** option is correctly set to
**2D Pixels (unfiltered)**, and that the **Compression Settings** is set to **UserInterface2D (RGBA)**. This will prevent the textures from being antialiased:

![TextureGroup](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media5.2/editor-texturegroup.png)

Also, expand the **Advanced** section, and set the **Filter** option to **Nearest**:

![SpriteNearest](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media5.2/editor-sprite-nearest.png)

## Scaling up sprites

Here is the charset used for Mario:

![Mario](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/Content/Textures/T_Mario.png)

As you can see, the size of one frame is really small (16x32 pixels). If it were displayed as is
in UE5, then all your physics would have to be configured with unrealistic values and placing or moving
Actors in the editor would become complicated due to their small size.

In order to keep consistent units between the physics and the rendering, all sprites are configured with a **pixels per unit** value of **0.5**, which effectively make them scaled by two:

![PixelsPerUnit](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media5.2/editor-pixelsperunit.png)

This is how the level looks up in editor with this configuration. You can see it is neither too small nor too big:

![LevelEditor](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media5.2/editor-preview.png)

## True sprite colors

One common problem is that rendered colors are altered by UE5's post processing effects.
By default, many post processing effects are enabled and are causing sprites
not to render correctly. In this sample, all post processing effects are disabled
by setting **EngineShowFlags.PostProcessing** to **0** with a custom **UGameViewportClient**
class:

```cpp
void USampleGameViewportClient::Activated(FViewport* InViewport, const FWindowActivateEvent& InActivateEvent)
{
    Super::Activated(InViewport, InActivateEvent);
    
    // Disable post processing effects when the viewport is activated
    EngineShowFlags.PostProcessing = 0;
}
```

The custom **UGameViewportClient** class can be configured in **Project Settings > Engine > General Settings**:

![GameViewportClient](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media5.2/editor-gameviewportclient.png)

Another possibility is to execute the following console command, however it turns out that it doesn't
work in shipping builds where console commands are disabled:

```cpp
APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
check(Controller);
Controller->ConsoleCommand(TEXT("showflag.postprocessing 0"));
```

Also, in **Project Settings > Engine > Rendering**, make sure to uncheck the **Mobile HDR** option and all post processing options such as **Bloom**, **Auto Exposure**, **Anti-Aliasing**, etc.

## Pixelated font

Importing a custom font to use in a TextRendererComponent seems complicated. This requires
the **Font Cache Type** parameter of your font to be set to **Offline**. Next, make
sure to uncheck the **Use Distance Field Alpha** option to prevent the font from becoming blurry:

![UseDistanceField](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media5.2/editor-usedistancefield.png)

Also make sure to uncheck **Enable Antialiasing** to prevent any antialiasing:

![Nearest](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media5.2/editor-nearest.png)

The last step is to create a new material to render the font. This can be done by copying the default material
used by any TextRendererComponent and modifying it:

![Nearest](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media5.2/editor-fontmaterial.png)

## Snap pixels to grid

In retro games, all sprites were snapped to a pixel grid, ensuring each pixel fitted in the grid and was correctly rendered.
In modern games, your Actors may be at positions containing float values, causing pixels to fall off the grid and render
incorrectly. Here is an example of moving the same sprite without pixel snapping (left) and with pixel snapping (right):

![PixelSnap](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media4.25/editor-pixelsnap.gif)

To do that, you can copy the default material used for sprites and modify it to offset vertex positions to make
sure they fall correctly on the grid:

![PixelSnapMaterial](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media5.2/editor-pixelsnapmaterial.png)

You can do the same for the font material, but by replacing the **PixelsPerUnit** parameter by **1**.

## Orthographic camera

This sample uses a static orthographic camera positioned at the center of the screen. The expected resolution of our viewport is
**512x448** pixels, the double of the SNES screen resolution, that's why the **OrthoWidth** parameter must be set to **512** pixels and
the **Aspect Ratio** parameter to **8/7**:

![Camera](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/media5.2/editor-camera.png)

## Revisions

### 2023/11/14:

* Added a step to set the **Filter** option to **Nearest** on sprites. Without that, the game build was all blurry despite
  the game being crisp in PIE.
* Replaced **ConsoleCommand** by creating a custom **UGameViewportClient** class to disable the flag as console commands
  are disabled in shipping builds.

## Credits

Sprites are coming from [The Spriters Resource](https://www.spriters-resource.com/).

Font from [FontSpace](https://www.fontspace.com/atlantis-international-font-f31357).

Pixel snap trick [Ludicrous Games](https://weareludicrous.com/blog/2018/3-tricks-to-improve-pixel-art-rendering-in-ue4/)

## License

Licensed under the [MIT](LICENSE) License.
