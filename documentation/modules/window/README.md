# nebula.window

| Functions                                                 | Description                                     |
| --------------------------------------------------------- | ----------------------------------------------- |
| [nebula.window.getSize](#nebulawindowgetsize)             | Gets the current window size.                   |
| [nebula.window.setSize](#nebulawindowsetsize)             | Sets the window width and height.               |
| [nebula.window.setTitle](#nebulawindowsettitle)           | Sets the window title.                          |
| [nebula.window.setIcon](#nebulawindowseticon)             | Sets the window icon using an image file.       |
| [nebula.window.setFullscreen](#nebulawindowsetfullscreen) | Enables or disables fullscreen mode.            |
| [nebula.window.setResizable](#nebulawindowsetresizable)   | Enables or disables window resizing.            |
| [nebula.window.setBorderless](#nebulawindowsetborderless) | Toggles borderless window mode.                 |
| [nebula.window.setVsync](#nebulawindowsetvsync)           | Sets vertical synchronization (vsync) mode.     |
| [nebula.window.swapBuffers](#nebulawindowswapbuffers)     | Swaps the front and back buffers for rendering. |

---

## Functions

### nebula.window.getSize

Gets the current window size.

```lua
nebula.window.getSize()
```

#### Arguments:

None.

#### Returns:

**[ number ]** The width of the window.  
**[ number ]** The height of the window.

#### Example:

```lua
local w, h = nebula.window.getSize()
print("Window size:", w, "x", h)
```

---

### nebula.window.setSize

Sets the window width and height.

```lua
nebula.window.setSize( width, height )
```

#### Arguments:

**[ number** width **]** Window width in pixels.  
**[ number** height **]** Window height in pixels.

#### Returns:

Nothing.

#### Example:

```lua
nebula.window.setSize(1280, 720)
```

---

### nebula.window.setTitle

Sets the window title.

```lua
nebula.window.setTitle( title )
```

#### Arguments:

**[ string** title **]** The text to display as the window title.

#### Returns:

Nothing.

#### Example:

```lua
nebula.window.setTitle("Nebula Engine - Demo")
```

---

### nebula.window.setIcon

Sets the window icon using an image file.

```lua
nebula.window.setIcon( filePath )
```

#### Arguments:

**[ string** filePath **]** Path to the image file used as the window icon.

#### Returns:

Nothing.

#### Example:

```lua
nebula.window.setIcon("resources/icons/app_icon.png")
```

---

### nebula.window.setFullscreen

Enables or disables fullscreen mode.

```lua
nebula.window.setFullscreen( fullscreen, desktopMode )
```

#### Arguments:

**[ boolean** fullscreen **]** Whether to enable fullscreen.  
**[ boolean** desktopMode **]** *(optional)* Whether to use borderless “desktop” fullscreen mode.

#### Returns:

Nothing.

#### Example:

```lua
-- Enable exclusive fullscreen
nebula.window.setFullscreen(true)

-- Enable borderless desktop fullscreen
nebula.window.setFullscreen(true, true)
```

---

### nebula.window.setResizable

Enables or disables window resizing.

```lua
nebula.window.setResizable( resizable )
```

#### Arguments:

**[ boolean** resizable **]** Whether the window can be resized.

#### Returns:

Nothing.

#### Example:

```lua
nebula.window.setResizable(true)
```

---

### nebula.window.setBorderless

Toggles borderless window mode.

```lua
nebula.window.setBorderless( borderless )
```

#### Arguments:

**[ boolean** borderless **]** Whether to hide the window borders and title bar.

#### Returns:

Nothing.

#### Example:

```lua
nebula.window.setBorderless(true)
```

---

### nebula.window.setVsync

Sets vertical synchronization (vsync) mode.

```lua
nebula.window.setVsync( mode )
```

#### Arguments:

**[ number** mode **]** The vsync mode:

* `-1` = Adaptive vsync.
* `0` = Immediate updates.
* `1` = Updates synchronized with the vertical retrace.

#### Returns:

Nothing.

#### Example:

```lua
nebula.window.setVsync(1)
```

---

### nebula.window.swapBuffers

Swaps the front and back buffers for rendering.

```lua
nebula.window.swapBuffers()
```

#### Arguments:

None.

#### Returns:

Nothing.

#### Example:

```lua
-- Typically called once per frame after rendering
nebula.window.swapBuffers()
```

---