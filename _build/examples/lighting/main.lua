SetScreenTitle("STEEL Game Engine - Lighting Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)

-- Create and setup camera
local cam = CreateCamera()
SetEntityPosition(cam, 0, 32, -90)
SetEntityRotation(cam, 16, 0, 0)

-- Setup lighting
SetAmbient(RGB(0, 0, 0))
local lights = {
	CreatePointLight(),
	CreatePointLight(),
	CreatePointLight()
}
SetLightRadius(lights[1], 100)
SetLightDiffuse(lights[1], RGB(255, 0, 0))
SetLightSpecular(lights[1], RGB(255, 55, 55))
SetEntityRotation(lights[1], 0, 0, 0)
SetLightRadius(lights[2], 100)
SetLightDiffuse(lights[2], RGB(0, 255, 0))
SetLightSpecular(lights[2], RGB(55, 255, 55))
SetEntityRotation(lights[2], 0, 120, 0)
SetLightRadius(lights[3], 100)
SetLightDiffuse(lights[3], RGB(0, 0, 255))
SetLightSpecular(lights[3], RGB(55, 55, 255))
SetEntityRotation(lights[3], 0, 240, 0)

-- Create spheres
local spheres = {}
local x = -32
local z = -32
for i = 1, 81 do
	local sphere = CreateSphereModel()
	SetEntityPosition(sphere, x, 0, z)
	SetEntityScale(sphere, 5, 5, 5)
	local mat = GetEntityMaterial(sphere, 0)
	SetMaterialShininess(mat, 2)
	spheres[i] = sphere
	x = x + 8
	if x > 32 then
		x = -32
		z = z + 8
	end
end

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
  SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())

	-- Update lights
	for _, light in ipairs(lights) do
		TurnEntity(light, 0, -32 * GetDelta(), 0)
		SetEntityPosition(light, 0, 0, 0)
		MoveEntity(light, 0, 0, -48)
	end

	Cls(RGB(0, 0, 0))
	DrawScene(cam)
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	RefreshScreen()
end
