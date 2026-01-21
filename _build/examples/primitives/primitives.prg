var MAX_PRIMITIVES:int = 1000
var PRIM_PLOT:int = 0
var PRIM_LINE:int = 1
var PRIM_RECT:int = 2
var PRIM_SIZE:int = 21
var primitives:int = CreateMemblock(MAX_PRIMITIVES * PRIM_SIZE)
var num_primitives:int = 0

function AddPrimitive(type:int, color:int, x:float, y:float, z:float, t:float)
	PokeByte(primitives, num_primitives * PRIM_SIZE, type)
	PokeInt(primitives, num_primitives * PRIM_SIZE + 1, color)
	PokeFloat(primitives, num_primitives * PRIM_SIZE + 5, x)
	PokeFloat(primitives, num_primitives * PRIM_SIZE + 9, y)
	PokeFloat(primitives, num_primitives * PRIM_SIZE + 13, z)
	PokeFloat(primitives, num_primitives * PRIM_SIZE + 17, t)
	num_primitives = num_primitives + 1
end

function GetPrimitiveType(index:int):int
	var result:int = PeekByte(primitives, num_primitives * index)
end result

function GetPrimitiveColor(index:int):int
	var result:int = PeekInt(primitives, num_primitives * index + 1)
end result

function GetPrimitiveX(index:int):float
	var result:float = PeekFloat(primitives, num_primitives * index + 5)
end result

function GetPrimitiveY(index:int):float
	var result:float = PeekFloat(primitives, num_primitives * index + 9)
end result

function GetPrimitiveZ(index:int):float
	var result:float = PeekFloat(primitives, num_primitives * index + 13)
end result

function GetPrimitiveT(index:int):float
	var result:float = PeekFloat(primitives, num_primitives * index + 17)
end result

function DrawPrimitive(index:int)
	SetColor(GetPrimitiveColor(index))
	if GetPrimitiveType(index) == PRIM_PLOT
		DrawPlot(GetPrimitiveX(index), GetPrimitiveY(index))
	elif GetPrimitiveType(index) == PRIM_LINE
		DrawLine(GetPrimitiveX(index), GetPrimitiveY(index), GetPrimitiveZ(index), GetPrimitiveT(index))
	else
		DrawRect(GetPrimitiveX(index), GetPrimitiveY(index), GetPrimitiveZ(index), GetPrimitiveT(index))
	end
end

function DrawPrimitives()
	var i:int = 0
	for i = 0, num_primitives - 1
		DrawPrimitive(i)
	end
end

function Main()
	while IsScreenOpened()
		// If we are below the limit, add a new primitive with random values
		if num_primitives < MAX_PRIMITIVES
			AddPrimitive(
				Rand(PRIM_PLOT, PRIM_RECT+1), // Type
				RGB(Rand(0, 256), Rand(0, 256), Rand(0, 256)), // Color
				Rand(0, GetScreenWidth()), // Coords
				Rand(0, GetScreenHeight()),
				Rand(0, GetScreenWidth()),
				Rand(0, GetScreenHeight())
			)
		end

		Cls(RGB(0, 0, 0))
		DrawPrimitives()
		RefreshScreen()
	end
end
