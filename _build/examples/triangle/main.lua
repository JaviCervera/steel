VERTEX_SIZE = 36
INDEX_SIZE = 2

function CreateTriangleMemblock(vertices, indices)
	local memblock = CreateMemblock(7 + #vertices * VERTEX_SIZE + #indices * INDEX_SIZE)
	PokeShort(memblock, 0, 1) -- buffer count
	PokeByte(memblock, 2, 0) -- has 2 uvs
	PokeShort(memblock, 3, #vertices)
	PokeShort(memblock, 5, #indices)
	for v = 0, #vertices - 1 do
		local vertex = vertices[v + 1]
		PokeFloat(memblock, 7 + v * VERTEX_SIZE + 0, vertex[1])
		PokeFloat(memblock, 7 + v * VERTEX_SIZE + 4, vertex[2])
		PokeFloat(memblock, 7 + v * VERTEX_SIZE + 8, vertex[3])
		PokeFloat(memblock, 7 + v * VERTEX_SIZE + 12, vertex[4])
		PokeFloat(memblock, 7 + v * VERTEX_SIZE + 16, vertex[5])
		PokeFloat(memblock, 7 + v * VERTEX_SIZE + 20, vertex[6])
		PokeInt(memblock, 7 + v * VERTEX_SIZE + 24, vertex[7])
		PokeFloat(memblock, 7 + v * VERTEX_SIZE + 28, vertex[8])
		PokeFloat(memblock, 7 + v * VERTEX_SIZE + 32, vertex[9])
	end
	for i = 0, #indices - 1 do
		local index = indices[i + 1]
		PokeShort(memblock, 7 + #vertices * VERTEX_SIZE + i * INDEX_SIZE, index)
	end
	return memblock
end

SetScreenTitle("STEEL Game Engine - Triangle Example")
SetScreenResizable(true)

local font = LoadFont("C:\\Windows\\Fonts\\courbd.ttf", 20)
if not font then font = LoadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20) end

local cam = CreateCamera()
SetEntityPosition(cam, 0, 0, -2)

local vertices = {
	-- x, y, z, nx, ny, nz, color, u, v
	{0, 0.5, 0, 0, 0, -1, RGB(255, 0, 0), 0, 0},
	{0.5, -0.5, 0, 0, 0, -1, RGB(0, 255, 0), 0, 0},
	{-0.5, -0.5, 0, 0, 0, -1, RGB(0, 0, 255), 0, 0},
}
local indices = {0, 1, 2}
local memblock = CreateTriangleMemblock(vertices, indices)
local triangle = CreateModel(memblock)
FreeMemblock(memblock)
SetMaterialLightingEnabled(GetEntityMaterial(triangle, 0), false)
SetMaterialBackfaceCullingEnabled(GetEntityMaterial(triangle, 0), false)

while IsScreenOpened() and not IsKeyHit(KEY_ESC) do
	SetCameraAspectRatio(cam, GetScreenWidth() / GetScreenHeight())
	TurnEntity(triangle, 0, 64 * GetDelta(), 0)

	BeginDrawing(true, true, RGB(0, 0, 64))
	DrawScene(cam)
	DrawText(font, tostring(GetScreenFPS()) .. " FPS", 2, 2)
	EndDrawing()
	RefreshScreen()
end
