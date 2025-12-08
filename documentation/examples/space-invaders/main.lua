function nebula.setup()
    nebula.graphics.setDefaultFilter("nearest")
    -- nebula components
    Position = nebula.ecs.component("Position")
    Quad = nebula.ecs.component("Quad")
    CollisionBox = nebula.ecs.component("CollisionBox")
    Sprite = nebula.ecs.component("Sprite")
    Text = nebula.ecs.component("Text")
    Color = nebula.ecs.component("Color")
    Scale = nebula.ecs.component("Scale")

    Speed = nebula.ecs.component("Speed", {x = 0, y = 0})
    Enemy = nebula.ecs.component("Enemy", {})
    Bullet = nebula.ecs.component("Bullet", {})

    playerTex = nebula.graphics.newTexture("resources/sprites/player.png")
    enemyTex = nebula.graphics.newTexture("resources/sprites/enemy.png")

    maruFont = nebula.graphics.newFont("resources/fonts/MaruMonica.ttf", 100)

    pongHit = nebula.audio.newSource("resources/effects/pongHitByNoiseCollector.wav")
    music = nebula.audio.newSource("resources/music/music.wav")

    nebula.audio.setVolume(0.2)

    player = nebula.ecs.spawn()

    nebula.audio.play(music, true)

    nebula.window.setSize(600, 800)

    winWidth, winHeight = nebula.window.getSize()

    nebula.ecs.addComponent(
        player,
        Position({x = winWidth/2 - playerTex.width, y = 650}),
        Sprite({texture = playerTex}),
        CollisionBox({width = 20, height = 100}),
        Speed({x = 0, y = 0}),
        Scale({x = 2, y = 2})
    )
    spawnEnemies()
    nebula.window.setIcon("resources/sprites/enemy.png")
end

function nebula.update(dt)
    local p1Speed = nebula.ecs.getComponent(player, Speed)

    if (nebula.keyboard.isKeyPressed("a")) then
        p1Speed.x = -200
    end
    if (nebula.keyboard.isKeyPressed("d")) then
        p1Speed.x = 200
    end
    if (nebula.keyboard.isKeyReleased("a") or nebula.keyboard.isKeyReleased("d")) then
        p1Speed.x = 0
    end
    if (nebula.keyboard.isKeyReleased("enter")) then
        spawnBullet()
    end

    for _, entity in pairs(nebula.ecs.getEntitiesWith(Position, Speed)) do
        entPos = nebula.ecs.getComponent(entity, Position)
        entSpeed = nebula.ecs.getComponent(entity, Speed)

        entPos.x = entPos.x + (entSpeed.x * dt)
        entPos.y = entPos.y + (entSpeed.y * dt)

        if (entPos.y < 0) then
            nebula.ecs.despawn(entity)
        end
    end

    checkEnemyCollision()

    nebula.window.setTitle("Space Invaders! FPS: "..tostring(nebula.time.getFPS()))
end

function nebula.draw()
    for i, entity in pairs(nebula.ecs.getEntitiesWith(Position)) do
        nebula.graphics.draw(entity)
    end
end

function spawnBullet()
    pPos = nebula.ecs.getComponent(player, Position)
    pSprite = nebula.ecs.getComponent(player, Sprite)
    pScale = nebula.ecs.getComponent(player, Scale)

    bulEntity = nebula.ecs.spawn()

    nebula.ecs.addComponent(bulEntity,
        Quad{width = 10, height = 20},
        Position{x = pPos.x + (pSprite.texture.width*pScale.x)/2, y = pPos.y},
        Speed{y = -300},
        CollisionBox{width = 10, height = 40},
        Bullet()
    )
end


function spawnEnemies()
    local posx = 10
    local posy = 30
    for _ = 1, 5, 1 do
        local enemy = nebula.ecs.spawn()

        nebula.ecs.addComponent(
            enemy,
            Position({x = posx, y = posy}),
            Sprite({texture = enemyTex}),
            CollisionBox({width = enemyTex.width, height = enemyTex.height}),
            Speed({x = 0, y = 0}),
            Scale({x = 2, y = 2}),
            Enemy()
        )

        posx = posx + 20 + (enemyTex.width*2)
    end
end

function checkEnemyCollision()
    for _, enemy in pairs(nebula.ecs.getEntitiesWith(Enemy)) do
        for _, bullet in pairs(nebula.ecs.getEntitiesWith(Bullet)) do
            if (nebula.physics.checkCollision(enemy, bullet)) then
                nebula.ecs.despawn(enemy)
                nebula.ecs.despawn(bullet)
            end
        end
    end
end