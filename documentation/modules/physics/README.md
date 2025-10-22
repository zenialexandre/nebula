# nebula.physics

| Functions | Description |
|------|-------------|
|[nebula.physics.checkCollision](#nebulaphysicscheckcollision)| Checks if two entities collide.

## Functions

### nebula.physics.checkCollision
Checks if two entities collide. This function requires the entities to have the CollisionBox component.
```lua
nebula.physics.checkCollision( entity1, entity2 )
```
#### Arguments:
**[ number** entity1 **]** First Entity ID,  
**[ number** entity2 **]** Second Entity ID.

#### Returns:
**[ bool ]** True if they collide.

#### Example:
```lua
if nebula.physics.checkCollision(entity1, entity2) then
    -- handle collision
end
```

---