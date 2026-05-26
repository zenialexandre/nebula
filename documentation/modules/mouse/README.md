# nebula.mouse

| Functions | Description |
|------|-------------|
|[nebula.mouse.getX](#nebulamousegetx)| Gets mouse X position.
|[nebula.mouse.getY](#nebulamousegety)| Gets mouse Y position.
|[nebula.mouse.getPosition](#nebulamousegetposition)| Gets mouse X and Y position.
|[nebula.mouse.setX](#nebulamousesetx)| Sets mouse X position.
|[nebula.mouse.setY](#nebulamousesety)| Sets mouse Y position.
|[nebula.mouse.setPosition](#nebulamousesetposition)| Sets mouse X and Y position.
|[nebula.mouse.isPressed](#nebulamouseispressed)| Checks if a mouse button is pressed.
|[nebula.mouse.isReleased](#nebulamouseisreleased)| Checks if a mouse button is released.
|[nebula.mouse.isGrabbed](#nebulamouseisgrabbed)| Checks if mouse is grabbed.
|[nebula.mouse.setGrabbed](#nebulamousesetgrabbed)| Sets if mouse is grabbed.

---

## Functions

### nebula.mouse.getX
Gets mouse X position.
```lua
nebula.mouse.getX()
```
#### Arguments:
None.

#### Returns:
**[ number ]** Mouse X position.

#### Example:
```lua
mX = nebula.mouse.getX()
```

---

### nebula.mouse.getY
Gets mouse Y position.
```lua
nebula.mouse.getY()
```
#### Arguments:
None.

#### Returns:
**[ number ]** Mouse Y position.

#### Example:
```lua
mY = nebula.mouse.getY()
```

---

### nebula.mouse.getPosition
Gets mouse X and Y position.
```lua
nebula.mouse.getPosition()
```
#### Arguments:
None.

#### Returns:
**[ number ]** Mouse X position,  
**[ number ]** Mouse Y position.

#### Example:
```lua
mX, mY = nebula.mouse.getPosition()
```

---

### nebula.mouse.setX
Sets mouse X position.
```lua
nebula.mouse.setX( mX )
```
#### Arguments:
**[ number** mX **]** Mouse X position.

#### Returns:
Nothing.

#### Example:
```lua
nebula.mouse.setX(200)
```

---

### nebula.mouse.setY
Sets mouse Y position.
```lua
nebula.mouse.setY( mY )
```
#### Arguments:
**[ number** mY **]** Mouse Y position.

#### Returns:
Nothing.

#### Example:
```lua
nebula.mouse.setY(200)
```

---

### nebula.mouse.setPosition
Sets mouse X and Y position.
```lua
nebula.mouse.setPosition( mX, mY )
```
#### Arguments:
**[ number** mX **]** Mouse X position,  
**[ number** mY **]** Mouse Y position.

#### Returns:
Nothing.

#### Example:
```lua
nebula.mouse.setPosition(200, 200)
```

---

### nebula.mouse.isPressed
Checks if a mouse button is pressed.
```lua
nebula.mouse.isPressed( button )
```
#### Arguments:
**[ string** button **]** Button name: `"left"`, `"lmb"`, `"middle"`, `"mmb"`, `"right"`, `"rmb"`, `"x1"`, `"x2"`.

#### Returns:
**[ bool ]** True if button is pressed.

#### Example:
```lua
if nebula.mouse.isPressed("lmb") then
    -- handle left click
end
```

---

### nebula.mouse.isReleased
Checks if a mouse button is released.
```lua
nebula.mouse.isReleased( button )
```
#### Arguments:
**[ string** button **]** Button name: `"left"`, `"lmb"`, `"middle"`, `"mmb"`, `"right"`, `"rmb"`, `"x1"`, `"x2"`.

#### Returns:
**[ bool ]** True if button is released.

#### Example:
```lua
if nebula.mouse.isReleased("lmb") then
    -- handle left click
end
```

---

### nebula.mouse.isGrabbed
Checks if mouse is grabbed.
```lua
nebula.mouse.isGrabbed()
```
#### Arguments:
None.

#### Returns:
**[ bool ]** True if mouse is grabbed.

#### Example:
```lua
if nebula.mouse.isGrabbed() then
    -- handle grab
end
```

---

### nebula.mouse.setGrabbed
Sets mouse grabbed.
```lua
nebula.mouse.setGrabbed( grabbed )
```
#### Arguments:
**[ bool** grabbed **]** 

#### Returns:
Nothing.

#### Example:
```lua
nebula.mouse.setGrabbed(true)
```

---
