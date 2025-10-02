local nebula = require("nebula")

print("[LUA] Achou")

function sleep(sec)
    local s = tonumber(os.clock() + sec)
    while (os.clock() < sec)do
    end
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

print("Pos.x", Pos.x)

print("here?")
local test = Pos()
local test2 = Pos({x = 11})

print("Pos.x", Pos.x)
print("test.x", test.x)
print("test2.x", test2.x)

--printTable(getmetatable(Pos))
printTable(getmetatable(test))

local entity = nebula.ecs.spawn()
-- 1
nebula.ecs.addComponent(entity, Pos({x = 10}))
-- 2
nebula.ecs.addComponent(entity, Pos:new())


nebula.ecs.addComponent(entity, Vel({x = 10}))

--nebula.ecs.print()

--print(nebula.time.tick())
--sleep(3)
--print(nebula.time.getDeltaTime())
--print(nebula.time.tick())
--print(nebula.time.getFPS())
return function()
    print("[LUA] Teste")
end
