R"(

local nebula = require("nebula")

print('call boot.lua')

function printError(msg, layer)
    print((debug.traceback("[LUA] Error: " .. tostring(msg), 1+(layer or 1))))
end

function nebula.boot()
    if (_nebulaArgs ~= nil) then
        if (_nebulaArgs["_gamePath"] ~= nil) then
            require(_nebulaArgs._gamePath:gsub("%.lua$", ""))
        else
            require("nebula.baseScreen")
        end
    end

    require("nebula.time")
    require("nebula.ecs")
    require("nebula.graphics")
    require("nebula.window")
end

function nebula.run()
    if nebula.setup then nebula.setup() end

    nebula.time.tick()

    return function()
        local dt = nebula.time.tick()

        if nebula.update then nebula.update(dt) end

        if nebula.draw then
            nebula.graphics._beginScene()
            nebula.draw()
            nebula.graphics._endScene()
            nebula.window.swapBuffers()
        end
    end
end

return function()
    local run = false

    print('call boot')
    local ok = xpcall(nebula.boot, printError)
    if not ok then return 1 end

    print('call run')
    ok, nRun = xpcall(nebula.run, printError)
    if ok then
        run = true
    end

    print('call run loop')
    while run do
        local ok = xpcall(nRun, printError)
        if not ok then
            return 0
        end
        coroutine.yield()
    end

    return 1
end

--)"