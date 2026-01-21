Strict

'Ensure 32 bit Windows builds
#If HOST = "winnt"
#CC_OPTS="-m32 -static -s"
#End

Import os
Import luagen
Import lexer
Import lib
Import parser
Import token

Function Main:Int()
	'Check arguments
	If AppArgs().Length <> 2
		Print "Usage: steel filename.prg"
		Return -1
	End
	Local fileArg:String = AppArgs()[1].Replace("~q", "")

	'Get script file(s)
	Local scriptFiles:String[]
	Select FileType(fileArg)
		Case 0	'None
			Print "Error: File '" + fileArg + "' does not exist"
			Return -1
		Case 1 'File
			scriptFiles = [fileArg]
		Case 2 'Directory
			scriptFiles = New String[0]
			Local files:String[] = LoadDir(fileArg)
			For Local file:String = Eachin files
				If ExtractExt(file).ToLower() = "prg"
					scriptFiles = scriptFiles.Resize(scriptFiles.Length + 1)
					scriptFiles[scriptFiles.Length - 1] = fileArg + "/" + file
				End
			Next
	End

	'Generate library from std.defs file
	Local lib:Lib = ParseStdDefs()
	If lib = Null Then Return -1

	'Lexical analysis of all files
	Local lexerTokens:Token[0]
	For Local scriptFile:String = Eachin scriptFiles
		Local lexer:Lexer = New Lexer(LoadString(scriptFile), scriptFile)
		If lexer.Err <> ""
			Print lexer.Err
			Return -1
		End
		lexerTokens = lexerTokens.Resize(lexerTokens.Length + lexer.Tokens.Length)
		For Local i:Int = 0 Until lexer.Tokens.Length
			lexerTokens[lexerTokens.Length - lexer.Tokens.Length + i] = lexer.Tokens[i]
		Next
	End

	'Parse syntax
	Local parser:Parser = New Parser(lexerTokens, lib)
	If parser.Err <> ""
		Print parser.Err
		Return -1
	End

	'Make sure there is a Main function
	If parser.Scanner.Func("Main") = Null
		Print "Main function not found."
		Return -1
	End
	If parser.Scanner.Func("Main").Args.Length <> 0
		Print "Main function cannot have parameters"
		Return -1
	End
	If parser.Scanner.Func("Main").Type <> TOK_VOID
		Print "Main function cannot return a value"
		Return -1
	End

	'Generate output
	Local code:String = New LuaGen(lexerTokens, parser.Scanner, lib).Code
	Local path:String = ExtractDir(fileArg)
	If FileType(fileArg) = 2 Then path = fileArg
	If path <> "" Then path += "/"
	SaveString(code, path + "code.bin")
	Execute("~q" + ExtractDir(AppPath()) + "/luac~q -s -o ~q" + path + "code.bin~q ~q" + path + "/code.bin~q")

	Return 0
End


Function ParseStdDefs:Lib()
	Local lib:Lib = New Lib

	'Load file contents (with UNIX-like file endings)
	Local fileContents:String = LoadString(ExtractDir(AppPath()) + "/std.defs").Replace("~r~n", "~n").Replace("~r", "~n")

	'Generate lines
	Local lines:String[] = fileContents.Split("~n")

	'Process each line
	For Local line:String = Eachin lines
		'Trim spaces
		line = line.Trim()

		'Ignore blank and comment lines
		If line = "" Or line[..2] = "//" Then Continue

		'This separates the data on the left and the right of the (
		Local parenSplit:String[] = line.Split("(")
		If parenSplit.Length <> 2
			Print "Function needs one set of arguments -> " + line
			Return Null
		End
		If parenSplit[0][..9] <> "function "
			Print "Expected function declaration: " + line
			Return Null
		End

		'Extract function name from the left of the (
		Local funcName:String = parenSplit[0].Replace("function ", "").Trim()

		'Extract parameters and type
		Local rightSplit: String[] = parenSplit[1].Split(")")
		Local funcType:Int = TOK_VOID
		If rightSplit.Length > 1 And rightSplit[1] <> ""
			Local repl: String = rightSplit[1].Replace(":", "").Trim()
			funcType = GetType(repl)
			If funcType = TOK_VOID
				Print "Invalid function type '" + repl + "' -> " + line
				Return Null
			End
		End

		'Extract parameters from the right of the (
		Local params:String[] = rightSplit[0].Split(",")
		Local paramTypes:Int[] = New Int[params.Length]
		If params.Length = 1 And params[0] = ""
			paramTypes = []
		Else
			For Local i:Int = 0 Until params.Length()
				paramTypes[i] = GetType(params[i].Split(":")[1])
			Next
		End

		'Add function to lib
		lib.AddFunc(funcName, funcType, paramTypes)
	Next

	Return lib
End


Function GetType:Int(type: String)
	Select type.Trim().ToLower()
		Case "int"
			Return TOK_INT
		Case "float"
			Return TOK_FLOAT
		Case "string"
			Return TOK_STRING
		Default
			Return TOK_VOID
	End
End
