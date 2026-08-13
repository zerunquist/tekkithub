if game:IsLoaded() ~= true then game.Loaded:Wait() end

local function checkandrun()
    local ui = gethui()
    if ui == nil then ui = game:GetService("CoreGui") end
    if ui then
        local script = false
        for _, desc in pairs(ui:GetDescendants()) do
            if string.find(string.lower(desc.Name), "windui") then
                script = true
            end
        end

        if script == false then

            task.spawn(function()
                loadstring(game:HttpGet("https://vss.pandauth.com/kv/1414ee5b666f5d9f"))()
            end)

        end 
    end
end


task.spawn(function()
    task.spawn(function()
        loadstring(game:HttpGet("https://vss.pandauth.com/kv/1414ee5b666f5d9f"))()
    end)

    while task.wait(15) do
        checkandrun()
    end
end)
