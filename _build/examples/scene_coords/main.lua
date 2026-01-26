SetScreenTitle("STEEL Game Engine - Scene Coordinates Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)

-- Create and setup camera
local cam = CreateCamera()
SetCameraRange(cam, 0.01, 100)

-- Create cube
local cube = CreateCubeModel()

local depth = 0
local depth_dir = 1

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	-- Compute aspect ratio based on camera viewport
	SetCameraAspectRatio(cam, (GetScreenWidth() - 64) / (GetScreenHeight() - 256))

	-- We get the scene coords AFTER setting the camera viewport,
	-- to make sure we get screen to scene coordinates
	depth = depth + depth_dir * 0.5 * GetDelta()
	if depth <= 0 or depth >= 1 then depth_dir = depth_dir * -1; depth = Clamp(depth, 0, 1); end
	SetViewport(32, 128, GetScreenWidth() - 64, GetScreenHeight() - 256)
	GetSceneCoords(cam, GetMouseX() - 32, GetMouseY() - 128, depth) -- Subtract viewport offset
	SetEntityPosition(cube, GetCoordX(), GetCoordY(), GetCoordZ())

	TurnEntity(cube, 0, 64 * GetDelta(), 0)

	Cls(RGB(32, 32, 32))
	SetViewport(32, 128, GetScreenWidth() - 64, GetScreenHeight() - 256)
	SetColor(RGB(55, 155, 255))
	DrawRect(0, 0, GetScreenWidth(), GetScreenHeight())
	DrawScene(cam)

	SetViewport(0, 0, GetScreenWidth(), GetScreenHeight())
	SetColor(RGB(255, 255, 255))
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	DrawText(font, "Mouse coords: " .. tostring(GetMouseX()) .. ", " .. tostring(GetMouseY()), 2, 24)
	DrawText(font, "Scene coords: " .. tostring(Int(GetCoordX())) .. ", " .. tostring(Int(GetCoordY())) .. ", " .. tostring(Int(GetCoordZ())), 2, 46)
	RefreshScreen()
end
