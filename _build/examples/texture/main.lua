SetScreenTitle("STEEL Game Engine - Texture Drawing Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end
local tex = LoadTexture("logo_small.png")

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	-- Clear the screen to black
	Cls(RGB(0, 0, 0))

	-- Draw background
	SetColor(RGB(32, 32, 32))
	DrawTextureEx(tex, 0, 0, GetScreenWidth(), GetScreenHeight())

	-- Draw texture
	SetColor(RGB(255, 255, 255))
	DrawTexture(
		tex,
		(GetScreenWidth() - GetTextureWidth(tex)) / 2,
		(GetScreenHeight() - GetTextureHeight(tex)) / 2)

	-- Draw fps
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)

	-- Present changes on screen
	RefreshScreen()
end
