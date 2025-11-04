# nebula.event

| Functions | Description |
|------|-------------|
|[nebula.event.quit](#nebulaeventquit)| Quits the game.
|[nebula.event.poll](#nebulaeventpoll)| **Mainly for internal uses**. Removes and returns one event.

---

## Functions

### nebula.event.quit
Quits the game, closing the window.
```lua
nebula.event.quit()
```
#### Arguments:
None.

#### Returns:
Nothing.

#### Example:
```lua
nebula.event.quit()
```

---

### nebula.event.poll
**Should be avoided**, nebula handles events internally.
```lua
event = nebula.event.poll()
```
#### Arguments:
None.

#### Returns:
**[ string ]** Event name.

#### Example:
```lua
event = nebula.event.poll()
```

---