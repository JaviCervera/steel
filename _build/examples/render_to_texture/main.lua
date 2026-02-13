SetScreenTitle("STEEL Game Engine -  Render to Texture Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

local light = CreateDirectionalLight()
SetEntityRotation(light, 45, 45, 0)
SetAmbient(RGB(64, 64, 64))

local cam = CreateCamera()
SetEntityPosition(cam, 0, 0, -2)

local cube = CreateCubeModel()

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())
	TurnEntity(cube, 0, 64 * GetDelta(), 0)

	Cls(RGB(255, 255, 255))
	DrawScene(cam)
	SetColor(RGB(0, 0, 0))
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	RefreshScreen()

	-- Capture screen pixmap and apply to texture
	local screen = CreatePixmapFromScreen()
	local tex = CreateTextureFromPixmap(screen)
	FreePixmap(screen)
	FreeTexture(GetMaterialTexture(GetEntityMaterial(cube, 0)))
	SetMaterialTexture(GetEntityMaterial(cube, 0), tex)
end
