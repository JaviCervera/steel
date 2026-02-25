SetScreenTitle("STEEL Game Engine - Viewport Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	-- Clear the screen to blue
	BeginDrawing(true, false, RGB(0, 0, 255))

	-- Set viewport to a square in the center of the screen
	-- Must be done after Cls, as it resets the viewport
	SetViewport(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 100, 200, 200)

	-- Draw red rectangle in whole triangle
	-- The viewport will clip it to the square area defined before
	SetColor(RGB(255, 0, 0))
	DrawRect(0, 0, GetScreenWidth(), GetScreenHeight())

	-- Reset viewport to full screen
	-- Due to a bug in Irrlicht, if it's not reset before drawing text,
	-- the text will appear scaled
	SetViewport(0, 0, GetScreenWidth(), GetScreenHeight())

	-- Draw fps
	SetColor(RGB(255, 255, 255))
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)

	-- Present changes on screen
	EndDrawing()
	RefreshScreen()
end
