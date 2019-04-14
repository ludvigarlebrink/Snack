class = require 'Data/middleclass'

Fruit = class('Fruit')

function Fruit:initialize(sweetness)
    self.sweetness = sweetness
end

Fruit.static.sweetness_threshold = 5

function Fruit:isSweet()
    print(self.sweetness > Fruit.sweetness_threshold)
end

Lemon = class('Lemon', Fruit)

function Lemon:initialize()
    Fruit.initialize(self, 4)
    print(true)
end

some = Lemon:new(32)
some:isSweet()
