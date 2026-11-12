if game:IsLoaded() ~= true then game.Loaded:Wait() end
task.wait(1)


local function execute()
    pcall(function()
        loadstring(game:HttpGet("https://api.luarmor.net/files/v4/loaders/5bfd68232034676923088ca8b6698be7.lua"))()
    end)
end

local function checkexecute()
    local plrs = game:GetService("Players")
    local plr = plrs.LocalPlayer

    if plr then
        if getgenv ~= nil then
            if getgenv().TekkitAccounts ~= nil then
                if getgenv().TekkitAccounts[plr.Name] ~= nil then
                    return true
                end
            end
        end
    end
    return false
end

repeat execute(); task.wait(7) until checkexecute() == true
