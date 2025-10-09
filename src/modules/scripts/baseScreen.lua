R"(

function nebula.setup()
    Sprite = nebula.ecs.component("Sprite")
    Position = nebula.ecs.component("Position")
    Quad = nebula.ecs.component("Quad")
    boxSprite = nebula.graphics.newSprite("resources/textures/container.jpg")
    player = nebula.ecs.spawn()
    nebula.ecs.addComponent(player, Position({x = 10; y = 10}), Sprite({texture = boxSprite}))
end

function nebula.update(dt)
    pPosition = nebula.ecs.getComponent(player, Position)
    pPosition.x = pPosition.x + (2.0 * dt)
end

function nebula.draw()
    nebula.graphics.draw(player)
end

--)"