R"(

function nebula.setup()
    Sprite = nebula.ecs.component("Sprite")
    Position = nebula.ecs.component("Position")
    Quad = nebula.ecs.component("Quad")
    Text = nebula.ecs.component("Text")
    Color = nebula.ecs.component("Color")

    ninaTexture = nebula.graphics.newTexture("resources/textures/Nina.png")
    maruFont = nebula.graphics.newFont("resources/fonts/MaruMonica.ttf", 200)

    player = nebula.ecs.spawn()

    square = nebula.ecs.spawn()

    nebula.ecs.addComponent(player, Position({x = 10; y = 10}), Color({r = 0.0; g = 1.0; b = 0.0}), Text({font = maruFont; value = "TESTE"}))
    nebula.ecs.addComponent(square, Position({x = 30; y = 40}), Color({r = 1.0; g = 1.0; b = 0.0}), Quad({width = 60; height = 60}))

    --nebula.ecs.addComponent(player, Position({x = 10; y = 10}), Quad({height = 200; width = 200}))
    --nebula.ecs.addComponent(player, Position({x = 10; y = 10}), Sprite({texture = ninaTexture}))
    nebula.graphics.setBackground(0.1, 0.0, 0.1)
end

function nebula.update(dt)
    pPosition = nebula.ecs.getComponent(player, Position)
    if (nebula.keyboard.isKeyPressed("w")) then
        --nebula.graphics.moveCamera(0, -200.0 * dt)
        pPosition.y = pPosition.y - (200.0 * dt)
    end
    if (nebula.keyboard.isKeyPressed("a")) then
        --nebula.graphics.moveCamera(-200.0 * dt, 0)
        pPosition.x = pPosition.x - (200.0 * dt)
    end
    if (nebula.keyboard.isKeyPressed("s")) then
        --nebula.graphics.moveCamera(0, 200.0 * dt)
        pPosition.y = pPosition.y + (200.0 * dt)
    end
    if (nebula.keyboard.isKeyPressed("d")) then
        --nebula.graphics.moveCamera(200.0 * dt, 0)
        pPosition.x = pPosition.x + (200.0 * dt)
    end
    if (nebula.keyboard.isKeyPressed("space")) then
        nebula.graphics.pointCameraTo(pPosition.x, pPosition.y)
    end

    local fps = nebula.time.getFPS()
    pText = nebula.ecs.getComponent(player, Text)
    pText.value = tostring(fps)

    nebula.window.setTitle("nebula - "..tostring(fps).." fps")
end

function nebula.draw()
    nebula.graphics.draw(player)
    nebula.graphics.draw(square)
end

--)"