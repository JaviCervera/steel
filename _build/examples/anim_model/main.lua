SetScreenTitle("STEEL Game Engine - Anim Model Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

SetAmbient(RGB(75, 75, 75))

local cam = CreateCamera()
SetEntityPosition(cam, 0, 30, -75)

local dwarf = LoadAnimModel("dwarf.x")

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())

	Cls(RGB(0, 0, 64))
	DrawScene(cam)
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	RefreshScreen()
end
