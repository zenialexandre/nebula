R"(

local nebula = require("nebula")

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
    require("nebula.event")
    require("nebula.keyboard")
    require("nebula.mouse")
end

function nebula.run()
    if nebula.setup then nebula.setup() end

    nebula.time.tick()

    return function()

        eventName = nebula.event.poll()
        while eventName ~= nil do
            if eventName == "quit" then
                return 0
            end
            eventName = nebula.event.poll()
        end

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

    local ok = xpcall(nebula.boot, printError)
    if not ok then return 1 end

    ok, nRun = xpcall(nebula.run, printError)
    if ok then
        run = true
    end

    while run do
        local ok, quit = xpcall(nRun, printError)
        if quit then
            return 0
        end
        if not ok then
            return 0
        end
        coroutine.yield()
    end

    return 1
end

--)"