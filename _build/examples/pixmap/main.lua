SetScreenResizable(true)

-- Create a pixmap
local pixmap = CreatePixmap(256, 256)

-- Fill pixmap with gradient
for y = 0, GetPixmapHeight(pixmap) - 1 do
	for x = 0, GetPixmapWidth(pixmap) - 1 do
		local r = math.floor((x / (GetPixmapWidth(pixmap) - 1)) * 255)
		local g = math.floor((y / (GetPixmapHeight(pixmap) - 1)) * 255)
		local b = 128
		WritePixel(pixmap, x, y, RGB(r, g, b))
	end
end

-- Create texture from pixmap
local tex = CreateTextureFromPixmap(pixmap)

-- Free pixmap as texture already contains the data
FreePixmap(pixmap)

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	-- Clear the screen to black
	Cls(RGB(0, 0, 0))

	-- Draw texture covering full screen
	DrawTextureEx(tex, 0, 0, GetScreenWidth(), GetScreenHeight())

	-- Present changes on screen
	RefreshScreen()
end
