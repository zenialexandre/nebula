# nebula.event

| Functions | Description |
|------|-------------|
|[nebula.event.poll](#nebulaeventpoll)| **Mainly for internal uses**. Removes and returns one event.

---

## Functions

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