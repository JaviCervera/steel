SetScreenTitle("STEEL Game Engine - Material Specular Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

-- Setup lighting
SetAmbient(RGB(0, 0, 0))
local light = CreateDirectionalLight()
SetEntityRotation(light, 30, 40, 0)

-- Create camera
local cam = CreateCamera()
SetEntityPosition(cam, 0, 0, -2)

-- Create sphere
local cube = CreateSphereModel()
local mat = GetEntityMaterial(cube, 0)
SetMaterialAmbient(mat, RGB(255, 128, 0))
SetMaterialDiffuse(mat, RGB(255, 128, 0))
SetMaterialShininess(mat, 0.5)

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	if IsKeyDown(KEY_LEFT) then SetMaterialShininess(mat, Clamp(GetMaterialShininess(mat) - 2 * GetDelta(), 0, 10)) end
	if IsKeyDown(KEY_RIGHT) then SetMaterialShininess(mat, Clamp(GetMaterialShininess(mat) + 2 * GetDelta(), 0, 10)) end
	SetMaterialSpecular(mat, MultiplyColor(RGB(255, 255, 255), GetMaterialShininess(mat) * 0.1 + 0.1))

	SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())

	BeginDrawing(true, true, RGB(0, 0, 0))
	DrawScene(cam)
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	DrawText(font, "Shininess: " .. tostring(GetMaterialShininess(mat)), 2, 24)
	EndDrawing()
	RefreshScreen()
end
