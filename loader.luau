if game:IsLoaded() ~= true then -- good
    game.Loaded:Wait()
end

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

            loadstring(game:HttpGet("https://vss.pandauth.com/kv/efb7d9e463f01a3a"))()

        end 
    end
end


task.delay(0.25, function()

    
    loadstring(game:HttpGet("https://vss.pandauth.com/kv/efb7d9e463f01a3a"))()

    while task.wait(20) do
        checkandrun()
    end

end)
