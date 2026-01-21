Strict


Class LibFunc
	Method New(name:String, nativeName:String, type: Int, args:Int[])
		Self.name = name
		Self.nativeName = nativeName
		Self.type = type
		Self.args = args
	End
	
	Method Name:String() Property
		Return name
	End
	
	Method NativeName:String() Property
		Return nativeName
	End
	
	Method Type:Int() Property
		Return type
	End
	
	Method Args:Int[]() Property
		Return args
	End
Private
	Field name : String
	Field nativeName : String
	Field type: Int
	Field args : Int[0]
End


Class Lib
	Method AddFunc:Void(realName:String, type:Int, args:Int[])
		Local desName:String = realName
		Local findPos:Int = desName.Find("<")
		If findPos <> -1 Then desName = desName[..findPos]
		functions = functions.Resize(functions.Length() + 1)
		functions[functions.Length() - 1] = New LibFunc(desName, realName, type, args)
	End
	
	Method NumFuncs:Int()
		Return functions.Length()
	End
	
	Method Func:LibFunc(index:Int)
		Return functions[index]
	End
	
	Method Func:LibFunc(name:String)
		For Local f:LibFunc = Eachin functions
			If f.Name = name Then Return f
		Next
		Return Null
	End
Private
	Field functions	: LibFunc[0]
End
