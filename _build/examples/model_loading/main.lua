MAX_PITCH = 80
ROT_SPEED = 15
MOVE_SPEED = 32
GRAVITY = -9.81 * 4
WORLD_MASK = 1

OpenScreen(640, 480, true)
SetMouseVisible(false)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

function DrawBanner()
    local text = ":: Parking Lot gile[s] sample scene - by Mikkel Fredborg ::"
		SetColor(RGB(0, 0, 0))
    DrawRect(0, GetScreenHeight() - 22, GetScreenWidth(), 22)
		SetColor(RGB(255, 255, 255))
    DrawText(font, text, (GetScreenWidth() - GetTextWidth(font, text)) / 2, GetScreenHeight() - 25)
end

-- Create player entity
local player = CreateEntity()
SetEntityPosition(player, 32, 16, 32)

-- Create and setup camera
local cam = CreateCamera()
SetEntityParent(cam, player)

-- Load scene
local scene = LoadAnimModel("parking_lot.b3d")
SetAnimModelCollider(scene)
SetEntityCollisionMask(scene, WORLD_MASK)

local mx_speed = 0
local my_speed = 0
SetMousePosition(GetScreenWidth()/2, GetScreenHeight()/2)

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
    -- Player yaw
    TurnEntity(player, 0, mx_speed * ROT_SPEED * GetDelta(), 0)

    -- Camera pitch
    TurnEntity(cam, my_speed * ROT_SPEED * GetDelta(), 0, 0)
    if (GetEntityPitch(cam) > MAX_PITCH) then SetEntityRotation(cam, MAX_PITCH, GetEntityYaw(cam), 0) end
    if (GetEntityPitch(cam) < -MAX_PITCH) then SetEntityRotation(cam, -MAX_PITCH, GetEntityYaw(cam), 0) end

    -- Move player
    local movX = 0
    local movZ = 0
    if (IsKeyDown(KEY_W)) then movZ = MOVE_SPEED * GetDelta() end
    if (IsKeyDown(KEY_S)) then movZ = -MOVE_SPEED * GetDelta() end
    if (IsKeyDown(KEY_A)) then movX = -MOVE_SPEED * GetDelta() end
    if (IsKeyDown(KEY_D)) then movX = MOVE_SPEED * GetDelta() end
		SlideEntity(player, movX, GRAVITY * GetDelta(), movZ, 2, 16, 2, WORLD_MASK)

    BeginDrawing(true, true, RGB(0, 0, 0))
		DrawScene(cam)
		SetColor(RGB(255, 255, 255))
    DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
    DrawBanner()
    EndDrawing()
    RefreshScreen()

    -- Update mouse speed
    mx_speed = GetMouseX() - GetScreenWidth()/2
    my_speed = GetMouseY() - GetScreenHeight()/2
    SetMousePosition(GetScreenWidth()/2, GetScreenHeight()/2)
end
