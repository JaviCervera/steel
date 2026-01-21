Strict

Private
Import token

Public
Class Lexer
Public
	Method New(buffer:String, filename:String)
		If buffer = "" Then Return

		'Init vars
		Self.buffer = buffer.Replace("~r~n", "~n").Replace("~r", "~n")
		Self.offset = 0
		Self.file = filename
		Self.line = 1

		'Fill types map
		Self.typeMap = New StringMap<Int>
		typeMap.Set("not", TOK_NOT)
		typeMap.Set("and", TOK_AND)
		typeMap.Set("or", TOK_OR)
		typeMap.Set("==", TOK_EQUAL)
		typeMap.Set("<>", TOK_NOTEQUAL)
		typeMap.Set(">", TOK_GREATER)
		typeMap.Set("<", TOK_LESSER)
		typeMap.Set(">=", TOK_GEQUAL)
		typeMap.Set("<=", TOK_LEQUAL)
		typeMap.Set("+", TOK_PLUS)
		typeMap.Set("-", TOK_MINUS)
		typeMap.Set("*", TOK_MUL)
		typeMap.Set("/", TOK_DIV)
		typeMap.Set("%", TOK_MOD)
		typeMap.Set("=", TOK_ASSIGN)
		typeMap.Set(",", TOK_COMMA)
		typeMap.Set(":", TOK_COLON)
		typeMap.Set(";", TOK_SEMICOLON)
		typeMap.Set("(", TOK_OPENPAREN)
		typeMap.Set(")", TOK_CLOSEPAREN)
		typeMap.Set("end", TOK_END)
		typeMap.Set("if", TOK_IF)
		typeMap.Set("elif", TOK_ELIF)
		typeMap.Set("else", TOK_ELSE)
		typeMap.Set("for", TOK_FOR)
		typeMap.Set("while", TOK_WHILE)
		typeMap.Set("var", TOK_VAR)
		typeMap.Set("function", TOK_FUNCTION)
		typeMap.Set("Int", TOK_INT)
		typeMap.Set("Float", TOK_FLOAT)
		typeMap.Set("String", TOK_STRING)

		'Fill symbols table (multichar ones must appear first)
		symbols = "== <> >= <= > < + - * / % = , : ; ( )".Split(" ")

		'Parse all tokens
		Local finish:Bool = False
		While Not finish
			Local tok:Token = NextToken()
			If tok.Type = TOK_EOF
				errToken = tok
				finish = True
			Elseif tok.Type <> TOK_EOL Or (tokens.Length > 0 And Not tokens[tokens.Length-1].IsStatementEnd())
				tokens = tokens.Resize(tokens.Length+1)
				tokens[tokens.Length-1] = tok
			End
		Wend
	End

	Method Tokens:Token[]() Property
		Return tokens
	End

	Method Err:String() Property
		If err = ""
			Return ""
		Elseif errToken.Data <> ""
			Return err + " on file '" + errToken.File + "' at line " + errToken.Line + ", element '" + errToken.Data + "'"
		Else
			Return err + " on file '" + errToken.File + "' at line " + errToken.Line
		End
	End

	Method ErrToken:Token() Property
		Return errToken
	End

	Method Text:String() Property
		Local descMap:IntMap<String> = New IntMap<String>
		descMap.Set(TOK_EOF, "eof")
		descMap.Set(TOK_EOL, "eol")
		descMap.Set(TOK_NUMBER, "number")
		descMap.Set(TOK_STRING, "string")
		descMap.Set(TOK_NOT, "not")
		descMap.Set(TOK_AND, "and")
		descMap.Set(TOK_OR, "or")
		descMap.Set(TOK_EQUAL, "equal")
		descMap.Set(TOK_NOTEQUAL, "notequal")
		descMap.Set(TOK_GREATER, "greater")
		descMap.Set(TOK_LESSER, "lesser")
		descMap.Set(TOK_GEQUAL, "gequal")
		descMap.Set(TOK_LEQUAL, "lequal")
		descMap.Set(TOK_PLUS, "plus")
		descMap.Set(TOK_MINUS, "minus")
		descMap.Set(TOK_MUL, "mul")
		descMap.Set(TOK_DIV, "div")
		descMap.Set(TOK_MOD, "mod")
		descMap.Set(TOK_ASSIGN, "assign")
		descMap.Set(TOK_COMMA, "comma")
		descMap.Set(TOK_SEMICOLON, "semicolon")
		descMap.Set(TOK_OPENPAREN, "openparen")
		descMap.Set(TOK_CLOSEPAREN, "closeparen")
		descMap.Set(TOK_END, "end")
		descMap.Set(TOK_IF, "if")
		descMap.Set(TOK_ELIF, "elif")
		descMap.Set(TOK_ELSE, "else")
		descMap.Set(TOK_FOR, "for")
		descMap.Set(TOK_WHILE, "while")
		descMap.Set(TOK_VAR, "var")
		descMap.Set(TOK_DEF, "def")
		descMap.Set(TOK_ID, "id")

		Local str:String = ""
		For Local i:Int = 0 Until tokens.Length()
			Local tok:String = descMap.Get(tokens[i].Type)
			If tokens[i].Type = TOK_NUMBER Or tokens[i].Type = TOK_STRING Or tokens[i].Type = TOK_ID
				str += tok + ":" + tokens[i].Data + "~n"
			Else
				str += tok + "~n"
			End
		Next
		Return str
	End
Private
	Method NextToken:Token()
		'Skip blank characters
		Local skipResult:Token = SkipBlank()
		If skipResult <> Null Then Return skipResult

		'Check end of file
		If offset = buffer.Length() Then Return New Token(TOK_EOF, "", file, line)

		'Check numeric literal
		Local negNumber:Bool = False
		If buffer[offset] = CHAR_MINUS And offset+1 < buffer.Length() And IsNumber(buffer[offset+1]) Then negNumber = True
		If negNumber Or IsNumber(buffer[offset])
			Local str:String = ""
			If buffer[offset] = CHAR_MINUS Then str = "-"; offset += 1
			While IsNumber(buffer[offset])
				str += String.FromChar(buffer[offset])
				offset += 1
			Wend
			If buffer[offset] = CHAR_DOT
				'Float
				str += "."
				offset += 1
				If Not IsNumber(buffer[offset])
					err = "Invalid decimal number"
					Return New Token(TOK_EOF, "", file, line)
				End
				While IsNumber(buffer[offset])
					str += String.FromChar(buffer[offset])
					offset += 1
				Wend
				Return New Token(TOK_FLOATLITERAL, str, file, line)
			Else
				'Int
				Return New Token(TOK_INTLITERAL, str, file, line)
			End
		End

		'Check symbol
		Local symbol:String = CheckSymbol()
		If symbol <> ""
			offset += symbol.Length()
			Return New Token(Type(symbol), symbol, file, line)
		End

		'Check string
		If buffer[offset] = CHAR_DQUOTE
			Local str:String = ""
			offset += 1	'Skip "
			While offset < buffer.Length()-1 And buffer[offset] <> CHAR_DQUOTE And buffer[offset] <> CHAR_LF
				str += String.FromChar(buffer[offset])
				offset += 1
			Wend
			If buffer[offset] <> CHAR_DQUOTE
				err = "String must be closed"
				Return New Token(TOK_EOF, "", file, line)
			End
			offset += 1	'Skip "
			Return New Token(TOK_STRINGLITERAL, str, file, line)
		#Rem
		Elseif buffer[offset] = CHAR_QUOTE
			Local str:String = ""
			offset += 1	'Skip '
			While offset < buffer.Length()-1 And buffer[offset] <> CHAR_QUOTE And buffer[offset] <> CHAR_LF
				str += String.FromChar(buffer[offset])
				offset += 1
			Wend
			If buffer[offset] <> CHAR_QUOTE
				err = "String must be closed"
				Return New Token(TOK_EOF, "", file, line)
			End
			offset += 1	'Skip '
			Return New Token(TOK_STRINGLITERAL, str, file, line)
		#End
		End

		'Check keyword or identifier
		If IsAlpha(buffer[offset])
			Local str:String = ""
			While offset < buffer.Length() And (IsAlpha(buffer[offset]) Or IsNumber(buffer[offset]))
				str += String.FromChar(buffer[offset])
				offset += 1
			Wend
			Return New Token(Type(str), str, file, line)
		End

		'Not recognized
		err = "Unrecognized token"
		Return New Token(TOK_EOF, String.FromChar(buffer[offset]), file, line)
	End

	Method SkipBlank:Token()
		While offset < buffer.Length() And (buffer[offset] = CHAR_SPACE Or buffer[offset] = CHAR_TAB Or buffer[offset] = CHAR_LF Or IsSLComment() Or IsMLComment())
			If IsSLComment()
				offset += 2	'Skip //
				While offset < buffer.Length() And buffer[offset] <> CHAR_LF
					offset += 1
				Wend
			End
			If IsMLComment()
				offset += 2	'Skip /*
				While offset < buffer.Length()-1 And (buffer[offset] <> CHAR_STAR Or (buffer[offset] = CHAR_STAR And buffer[offset+1] <> CHAR_FSLASH))
					If buffer[offset] = CHAR_LF Then line += 1
					offset += 1
				Wend
				If offset+1 = buffer.Length()
					err = "Comment must be closed"
					Return New Token(TOK_EOF, "", file, line)
				End
				offset += 1	'Skip ending *
			End
			Local isEol:Bool = False
			If buffer[offset] = CHAR_LF Then isEol = True
			If isEol Then line += 1
			If offset < buffer.Length() Then offset += 1	'Skip LF or trailing /
			If isEol Then Return New Token(TOK_EOL, "\n", file, line-1)
		Wend
		Return Null
	End

	Method IsSLComment:Bool()
		If buffer[offset] = CHAR_FSLASH And offset+1 < buffer.Length() And buffer[offset+1] = CHAR_FSLASH
			Return True
		Else
			Return False
		End
	End

	Method IsMLComment:Bool()
		If buffer[offset] = CHAR_FSLASH And offset+1 < buffer.Length() And buffer[offset+1] = CHAR_STAR
			Return True
		Else
			Return False
		End
	End

	Method IsNumber:Bool(c:Int)
		If c >= CHAR_0 And c <= CHAR_9
			Return True
		Else
			Return False
		End
	End

	Method IsAlpha:Bool(c:Int)
		If c = CHAR_UNDERSCORE Or (c >= CHAR_A And c <= CHAR_Z) Or (c >= CHAR_a And c <= CHAR_z)
			Return True
		Else
			Return False
		End
	End

	Method CheckSymbol:String()
		For Local symbolIndex:Int = 0 Until symbols.Length()
			Local str:String = ""
			For Local bufferIndex:Int = 0 Until symbols[symbolIndex].Length()
				If offset + bufferIndex < buffer.Length()
					str += String.FromChar(buffer[offset + bufferIndex])
				End
			Next
			If str = symbols[symbolIndex] Then Return str
		Next
		Return ""
	End

	Method Type:Int(symbol:String)
		If typeMap.Contains(symbol)
			Return typeMap.Get(symbol)
		Else
			Return TOK_ID
		End
	End

	Const CHAR_TAB			: Int = 9
	Const CHAR_LF			: Int = 10
	Const CHAR_SPACE		: Int = 32
	Const CHAR_DQUOTE		: Int = 34
	Const CHAR_QUOTE		: Int = 39
	Const CHAR_STAR			: Int = 42
	Const CHAR_MINUS		: Int = 45
	Const CHAR_DOT			: Int = 46
	Const CHAR_FSLASH		: Int = 47
	Const CHAR_0			: Int = 48
	Const CHAR_9			: Int = 57
	Const CHAR_A			: Int = 65
	Const CHAR_Z			: Int = 90
	Const CHAR_a			: Int = 97
	Const CHAR_z			: Int = 122
	Const CHAR_UNDERSCORE	: Int = 95

	Field buffer		: String
	Field offset		: Int
	Field file			: String
	Field line			: Int
	Field symbols		: String[0]
	Field err			: String
	Field errToken		: Token
	Field tokens		: Token[0]
	Field typeMap		: StringMap<Int>
End
