SetScreenTitle("STEEL Game Engine - Box Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)

-- Create and setup camera
local cam = CreateCamera()
SetEntityPosition(cam, 0, 2, -2)
SetEntityRotation(cam, 45, 0, 0)

-- Create cube
local cube = CreateCubeModel()
local mat = GetEntityMaterial(cube, 0)
SetMaterialTexture(mat, LoadTexture("logo_small.png"))
SetMaterialLightmap(mat, LoadTexture("lightmap.png"))

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())
	TurnEntity(cube, 0, 64 * GetDelta(), 0)

	Cls(RGB(0, 0, 0))
	DrawScene(cam)
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	RefreshScreen()
end
