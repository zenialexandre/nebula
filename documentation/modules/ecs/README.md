# nebula.ecs

| Functions | Description |
|------|-------------|
|[nebula.ecs.spawn](#nebulaecsspawn)| Spawns an entity.
|[nebula.ecs.component](#nebulaecscomponent)| Defines a component.
|[nebula.ecs.addComponent](#nebulaecsaddComponent)| Adds component(s) to an entiy.
|[nebula.ecs.getComponent](#nebulaecsgetComponent)| Gets component(s) from an entity.
|[nebula.ecs.removeComponent](#nebulaecsremoveComponent)| Removes component(s) from an entity.
|[nebula.ecs.hasComponent](#nebulaecshasComponent)| Checks if an entity has component(s).
|[nebula.ecs.getEntitiesWith](#nebulaecsgetEntitiesWith)| Gets all the entities with the component(s).
|[nebula.ecs.print](#nebulaecsprint)| Prints the world state. (mainly for Debug)

---

| Nebula Pre-Made Components |
|------|
|[Position](#Position)
|[Scale](#Scale)
|[Quad](#Quad)
|[Sprite](#Sprite)
|[Text](#Text)
|[Color](#Color)
|[Rotation](#Rotation)
|[CollisionBox](#CollisionBox)

---

## Functions

### nebula.ecs.spawn
Spawns an entity.
```lua
nebula.ecs.spawn()
```
#### Arguments:
None.

#### Returns:
**[ number ]** Entity ID.

#### Example:
```lua
entity = nebula.ecs.spawn()
```

---

### nebula.ecs.component
Defines a component.
```lua
nebula.ecs.component( name , definition )
```
#### Arguments:
**[ string** name **]** Component name,  
**[ table** definition **]** Component definition.

#### Returns:
**[ table ]** Component defintion.

#### Example:
To get a Nebula pre-made component, you should not pass a definition table, as they are already defined:
```lua
local Position = nebula.ecs.component("Position")
```

To create your own component, you should pass a definition table:
```lua
local Speed = nebula.ecs.component("Speed", { x = 0.0; y = 0.0 })
```
Example of a "flag" component (component with no data):
```lua
local Player = nebula.ecs.component("Player", {})
```

---

### nebula.ecs.addComponent
Adds component(s) to an entiy.
```lua
nebula.ecs.addComponent( entity , component... )
```
#### Arguments:
**[ number** entity **]** Entity ID,  
**[ table** component **]** Component(s).

#### Returns:
Nothing.

#### Example:
Nebula pre-made components:
```lua
local Quad = nebula.ecs.component("Quad")
local Position = nebula.ecs.component("Position")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Position({ x = 20.0; y = 100.0 }),
    Quad({ width = 100.0; height = 100.0 })
)
```

Using your own created components:
```lua
local Speed = nebula.ecs.component("Speed", { x = 0.0; y = 0.0 })
local Health = nebula.ecs.component("Health", { value = 100.0 })
local Player = nebula.ecs.component("Player", {})
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Player(),
    Health(),
    Speed({ x = 10.0; y = 10.0 })
)
```

---

### nebula.ecs.getComponent
Gets component(s) from an entity.
```lua
nebula.ecs.getComponent( entity , componentDefinition... )
```
#### Arguments:
**[ number** entity **]** Entity ID,  
**[ table** componentDefinition **]** Component definition(s).

#### Returns:
**[ table ]** Component(s).

#### Example:
Nebula pre-made components:
```lua
local Position = nebula.ecs.component("Position")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Position({ x = 20.0; y = 100.0 })
)

local entityPosition = nebula.ecs.getComponent(entity, Position)
entityPosition.x = 100.0
entityPosition.y = 200.0
```

Using your own created components:
```lua
local Speed = nebula.ecs.component("Speed", { x = 0.0; y = 0.0 })
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Speed({ x = 10.0; y = 10.0 })
)

local entitySpeed = nebula.ecs.getComponent(entity, Speed)
entitySpeed.x = 100.0
entitySpeed.y = 200.0
```

---

### nebula.ecs.removeComponent
Removes component(s) from an entity.
```lua
nebula.ecs.removeComponent( entity , componentDefinition... )
```
#### Arguments:
**[ number** entity **]** Entity ID,  
**[ table** componentDefinition **]** Component definition(s).

#### Returns:
Nothing.

#### Example:
Nebula pre-made components:
```lua
local Position = nebula.ecs.component("Position")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Position({ x = 20.0; y = 100.0 })
)

nebula.ecs.removeComponent(entity, Position)
```

Using your own created components:
```lua
local Speed = nebula.ecs.component("Speed", { x = 0.0; y = 0.0 })
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Speed({ x = 10.0; y = 10.0 })
)

nebula.ecs.removeComponent(entity, Speed)
```

---

### nebula.ecs.hasComponent
Checks if an entity has component(s).
```lua
nebula.ecs.hasComponent( entity , componentDefinition... )
```
#### Arguments:
**[ number** entity **]** Entity ID,  
**[ table** componentDefinition **]** Component definition(s).

#### Returns:
**[ bool ]** True if entity has component(s).

#### Example:
Nebula pre-made components:
```lua
local Position = nebula.ecs.component("Position")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Position({ x = 20.0; y = 100.0 })
)

if nebula.ecs.hasComponent(entity, Position) then
    -- do stuff
end
```

Using your own created components:
```lua
local Speed = nebula.ecs.component("Speed", { x = 0.0; y = 0.0 })
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Speed({ x = 10.0; y = 10.0 })
)

if nebula.ecs.hasComponent(entity, Speed) then
    -- do stuff
end
```

---

### nebula.ecs.getEntitiesWith
Gets all the entities with the component(s).
```lua
nebula.ecs.getEntitiesWith( entity , componentDefinition... )
```
#### Arguments:
**[ number** entity **]** Entity ID,  
**[ table** componentDefinition **]** Component definition(s).

#### Returns:
**[ table ]** Table of all entities that have the collection of components.

#### Example:
Nebula pre-made components:
```lua
local Position = nebula.ecs.component("Position")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Position({ x = 20.0; y = 100.0 })
)

for index, entity in pairs(nebula.ecs.getEntitiesWith(Position)) do
    print(entity)
end
```

Using your own created components:
```lua
local Speed = nebula.ecs.component("Speed", { x = 0.0; y = 0.0 })
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Speed({ x = 10.0; y = 10.0 })
)

for index, entity in pairs(nebula.ecs.getEntitiesWith(Speed)) do
    print(entity)
end
```

---

### nebula.ecs.print
Prints the world state. (mainly for Debug)
```lua
nebula.ecs.print()
```
#### Arguments:
None.

#### Returns:
Nothing.

#### Example:
```lua
nebula.ecs.print()
```

---

## Nebula Pre-Made Components

### Position
A point (x, y) representing an entity's position in the world. **Required** for drawing an entity.

#### C++ Definition:
```cpp
struct Position {
    float x, y;
};
```

#### Example:
```lua
Position = nebula.ecs.component("Position")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Position({ x = 20.0; y = 100.0 })
)
```

---

### Scale
A factor that represents a ratio of sizes. Use it to resize an entity on x or y axis.

#### C++ Definition:
```cpp
struct Scale {
    float x, y;
};
```

#### Example:
```lua
Scale = nebula.ecs.component("Scale")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Scale({ x = 2.0; y = 2.0 })
)
```

---

### Quad
Drawable Quad.

#### C++ Definition:
```cpp
struct Quad {
    float width, height;
};
```

#### Example:
```lua
Quad = nebula.ecs.component("Quad")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Quad({ width = 50.0; height = 50.0 })
)
```

---

### Sprite
Drawable Sprite.

#### C++ Definition:
```cpp
struct Sprite {
    nebula::graphics::Texture* texture;
};
```

#### Example:
```lua
Sprite = nebula.ecs.component("Sprite")
entity = nebula.ecs.spawn()

myTexture = nebula.graphics.newTexture("path/to/texture")

nebula.ecs.addComponent(
    entity,
    Sprite({ texture = myTexture })
)
```

---

### Text
Drawable Text.

#### C++ Definition:
```cpp
struct Text {
    nebula::graphics::Font *font;
    std::string value {};
};
```

#### Example:
```lua
Text = nebula.ecs.component("Text")
entity = nebula.ecs.spawn()

myFont = nebula.graphics.newFont("path/to/font", 10)

nebula.ecs.addComponent(
    entity,
    Text({ font = myFont, value = "Hello, world!" })
)
```

---

### Color
Color (R, G, B) to be applied to an entity.

#### C++ Definition:
```cpp
struct Color {
    float r, g, b, a;
};
```

#### Example:
```lua
Color = nebula.ecs.component("Color")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Color({ r = 1.0, g = 1.0, b = 1.0 })
)
```

---

### Rotation
Angle value to rotate an entity.

#### C++ Definition:
```cpp
struct Rotation {
    float value;
};
```

#### Example:
```lua
Rotation = nebula.ecs.component("Rotation")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    Rotation({ value = 90.0 })
)
```

---

### CollisionBox
Box used for Nebula's collision checking.

#### C++ Definition:
```cpp
struct CollisionBox {
    float width, height;
    float x, y;
};
```
**Notes:** Fields **x** and **y** are used as an offset for Position Component. If the box is meant to be in the same point as the Position Component, do not change x and y.

#### Example:
```lua
CollisionBox = nebula.ecs.component("CollisionBox")
entity = nebula.ecs.spawn()

nebula.ecs.addComponent(
    entity,
    CollisionBox({ width = 10.0; height = 10.0 })
)
```

---