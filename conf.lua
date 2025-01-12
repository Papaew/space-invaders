function limb:conf(t)
	t.app.version = {0, 0, 0}
	t.app.codename = 'InDev'
	t.app.entrypoint = 'main.lua'

	t.modules.audio = true
	t.modules.video = true
	t.modules.camera = true
	t.modules.mouse = true
	t.modules.keyboard = true
	t.modules.window = true

	t.window.renderer = 'direct3d11' -- direct3d|direct3d12|opengl|opengles2|vulkan|metal|gpu
	t.window.title = 'Test window'
	t.window.size = {1280, 720}
	t.window.minsize = {240, 320}
	-- t.window.position = {0, 0}
	t.window.resizeable = true
	t.window.borderless = false
	t.window.centered = true
	t.window.displayindex = 1
end
