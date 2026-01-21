Strict

Private
Import lib
Import scanner
Import token
Import tokenstream

Public
Class LuaGen
	Method New(tokens:Token[], scanner:Scanner, lib:Lib)
		Self.stream = New TokenStream(tokens)
		Self.scanner = scanner
		Self.lib = lib

		'Fill buffer
		buffer = GenGlobals()
		buffer += GenFunctions()
		buffer += "__st__" + scanner.Func("Main").Name + "()~n"
	End

	Method Code:String() Property
		Return buffer
	End
Private
	Method GenGlobals:String()
		Local str:String = ""
		For Local glob:ScriptVar = Eachin scanner.Globals
			str += "__st__" + glob.Name + " = "
			stream.Seek(glob.Offset)
			str += GenExp(Null) + "~n"
		Next
		If scanner.Globals.Length > 0 Then str += "~n"
		Return str
	End

	Method GenFunctions:String()
		Local str:String = ""
		For Local f:ScriptFunc = Eachin scanner.Functions
			str += GenFunction(f)
		Next
		Return str
	End

	Method GenFunction:String(f:ScriptFunc)
		Local str:String = ""

		'Header
		str += "function __st__" + f.Name + "("
		For Local arg:Int = 0 Until f.Args.Length
			str += "__st__" + f.Locals[arg].Name
			If arg < f.Args.Length - 1 Then str += ", "
		Next
		str += ")~n"

		'Locals
		Local tabs:String = GenTabs(1)
		For Local l:Int = f.Args.Length Until f.Locals.Length
			str += tabs + "local __st__" + f.Locals[l].Name + "~n"
		Next

		'Block
		stream.Seek(f.Offset)
		str += GenBlockContents(f, 1)

		'Footer
		stream.Skip(1)	'end
		If f.Type <> TOK_VOID Then str += "~nreturn __st__" + f.ReturnVar
		str += "~n" + GenEnd() + "~n~n"

		Return str
	End

	Method GenReturn:String(f:ScriptFunc)
		stream.Skip(1) 'skip return
		Local str:String = "return"
		If stream.Peek().Type <> TOK_SEMICOLON Then str += " " + GenExp(f) Else str += " 0"
		str += GenEndStatement()
		Return str
	End

	Method GenBlockContents:String(f:ScriptFunc, indent:Int)
		Local str:String = GenTabs(indent)
		Local type:Int = stream.Peek().Type

		'While we do not find the end of a block, gen statements
		While type <> TOK_ELIF And type <> TOK_ELSE And type <> TOK_END
			str += GenStatement(f, indent)
			type = stream.Peek().Type
		Wend

		Return str
	End

	Method GenStatement:String(f:ScriptFunc, indent:Int)
		If stream.Peek().IsControl()
			Return GenControl(f, indent)
		Else
			If stream.Peek().Type = TOK_VAR Then stream.Skip(1)	'skip var
			Local str:String = GenExp(f)
			str += GenEndStatement()
			Return str
		End
	End

	Method GenControl:String(f:ScriptFunc, indent:Int)
		Local str:String = "~n" + GenTabs(indent)
		Local type:Int = stream.Peek().Type
		Select type
		Case TOK_IF
			str += GenIf(f, indent)
		Case TOK_FOR
			str += GenFor(f, indent)
		Case TOK_WHILE
			str += GenWhile(f, indent)
		End
		str +=  "~n" + GenTabs(indent)
		Return str
	End

	Method GenIf:String(f:ScriptFunc, indent:Int)
		'if
		stream.Skip(1)	'skip if
		Local str:String = "if " + GenExp(f) + " then~n"
		str += GenTabs(indent + 1) + GenBlockContents(f, indent + 1) + "~n"

		'optional elseif
		While stream.Peek().Type = TOK_ELIF
			stream.Skip(1) 'skip elseif
			str += GenTabs(indent) + "elseif " + GenExp(f) + " then~n"
			str += GenTabs(indent + 1) + GenBlockContents(f, indent + 1) + "~n"
		Wend

		'optional else
		If stream.Peek().Type = TOK_ELSE
			stream.Skip(1) 'skip else
			str += GenTabs(indent) + "else~n"
			str += GenTabs(indent + 1) + GenBlockContents(f, indent + 1) + "~n"
		End

		'end
		str += GenTabs(indent) + GenEnd()

		Return str
	End

	Method GenFor:String(f:ScriptFunc, indent:Int)
		'header
		stream.Skip(1)	'skip for
		Local varToken:Token = stream.NextToken()
		stream.Skip(1)	'skip =
		Local str:String = "for __st__" + varToken.Data + " = "	' TODO: gen as local and get real name despite of casing

		'from exp
		str += GenExp(f) + ", "
		stream.Skip(1)	'skip ,

		'to exp
		str += GenExp(f)

		'optional step exp
		If stream.Peek().Type = TOK_COMMA
			stream.Skip(1) 'skip ,
			str += ", " + GenExp(f)
		End

		'$block
		str += " do~n" + GenTabs(indent+1) + GenBlockContents(f, indent+1) + "~n"

		'end
		str += GenTabs(indent) + GenEnd()

		Return str
	End

	Method GenWhile:String(f:ScriptFunc, indent:Int)
		stream.Skip(1)	'skip while
		Local str:String = "while " + GenExp(f) + " do~n"
		str += GenTabs(indent + 1) + GenBlockContents(f, indent+1) + "~n"
		str += GenTabs(indent) + GenEnd()
		Return str
	End

	Method GenExp:String(f:ScriptFunc)
		Local str:String = GenOrExp(f)
		If stream.Peek().Type = TOK_COLON Then stream.Skip(2)
		If stream.Peek().Type = TOK_ASSIGN
			stream.Skip(1)	'Skip =
			str += " = " + GenExp(f)
		End
		Return str
	End

	Method GenOrExp:String(f:ScriptFunc)
		Local str:String = GenAndExp(f)
		While stream.Peek().Type = TOK_OR
			stream.Skip(1) 'skip or
			str += " or " + GenAndExp(f)
		End
		Return str
	End

	Method GenAndExp:String(f:ScriptFunc)
		Local str:String = GenEqualExp(f)
		While stream.Peek().Type = TOK_AND
			stream.Skip(1) 'skip and
			str += " and " + GenEqualExp(f)
		Wend
		Return str
	End

	Method GenEqualExp:String(f:ScriptFunc)
		Local str:String = GenRelExp(f)
		While stream.Peek().Type = TOK_EQUAL Or stream.Peek().Type = TOK_NOTEQUAL
			If stream.NextToken().Type = TOK_EQUAL Then str += " == " Else str += " ~~= "
			str += GenRelExp(f)
		Wend
		Return str
	End

	Method GenRelExp:String(f:ScriptFunc)
		Local str:String = GenAddExp(f)
		Local tokType:Int = stream.Peek().Type
		While tokType = TOK_LESSER Or tokType = TOK_LEQUAL Or tokType = TOK_GREATER Or tokType = TOK_GEQUAL
			Select stream.NextToken().Type
				Case TOK_LESSER
					str += " < "
				Case TOK_LEQUAL
					str += " <= "
				Case TOK_GREATER
					str += " > "
				Case TOK_GEQUAL
					str += " >= "
			End
			str += GenAddExp(f)
			tokType = stream.Peek().Type
		Wend
		Return str
	End

	Method GenAddExp:String(f:ScriptFunc)
		Local str:String = GenMulExp(f)
		While stream.Peek().Type = TOK_PLUS Or stream.Peek().Type = TOK_MINUS
			If stream.NextToken().Type = TOK_PLUS Then str += " + " Else str += " - "
			str += GenMulExp(f)
		Wend
		Return str
	End

	Method GenMulExp:String(f:ScriptFunc)
		Local str:String = GenUnaryExp(f)
		While stream.Peek().Type = TOK_MUL Or stream.Peek().Type = TOK_DIV Or stream.Peek().Type = TOK_MOD
			Select stream.NextToken().Type
				Case TOK_MUL
					str += " * "
				Case TOK_DIV
					str += " / "
				Case TOK_MOD
					str += " % "
			End
			str += GenUnaryExp(f)
		Wend
		Return str
	End

	Method GenUnaryExp:String(f:ScriptFunc)
		Local str:String = ""
		If stream.Peek().Type = TOK_NOT Or stream.Peek().Type = TOK_MINUS
			If stream.NextToken().Type = TOK_NOT Then str += "not " Else str += "-"
		End
		str += GenGroupExp(f)
		Return str
	End

	Method GenGroupExp:String(f:ScriptFunc)
		If stream.Peek().Type = TOK_OPENPAREN
			stream.Skip(1) 'skip (
			Local str:String = "(" + GenExp(f) + ")"
			stream.Skip(1) 'skip )
			Return str
		Else
			Return GenAtomicExp(f)
		End
	End

	Method GenAtomicExp:String(f:ScriptFunc)
		Local token:Token = stream.NextToken
		Select token.Type
			Case TOK_INTLITERAL
				Return token.Data
			Case TOK_FLOATLITERAL
				Return token.Data
			Case TOK_STRINGLITERAL
				Return "~q" + token.Data + "~q"
			Case TOK_ID
				If stream.Peek().Type = TOK_OPENPAREN 'function call
					stream.GoBack()	'Move before function name
					Return GenCall(f)
				Else 'var id
					Return "__st__" + token.Data 'TODO set correct format (casing etc)
				End
		End
		Return ""	'Should not get here, but Monkey compiler complains
	End

	Method GenCall:String(f:ScriptFunc)
		'id
		Local funcToken:Token = stream.NextToken
		Local libFunc:LibFunc = lib.Func(funcToken.Data)
		Local scriptFunc:ScriptFunc = scanner.Func(funcToken.Data)
		Local str:String = ""
		If libFunc
			str += libFunc.NativeName
		Else
			str += "__st__" + scriptFunc.Name
		End
		str += GenArgs(f)
		Return str
	End

	Method GenArgs:String(f:ScriptFunc)
		stream.Skip(1)	'skip (
		Local str:String = "("
		If stream.Peek().Type <> TOK_CLOSEPAREN
			str += GenExp(f)
			While stream.Peek().Type = TOK_COMMA
				stream.Skip(1) 'skip ,
				str += ", " + GenExp(f)
			Wend
		End
		str += ")"
		stream.Skip(1)	'skip )
		Return str
	End

	Method GenEndStatement:String()
		If stream.Peek().Type = TOK_SEMICOLON Then stream.Skip(1)	';
		Return "; "
	End

	Method GenEnd:String()
		stream.Skip(1)	'end
		Return "end"
	End

	Function GenTabs:String(indent:Int)
		Local str:String = ""
		For Local i:Int = 0 Until indent
			str += "~t"
		Next
		Return str
	End

	Field stream : TokenStream
	Field scanner : Scanner
	Field lib : Lib
	Field buffer : String
End
