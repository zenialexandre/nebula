-- Breakout Game Prototype for Nebula Engine
-- Componentes
Position = nil
Quad = nil
CollisionBox = nil
Speed = nil
BlockActive = nil

-- Entidades do jogo
paddle = nil
ball = nil
blocks = {}

-- Configurações do jogo
winWidth = 0
winHeight = 0
PADDLE_WIDTH = 200
PADDLE_HEIGHT = 25
PADDLE_SPEED = 700
BALL_SIZE = 20
BALL_SPEED = 400
BLOCK_ROWS = 5
BLOCK_COLS = 10
BLOCK_PADDING = 5
BLOCK_HEIGHT = 25
BLOCK_WIDTH = 75

-- Estado do jogo
GAMESTATE = "playing" -- playing, won, lost
SCORE = 0

function nebula.setup()
    -- Definir componentes
    Position = nebula.ecs.component("Position")
    Quad = nebula.ecs.component("Quad")
    CollisionBox = nebula.ecs.component("CollisionBox")
    Speed = nebula.ecs.component("Speed", {x = 0, y = 0})
    BlockActive = nebula.ecs.component("BlockActive", {active = true})
    winWidth, winHeight = nebula.window.getSize()
    
    -- Centralizar blocos na tela
    local totalBlockWidth = BLOCK_COLS * BLOCK_WIDTH + (BLOCK_COLS - 1) * BLOCK_PADDING
    local startXCalc = (winWidth - totalBlockWidth) / 2

    -- Criar paddle (raquete)
    paddle = nebula.ecs.spawn()
    nebula.ecs.addComponent(
        paddle,
        Position({x = winWidth / 2 - PADDLE_WIDTH / 2, y = winHeight - 50}),
        Quad({width = PADDLE_WIDTH, height = PADDLE_HEIGHT}),
        CollisionBox({width = PADDLE_WIDTH, height = PADDLE_HEIGHT}),
        Speed({x = PADDLE_SPEED, y = 0})
    )

    -- Criar blocos - preencher a tela toda
    local startX = startXCalc
    local startY = 50
    
    for row = 0, BLOCK_ROWS - 1 do
        for col = 0, BLOCK_COLS - 1 do
            local block = nebula.ecs.spawn()
            local x = startX + col * (BLOCK_WIDTH + BLOCK_PADDING)
            local y = startY + row * (BLOCK_HEIGHT + BLOCK_PADDING)
            
            nebula.ecs.addComponent(
                block,
                Position({x = x, y = y}),
                Quad({width = BLOCK_WIDTH, height = BLOCK_HEIGHT}),
                CollisionBox({width = BLOCK_WIDTH, height = BLOCK_HEIGHT}),
                BlockActive({active = true})
            )
            
            table.insert(blocks, block)
        end
    end
    
    -- Criar bola DEPOIS dos blocos (abaixo deles, indo em direção ao paddle)
    ball = nebula.ecs.spawn()
    local ballStartY = startY + (BLOCK_ROWS * (BLOCK_HEIGHT + BLOCK_PADDING)) + 80
    nebula.ecs.addComponent(
        ball,
        Position({x = winWidth / 2 - BALL_SIZE / 2, y = ballStartY}),
        Quad({width = BALL_SIZE, height = BALL_SIZE}),
        CollisionBox({width = BALL_SIZE, height = BALL_SIZE}),
        Speed({x = BALL_SPEED, y = BALL_SPEED})
    )

    nebula.window.setTitle("Breakout - Nebula Engine")
end

function nebula.update(dt)    
    if GAMESTATE ~= "playing" then
        -- Reiniciar o jogo com R
        if nebula.keyboard.isKeyPressed("r") then
            -- Limpar tudo e reiniciar
            blocks = {}
            SCORE = 0
            GAMESTATE = "playing"

            -- Resetar posição da bola (abaixo dos blocos)
            local ballPos = nebula.ecs.getComponent(ball, Position)
            ballPos.x = winWidth / 2 - BALL_SIZE / 2
            local startY = 60
            ballPos.y = startY + (BLOCK_ROWS * (BLOCK_HEIGHT + BLOCK_PADDING)) + 80
            
            -- Resetar velocidade da bola
            local ballSpeed = nebula.ecs.getComponent(ball, Speed)
            ballSpeed.x = BALL_SPEED
            ballSpeed.y = BALL_SPEED
            
            -- Resetar posição do paddle
            local paddlePos = nebula.ecs.getComponent(paddle, Position)
            paddlePos.x = winWidth / 2 - PADDLE_WIDTH / 2
            
            -- Recalcular posição dos blocos centralizados
            local totalBlockWidth = BLOCK_COLS * BLOCK_WIDTH + (BLOCK_COLS - 1) * BLOCK_PADDING
            local startXCalc = (winWidth - totalBlockWidth) / 2
            
            -- Recriar blocos - preencher a tela toda
            local startX = startXCalc
            local startY = 50
            
            for row = 0, BLOCK_ROWS - 1 do
                for col = 0, BLOCK_COLS - 1 do
                    local block = nebula.ecs.spawn()
                    local x = startX + col * (BLOCK_WIDTH + BLOCK_PADDING)
                    local y = startY + row * (BLOCK_HEIGHT + BLOCK_PADDING)
                    
                    nebula.ecs.addComponent(
                        block,
                        Position({x = x, y = y}),
                        Quad({width = BLOCK_WIDTH, height = BLOCK_HEIGHT}),
                        CollisionBox({width = BLOCK_WIDTH, height = BLOCK_HEIGHT}),
                        BlockActive({active = true})
                    )
                    
                    table.insert(blocks, block)
                end
            end
        end
        return
    end

    -- Atualizar paddle (controle do jogador)
    local paddlePos = nebula.ecs.getComponent(paddle, Position)
    local paddleSpeed = nebula.ecs.getComponent(paddle, Speed)
    
    if nebula.keyboard.isKeyPressed("left") or nebula.keyboard.isKeyPressed("a") then
        paddlePos.x = paddlePos.x - (paddleSpeed.x * dt)
    end
    if nebula.keyboard.isKeyPressed("right") or nebula.keyboard.isKeyPressed("d") then
        paddlePos.x = paddlePos.x + (paddleSpeed.x * dt)
    end
    
    -- Limitar paddle na tela (usando winWidth dinâmico atual)
    local currentWinWidth, currentWinHeight = nebula.window.getSize()
    if paddlePos.x < 0 then
        paddlePos.x = 0
    end
    if paddlePos.x + PADDLE_WIDTH > currentWinWidth then
        paddlePos.x = currentWinWidth - PADDLE_WIDTH
    end

    -- Atualizar bola
    local ballPos = nebula.ecs.getComponent(ball, Position)
    local ballSpeed = nebula.ecs.getComponent(ball, Speed)
    
    ballPos.x = ballPos.x + (ballSpeed.x * dt)
    ballPos.y = ballPos.y + (ballSpeed.y * dt)
    
    -- Colisão com paredes laterais (usando winWidth dinâmico atual)
    local currentWinWidth, currentWinHeight = nebula.window.getSize()
    if ballPos.x <= 0 then
        ballSpeed.x = math.abs(ballSpeed.x)
        ballPos.x = 0
    elseif ballPos.x + BALL_SIZE >= currentWinWidth then
        ballSpeed.x = -math.abs(ballSpeed.x)
        ballPos.x = currentWinWidth - BALL_SIZE
    end
    
    -- Colisão com teto
    if ballPos.y <= 0 then
        ballSpeed.y = math.abs(ballSpeed.y)
        ballPos.y = 0
    end
    
    -- Colisão com paddle usando sistema de física da engine
    if nebula.physics.checkCollision(ball, paddle) then
        ballSpeed.y = -math.abs(ballSpeed.y) -- Sempre para cima
        
        -- Adicionar efeito de "inglês" baseado em onde bateu no paddle
        local hitPos = (ballPos.x - paddlePos.x) / PADDLE_WIDTH
        ballSpeed.x = (hitPos - 0.5) * BALL_SPEED * 2
    end
    
    -- Colisão com blocos
    local activeBlocks = 0
    for i, block in ipairs(blocks) do
        local blockActive = nebula.ecs.getComponent(block, BlockActive)
        
        if blockActive.active then
            activeBlocks = activeBlocks + 1
            
            if nebula.physics.checkCollision(ball, block) then
                ballSpeed.y = -ballSpeed.y
                blockActive.active = false
                SCORE = SCORE + 10
                break -- Apenas um bloco por frame
            end
        end
    end
    
    -- Verificar vitória
    if activeBlocks == 0 then
        GAMESTATE = "won"
    end
    
    -- Verificar derrota (bola caiu - usando winHeight dinâmico atual)
    local currentWinWidth, currentWinHeight = nebula.window.getSize()
    if ballPos.y >= currentWinHeight then
        GAMESTATE = "lost"
    end
end

function nebula.draw()
    -- Desenhar paddle
    nebula.graphics.draw(paddle)
    
    -- Desenhar bola
    nebula.graphics.draw(ball)
    
    -- Desenhar blocos ativos
    for i, block in ipairs(blocks) do
        local blockActive = nebula.ecs.getComponent(block, BlockActive)
        if blockActive.active then
            nebula.graphics.draw(block)
        end
    end
end