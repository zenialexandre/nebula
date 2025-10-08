R"(

local nebula = require("nebula")

function sleep(sec)
    local s = tonumber(os.clock() + sec)
    while (os.clock() < sec)do
    end
end

function debugPos(pos, name, e_x, e_y)
    print(name)
    print("RESULT: ", pos.x == e_x," | x: ", pos.x, " - expected: ", e_x)
    print("RESULT: ", pos.y == e_y," | y: ", pos.y, " - expected: ", e_y)
    print("-----------------------------\n")
end

function printTable(tab)
    for key, value in pairs(tab) do
        print("key: ", key)
        print("value: ", value)
    end
end

require("nebula.time")
require("nebula.ecs")
require("nebula.graphics")
require("nebula.window")

local Sprite = nebula.ecs.component("Sprite")
local Position = nebula.ecs.component("Position")
local Quad = nebula.ecs.component("Quad")

local containerSprite = nebula.graphics.newSprite("resources/textures/container.jpg")

local entity = nebula.ecs.spawn()

nebula.ecs.addComponent(entity, Position({x = 10; y = 10}), Sprite({texture = containerSprite}))
--nebula.ecs.addComponent(entity, Position({x = 200; y = 100}), Quad({width = 500; height = 500}))

nebula.graphics.setBackground(0.07, 0.0, 0.125)

nebula.graphics._beginScene()
nebula.graphics.draw(entity)
nebula.graphics._endScene()
nebula.window.swapBuffers()

nebula.graphics._beginScene()
nebula.graphics.draw(entity)
nebula.graphics._endScene()
nebula.window.swapBuffers()

nebula.graphics._beginScene()
nebula.graphics.draw(entity)
nebula.graphics._endScene()
nebula.window.swapBuffers()

--print(nebula.time.tick())
sleep(3)
--print(nebula.time.getDeltaTime())
--print(nebula.time.tick())
--print(nebula.time.getFPS())
return function()
    print("[LUA] Teste")
end

--)"