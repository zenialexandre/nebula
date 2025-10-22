# nebula.graphics

| Functions | Description |
|------|-------------|
|[nebula.graphics.draw](#nebulagraphicsdraw)| Draws an entity.
|[nebula.graphics.newTexture](#nebulagraphicsnewtexture)| Creates a new Texture.
|[nebula.graphics.newFont](#nebulagraphicsnewfont)| Creates a new Font.
|[nebula.graphics.setBackground](#nebulagraphicssetbackground)| Sets the color of the background.
|[nebula.graphics.moveCamera](#nebulagraphicsmovecamera)| Moves the camera.
|[nebula.graphics.moveCameraTo](#nebulagraphicsmovecamerato)| Moves the camera to a point.
|[nebula.graphics.pointCameraTo](#nebulagraphicspointcamerato)| Points the center of the camera to a point.
|[nebula.graphics._beginScene](#nebulagraphics_beginscene)| **Mainly for internal uses**. Starts the rendering process.
|[nebula.graphics._endScene](#nebulagraphics_endscene)| **Mainly for internal uses**. Ends the rendering process.

| Types |
|------|
| [Texture](#texture)
| [Font](#font)

---

## Functions

### nebula.graphics.draw
Draws an entity.
```lua
nebula.graphics.draw( entity )
```
#### Arguments:
**[ number** entity **]** Entity ID.

#### Returns:
Nothing.

#### Example:
```lua
nebula.graphics.draw(entity)
```

---

### nebula.graphics.newTexture
Creates a new Texture.
```lua
nebula.graphics.newTexture( texturePath )
```
#### Arguments:
**[ string** texturePath **]** Path to texture.

#### Returns:
**[ Texture ]** Texture.

#### Example:
```lua
local myTexture = nebula.graphics.newTexture("resources/sprites/MySprite.png")
```

---

### nebula.graphics.newFont
Creates a new Font
```lua
nebula.graphics.newFont( fontPath, fontSize )
```
#### Arguments:
**[ string** fontPath **]** Path to font,  
**[ number** fontSize **]** Size of the font.

#### Returns:
**[ Font ]** Font.

#### Example:
```lua
local myFont = nebula.graphics.newFont("resources/sprites/MyFont.ttf")
```

---

### nebula.graphics.setBackground
Sets the color of the background.
```lua
nebula.graphics.setBackground( r, g, b )
```
#### Arguments:
**[ number** r **]** Red value,  
**[ number** g **]** Green value,  
**[ number** b **]** Blue value.

**Notes:** r/g/b should have values between 0 and 1.

#### Returns:
Nothing.

#### Example:
```lua
nebula.graphics.setBackground(1.0, 1.0, 1.0)
```

---

### nebula.graphics.moveCamera
Moves the camera in x pixels on x axis, and y pixels on y axis.
```lua
nebula.graphics.moveCamera( x, y )
```
#### Arguments:
**[ number** x **]** Value on x axis,  
**[ number** y **]** Value on y axis.

#### Returns:
Nothing.

#### Example:
```lua
nebula.graphics.moveCamera(3.0, 3.0)
```

---

### nebula.graphics.moveCameraTo
Moves the camera to a point (x, y).
```lua
nebula.graphics.moveCameraTo( x, y )
```
#### Arguments:
**[ number** x **]** Coordinate on x axis,  
**[ number** y **]** Coordinate on y axis.

#### Returns:
Nothing.

#### Example:
```lua
nebula.graphics.moveCameraTo(100.0, 80.0)
```

---

### nebula.graphics.pointCameraTo
Moves the center of the camera to a point (x, y).
```lua
nebula.graphics.pointCameraTo( x, y )
```
#### Arguments:
**[ number** x **]** Coordinate on x axis,  
**[ number** y **]** Coordinate on y axis.

#### Returns:
Nothing.

#### Example:
```lua
nebula.graphics.pointCameraTo(100.0, 80.0)
```

---

### nebula.graphics._beginScene
Starts the rendering process. **Should be avoided**, nebula already manages rendering internally.
```lua
nebula.graphics._beginScene()
```
#### Arguments:
None.

#### Returns:
Nothing.

#### Example:
```lua
nebula.graphics._beginScene()
```

---

### nebula.graphics._endScene
Ends the rendering process. **Should be avoided**, nebula already manages rendering internally.
```lua
nebula.graphics._endScene()
```
#### Arguments:
None.

#### Returns:
Nothing.

#### Example:
```lua
nebula.graphics._endScene()
```

---

## Types

### Texture
#### Fields:
**[ number ]** width: Texture's width,  
**[ number ]** height: Texture's height.
#### Example:
```Lua
local myTexture = nebula.graphics.newTexture("resources/sprites/MySprite.png")
print(myTexture.width, myTexture.height)
```

---

### Font
#### Fields:
**[ number ]** lineHeight: Font's line height.
#### Example:
```Lua
local myFont = nebula.graphics.newFont("resources/sprites/MyFont.ttf")
print(myFont.lineHeight)
```