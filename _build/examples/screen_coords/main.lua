SetScreenTitle("STEEL Game Engine - Screen Coordinates Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

-- Create and setup camera
local cam = CreateCamera()
SetEntityPosition(cam, 0, 2, -2)
SetEntityRotation(cam, 45, 0, 0)

-- Create cube
local cube = CreateCubeModel()

local dir_x = 1

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	-- Compute aspect ratio based on camera viewport
	SetCameraAspectRatio(cam, (GetScreenWidth() - 64) / (GetScreenHeight() - 256))
	TurnEntity(cube, 0, 64 * GetDelta(), 0)
	TranslateEntity(cube, dir_x * GetDelta(), 0, 0)
	if GetEntityX(cube) <= -3 or GetEntityX(cube) >= 3 then
		SetEntityPosition(cube, Clamp(GetEntityX(cube), -3, 3), GetEntityY(cube), GetEntityZ(cube))
		dir_x = dir_x * -1
	end

	-- We get the screen coords BEFORE setting the camera viewport,
	-- to make sure we get screen coordinates
	GetScreenCoords(cam, GetEntityX(cube), GetEntityY(cube), GetEntityZ(cube))

	BeginDrawing(true, true, RGB(32, 32, 32))
	SetViewport(32, 128, GetScreenWidth() - 64, GetScreenHeight() - 256)
	SetColor(RGB(55, 155, 255))
	DrawRect(0, 0, GetScreenWidth(), GetScreenHeight())
	DrawScene(cam)

	SetViewport(0, 0, GetScreenWidth(), GetScreenHeight())
	SetColor(RGB(255, 255, 255))
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)

	SetColor(RGB(64, 64, 64))
	local text = "This is a cube"
	DrawText(font, text, GetCoordX() - GetTextWidth(font, text) / 2, GetCoordY() - GetTextHeight(font, text) / 2)
	EndDrawing()
	RefreshScreen()
end
