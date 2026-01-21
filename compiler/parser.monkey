Strict

Private
Import lib
Import scanner
Import tokenstream

Public
Class Parser
	Method New(tokens:Token[], lib:Lib)
		Self.stream = New TokenStream(tokens)
		Self.scanner = New Scanner(tokens)
		Self.lib = lib

		'Scan
		scanner.ScanDefs()

		'Parse
		While stream.HasNext() And err = ""
			'Global
			If stream.Peek().Type = TOK_VAR
				ParseVarDecl()
			'Function
			Elseif stream.Peek().Type = TOK_FUNCTION
				ParseFunction()
			'Unexpected token
			Else
				err = "Unexpected element"
				errToken = New Token(TOK_EOF, stream.Peek().Data, stream.Peek().File, stream.Peek().Line)
			End
		Wend
	End

	Method Err:String() Property
		If err = ""
			Return ""
		Else
			Return err + " on file '" + errToken.File + "' at line " + errToken.Line + ", element '" + errToken.Data + "'"
		End
	End

	Method Scanner:Scanner() Property
		Return scanner
	End

	'Method Bytecode:DataBuffer() Property
	'	Local stream:DataStream = New DataStream(New DataBuffer(BufferLength()))
	'End
Private
	'function id $args [colon type] $block end
	Method ParseFunction:Void()
		'function
		stream.Skip(1)

		'id
		Local nameToken:Token = ParseId()
		Local func:ScriptFunc = scanner.Func(nameToken.Data)

		'Scan for params and locals
		scanner.ScanLocals(stream.Pos)

		'$args
		ParseArgs()
		If err <> "" Then Return

		'colon type
		Local hasType: Bool = False
		If stream.Peek().Type = TOK_COLON
			hasType = True
			stream.Skip(1)	'colon
			If Not stream.Peek().IsType()
				err = "Expected type"
				errToken = stream.NextToken
				Return
			End
			stream.Skip(1)	'type
		End

		'$block
		Local offset:Int = stream.Pos
		ParseBlock(func)
		If err <> "" Then Return

		'end
		ParseEnd()
		If err <> "" Then Return

		'Parse return var
		If hasType
			Local returnTok:Token = stream.NextToken
			If returnTok.Type <> TOK_ID
				err = "Expected return variable"
				errToken = returnTok
				Return
			End
			If Not scanner.IsVar(returnTok.Data)
				err = "Return value must be a variable"
				errToken = returnTok
				Return
			End
			If Not AreCompatible(scanner.Var(returnTok.Data).Type, func.Type)
				err = "Incompatible type in return variable"
				errToken = returnTok
			End
			func.ReturnVar = returnTok.Data
		End

		'Set function offset and locals
		func.Offset = offset
		func.Locals = scanner.Locals[..]
	End

	'openparen [id colon type *[comma id colon type]] closeparen
	Method ParseArgs:Void()
		'openparen
		If stream.Peek().Type <> TOK_OPENPAREN
			err = "Expected '('"
			errToken = stream.NextToken
			Return
		End
		stream.Skip(1)

		'[id colon type *[comma id colon type]]
		While stream.Peek().Type = TOK_ID
			'id
			Local nameToken:Token = ParseId()
			If err <> "" Then Return

			'colon
			If stream.Peek().Type <> TOK_COLON
				err = "Expected ':'"
				errToken = stream.NextToken
				Return
			End
			stream.Skip(1)	'colon

			'type
			If Not stream.Peek().IsType()
				err = "Expected type"
				errToken = stream.NextToken
				Return
			End
			stream.Skip(1)	'type

			'comma
			If stream.Peek().Type = TOK_COMMA Then stream.Skip(1)
		Wend

		'closeparen
		If stream.Peek().Type <> TOK_CLOSEPAREN
			err = "Expected ')'"
			errToken = stream.NextToken
			Return
		End
		stream.Skip(1)
	End

	'*[$statement]
	Method ParseBlock:Void(f:ScriptFunc)
		'While we do not find the end of a block, parse statements
		Local type:Int = stream.Peek().Type
		While err = "" And type <> TOK_ELIF And type <> TOK_ELSE And type <> TOK_END And type <> TOK_EOF
			ParseStatement(f)
			If stream.HasNext() Then type = stream.Peek().Type
		Wend
	End

	'$local | $control | ($expression endst)
	Method ParseStatement:Void(f:ScriptFunc)
		If stream.Peek().Type = TOK_VAR
			ParseVarDecl()
		Elseif stream.Peek().IsControl()
			ParseControl(f)
		Else
			ParseExp(EXP_NORMAL)
			If err <> "" Then Return
			ParseEndStatement()
		End
	End

	'var id colon type assign $block endst
	Method ParseVarDecl:Void()
		'var
		stream.Skip(1)

		'id
		ParseId()
		If err <> "" Then Return

		'colon
		If stream.Peek().Type <> TOK_COLON
			err = "Expected ':'"
			errToken = stream.NextToken
			Return
		End
		stream.Skip(1)

		'type
		Local typeToken:Token = stream.NextToken
		If Not typeToken.IsType()
			err = "Expected type"
			errToken = typeToken
			Return
		End

		'assign
		If stream.Peek().Type <> TOK_ASSIGN
			err = "Expected '='"
			errToken = stream.NextToken
			Return
		End
		stream.Skip(1)

		'$exp
		Local expToken:Token = stream.Peek()
		Local type:Int = ParseExp(EXP_NORMAL)
		If err <> "" Then Return

		'Check type compatibility
		If Not AreCompatible(type, typeToken.Type)
			err = "Incompatible types"
			errToken = expToken
			Return
		End

		'endst
		ParseEndStatement()
	End

	'$if | $for | $while | $return
	Method ParseControl:Void(f:ScriptFunc)
		Local type:Int = stream.Peek().Type
		Select type
		Case TOK_IF
			ParseIf(f)
		Case TOK_FOR
			ParseFor(f)
		Case TOK_WHILE
			ParseWhile(f)
		End
	End

	'if $exp $block *[elif $exp $block] [else $block] end
	Method ParseIf:Void(f:ScriptFunc)
		'if
		stream.Skip(1)

		'$exp
		ParseExp(EXP_CONDITIONAL)
		If err <> "" Then Return

		'$block
		ParseBlock(f)
		If err <> "" Then Return

		'*[elif $exp $block]
		While stream.Peek().Type = TOK_ELIF
			'elif
			stream.Skip(1)

			'$exp
			ParseExp(EXP_CONDITIONAL)
			If err <> "" Then Return

			'$block
			ParseBlock(f)
			If err <> "" Then Return
		Wend

		'[else $block]
		If stream.Peek().Type = TOK_ELSE
			'else
			stream.Skip(1)

			'$block
			ParseBlock(f)
			If err <> "" Then Return
		End

		'end
		ParseEnd()
	End

	'for id assign $expression comma $expression [comma $expression] $block end
	Method ParseFor:Void(f:ScriptFunc)
		'for
		stream.Skip(1)

		'id
		If stream.Peek().Type <> TOK_ID
			err = "Expected variable"
			errToken = stream.NextToken
			Return
		End
		stream.Skip(1)	'id

		'assign
		If stream.Peek().Type <> TOK_ASSIGN
			err = "Expected '='"
			errToken = stream.NextToken
			Return
		End
		stream.Skip(1)	'=

		'$expression
		ParseExp(EXP_CONDITIONAL)
		If err <> "" Then Return

		'comma
		If stream.Peek().Type <> TOK_COMMA
			err = "Expected ','"
			errToken = stream.NextToken
			Return
		End
		stream.Skip(1)	',

		'$expression
		ParseExp(EXP_CONDITIONAL)
		If err <> "" Then Return

		'[comma $expression]
		If stream.Peek().Type = TOK_COMMA
			'comma
			stream.Skip(1)

			'$expression
			ParseExp(EXP_CONDITIONAL)
			If err <> "" Then Return
		End

		'$block
		ParseBlock(f)
		If err <> "" Then Return

		'end
		ParseEnd()
	End

	'while $expression $block end
	Method ParseWhile:Void(f:ScriptFunc)
		'while
		stream.Skip(1)

		'$expression
		ParseExp(EXP_CONDITIONAL)
		If err <> "" Then Return

		'$block
		ParseBlock(f)
		If err <> "" Then Return

		'end
		ParseEnd()
	End

	'$assignexp | $orexp
	Method ParseExp:Int(type:Int)
		If type = EXP_NORMAL
			Return ParseAssignExp(type)
		Else
			Return ParseOrExp(type)
		End
	End

	'TODO: Left part must be an l-value
	'$orexp [assign $assignexp]
	Method ParseAssignExp:Int(type_:Int)
		'$orexp
		Local type:Int = ParseOrExp(type_)
		If err <> "" Then Return TOK_VOID

		'assign
		If stream.Peek().Type = TOK_ASSIGN
			Local token:Token = stream.NextToken

			'$assignexp
			Local type2:Int = ParseAssignExp(type_)
			If err <> "" Then Return TOK_VOID

			'Check type compatibility
			If Not AreCompatible(type, type2)
				err = "Incompatible types"
				errToken = token
				Return TOK_VOID
			End

			type = BalanceTypes(type, type2)
		End

		Return type
	End

	'$andexp *[or $andexp]
	'expanded from [$orexp or] $andexp
	Method ParseOrExp:Int(type_:Int)
		'$andexp
		Local type:Int = ParseAndExp(type_)
		If err <> "" Then Return TOK_VOID

		'*[or $andexp]
		While stream.Peek().Type = TOK_OR
			If Not AreCompatible(type, TOK_INT)
				err = "Cannot use in boolean expression"
				errToken = stream.NextToken
				Return TOK_VOID
			End

			'or
			Local orToken:Token = stream.NextToken

			'$andexp
			Local type2:Int = ParseAndExp(type_)
			If err <> "" Then Return TOK_VOID

			'Check type compatibility
			If Not AreCompatible(type, type2)
				err = "Incompatible types"
				errToken = orToken
				Return TOK_VOID
			End

			type = BalanceTypes(type, type2)
		End

		Return type
	End

	'$equalexp *[and $equalexp]
	'expanded from [$andexp and] $equalexp
	Method ParseAndExp:Int(type_:Int)
		'$equalexp
		Local type:Int = ParseEqualExp(type_)
		If err <> "" Then Return TOK_VOID

		'*[and $equalexp]
		While stream.Peek().Type = TOK_AND
			If Not AreCompatible(type, TOK_INT)
				err = "Cannot use in boolean expression"
				errToken = stream.NextToken
				Return TOK_VOID
			End

			'and
			Local andToken:Token = stream.NextToken

			'$equalexp
			Local type2:Int = ParseEqualExp(type_)
			If err <> "" Then Return TOK_VOID

			'Check type compatibility
			If Not AreCompatible(type, type2)
				err = "Incompatible types"
				errToken = andToken
				Return TOK_VOID
			End

			type = BalanceTypes(type, type2)
		Wend

		Return type
	End

	'$relexp *[equal | notequal $relexp]
	'expanded from ([$equalexp equal] $relexp) | ([$equalexp notequal] $relexp)
	Method ParseEqualExp:Int(type_:Int)
		'$relexp
		Local type:Int = ParseRelExp(type_)
		If err <> "" Then Return TOK_VOID

		'*[equal | notequal $relexp]
		While stream.Peek().Type = TOK_EQUAL Or stream.Peek().Type = TOK_NOTEQUAL
			'equal | notequal
			Local token:Token = stream.NextToken

			'$relexp
			Local type2:Int = ParseRelExp(type_)
			If err <> "" Then Return TOK_VOID

			'Check type compatibility
			If Not AreCompatible(type, type2)
				err = "Incompatible types"
				errToken = token
				Return TOK_VOID
			End

			type = TOK_INT
		Wend

		Return type
	End

	'$addexp *[lesser | lequal | greater | gequal $addexp]
	'expanded from ([$relexp lesser] $addexp) | ([$relexp lequal] $addexp) | ([$relexp greater] $addexp) | ([$relexp gequal] $addexp)
	Method ParseRelExp:Int(type_:Int)
		'$addexp
		Local type:Int = ParseAddExp(type_)
		If err <> "" Then Return TOK_VOID

		'*[lesser | lequal | greater | gequal $addexp]
		Local tokType:Int = stream.Peek().Type
		While tokType = TOK_LESSER Or tokType = TOK_LEQUAL Or tokType = TOK_GREATER Or tokType = TOK_GEQUAL
			'lesser | lequal | greater | gequal
			Local token:Token = stream.NextToken

			'$addexp
			Local type2:Int = ParseAddExp(type_)
			If err <> "" Then Return TOK_VOID

			'Check type compatibility
			If Not AreCompatible(type, type2)
				err = "Incompatible types"
				errToken = token
				Return TOK_VOID
			End

			type = TOK_INT

			tokType = stream.Peek().Type
		Wend

		Return type
	End

	'$mulexp *[plus | minus $mulexp]
	'expanded from ([$addexp plus] $mulexp) | ([$addexp minus] $mulexp)
	Method ParseAddExp:Int(type_:Int)
		'$mulexp
		Local type:Int = ParseMulExp(type_)
		If err <> "" Then Return TOK_VOID

		'*[plus | minus $mulexp]
		While stream.Peek().Type = TOK_PLUS Or stream.Peek().Type = TOK_MINUS
			'plus | minus
			Local token:Token = stream.NextToken

			'$mulexp
			Local type2:Int = ParseMulExp(type_)
			If err <> "" Then Return TOK_VOID

			'Check type compatibility
			If Not AreCompatible(type, type2)
				err = "Incompatible types"
				errToken = token
				Return TOK_VOID
			End

			type = BalanceTypes(type, type2)
		Wend

		Return type
	End

	'$unaryexp *[mul | div | mod $unaryexp]
	'expanded from ([$mulexp mul] $unaryexp) | ([$mulexp div] $unaryexp) | [$mulexp mod] $unaryexp)
	Method ParseMulExp:Int(type_:Int)
		'$unaryexp
		Local type:Int = ParseUnaryExp(type_)
		If err <> "" Then Return TOK_VOID

		'*[mul | div | mod $unaryexp]
		While stream.Peek().Type = TOK_MUL Or stream.Peek().Type = TOK_DIV Or stream.Peek().Type = TOK_MOD
			'mul | div | mod
			Local token:Token = stream.NextToken

			'$unaryexp
			Local type2:Int = ParseUnaryExp(type_)
			If err <> "" Then Return TOK_VOID

			'Check type compatibility
			If Not AreCompatible(type, type2)
				err = "Incompatible types"
				errToken = token
				Return TOK_VOID
			End

			type = BalanceTypes(type, type2)
		Wend

		Return type
	End

	'[not | minus] $groupexp
	Method ParseUnaryExp:Int(type_:Int)
		'not | minus
		Local token:Token = Null
		If stream.Peek().Type = TOK_NOT Or stream.Peek().Type = TOK_MINUS
			token = stream.NextToken
		End

		'$groupexp
		Local type:Int = ParseGroupExp(type_)
		If token <> Null And type <> TOK_INT And type <> TOK_FLOAT
			err = "Incompatible types"
			errToken = token
			Return TOK_VOID
		End
		Return type
	End

	'(openparen $expression closeparen) | $atomicexp
	Method ParseGroupExp:Int(type_:Int)
		'(openparen $expression closeparen)
		If stream.Peek().Type = TOK_OPENPAREN
			'openparen
			stream.Skip(1)

			'$expression
			Local type:Int = ParseExp(type_)
			If err <> "" Then Return TOK_VOID

			'closeparen
			Local closeparenToken:Token = stream.NextToken
			If closeparenToken.Type <> TOK_CLOSEPAREN
				err = "Expected ')'"
				errToken = closeparenToken
				Return TOK_VOID
			End

			Return type
		'$atomicexp
		Else
			Return ParseAtomicExp(type_)
		End
	End

	'intliteral | floatliteral | stringliteral | $call | id
	Method ParseAtomicExp:Int(type:Int)
		Local token:Token = stream.NextToken
		Select token.Type
		Case TOK_INTLITERAL
			Return TOK_INT
		Case TOK_FLOATLITERAL
			Return TOK_FLOAT
		Case TOK_STRINGLITERAL
			Return TOK_STRING
		Case TOK_ID
			'$call
			If stream.Peek().Type = TOK_OPENPAREN
				stream.GoBack()	'Move before function name
				Return ParseCall(type)
			'var
			Else
				If Not scanner.IsVar(token.Data)
					If scanner.Func(token.Data)
						err = "Expected '(' in function call"
					Else
						err = "Variable has not been declared"
					End
					errToken = token
					Return TOK_VOID
				End
				Return scanner.Var(token.Data).Type
			End
		Default
			err = "Unexpected element"
			errToken = token
		End
		Return TOK_VOID
	End

	'id $params
	Method ParseCall:Int(type:Int)
		'id
		Local funcToken:Token = stream.NextToken
		Local libFunc:LibFunc = lib.Func(funcToken.Data)
		Local scriptFunc:ScriptFunc = scanner.Func(funcToken.Data)
		If Not libFunc And Not scriptFunc
			err = "Unknown function"
			errToken = funcToken
			Return TOK_VOID
		End
		Local funcType:Int
		Local argTypes:Int[]
		If libFunc
			funcType = libFunc.Type
			argTypes = libFunc.Args
		Else
			funcType = scriptFunc.Type
			argTypes = scriptFunc.Args
		End

		'$params
		Local numParamsError:Bool = False
		Local numParams:Int = ParseParams(type, argTypes)
		If err <> "" Then Return TOK_VOID
		If argTypes.Length <> numParams
			err = "Function call does not match number of arguments"
			errToken = funcToken
			Return TOK_VOID
		End

		Return funcType
	End

	'openparen [$exp *[comma $exp]] closeparen
	Method ParseParams:Int(type_:Int, argTypes:Int[])
		Local numArgs:Int = 0

		'openparen
		If stream.Peek().Type <> TOK_OPENPAREN
			err = "Expected '('"
			errToken = stream.NextToken
			Return numArgs
		End
		stream.Skip(1)

		'[$exp *[comma $exp]]
		If stream.Peek().Type <> TOK_CLOSEPAREN
			'$exp
			Local token:Token = stream.Peek()
			Local type:Int = ParseExp(type_)
			If err <> "" Then Return numArgs

			'Check argument type
			If Not AreCompatible(type, argTypes[numArgs])
				err = "Incompatible types"
				errToken = token
				Return TOK_VOID
			End
			numArgs += 1

			'*[comma $exp]
			While stream.Peek().Type = TOK_COMMA
				'comma
				stream.Skip(1)

				'$exp
				Local token:Token = stream.Peek()
				Local type:Int = ParseExp(type_)
				If err <> "" Then Return numArgs

				'Check argument type
				If Not AreCompatible(type, argTypes[numArgs])
					err = "Incompatible types"
					errToken = token
					Return TOK_VOID
				End
				numArgs += 1
			Wend
		End

		'closeparen
		If stream.Peek().Type <> TOK_CLOSEPAREN
			err = "Expected ')'"
			errToken = stream.NextToken
			Return numArgs
		End
		stream.Skip(1)

		Return numArgs
	End

	Method ParseId:Token()
		Local nameToken:Token = stream.NextToken
		If nameToken.Type <> TOK_ID
			err = "Expected identifier"
		'Check if identifier has been defined as a library function
		Elseif lib.Func(nameToken.Data)
			err = "Identifier cannot have the same name as a library function"
		'Check if identifier has been defined multiple times
		Elseif scanner.NumDefs(nameToken.Data) > 1
			err = "Identifier defined multiple times"
		End

		'Set error token if an error was found
		If err <> "" Then errToken = nameToken

		Return nameToken
	End

	Method ParseEndStatement:Void()
		Local hasEol:Bool = stream.SkipEols()
		If Not hasEol
			Local token:Token = stream.NextToken
			If token.Type <> TOK_SEMICOLON
				err = "Expected semicolon or new line"
				errToken = token
			End
		End
	End

	Method ParseEnd:Void()
		Local endToken:Token = stream.NextToken
		If endToken.Type <> TOK_END
			err = "Expected 'end'"
			errToken = endToken
		End
	End

	Const EXP_NORMAL		: Int = 0
	Const EXP_CONDITIONAL	: Int = 1

	Field stream	: TokenStream
	Field scanner	: Scanner
	Field lib		: Lib
	Field err		: String
	Field errToken	: Token
End
