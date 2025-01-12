print("Hello, world!")

local object = class()
function object:init()
	limb.addEventListener(object, limb.keyboard.key_down)
	limb.addEventListener(object, limb.update)
	limb.addEventListener(object, limb.render)
end

function object:on_key_down(key)
	print('Key pressed!!', key)
end

function object:process(dt)

end

function object:render(pass)

end

local game = {}
function game.process(self, dt)
	
end

function game.render(self, pass)
	
end