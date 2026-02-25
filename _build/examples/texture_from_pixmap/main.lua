SetScreenTitle("STEEL Game Engine - Texture From Pixmap Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

local pixmap = CreatePixmap(128, 128)
for y = 0, GetPixmapHeight(pixmap) - 1 do
    for x = 0, GetPixmapWidth(pixmap) - 1 do
        WritePixel(pixmap, x, y, RGB(Rand(0, 255), Rand(0, 255), Rand(0, 255)))
    end
end

local tex = CreateTextureFromPixmap(pixmap)
FreePixmap(pixmap)

local cam = CreateCamera()
SetEntityPosition(cam, 0, 2, -2)
SetEntityRotation(cam, 45, 0, 0)

local cube = CreateCubeModel()
SetMaterialTexture(GetEntityMaterial(cube, 0), tex)

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
    SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())
		TurnEntity(cube, 30 * GetDelta(), 60 * GetDelta(), 0)

    BeginDrawing(true, true, RGB(255, 255, 255))
		DrawScene(cam)
		SetColor(RGB(0, 0, 0))
    DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
    EndDrawing()
    RefreshScreen()
end
