if game:IsLoaded() ~= true then game.Loaded:Wait() end

local function checkgenv(string)
    if getgenv ~= nil and getgenv().TCFG ~= nil and getgenv().TCFG[string] ~= nil then return getgenv().TCFG[string] end
end

local function newcloneref(instance)
    if instance == nil then return nil end
    if cloneref ~= nil then
        local ok, cloned = pcall(cloneref, instance)
        if ok and cloned ~= nil then return cloned end
    end
    return instance
end

local s = {
    wp = newcloneref(game:GetService("Workspace")),
    rs = newcloneref(game:GetService("ReplicatedStorage")),
    gui = newcloneref(game:GetService("GuiService")),
    plrs = newcloneref(game:GetService("Players")),
    startergui = newcloneref(game:GetService("StarterGui")),
    vip = newcloneref(game:GetService("VirtualInputManager")),
    uip = newcloneref(game:GetService("UserInputService")),
}

local a = {
    target = 'Titan',
    nape = nil,
    titan = nil,
    titanroot = nil,
}

s.startergui:SetCore("SendNotification", {
    Title = "Tekkit Hub", 
    Text = "Execution Check."
});



local postrem = nil
local function fire(...)

    local args = {...}

    if postrem ~= nil and typeof(postrem) == "Instance" and postrem:IsA("RemoteEvent") then
        postrem:FireServer(table.unpack(args))
    else
        local ass = s.rs:FindFirstChild("Assets")
        local remotes = ass and ass:FindFirstChild("Remotes")
        local rem = remotes and remotes:FindFirstChild("POST")

        if rem then
            postrem = rem
            rem:FireServer(table.unpack(args))
        end
    end

end

local invokerem = nil
local function invoke(...)
    
    local args = {...}

    if invokerem ~= nil and typeof(invokerem) == "Instance" and invokerem:IsA("RemoteFunction") then
        return invokerem:InvokeServer(table.unpack(args))
    else
        local ass = s.rs:FindFirstChild("Assets")
        local remotes = ass and ass:FindFirstChild("Remotes")
        local rem = remotes and remotes:FindFirstChild("GET")

        if rem then
            invokerem = rem
            return rem:InvokeServer(table.unpack(args))
        end
    end

end

local data
local lastdatacheck = os.clock()
local function getdata()
    if os.clock() - lastdatacheck >= 5 then
        lastdatacheck = os.clock()

        local newdata = invoke("Functions", "Settings", "Music", math.random(1, 10))
        if newdata ~= nil and newdata.Slots ~= nil then
            data = newdata
        end
    end

    return data
end

local function presskey(keycode)
    if not s.vip then return end
    s.vip:SendKeyEvent(true, keycode, false, game)
    task.wait(0.1)
    s.vip:SendKeyEvent(false, keycode, false, game)
end

local function click(x, y)
    if s.gui.MenuIsOpen == false then
        if s.uip.TouchEnabled then
            s.vip:SendTouchEvent(x or 1, y or 1, 1, true, false, game)
            s.vip:SendTouchEvent(x or 1, y or 1, 1, false, false, game)
        end
        s.vip:SendMouseButtonEvent(x or 1, y or 1, 0, true, game, 0)
        s.vip:SendMouseButtonEvent(x or 1, y or 1, 0, false, game, 0)
    end
end

local function pressgui(button)
    s.gui.SelectedObject = button

    if s.gui.SelectedObject == button then
        presskey(Enum.KeyCode.Return)
    end
end

local function defineplayer()
    local plr = s.plrs.LocalPlayer
    local char = plr and plr.Character
    local root = char and char:FindFirstChild("HumanoidRootPart")
    local hum = char and char:FindFirstChildOfClass("Humnaoid")
    local rig = char and char:FindFirstChild("Rig_" .. plr.Name)

    return plr, char, root, hum, rig
end

local function definetitans()
    local titansfolder = s.wp:FindFirstChild("Titans")
    local titans = {}

    if titansfolder then
        for _, titan in pairs(titansfolder:GetChildren()) do
            if titan:IsA("Model") and titan:FindFirstChildOfClass("Humanoid") then
                table.insert(titans, titan)
            end
        end
    end


    return titans
end

local function nearestTitan()
    
    local titans = definetitans()
    local nearest = math.huge

    local _, _, root = defineplayer()

    if root and titans then
        
        for _, titan in pairs(titans) do
            local titanroot = titan:FindFirstChild("HumanoidRootPart")



            if titanroot then
                local dis = (root.Position - titanroot.Position).Magnitude
                if dis < nearest then
                    nearest = dis


                    local hitboxes = titan:FindFirstChild("Hitboxes")
                    local hit = hitboxes and hitboxes:FindFirstChild("Hit")
                    local nape = hit and hit:FindFirstChild("Nape")

                    if nape then
                        a.nape = nape
                    end

                    a.titanroot = titanroot
                    a.titan = titan

                end
            end


        end
    end
end

local function getstation()
    local tallest = 0
    local _, _, root = defineplayer()
    local returning = nil
    if root then
        for _, desc in pairs(s.wp:GetDescendants()) do
            if desc.Name == "GasTanks" then
                local refill = desc:FindFirstChild("Refill")
                if refill then
                    local y = refill.Position.Y
                    if y >= 0 and y >= tallest then
                        tallest = y
                        returning = refill
                    end
                end
            end
        end
    end

    return returning
end

local lastreload = os.clock()
local lasthit = os.clock()
local function hitnormal()
    
    if (os.clock() - lasthit >= 0.9) and (os.clock() - lastreload >= 1) then
        lasthit = os.clock()


        local _, _, root = defineplayer()
        nearestTitan()



        if a.nape and a.titanroot and a.titan and root then 

            local dis = (root.Position - a.titanroot.Position).Magnitude
            if dis <= 400 then
                click(1,1)
                fire("Attacks", "Slash", true)
                task.wait(0.1)
                for x = 1, 3 do
                    fire("Hitboxes", "Register", a.nape, (math.random(10, 100) / 100) )
                end
                task.wait(0.1)
                fire("Attacks", "Slash", false)
            end
        end
    end

end

local function noclip()
    local _, char = defineplayer()
    if char then
        for _, part in pairs(char:GetChildren()) do
            if part:IsA("BasePart") then
                part.CanCollide = false
            end
        end
    end
end

local lastfullreloadremote = os.clock()
local lasthover = os.clock()
local function hover()
    
    if os.clock() - lasthover >= 0.1 then
        lasthover = os.clock()
        local plr, char, root = defineplayer()
        nearestTitan()

        if root and a.titanroot and a.titan then
            
            local finalpos = a.titanroot.Position + Vector3.new(0, 200, 0)

            if a.target == "Station" then
                local station = getstation()
                if station then
                    finalpos = station.Position + Vector3.new(0, 10, 0)

                    local dis = (root.Position - finalpos).Magnitude
                    local dir = (finalpos - root.Position).Unit

                    local finalspeed = dis and dir and math.clamp(dis * 10, 0, 900)
                    if finalspeed then
                        root.AssemblyLinearVelocity = dir * finalspeed
                        task.spawn(noclip)

                        if os.clock() - lastfullreloadremote >= 4 then
                            lastfullreloadremote = os.clock()
                            invoke("Attacks", "Reload", station)
                        end

                        return
                    end

                end
            end


                    
                    local toTarget = finalpos - root.Position
                    local flat = Vector3.new(toTarget.X, 0, toTarget.Z)
                    local dist = flat.Magnitude
                    local vertical = Vector3.new(0, (finalpos.Y - root.Position.Y) * 6, 0)
                    local vel

                    if dist > 0.01 then
                        local radial = flat / dist
                        local tangent = Vector3.new(-radial.Z, 0, radial.X)
                        vel = tangent * 650 + radial * ((dist - 45) * 6) + vertical
                    else
                        vel = vertical
                    end

                    if vel.X ~= vel.X or vel.Y ~= vel.Y or vel.Z ~= vel.Z then
                        vel = vertical
                    end

                    local cap = 900
                    if vel.Magnitude > cap then
                        vel = (cap > 0) and (vel.Unit * cap) or Vector3.zero
                    end
                    root.AssemblyLinearVelocity = vel
                    task.spawn(noclip)
        end
    end
end


local lastscenecheck = os.clock()
local function cutscene()
    
    if os.clock() - lastscenecheck >= 2 then
        lastscenecheck = os.clock()

        local plr = defineplayer()
        local plrgui = plr and plr:FindFirstChild("PlayerGui")
        local int = plrgui and plrgui:FindFirstChild("Interface")
        local skip = int and int:FindFirstChild("Skip")

        if skip and skip.Visible == true then
            presskey(Enum.KeyCode.E)
        end
    end

end

local function checkreturn()
    getdata()

    if data ~= nil and data.Statistics ~= nil then
        local returnamount = checkgenv("LobbyReturnAmount") or 15

        local type = s.wp:GetAttribute("Type")
        local total = type and data.Statistics[type] and data.Statistics[type].Total
        if total then
            if total % returnamount == 0 then
                return true
            end
        end
    end
    return false
end

local lastretrycheck = os.clock()
local function checkretry()
    
    if os.clock() - lastretrycheck >= 2 then
        lastretrycheck = os.clock()


        local plr = defineplayer()
        local plrgui = plr and plr:FindFirstChild("PlayerGui")
        local int = plrgui and plrgui:FindFirstChild("Interface")
        local rewards = int and int:FindFirstChild("Rewards")
        if rewards and rewards.Visible == true then

            local main = rewards:FindFirstChild("Main")
            local info = main and main:FindFirstChild("Info")
            local main2 = info and info:FindFirstChild("Main")
            local buttons = main2 and main2:FindFirstChild("Buttons")

            local retry = buttons and buttons:FindFirstChild("Retry")
            local retrytext = retry and retry:FindFirstChild("Title")
            local leave = buttons and buttons:FindFirstChild("Leave_2")

            if checkreturn() == true then pressgui(leave); return end

            if retry and retrytext and not string.find(string.lower(retrytext.Text), "starting") then
                pressgui(retry)
            end
            
        end

    end

end

local function reload()
    
    if (os.clock() - lastreload >= 2) and (os.clock() - lastfullreloadremote >= 6) then
        lastreload = os.clock()

        invoke("Blades", "Reload")

    end

end

local lastfullreload = os.clock()
local function fullreload()
    
    if os.clock() - lastfullreload >= 2 then
        lastreload = os.clock()

        a.target = "Station"

    end

end

local lastreloadcheck = os.clock()
local function checkreload()
    
    if os.clock() - lastreloadcheck >= 0.5 then
        lastreloadcheck = os.clock()

        local _, _, _, _, rig = defineplayer()
        local lefthand = rig and rig:FindFirstChild("LeftHand")
        local blade = lefthand and lefthand:FindFirstChild("Blade_1")

        if blade then
            
            if blade.Transparency == 1 then

                local sets = 3
                local torso
                for _, chi in pairs(rig:GetChildren()) do
                    if chi:FindFirstChild("Left_3") then torso = chi; break end
                end

                if torso and torso:FindFirstChild("Left_3") and torso:FindFirstChild("Left_3"):GetAttribute("Used") then sets = 0 end

                if sets == 0 then
                    fullreload()
                    return
                else
                    reload()
                end
            end

        end
        



        a.target = "Titan"
    end
end


local exec = false
local function autoexec()
    if exec == false then
        exec = true


        local key = script_key or ""

        if getgenv().TCFG then
            
            local function serialize(value)
                local valueType = typeof(value)

                if valueType == "string" then
                    return string.format("%q", value)

                elseif valueType == "number" or valueType == "boolean" then
                    return tostring(value)

                elseif valueType == "table" then
                    local parts = {"{"}

                    for k, v in pairs(value) do
                        local keyString

                        if type(k) == "string" and k:match("^[%a_][%w_]*$") then
                            keyString = k
                        else
                            keyString = "[" .. serialize(k) .. "]"
                        end

                        parts[#parts + 1] =
                            keyString .. "=" .. serialize(v) .. ","
                    end

                    parts[#parts + 1] = "}"
                    return table.concat(parts)

                end

                return "nil"
            end

            local config = serialize(getgenv().TCFG)

            local code = [[
            
                script_key = %q
                getgenv().TCFG = %s
                loadstring(game:HttpGet("https://api.luarmor.net/files/v4/loaders/5bfd68232034676923088ca8b6698be7.lua"))()

            ]]

            local script = string.format(code, key, config)

            queue_on_teleport(script)

        else

            local code = [[

                script_key = "%s"
                loadstring(game:HttpGet("https://api.luarmor.net/files/v4/loaders/5bfd68232034676923088ca8b6698be7.lua"))()

            ]]

            local script = string.format(code, key)

            queue_on_teleport(script)

        end

    end
end

if checkgenv("AutoExecute") then
    autoexec()
end

local function sendstats()
    task.spawn(function()
        if game.GameId ~= 4658598196 then
            return
        end

        local KEY = script_key or ""
        local URL = "https://tekkitstattracking-production.up.railway.app/api/stats"


        local data
        for _ = 1, 60 do
            data = getdata()
            if type(data) == "table" and next(data) ~= nil then break end
            task.wait(1)
        end

        local slot = data.Slots[data.Current_Slot]
        if not slot or not slot.Currency or not slot.Progression then
            return
        end

        local player = defineplayer()
        local inv = slot.Inventory
        local banned = data.Disabled ~= nil

        if KEY ~= "" and player and inv then
            pcall(request, {
                Url = URL,
                Method = "POST",
                Headers = { ["Content-Type"] = "application/json" },
                Body = s.http:JSONEncode({
                    key = KEY,
                    accounts = {{
                        playerName = player.Name,
                        slot = tostring(data.Current_Slot),
                        level = slot.Progression.Level,
                        gems = slot.Currency.Gems,
                        gold = slot.Currency.Gold,
                        status = banned and "Banned" or "Safe",
                        banned = banned,
                        inventory = inv and inv.Items or nil,
                        families = inv and inv.Families or nil,
                    }},
                }),
            })
        end

    end)
end

if checkgenv("StatTracking") then
    sendstats()
end



task.spawn(function()
    while true do
    
        task.spawn(hover)
        task.spawn(hitnormal)
        task.spawn(checkretry)
        task.spawn(checkreload)
        task.spawn(cutscene)

        task.wait(0.1)
    end
end)






