Strict

'End of file
Const TOK_EOF			: Int = 0
Const TOK_EOL			: Int = 1

'Literals
Const TOK_INTLITERAL	: Int = 2
Const TOK_FLOATLITERAL	: Int = 3
Const TOK_STRINGLITERAL	: Int = 4

'Operators
Const TOK_NOT			: Int = 10
Const TOK_AND			: Int = 11
Const TOK_OR			: Int = 12
Const TOK_EQUAL			: Int = 13
Const TOK_NOTEQUAL		: Int = 14
Const TOK_GREATER		: Int = 15
Const TOK_LESSER		: Int = 16
Const TOK_GEQUAL		: Int = 17
Const TOK_LEQUAL		: Int = 18
Const TOK_PLUS			: Int = 19
Const TOK_MINUS			: Int = 20
Const TOK_MUL			: Int = 21
Const TOK_DIV			: Int = 22
Const TOK_MOD			: Int = 23
Const TOK_ASSIGN		: Int = 24

'Separators
Const TOK_COMMA			: Int = 30
Const TOK_COLON			: Int = 31
Const TOK_SEMICOLON		: Int = 32
Const TOK_OPENPAREN		: Int = 33
Const TOK_CLOSEPAREN	: Int = 34
Const TOK_END			: Int = 35

'Control statements
Const TOK_IF			: Int = 40
Const TOK_ELIF			: Int = 41
Const TOK_ELSE			: Int = 42
Const TOK_FOR			: Int = 43
Const TOK_WHILE			: Int = 44

'Variable and function definitions
Const TOK_VAR			: Int = 50
Const TOK_FUNCTION : Int = 51

'Identifiers
Const TOK_ID			: Int = 60

'Types
Const TOK_INT			: Int = -1
Const TOK_FLOAT			: Int = -2
Const TOK_STRING		: Int = -3
Const TOK_VOID			: Int = -4 'Not a real token, but functions can be of this type

Class Token
	Method New()
		type = TOK_EOF
		data = ""
		line = 0
	End

	Method New(type:Int, data:String, file:String, line:Int)
		Self.type = type
		Self.data = data
		Self.file = file
		Self.line = line
	End

	Method Type:Int() Property
		Return type
	End

	Method Data:String() Property
		Return data
	End

	Method File:String() Property
		Return file
	End

	Method Line:Int() Property
		Return line
	End

	Method IsControl:Bool()
		Return IsControl(type)
	End

	Method IsBooleanOp:Bool()
		Return IsBooleanOp(type)
	End

	Method IsRelationalOp:Bool()
		Return IsRelationalOp(type)
	End

	Method IsAdditiveOp:Bool()
		Return IsAdditiveOp(type)
	End

	Method IsMultiplicativeOp:Bool()
		Return IsMultiplicativeOp(type)
	End

	Method IsUnaryOp:Bool()
		Return IsUnaryOp(type)
	End

	Method IsType:Bool()
		Return IsType(type)
	End


	Method IsStatementEnd:Bool()
		Return IsStatementEnd(type)
	End

	Function IsControl:Bool(type:Int)
		If type = TOK_IF Or type = TOK_FOR Or type = TOK_WHILE
			Return True
		Else
			Return False
		End
	End

	Function IsBooleanOp:Bool(type:Int)
		If type = TOK_AND Or type = TOK_OR
			Return True
		Else
			Return False
		End
	End

	Function IsRelationalOp:Bool(type:Int)
		If type >= TOK_EQUAL And type <= TOK_LEQUAL
			Return True
		Else
			Return False
		End
	End

	Function IsAdditiveOp:Bool(type:Int)
		If type = TOK_PLUS Or type = TOK_MINUS
			Return True
		Else
			Return False
		End
	End

	Function IsMultiplicativeOp:Bool(type:Int)
		If type = TOK_MUL Or type = TOK_DIV Or type = TOK_MOD
			Return True
		Else
			Return False
		End
	End

	Function IsUnaryOp:Bool(type:Int)
		If type = TOK_NOT Or type = TOK_MINUS
			Return True
		Else
			Return False
		End
	End

	Function IsType:Bool(type:Int)
		If type <= TOK_INT And type >= TOK_STRING
			Return True
		Else
			Return False
		End
	End

	Function IsStatementEnd:Bool(type:Int)
		If type = TOK_EOL Or type = TOK_SEMICOLON
			Return True
		Else
			Return False
		End
	End
Private
	Field type	: Int
	Field data	: String
	Field file	: String
	Field line	: Int
End


Function AreCompatible:Bool(type1:Int, type2:Int)
	If type1 = type2 And type1 <> TOK_VOID
		Return True
	Elseif type1 = TOK_INT And type2 = TOK_FLOAT
		Return True
	Elseif type1 = TOK_FLOAT And type2 = TOK_INT
		Return True
	Else
		Return False
	End
End


Function BalanceTypes:Int(type1:Int, type2:Int)
	If type1 = type2
		Return type1
	Elseif type1 = TOK_INT And type2 = TOK_FLOAT
		Return TOK_FLOAT
	Elseif type1 = TOK_FLOAT And type2 = TOK_INT
		Return TOK_FLOAT
	Else
		Return TOK_VOID
	End
End
