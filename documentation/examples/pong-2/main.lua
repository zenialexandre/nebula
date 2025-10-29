function nebula.setup()
    -- nebula components
    Position = nebula.ecs.component("Position")
    Quad = nebula.ecs.component("Quad")
    CollisionBox = nebula.ecs.component("CollisionBox")
    Sprite = nebula.ecs.component("Sprite")
    Text = nebula.ecs.component("Text")
    Color = nebula.ecs.component("Color")

    -- custom components
    Speed = nebula.ecs.component("Speed", {x = 1, y = 1})
    Score = nebula.ecs.component("Score", {value = 0})

    leftPongTex = nebula.graphics.newTexture("resources/sprites/left-pong.png")
    rightPongTex = nebula.graphics.newTexture("resources/sprites/right-pong.png")
    ballTex = nebula.graphics.newTexture("resources/sprites/ball.png")
    ceilingTex = nebula.graphics.newTexture("resources/sprites/ceiling.png")
    floorTex = nebula.graphics.newTexture("resources/sprites/floor.png")

    maruFont = nebula.graphics.newFont("resources/fonts/MaruMonica.ttf", 100)

    pongHit = nebula.audio.newSource("resources/effects/pongHitByNoiseCollector.wav")
    music = nebula.audio.newSource("resources/music/music.wav")

    nebula.audio.setVolume(0.2)

    pong1 = nebula.ecs.spawn()
    pong2 = nebula.ecs.spawn()

    ball  = nebula.ecs.spawn()

    floor = nebula.ecs.spawn()
    ceiling = nebula.ecs.spawn()
    
    scoreP1 = nebula.ecs.spawn()
    scoreP2 = nebula.ecs.spawn()

    nebula.audio.play(music, true)

    winWidth, winHeight = nebula.window.getSize()

    nebula.ecs.addComponent(
        pong1,
        Position({x = 10, y = winHeight / 2 - 50}),
        Sprite({texture = leftPongTex}),
        CollisionBox({width = 20, height = 100}),
        Speed({y = 200}),
        Score()
    )

    nebula.ecs.addComponent(
        pong2,
        Position({x = winWidth - 10 - 20, y = winHeight / 2 - 50}),
        Sprite({texture = rightPongTex}),
        CollisionBox({width = 20, height = 100}),
        Speed({y = 200}),
        Score()
    )

    nebula.ecs.addComponent(
        ball,
        Position({x = winWidth / 2, y =  winHeight / 2}),
        Sprite({texture = ballTex}),
        CollisionBox({width = 10, height = 10}),
        Speed({x = 250; y = 250})
    )

    nebula.ecs.addComponent(
        floor,
        Position({x = 0, y =  winHeight - 30}),
        Sprite({texture = floorTex}),
        CollisionBox({width = winWidth, height = 30})
    )

    nebula.ecs.addComponent(
        ceiling,
        Position({x = 0, y =  0}),
        Sprite({texture = ceilingTex}),
        CollisionBox({width = winWidth, height = 30})
    )

    nebula.ecs.addComponent(
        scoreP1,
        Position({x = winWidth / 2 - 70 - 27, y =  winHeight / 2 - 20}),
        Text({font = maruFont, value = "0"}),
        Color({r = 0.85, g = 0.63, b = 0.4})
    )

    nebula.ecs.addComponent(
        scoreP2,
        Position({x = winWidth / 2 + 70, y =  winHeight / 2 - 20}),
        Text({font = maruFont, value = "0"}),
        Color({r = 0.37, g = 0.80, b = 0.89})
    )

    nebula.window.setIcon("resources/sprites/ball.png")
end

function nebula.update(dt)
    local p1Pos = nebula.ecs.getComponent(pong1, Position)
    local p1Speed = nebula.ecs.getComponent(pong1, Speed)

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

    local p2Pos = nebula.ecs.getComponent(pong2, Position)
    local p2Speed = nebula.ecs.getComponent(pong2, Speed)

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

    local ballPos = nebula.ecs.getComponent(ball, Position);
    local ballSpeed = nebula.ecs.getComponent(ball, Speed);

    if nebula.physics.checkCollision(ball, floor) then
        ballSpeed.y = - ballSpeed.y
    end
    if nebula.physics.checkCollision(ball, ceiling) then
        ballSpeed.y = - ballSpeed.y
    end
    if nebula.physics.checkCollision(ball, pong1) then
        if ballPos.x < 20 then
            ballSpeed.y = - ballSpeed.y
        end
        ballSpeed.x = - ballSpeed.x

        if (not nebula.audio.isPlaying(pongHit)) then
            nebula.audio.play(pongHit, false)
        end
    end
    if nebula.physics.checkCollision(ball, pong2) then
        if ballPos.x > winWidth - 20 then
            ballSpeed.y = - ballSpeed.y
        end
        ballSpeed.x = - ballSpeed.x

        if (not nebula.audio.isPlaying(pongHit)) then
            nebula.audio.play(pongHit, false)
        end
    end

    ballPos.x = ballPos.x + (ballSpeed.x * dt)
    ballPos.y = ballPos.y + (ballSpeed.y * dt)

    if ballPos.x < -10 then
        local p2Score = nebula.ecs.getComponent(pong2, Score)
        local score2Text = nebula.ecs.getComponent(scoreP2, Text)

        p2Score.value = p2Score.value + 1
        score2Text.value = tostring(p2Score.value)

        ballPos.x = winWidth / 2
        ballPos.y =  winHeight / 2
    end
    if ballPos.x > winWidth then
        local p1Score = nebula.ecs.getComponent(pong1, Score)
        local score1Text = nebula.ecs.getComponent(scoreP1, Text)

        p1Score.value = p1Score.value + 1
        score1Text.value = tostring(p1Score.value)

        ballPos.x = winWidth / 2
        ballPos.y =  winHeight / 2
    end

    nebula.window.setTitle("pong 2! fps: "..tostring(nebula.time.getFPS()))
end

function nebula.draw()
    for i, entity in pairs(nebula.ecs.getEntitiesWith(Position)) do
        nebula.graphics.draw(entity)
    end
end