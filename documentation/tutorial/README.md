# Nebula Tutorial

## About ECS
Nebula is an **ECS** (Entity Component System) Game Engine, which means that every game object can be referred to as an Entity, and every property of this object can be referred as a Component.

Unlike standard Object Oriented Programming, which each entity is an instance of a class, in ECS an entity is basically an id, and all the data are stored in Components.

ECS can sound very hard, but it is simpler than you would expect.

## Drawing your first Quad!

Here I will show you a snippet for drawing a simple Quad, using the **nebula.ecs** and **nebula.graphics** modules:

First things first, you need to create a **main.lua** file, and it needs to have exactly this name ("main.lua").

In it, you may create 3 functions: **nebula.setup**, **nebula.update** and **nebula.draw**. Like this:

```Lua
--your main.lua file
function nebula.setup()

end

function nebula.update(dt) -- dt here is delta time

end

function nebula.draw()

end
```

With this functions defined, we can create our first entity! To do this, simply use **nebula.ecs.spawn()**. As we only want to spawn our entity once, we are going to put it in **nebula.setup**. Like this:

```Lua
--your main.lua file
function nebula.setup()
    entity = nebula.ecs.spawn()
end

function nebula.update(dt) -- dt here is delta time

end

function nebula.draw()

end
```
Great! We have our first entity spawned! But remember, this entity is just an id, it doesn't have any data yet.

Now we need to render this boy. To do that, we are going to need some Components.

Nebula has its own pre-made Components, one of those is the **Position** Component, which have a **x** and **y** values. These values represent where the entity is in the game.

Another pre-made Component is **Quad**, which have a **width** and **height** values. This component is used to render a square.

To get their constructors, we can call **nebula.ecs.component(***componentName***)**. And as we only want to get it's constructors once, we are going to put it in **nebula.setup** again:
```Lua
--your main.lua file
function nebula.setup()
    -- nebula pre-made components:
    PositionConstructor = nebula.ecs.component("Position")
    QuadConstructor = nebula.ecs.component("Quad")

    entity = nebula.ecs.spawn()
end

function nebula.update(dt)

end

function nebula.draw()

end
```

With the constructors set, we can add them to our entity with **nebula.ecs.addComponent(***entity, Component...***)**:

```Lua
--your main.lua file
function nebula.setup()
    PositionConstructor = nebula.ecs.component("Position")
    QuadConstructor = nebula.ecs.component("Quad")

    entity = nebula.ecs.spawn()

    nebula.ecs.addComponent(
        entity,
        PositionConstructor({x = 10, y = 10}),
        QuadConstructor({width = 100, height = 100})
    )
end

function nebula.update(dt)

end

function nebula.draw()

end
```

Great! Our entity is a Quad of 100x100 and it is located at (10, 10). Now there is only one thing left, we need to tell nebula that this quad has to be rendered.

To do that, we call **nebula.graphics.draw(***entity***)** in our **nebula.draw** function:

```Lua
--your main.lua file
function nebula.setup()
    PositionConstructor = nebula.ecs.component("Position")
    QuadConstructor = nebula.ecs.component("Quad")

    entity = nebula.ecs.spawn()

    nebula.ecs.addComponent(
        entity,
        PositionConstructor({x = 10, y = 10}),
        QuadConstructor({width = 100, height = 100})
    )
end

function nebula.update(dt)

end

function nebula.draw()
    nebula.graphics.draw(entity)
end
```

And voilà, our code is ready! To run it, put the nebula executable in the same folder as your main.lua, or you can drag the folder (which has the main.lua file in it) to the executable.

Running the code should open a window like this:

img