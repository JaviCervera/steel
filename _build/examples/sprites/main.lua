SetScreenTitle("STEEL Game Engine - Sprites Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

local tex = LoadTexture("logo_small.png")

local cam = CreateCamera()
SetEntityRotation(cam, 30, 0, 0)

for z = -8, 8, 2 do
    for x = -8, 8, 2 do
        local tree = CreateSprite(tex)
        SetEntityPosition(tree, x, 0, z)
        SetSpriteSize(tree, 2, 2)
    end
end

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
		SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())

    TurnEntity(cam, 0, 15 * GetDelta(), 0)
    SetEntityPosition(cam, 0, 0, 0)
    MoveEntity(cam, 0, 0, -8)

		Cls(RGB(0, 0, 0))
    DrawScene(cam)
		DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
    RefreshScreen()
end
