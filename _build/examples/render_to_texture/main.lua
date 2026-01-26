function GetPixmapRect(pixmap, x, y, w, h)
	local result = CreatePixmap(w, h)
	for py = 0, h - 1 do
		for px = 0, w - 1 do
			local color = ReadPixel(pixmap, x + px, y + py)
			WritePixel(result, px, py, color)
		end
	end
	return result
end

SetScreenTitle("STEEL Game Engine -  Render to Texture Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)

--local tex = CreateRenderTexture(128, 128)

local cam = CreateCamera()
SetEntityPosition(cam, 0, 0, -2)

local cube = CreateCubeModel()

local x_pos = 0
local y_pos = 0
local x_dir = 1
local y_dir = 1

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())
	TurnEntity(cube, 0, 64 * GetDelta(), 0)
	x_pos = x_pos + x_dir * 64 * GetDelta()
	y_pos = y_pos + y_dir * 64 * GetDelta()
	if x_pos <= 0 or x_pos >= 31 then x_pos = Clamp(x_pos, 0, 31); x_dir = x_dir * -1 end
	if y_pos <= 0 or y_pos >= 31 then y_pos = Clamp(y_pos, 0, 31); y_dir = y_dir * -1 end

	-- Draw 2D pixmap and render to texture
	Cls(RGB(255, 0, 0))
	SetColor(RGB(255, 255, 255))
	DrawRect(x_pos, y_pos, 32, 32)
	SetColor(RGB(255, 0, 0))
	DrawLine(x_pos, y_pos, x_pos + 32, y_pos + 32)
	DrawLine(x_pos + 32, y_pos, x_pos, y_pos + 32)
	local screen = CreatePixmapFromScreen()
	local pixmap = GetPixmapRect(screen, 0, 0, 64, 64)
	FreePixmap(screen)
	local tex = CreateTextureFromPixmap(pixmap)
	FreePixmap(pixmap)
	FreeTexture(GetMaterialTexture(GetEntityMaterial(cube, 0)))
	SetMaterialTexture(GetEntityMaterial(cube, 0), tex)

	Cls(RGB(0, 0, 64))
	DrawScene(cam)
	SetColor(RGB(255, 255, 255))
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	RefreshScreen()
end
