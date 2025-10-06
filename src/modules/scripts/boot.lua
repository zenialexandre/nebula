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

local Pos = nebula.ecs.component("Pos", {x = 20; y = 30})
local Vel = nebula.ecs.component("Vel", {x = 0})
local Flag = nebula.ecs.component("Flag", {})

local pos1 = Pos({x = 0; y = 0})
local entity = nebula.ecs.spawn()

nebula.ecs.addComponent(entity, pos1, Pos({x = 210; y = 30}), pos1, Vel:new({x = 1000}), Flag())

local entPos = nebula.ecs.getComponent(entity, Pos)

local entPos, entVel = nebula.ecs.getComponent(entity, Pos, Vel)
print(entPos.x)
print(entPos.y)
print(entVel.x)

print("-------------")

local ent2 = nebula.ecs.spawn()
nebula.ecs.addComponent(ent2, pos1, Pos({x = 210; y = 30}), Vel:new({x = 1000}))
local entPos2, entVel2 = nebula.ecs.getComponent(ent2, Pos, Vel)
print(entPos2.x)
print(entPos2.y)
print(entVel2.x)

local ent3 = nebula.ecs.spawn()
nebula.ecs.addComponent(ent3, Pos())

local ent4 = nebula.ecs.spawn()
nebula.ecs.addComponent(ent4, Vel())

--nebula.ecs.removeComponent(ent2, Vel, Pos)
--nebula.ecs.removeComponent(entity, Pos)
--nebula.ecs.removeComponent(entity, Pos)
--nebula.ecs.removeComponent(entity, Vel)

local test = nebula.ecs.getEntitiesWith(Vel, Pos, Pos)

print("==========================")

local Position = nebula.ecs.component("Position")
local Scale = nebula.ecs.component("Scale")

local ee = nebula.ecs.spawn()

nebula.ecs.addComponent(ee, Position({x = 20; y = 100.5}), Scale())
local eePos = nebula.ecs.getComponent(ee, Position)

print(eePos.x)
print(eePos.y)
eePos.x = 10;
eePos.y = 100;

local eePos2 = nebula.ecs.getComponent(ee, Position)
print(eePos2.x)
print(eePos2.y)

nebula.ecs.print()

--print(nebula.time.tick())
--sleep(3)
--print(nebula.time.getDeltaTime())
--print(nebula.time.tick())
--print(nebula.time.getFPS())
return function()
    print("[LUA] Teste")
end
