R"(

function nebula.setup()
    Sprite = nebula.ecs.component("Sprite")
    Position = nebula.ecs.component("Position")
    Quad = nebula.ecs.component("Quad")
    player = nebula.ecs.spawn()
    nebula.ecs.addComponent(player, Position({x = 10; y = 10}), Quad({height = 200; width = 300}))
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
end

function nebula.draw()
    nebula.graphics.draw(player)
end

--)"