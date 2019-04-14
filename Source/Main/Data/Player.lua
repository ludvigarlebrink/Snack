Player = {}

Player.prototype = {
    x = 0,
    y = 0
}

Player.mt = {}

function Player:OnAwake(self)

end

function Player:OnTick(self, deltaTime)
    t = Instantiate()
    t2 = Instantiate(t)
    t2:SetLocalPosition(23, 12, 2)
end

function Player.New()
    local t = {}
    setmetatable(t, Player.mt)
    return t;
end

Player.mt.__index = Player.prototype

p2 = Player.New()
Player:OnTick(p2, 0.1)
