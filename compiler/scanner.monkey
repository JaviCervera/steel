Strict

Private
Import tokenstream


Public


Class ScriptVar
	Method New(name:String, type:Int, offset:Int)
		Self.name = name
		Self.type = type
		Self.offset = offset
	End

	Method Name:String() Property
		Return name
	End

	Method Type:Int() Property
		Return type
	End

	Method Offset:Int() Property
		Return offset
	End
Private
	Field name : String
	Field type : Int
	Field offset : Int
End


Class ScriptFunc
	Method New(name:String, type:Int, args:Int[])
		Self.name = name
		Self.type = type
		Self.args = args
	End

	Method Name:String() Property
		Return name
	End

	Method Type:Int() Property
		Return type
	End

	Method Args:Int[]() Property
		Return args
	End

	#Rem
	Method LocalId:Int(name:String)
		For Local localIndex:Int = 0 Until Locals.Length()
			If Locals[localIndex] = name Then Return localIndex
		Next
		Return -1
	End
	#End

	Method GetLocal:ScriptVar(name:String)
		For Local l:ScriptVar = Eachin Locals
			If l.Name = name Then Return l
		Next
		Return Null
	End

	Field Locals	: ScriptVar[0]
	Field Offset	: Int
	Field ReturnVar	: String
Private
	Field name		: String
	Field type		: Int
	Field args		: Int[0]
End


Class Scanner
	Method New(tokens:Token[])
		stream = New TokenStream(tokens)
	End

	Method ScanDefs:Void()
		'Move to the beginning of the stream
		stream.Seek(0)

		'Check for global and function declarations
		Local block:Int = 0
		Local token:Token = stream.NextToken
		While stream.HasNext()
			'Count blocks
			If token.IsControl() Or token.Type = TOK_FUNCTION
				block += 1
			Elseif token.Type = TOK_END
				block = Max(block - 1, 0)
			End

			If token.Type = TOK_VAR
				If stream.Peek().Type = TOK_ID And block = 0
					Local name:String = stream.NextToken.Data
					stream.Skip(1) ' Skip ':'
					Local type:Int = stream.NextToken.Type
					globals = globals.Resize(globals.Length() + 1)
					globals[globals.Length() - 1] = New ScriptVar(name, type, stream.Pos + 1)
				End
			Elseif token.Type = TOK_FUNCTION
				Local name:String = stream.NextToken.Data

				'Parse params
				Local paramTypes:Int[] = New Int[0]
				stream.Skip(1)	'Skip '('
				While stream.HasNext() And stream.Peek().Type <> TOK_CLOSEPAREN
					If stream.Peek().Type = TOK_ID Then stream.Skip(1) 'Skip name
					If stream.Peek().Type = TOK_COLON Then stream.Skip(1) 'Skip colon
					paramTypes = paramTypes.Resize(paramTypes.Length + 1)
					If stream.Peek().IsType()
						paramTypes[paramTypes.Length - 1] = stream.NextToken.Type
					Else
						paramTypes[paramTypes.Length - 1] = TOK_VOID
					End
					If stream.HasNext() And stream.Peek().Type = TOK_COMMA Then stream.Skip(1)	'Skip comma
				Wend
				If stream.HasNext() Then stream.Skip(1)	'Skip ')'

				'Parse return type
				Local type: Int = TOK_VOID
				If stream.Peek().Type = TOK_COLON
					stream.Skip(1) 'Skip ':'
					type = stream.NextToken.Type
				End
				functions = functions.Resize(functions.Length + 1)
				functions[functions.Length - 1] = New ScriptFunc(name, type, paramTypes)
			End

			'Get next token
			If stream.HasNext() Then token = stream.NextToken
		Wend
	End

	Method ScanLocals:Void(pos:Int)
		'Reset locals
		locals = New ScriptVar[0]

		'Seek position in stream
		stream.Seek(pos)

		'Scan arguments
		If stream.Peek().Type = TOK_OPENPAREN Then stream.Skip(1)	'Skip (
		While stream.HasNext() And stream.Peek().Type <> TOK_CLOSEPAREN
			If stream.Peek().Type = TOK_ID
				Local name:String = stream.NextToken.Data
				If stream.Peek().Type = TOK_COLON Then stream.Skip(1) 'Skip colon
				locals = locals.Resize(locals.Length + 1)
				If stream.Peek().IsType()
					locals[locals.Length - 1] = New ScriptVar(name, stream.NextToken.Type, -1)
				Else
					locals[locals.Length - 1] = New ScriptVar(name, TOK_VOID, -1)
				End
			Else
				stream.Skip(1)
			End
		Wend
		stream.Skip(1)	')

		'Scan
		Local block:Int = 1
		While stream.HasNext() And block > 0
			Local token:Token = stream.NextToken

			'Count blocks
			If token.IsControl()
				block += 1
			Elseif token.Type = TOK_END
				block -= 1
			End

			'Scan vars
			If token.Type = TOK_VAR And stream.Peek().Type = TOK_ID
				Local name:String = stream.NextToken.Data
				stream.Skip(1) ' Skip ':'
				Local type:Int = stream.NextToken.Type
				locals = locals.Resize(locals.Length + 1)
				locals[locals.Length - 1] = New ScriptVar(name, type, stream.Pos + 1)
			End
		Wend
	End

	Method NumDefs:Int(name:String)
		Local count:Int = 0
		For Local f:ScriptFunc = Eachin functions
			If f.Name = name Then count += 1
		Next
		For Local g:ScriptVar = Eachin globals
			If g.Name = name Then count += 1
		Next
		For Local l:ScriptVar = Eachin locals
			If l.Name = name Then count += 1
		Next
		Return count
	End

	Method Locals:ScriptVar[]() Property
		Return locals
	End

	Method Var:ScriptVar(name:String)
		For Local l:ScriptVar = Eachin locals
			If l.Name = name Then Return l
		Next
		For Local g:ScriptVar = Eachin globals
			If g.Name = name Then Return g
		Next
		Return Null
	End

	Method Func:ScriptFunc(name:String)
		For Local func:ScriptFunc = Eachin functions
			If func.Name = name Then Return func
		Next
		Return Null
	End

	Method FuncId:Int(f:ScriptFunc)
		For Local i:Int = 0 Until functions.Length()
			If functions[i] = f Then Return i
		Next
		Return -1
	End

	Method IsVar:Bool(name:String)
		For Local l:ScriptVar = Eachin locals
			If l.Name = name Then Return True
		Next
		For Local g:ScriptVar = Eachin globals
			If g.Name = name Then Return True
		Next
		Return False
	End

	Method GlobalId:Int(name:String)
		For Local i:Int = 0 Until globals.Length()
			If globals[i].Name = name Then Return i
		Next
		Return -1
	End

	Method Text:String() Property
		Local str:String
		str += "[globals]~n"
		For Local g:String = Eachin globals
			str += g + "~n"
		Next
		str += "~n[functions]~n"
		For Local f:ScriptFunc = Eachin functions
			str += f.Name + ":"
			str += f.NumArgs + ":"
			For Local l:String = Eachin f.Locals
				str += l
				If l <> f.Locals[f.Locals.Length() - 1] Then str += ","
			Next
			str += "~n"
		Next
		Return str
	End

	Method Globals:ScriptVar[]() Property
		Return globals
	End

	Method Functions:ScriptFunc[]() Property
		Return functions
	End
Private
	Field stream	: TokenStream
	Field globals	: ScriptVar[0]
	Field functions	: ScriptFunc[0]
	Field locals	: ScriptVar[0]
End
