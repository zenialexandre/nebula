# Nebula Tutorial

## About ECS
Nebula is an **ECS** (Entity Component System) Game Engine, which means that every game object can be referred to as an Entity, and every property of this object can be referred as a Component.

Unlike standard Object Oriented Programming, which each entity is an instance of a class, in ECS an entity is basically an id, and all the data are stored in Components.

ECS can sound very hard, but it is simpler than you would expect.

## Download

If you have not downloaded nebula yet, go to [Downloads](https://github.com/maumafra/nebula/releases) and download the .zip of your platform from the latest version.  

Example: If you have Windows 64bit, you should download the nebula_win64.zip file.

After downloading the .zip, extract the files from it. Inside the exctracted folder, there should have two executables: `nebula.exe` and `nebula_console.exe`.

You can place these files wherever you want, just make sure that you will be able to get their paths later.

**Notes:** If there is not a .zip for your platform, you will have to build the project. Check [Building the Game Engine](https://github.com/maumafra/nebula?tab=readme-ov-file#building-the-game-engine-code).

## Download VSCode
Nebula is a **code only** Game Engine, which means that there is no User Interface. So it is **heavily recommended** that you have an IDE for developing your games.

If you already have VSCode installed, you can [skip](#download-vscode-extension) this section.

VSCode is an light and simple IDE, that support multiple extensions (including an official **Nebula Extension**). So if you are new to coding or to the Game Engine, download [VSCode](https://code.visualstudio.com/download) to follow this tutorial.

## Download VSCode Extension

Nebula has it's own VSCode Extension!  

To download it, go to **Extensions**, search `Nebula Game Engine Support` and click on **Install**:

<img width="1188" height="623" alt="image" src="https://github.com/user-attachments/assets/3f8dc291-4cb7-49f4-a2cd-e1d58dc7b816" />

---
Make sure to configure the extension, pasting the executable path in there:  

<img width="879" height="290" alt="image" src="https://github.com/user-attachments/assets/c03583a8-6860-4a13-8270-a6e4f1ae5ae2" />

**Notes:** While developing your game, you can point the Engine Executable Path to the **nebula_console.exe**, as it will print the game output in the VSCode Terminal.  

---

## Setting Up the Project

In order to begin developing your game, you will need to create a folder. We will call this folder as the **Project Folder**.

This **Project Folder** is where you will want to place all your game's source-code and assets. You can create multiple folders inside your **Project Folder**, so you can organize your game files however you want.

So inside your **Project Folder**, you need to create a file called `main.lua`, and it should have exactly this name.

The **ONLY RESTRICTION** nebula has, is that the `main.lua` file should be placed at the root of your **Project Folder**, like this:

```shell
project-folder/
├── assets/
│ └── ...
├── src/
│ └── ...
└── main.lua
```

With everything set, you may open the `main.lua` file in VSCode.

## Drawing your first Quad!

Here I will show you a quick guide for drawing a simple Quad, using the **nebula.ecs** and **nebula.graphics** modules:

### Setup, Update and Draw

In your `main.lua` file, you may create these 3 functions: `nebula.setup()`, `nebula.update(dt)` and `nebula.draw()`. Like this:

```Lua
--your main.lua file
function nebula.setup()

end

function nebula.update(dt) -- dt here is delta time

end

function nebula.draw()

end
```
Let's understand what each of these functions do:
- `nebula.setup`: This function is called only **once** in your game, so it is a great place to put all the configuration code and definitions.

- `nebula.update`: This function is called **once** every frame, so it is the proper place to update your entities, handle inputs, movement etc. Note that this function receives a `dt`, this `dt` is **Delta Time**, which is crucial for game development. If you do not know how to use delta time, it is recommended to learn before developing your game.

- `nebula.draw`: This function is also called **once** every frame, and it is the best place to put the `nebula.graphics.draw` functions.

### Spawning an Entity

With those three functions defined, we can create our first entity! To do this, simply use **nebula.ecs.spawn()**. As we only want to spawn our entity once in the game, we are going to put it in **nebula.setup**. Like this:

```Lua
--your main.lua file
function nebula.setup()
    entity = nebula.ecs.spawn()
end

function nebula.update(dt) -- dt = delta time

end

function nebula.draw()

end
```
Great! We have our first entity spawned! But remember, this entity is just an id, it doesn't have any data yet.

### Adding Components

Now we need to add some data to this boy. To do that, we are going to need some Components.

Nebula has its own pre-made Components, one of those is the **Position** Component, which have a **x** and **y** fields. These fields represent where the entity is in the game. **This component is required for rendering an entity**.

Another pre-made Component is **Quad**, which have a **width** and **height** fields. This component is used to render a square.

To get their definitions, we can call **nebula.ecs.component(** *componentName* **)**. And as we only want to get the definitions once, we are going to put it in **nebula.setup** again:
```Lua
--your main.lua file
function nebula.setup()
    -- nebula pre-made components:
    PositionDefinition = nebula.ecs.component("Position")
    QuadDefinition = nebula.ecs.component("Quad")

    entity = nebula.ecs.spawn()
end

function nebula.update(dt)

end

function nebula.draw()

end
```

With the definitions set, we can add them to our entity with **nebula.ecs.addComponent(** *entity, Component...* **)**:

```Lua
--your main.lua file
function nebula.setup()
    PositionDefinition = nebula.ecs.component("Position")
    QuadDefinition = nebula.ecs.component("Quad")

    entity = nebula.ecs.spawn()

    nebula.ecs.addComponent(
        entity,
        PositionDefinition({x = 10, y = 10}),
        QuadDefinition({width = 100, height = 100})
    )
end

function nebula.update(dt)

end

function nebula.draw()

end
```

Great! Our entity is a Quad of 100x100 and it is located at (10, 10). Now there is only one thing left, we need to tell nebula that this quad has to be rendered.

### Rendering the entity

To do that, we call **nebula.graphics.draw(** *entity* **)** in our **nebula.draw** function:

```Lua
--your main.lua file
function nebula.setup()
    PositionDefinition = nebula.ecs.component("Position")
    QuadDefinition = nebula.ecs.component("Quad")

    entity = nebula.ecs.spawn()

    nebula.ecs.addComponent(
        entity,
        PositionDefinition({x = 10, y = 10}),
        QuadDefinition({width = 100, height = 100})
    )
end

function nebula.update(dt)

end

function nebula.draw()
    nebula.graphics.draw(entity)
end
```

And voilà, our code is ready!

### Running the code

If you installed the VSCode Extension and configured it properly, a **Green Button** should appear on the top-right corner, clicking it should run your code:

<img width="1503" height="570" alt="image" src="https://github.com/user-attachments/assets/053fc959-915e-458e-ab2a-6a4cb11d8f1a" />

If everything goes right, a window like this should be opened:

<img width="406" height="325" alt="image" src="https://github.com/user-attachments/assets/57cba878-5ee6-4872-818d-c25bc562429e" />
