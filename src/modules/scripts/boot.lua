R"(

local nebula = require("nebula")

function printError(msg, layer)
    print((debug.traceback("[LUA] Error: " .. tostring(msg), 1+(layer or 1))))
end

local function isAbsolute(path)
    if path:match("^%a:[/\\]") then return true end
    if path:sub(1, 1) == "/" then return true end
    return false
end

local function joinPath(base, rel)
    if base:sub(-1) ~= "/" and base:sub(-1) ~= "\\" then
        base = base .. "/"
    end
    return (base .. rel):gsub("\\", "/")
end

local function safeRequire(path)
    local ok, err = pcall(function()
        local clean = path:gsub("\\", "/"):gsub("%.lua$", "")
        local absPath = clean

        if not isAbsolute(clean) and _nebulaArgs and _nebulaArgs._exePath then
            local exeDir = _nebulaArgs._exePath:gsub("[^/\\]+$", "")
            absPath = joinPath(exeDir, clean)
        end

        local luaFile = absPath .. ".lua"
        local chunk, loadErr = loadfile(luaFile)
        if not chunk then
            error("Could not load file: " .. luaFile .. " [" .. tostring(loadErr) .. "]")
        end
        return chunk()
    end)

    if not ok then
        printError(err)
    end
    return ok
end

function nebula.boot()
    if (_nebulaArgs ~= nil) then
        if (_nebulaArgs["_gamePath"] ~= nil) then
            local gamePath = _nebulaArgs._gamePath
            if safeRequire(gamePath) then
                local gameDir = gamePath:gsub("\\", "/"):gsub("[^/]+$", "")
                if not isAbsolute(gameDir) and _nebulaArgs and _nebulaArgs._exePath then
                    local exeDir = _nebulaArgs._exePath:gsub("[^/\\]+$", "")
                    gameDir = joinPath(exeDir, gameDir)
                end

                if gameDir:sub(-1) ~= "/" then gameDir = gameDir .. "/" end

                package.path = gameDir .. "?.lua;" .. gameDir .. "?/init.lua;" .. package.path
            else
                require("nebula.baseScreen")
            end
        else
            require("nebula.baseScreen")
        end
    else
        require("nebula.baseScreen")
    end

    require("nebula.time")
    require("nebula.ecs")
    require("nebula.graphics")
    require("nebula.window")
    require("nebula.event")
    require("nebula.keyboard")
    require("nebula.mouse")
    require("nebula.physics")
    require("nebula.audio")
end

function nebula.error()
    eventName = nebula.event.poll()
    while eventName ~= nil do
        if eventName == "quit" then
            return 0
        end
        eventName = nebula.event.poll()
    end
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

        nebula.keyboard._resetKeysReleased()
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
            nRun = nebula.error
        end
        coroutine.yield()
    end

    return 1
end

--)"