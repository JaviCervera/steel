MAX_PITCH = 80
WORLD_MASK = 1
ROT_SPEED = 15
MOVE_SPEED = 16
SOUND_RADIUS = 25

OpenScreen(GetDesktopWidth(), GetDesktopHeight(), true)
SetMouseVisible(false)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

-- Create player entity
local player = CreateEntity()
SetEntityPosition(player, 0, 2, 0)

-- Create and setup camera
local cam = CreateCamera()
SetEntityParent(cam, player)

-- Setup environment
SetAmbient(RGB(155, 155, 255))
local light = CreatePointLight()
SetEntityRotation(light, 45, 215, 0)

-- Create floor
local floor = CreateCubeModel()
local mat = GetEntityMaterial(floor, 0)
SetMaterialDiffuse(mat, RGB(55, 55, 55))
SetMaterialAmbient(mat, RGB(55, 55, 55))
SetEntityScale(floor, 50, 1, 50)
SetBoxCollider(floor)
SetEntityCollisionMask(floor, WORLD_MASK)
SetEntityPosition(floor, 0, -0.5, 0)

-- Create pillars
local xpos = {-10, -10, 10, 10}
local zpos = {-10, 10, -10, 10}
for i = 1, #xpos do
	local pillar = CreateCubeModel()
	local mat = GetEntityMaterial(pillar, 0)
	SetMaterialDiffuse(mat, RGB(120, 0, 0))
	SetMaterialAmbient(mat, RGB(120, 0, 0))
	SetEntityScale(pillar, 4, 8, 4)
	SetBoxCollider(pillar)
	SetEntityCollisionMask(pillar, WORLD_MASK)
	SetEntityPosition(pillar, xpos[i], 4, zpos[i])
end

-- Create floating sphere
local sphere = CreateSphereModel()
SetMaterialEmissive(GetEntityMaterial(sphere, 0), RGB(155, 155, 255))

-- Play sound
local sound = LoadSound("heli.ogg")
local channel = PlaySound3D(sound, GetEntityX(sphere), GetEntityY(sphere), GetEntityZ(sphere), SOUND_RADIUS, true)

local mx_speed = 0
local my_speed = 0
SetMousePosition(GetScreenWidth()/2, GetScreenHeight()/2)

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())

	-- Player yaw
	TurnEntity(player, 0, mx_speed * ROT_SPEED * GetDelta(), 0)

	-- Camera pitch
	TurnEntity(cam, my_speed * ROT_SPEED * GetDelta(), 0, 0)
	if GetEntityPitch(cam) > MAX_PITCH then SetEntityRotation(cam, MAX_PITCH, GetEntityYaw(cam), 0) end
	if GetEntityPitch(cam) < -MAX_PITCH then SetEntityRotation(cam, -MAX_PITCH, GetEntityYaw(cam), 0) end

	-- Move player
	local movX = 0
	local movZ = 0
	if IsKeyDown(KEY_W) then movZ = MOVE_SPEED * GetDelta() end
	if IsKeyDown(KEY_S) then movZ = -MOVE_SPEED * GetDelta() end
	if IsKeyDown(KEY_A) then movX = -MOVE_SPEED * GetDelta() end
	if IsKeyDown(KEY_D) then movX = MOVE_SPEED * GetDelta() end
	SlideEntity(player, movX, 0, movZ, 1, 1, 1, WORLD_MASK)

	-- Move sphere
	SetEntityPosition(sphere, 0, 3, 0)
	TurnEntity(sphere, 0, 90 * GetDelta(), 0)
	MoveEntity(sphere, 0, 0, -20)
	SetEntityPosition(light, GetEntityX(sphere), GetEntityY(sphere), GetEntityZ(sphere))
	SetChannel3DPosition(channel, GetEntityX(sphere), GetEntityY(sphere), GetEntityZ(sphere))
	SetListener(GetEntityX(cam), GetEntityY(cam), GetEntityZ(cam), GetEntityYaw(player))

	Cls(RGB(0, 0, 64))
	DrawScene(cam)
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	RefreshScreen()

	-- Update mouse speed
	mx_speed = GetMouseX() - GetScreenWidth()/2
	my_speed = GetMouseY() - GetScreenHeight()/2
	SetMousePosition(GetScreenWidth()/2, GetScreenHeight()/2)
end
