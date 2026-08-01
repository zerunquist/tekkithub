if game:IsLoaded() ~= true then game.Loaded:Wait() end

local function checkandrun()
    local ui = gethui()
    if ui == nil then ui = game:GetService("CoreGui") end
    if ui then
        local script = false
        for _, desc in pairs(ui:GetDescendants()) do
            if string.find(string.lower(desc.Name), "cascade") then
                script = true
            end
        end

        if script == false then

            pcall(function()
                loadstring(game:HttpGet("https://vss.pandauth.com/kv/c4fcded61b9f0d8f"))()
            end)

        end 
    end
end


task.delay(0.25, function()

    
    pcall(function()
        loadstring(game:HttpGet("https://vss.pandauth.com/kv/c4fcded61b9f0d8f"))()
    end)

    while task.wait(35) do
        checkandrun()
    end

end)
