local nebula = require("nebula")

print("[LUA] Achou")

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

local Pos = nebula.ecs.component("Pos", {x = 20; y = 30})
local Vel = nebula.ecs.component("Vel", {x = 0})

local pos1 = Pos()
local pos2 = Pos({x = 100})
local pos3 = Pos({x = 50; y = 50})

local pos4 = Pos:new()
local pos5 = Pos:new({x = 100})
local pos6 = Pos:new({x = 50; y = 50})

debugPos(pos1, "POS 1", 20, 30)
debugPos(pos2, "POS 2", 100, 30)
debugPos(pos3, "POS 3", 50, 50)
debugPos(pos4, "POS 4", 20, 30)
debugPos(pos5, "POS 5", 100, 30)
debugPos(pos6, "POS 6", 50, 50)

--nebula.ecs.print()

--print(nebula.time.tick())
--sleep(3)
--print(nebula.time.getDeltaTime())
--print(nebula.time.tick())
--print(nebula.time.getFPS())
return function()
    print("[LUA] Teste")
end
