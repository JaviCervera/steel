NUM_CUBES = 16 * 25

SetScreenTitle("STEEL Game Engine - Fog Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end
local brown = RGB(139, 69, 19)

SetFog(RGB(30, 30, 30), 0, 20)

local cam = CreateCamera()
SetEntityPosition(cam, 0, 0, -7)
SetCameraRange(cam, 1, 5000)

local cubes = {}
local x = -7
local z = NUM_CUBES / 16 * 2 - 2
for i = 1, NUM_CUBES, 2 do
	cubes[i] = CreateCubeModel()
	local mat = GetEntityMaterial(cubes[i], 0)
	SetMaterialDiffuse(mat, brown)
	SetMaterialAmbient(mat, brown)
	SetMaterialFogEnabled(mat, true)
	SetEntityPosition(cubes[i], x, -1.5, z)
	cubes[i+1] = CreateCubeModel()
	local mat2 = GetEntityMaterial(cubes[i+1], 0)
	SetMaterialDiffuse(mat2, brown)
	SetMaterialAmbient(mat2, brown)
	SetMaterialFogEnabled(mat2, true)
	SetEntityPosition(cubes[i+1], x, 1.5, z)
	x = x + 2
	if x > 7 then
		x = -7
		z = z - 2
	end
end

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())

	if IsKeyHit(KEY_SPACE) then
		for _, cube in ipairs(cubes) do
			local mat = GetEntityMaterial(cube, 0)
			SetMaterialFogEnabled(mat, not IsMaterialFogEnabled(mat))
		end
	end

	for _, cube in ipairs(cubes) do
			TurnEntity(cube, 0, 32 * GetDelta(), 0)
	end
	Cls(RGB(30, 30, 30))
	DrawScene(cam)
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	DrawText(font, "Press SPACE to toggle fog", 2, 24)
	RefreshScreen()
end
