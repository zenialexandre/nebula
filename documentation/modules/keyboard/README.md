# nebula.keyboard

| Functions | Description |
|------|-------------|
|[nebula.keyboard.isKeyPressed](#nebulakeyboardiskeypressed)| Gets if a key is pressed.
|[nebula.keyboard.isKeyReleased](#nebulakeyboardiskeyreleased)| Gets if a key is released.
|[nebula.keyboard._resetKeysReleased](#nebulakeyboard_resetkeysreleased)|  **Mainly for internal uses**. Resets keys released list.

---

## Functions

### nebula.keyboard.isKeyPressed
Gets if a key is pressed.
```lua
nebula.keyboard.isKeyPressed( key )
```
#### Arguments:
**[string** key **]** Key.

#### Returns:
**[ bool ]** True if the key is being pressed.

#### Example:
```lua
if nebula.keyboard.isKeyPressed("lctrl") then
    -- handles the Left Control key pressed
    if nebula.keyboard.isKeyPressed("w") then
        -- handles the Left Control + W keys pressed
    end
end
```

---

### nebula.keyboard.isKeyReleased
Gets if a key is released.
```lua
nebula.keyboard.isKeyReleased( key )
```
#### Arguments:
**[string** key **]** Key.

#### Returns:
**[ bool ]** True if the key is released.

#### Example:
```lua
if nebula.keyboard.isKeyReleased("lctrl") then
    -- handles the Left Control key released
    if nebula.keyboard.isKeyReleased("w") then
        -- handles the Left Control + W keys released
    end
end
```

---

### nebula.keyboard._resetKeysReleased
**Should be avoided**, nebula already resets the keys released list internally.
```lua
nebula.keyboard._resetKeysReleased()
```
#### Arguments:
None.
#### Returns:
Nothing.

#### Example:
```lua
nebula.keyboard._resetKeysReleased()
```

---