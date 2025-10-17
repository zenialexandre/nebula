function nebula.setup()
    Position = nebula.ecs.component("Position")
    Quad = nebula.ecs.component("Quad")
    CollisionBox = nebula.ecs.component("CollisionBox")

    -- custom components
    Speed = nebula.ecs.component("Speed", {x = 1, y = 1})

    pong1 = nebula.ecs.spawn()
    pong2 = nebula.ecs.spawn()

    ball  = nebula.ecs.spawn()

    floor = nebula.ecs.spawn()
    ceiling = nebula.ecs.spawn()

    winWidth, winHeight = nebula.window.getSize()

    nebula.ecs.addComponent(
        pong1,
        Position({x = 10, y = winHeight / 2 - 50}),
        Quad({width = 20, height = 100}),
        CollisionBox({width = 20, height = 100}),
        Speed({y = 200})
    )

    nebula.ecs.addComponent(
        pong2,
        Position({x = winWidth - 10 - 20, y = winHeight / 2 - 50}),
        Quad({width = 20, height = 100}),
        CollisionBox({width = 20, height = 100}),
        Speed({y = 200})
    )

    nebula.ecs.addComponent(
        ball,
        Position({x = winWidth / 2, y =  winHeight / 2}),
        Quad({width = 10, height = 10}),
        CollisionBox({width = 10, height = 10}),
        Speed({x = 250; y = 250})
    )

    nebula.ecs.addComponent(
        floor,
        Position({x = 0, y =  winHeight - 30}),
        Quad({width = winWidth, height = 30}),
        CollisionBox({width = winWidth, height = 30})
    )

    nebula.ecs.addComponent(
        ceiling,
        Position({x = 0, y =  0}),
        Quad({width = winWidth, height = 30}),
        CollisionBox({width = winWidth, height = 30})
    )
end

function nebula.update(dt)
    p1Pos = nebula.ecs.getComponent(pong1, Position)
    p1Speed = nebula.ecs.getComponent(pong1, Speed)

    if (nebula.keyboard.isKeyPressed("w")) then
        if not nebula.physics.checkCollision(pong1, ceiling) then
            p1Pos.y = p1Pos.y - (p1Speed.y * dt)
        end
    end
    if (nebula.keyboard.isKeyPressed("s")) then
        if not nebula.physics.checkCollision(pong1, floor) then
            p1Pos.y = p1Pos.y + (p1Speed.y * dt)
        end
    end

    p2Pos = nebula.ecs.getComponent(pong2, Position)
    p2Speed = nebula.ecs.getComponent(pong2, Speed)

    if (nebula.keyboard.isKeyPressed("up")) then
        if not nebula.physics.checkCollision(pong2, ceiling) then
            p2Pos.y = p2Pos.y - (p2Speed.y * dt)
        end
    end
    if (nebula.keyboard.isKeyPressed("down")) then
        if not nebula.physics.checkCollision(pong2, floor) then
            p2Pos.y = p2Pos.y + (p2Speed.y * dt)
        end
    end

    ballPos = nebula.ecs.getComponent(ball, Position);
    ballSpeed = nebula.ecs.getComponent(ball, Speed);

    if nebula.physics.checkCollision(ball, floor) then
        ballSpeed.y = - ballSpeed.y
    end
    if nebula.physics.checkCollision(ball, ceiling) then
        ballSpeed.y = - ballSpeed.y
    end
    if nebula.physics.checkCollision(ball, pong1) then
        if ballPos.x < 30 then
            ballSpeed.y = - ballSpeed.y
        end
        ballSpeed.x = - ballSpeed.x
    end
    if nebula.physics.checkCollision(ball, pong2) then
        if ballPos.x > winWidth - 30 then
            ballSpeed.y = - ballSpeed.y
        end
        ballSpeed.x = - ballSpeed.x
    end

    ballPos.x = ballPos.x + (ballSpeed.x * dt)
    ballPos.y = ballPos.y + (ballSpeed.y * dt)
end

function nebula.draw()
    for i, entity in pairs(nebula.ecs.getEntitiesWith(Position)) do
        nebula.graphics.draw(entity)
    end
end