if game:IsLoaded() ~= true then game.Loaded:Wait() end

local link = "https://vss.pandauth.com/kv/87894805d08c7b37"
local aotrlink = "https://vss.pandauth.com/kv/1414ee5b666f5d9f"

local usable = link

if game.GameId ~= nil and game.GameId == 4658598196 then usable = aotrlink end

local function checkandrun()
    local ui = gethui()
    if ui == nil then ui = game:GetService("CoreGui") end
    if ui then
        local script = false
        for _, desc in pairs(ui:GetDescendants()) do
            if string.find(string.lower(desc.Name), "cascade") then
                script = true
            end
            if desc.Name == "Base" then
                script = true
            end
        end

        if script == false then

            task.spawn(function()
                loadstring(game:HttpGet(usable))()
            end)

        end 
    end
end


task.delay(0.25, function()

    
    task.spawn(function()
        loadstring(game:HttpGet(usable))()
    end)

    while task.wait(35) do
        checkandrun()
    end

end)
