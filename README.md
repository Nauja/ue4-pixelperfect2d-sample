# ue4-pixelperfect2d-sample

![UE4](https://img.shields.io/badge/UE4-4.25+-blue)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/Nauja/ue4-jetpack-sample/master/LICENSE)

Sample of coding a pixel perfect 2D game with Paper2D.

![Preview](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/docs/preview.gif)

The sole purpose of this sample is to compile all the config required, and common
pitfalls to avoid, to correctly render pixel perfect sprites with Paper2D.

Features:
  * Importing textures
  * Scaling up sprites
  * True sprite colors
  * Pixelated font
  * Orthographic camera

### Importing textures

The only thing you need to check when importing new textures is that the **Texture Group** option is correctly set to
**2D Pixels (unfiltered)**. This will prevent the textures from being antialiased:

![LevelEditor](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/docs/editor-texturegroup.png)

### Scaling up sprites

Here is the charset used for Mario:

![Mario](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/Content/Textures/T_Mario.png)

As you can see, the size of one frame is really small (16x32 pixels). If it were displayed as is
in UE4, then all your physics would have to be configured with unrealistic values and placing or moving
Actors in the editor would become complicated due to their small size.

In order to keep consistent units between the physics and the rendering, all sprites are configured with a **pixels per unit** value of **0.5**, which effectively make them scaled by two:

![PixelsPerUnit](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/docs/editor-pixelsperunit.png)

This is how the level looks up in editor with this configuration. You can see it is neither too small nor too big:

![LevelEditor](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/docs/editor-preview.png)

### True sprite colors

One common problem is that rendered colors are altered by UE4's post processing effects.
By default, many post processing effects are enabled and are causing sprites
not to render correctly. In this sample, all post processing effects are disabled
with this single command:

```cpp
APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
check(Controller);
Controller->ConsoleCommand(TEXT("showflag.postprocessing 0"));
```

Also, in **Project Settings > Engine > Rendering**, make sure to uncheck the **Mobile HDR** option and all post processing options such as **Bloom**, **Auto Exposure**, **Anti-Aliasing**, etc.

### Pixelated font

Importing a custom font to use in a TextRendererComponent seems complicated. This requires
the **Font Cache Type** parameter of your font to be set to **Offline**. Next, make
sure to uncheck the **Use Distance Field Alpha** option to prevent the font from becoming blurry:

![UseDistanceField](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/docs/editor-usedistancefield.png)

Also make sure to set the **Filter** as **Nearest** to prevent any antialiasing:

![Nearest](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/docs/editor-nearest.png)

The last step is to create a new material to render the font. This can be done by copying the default material
used by any TextRendererComponent and modifying it:

![Nearest](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/docs/editor-fontmaterial.png)

### Orthographic camera

This sample uses a static orthographic camera positioned at the center of the screen. The expected resolution of our viewport is
**512x448** pixels, the double of the SNES screen resolution, that's why the **OrthoWidth** parameter must be set to **512** pixels:

![Camera](https://github.com/Nauja/ue4-pixelperfect2d-sample/raw/master/docs/editor-camera.png)

### Credits

Sprites are coming from [The Spriters Resource](https://www.spriters-resource.com/).
Font from [FontSpace](https://www.fontspace.com/atlantis-international-font-f31357).
