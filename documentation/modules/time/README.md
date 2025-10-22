# nebula.time

| Functions | Description |
|------|-------------|
|[nebula.time.now](#nebulatimenow)| Gets the current time.
|[nebula.time.getFPS](#nebulatimegetfps)| Gets the Frames per Second ratio.
|[nebula.time.getDeltaTime](#nebulatimegetdeltatime)| Gets Delta Time.
|[nebula.time.tick](#nebulatimetick)| **Mainly for internal uses**. "Ticks" the Time Module.

---

## Functions

### nebula.time.now
Gets the current time in milliseconds.
```lua
nebula.time.now()
```
#### Arguments:
None.

#### Returns:
**[ number ]** Current time in milliseconds.

#### Example:
```lua
time = nebula.time.now()
```

---

### nebula.time.getFPS
Gets the Frames per Second ratio.
```lua
nebula.time.getFPS()
```
#### Arguments:
None.

#### Returns:
**[ number ]** Frames per Second Ratio.

#### Example:
```lua
fps = nebula.time.getFPS()
```

---

### nebula.time.getDeltaTime
Gets Delta Time (time between frames).
```lua
nebula.time.getDeltaTime()
```
#### Arguments:
None.

#### Returns:
**[ number ]** Delta Time.

#### Example:
```lua
dt = nebula.time.getDeltaTime()
```

---

### nebula.time.tick
**Should be avoided**, nebula already manages the time component.
```lua
nebula.time.tick()
```
#### Arguments:
None.

#### Returns:
**[ number ]** Delta Time.

#### Example:
```lua
dt = nebula.time.tick()
```

---