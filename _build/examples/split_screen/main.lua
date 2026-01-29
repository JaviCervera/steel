SetScreenTitle("STEEL Game Engine -  Split Screen Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

-- Create first camera
local cam = CreateCamera()
SetEntityPosition(cam, 1, 2, -2)
SetEntityRotation(cam, 45, 0, 0)

-- Create second camera
local cam2 = CreateCamera()
SetEntityPosition(cam2, -1, 2, -2)
SetEntityRotation(cam2, 45, 0, 0)

-- Create cube
local cube = CreateCubeModel()

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())
	SetCameraAspectRatio(cam2, GetScreenWidth() / GetScreenHeight())
	TurnEntity(cube, 32 * GetDelta(), 64 * GetDelta(), 0)

	Cls(RGB(0, 0, 128))

	SetViewport(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight() / 2)
	SetColor(RGB(128, 0, 0))
	DrawRect(0, 0, GetScreenWidth(), GetScreenHeight())
	DrawScene(cam)

	SetViewport(0, GetScreenHeight() / 2, GetScreenWidth() / 2, GetScreenHeight() / 2)
	SetColor(RGB(0, 128, 0))
	DrawRect(0, 0, GetScreenWidth(), GetScreenHeight())
	DrawScene(cam2)

	SetViewport(0, 0, GetScreenWidth(), GetScreenHeight())
	SetColor(RGB(255, 255, 255))
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	RefreshScreen()
end
