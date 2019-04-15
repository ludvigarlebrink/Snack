local class = require 'middleclass'
Player = class('Player')
Player.someVar = 2

function Player:initialize()
    print('TestClass Created!')
    self.someVar = math.random(60, 90)
end

-- Called when the object is created.
function Player:OnBegin(deltaTime)
    print(self.someVar)
end

-- Called when the object is destroyed.
function Player:OnEnd(deltaTime)
    print(self.someVar)
end

-- Called once every frame.
function Player:OnTick(deltaTime)
    print(self.someVar)
end
