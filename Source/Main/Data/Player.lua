local class = require 'middleclass'
Player = class('Player')

Player.someVar = 2

function Player:initialize()

end

-- Called when the object is created.
function Player:OnBegin(deltaTime)
end

-- Called when the object is destroyed.
function Player:OnEnd(deltaTime)

end

-- Called once every frame.
function Player:OnTick(deltaTime)
    local tmp = Instantiate()
    local test = tmp:AddComponent("CameraComponent")
    test.enabled = false

    print("Something")
end
