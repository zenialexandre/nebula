# nebula.physics

| Functions | Description |
|------|-------------|
|[nebula.physics.checkCollision](#nebulaphysicscheckcollision)| Checks if two elements collide.

## Functions

### nebula.physics.checkCollision
Checks if two elements collide, it can be a point or an entity. This function requires the entities to have the `CollisionBox` component.
```lua
nebula.physics.checkCollision( entity1, entity2 )
-- or
nebula.physics.checkCollision( x, y, entity )
```
#### Arguments:
**[ number** entity1 **]** First Entity ID,  
**[ number** entity2 **]** Second Entity ID.

Or:  
**[ number** x **]** X coordinate,  
**[ number** y **]** Y coordinate,  
**[ number** entity **]** Entity ID.


#### Returns:
**[ bool ]** True if they collide.

#### Example:
```lua
if nebula.physics.checkCollision(entity1, entity2) then
    -- handle collision between entity1 and entity2
end

if nebula.physics.checkCollision(mouseX, mouseY, entity) then
    -- handle collision between mouse and entity
end
```

---