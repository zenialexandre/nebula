R"(

function nebula.setup()
    Sprite = nebula.ecs.component("Sprite")
    Position = nebula.ecs.component("Position")
    Quad = nebula.ecs.component("Quad")
    Text = nebula.ecs.component("Text")

    ninaTexture = nebula.graphics.newTexture("resources/textures/Nina.png")
    maruFont = nebula.graphics.newFont("resources/fonts/MaruMonica.ttf", 200)

    player = nebula.ecs.spawn()

    nebula.ecs.addComponent(player, Position({x = 10; y = 10}), Text({font = maruFont; value = "TESTE"}))
    --nebula.ecs.addComponent(player, Position({x = 10; y = 10}), Quad({height = 200; width = 200}))
    --nebula.ecs.addComponent(player, Position({x = 10; y = 10}), Sprite({texture = ninaTexture}))
end

function nebula.update(dt)
    pPosition = nebula.ecs.getComponent(player, Position)
    if (nebula.keyboard.isKeyPressed("w")) then
        pPosition.y = pPosition.y - (200.0 * dt)
    end
    if (nebula.keyboard.isKeyPressed("a")) then
        pPosition.x = pPosition.x - (200.0 * dt)
    end
    if (nebula.keyboard.isKeyPressed("s")) then
        pPosition.y = pPosition.y + (200.0 * dt)
    end
    if (nebula.keyboard.isKeyPressed("d")) then
        pPosition.x = pPosition.x + (200.0 * dt)
    end

    local fps = nebula.time.getFPS()
    pText = nebula.ecs.getComponent(player, Text)
    pText.value = tostring(fps)
end

function nebula.draw()
    nebula.graphics.draw(player)
end

--)"