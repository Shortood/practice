public enum TokenType { // 토큰의 id
     Bool, Char, Else, False, Float,
     If, Int, Main, True, While,
     Eof, LeftBrace, RightBrace, LeftBracket, RightBracket,
     LeftParen, RightParen, Semicolon, Comma, Assign,
     Equals, Less, LessEqual, Greater, GreaterEqual,
     Not, NotEqual, Plus, Minus, Multiply,
     Divide, And, Or, Identifier, IntLiteral,
     FloatLiteral, CharLiteral
}
// lexical structer에 해당하는 토큰들의 정보를 정의하기 위한 선언