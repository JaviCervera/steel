Strict

Import token

Public
Class TokenStream
	Method New(tokens:Token[])
		Self.tokens = tokens
		Self.pos = 0
	End
	
	Method Tokens:Token[]() Property
		Return tokens
	End
	
	Method Pos:Int() Property
		Return pos
	End
	
	Method NextToken:Token() Property
		SkipEols()
		Local tok:Token = tokens[pos]
		pos += 1
		Return tok
	End
	
	Method Peek:Token(offset:Int = 0)
		Local prevPos:Int = Self.pos
		Skip(offset)
		Local tok:Token = Self.NextToken
		Self.pos = prevPos
		Return tok
	End
	
	Method GoBack:Void()
		pos -= 1
		While pos > 0 And tokens[pos].Type = TOK_EOL
			pos -= 1
		Wend
	End
	
	Method HasNext:Bool()
		Local prevPos:Int = Self.pos
		SkipEols()
		Local hasNext:Bool = pos < tokens.Length()
		Self.pos = prevPos
		Return hasNext
	End
	
	Method Seek:Void(pos:Int)
		Self.pos = pos
	End
	
	Method Skip:Void(count:Int)
		For Local i:Int = 1 To count
			NextToken()
		Next
	End
	
	Method SkipEols:Bool()
		Local skipped: Bool = False
		While pos < tokens.Length() And tokens[pos].Type = TOK_EOL
			pos += 1
			skipped = True
		Wend
		Return skipped
	End
Private
	Field tokens	: Token[]
	Field pos		: Int
End
