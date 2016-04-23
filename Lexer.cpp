#include "Lexer.h"

Lexer::Lexer(string filePath)  {
  fileReader = new FileReader(filePath);
  fileReader->OpenFile();
  TokenQueue = new queue<Token>();
  Trees = new stack<Tree*>();
}

Tree* Lexer::Parse()  {

  Tiny();
  return Trees->top();
}

void Lexer::Tiny()  {
  ReadToken(Token_Program);
  Name();
  ReadToken(TokenColon);
  Consts();
  Types();
  Dclns();
  SubProgs();
  Body();
  Name();
  ReadToken(TokenSingleDot);
  BuildTree("program", 7);
}

void Lexer::ReadToken(TokenType type) {

  Token token = TokenQueue->front();

  if (token.Type != type)
  {
    string message = "Expected: " + to_string(type) + ". Found: " + to_string(token.Type);
    throw logic_error(message);
  }

  TokenQueue->pop();
}

void Lexer::Name()  {
  ReadIdentifier();
}

void Lexer::Consts()  {
  if (TokenQueue->front().Type == Token_Const)
  {
    ReadToken(Token_Const);
    int count = 1;
    Const();
    while (TokenQueue->front().Type == TokenComma)
    {
      ReadToken(TokenComma);
      Const();
      count++;
    }
    BuildTree("consts", count);
  }
  else
  {
    BuildTree("consts", 0);
  }
}

void Lexer::Const() {
  Name();
  ReadToken(TokenEquals);
  ConstVal();

  BuildTree("const", 2);
}

void Lexer::ConstVal()  {
  switch (TokenQueue->front().Type) {
    case TokenInteger:
      ReadInt();
      break;
    case TokenChar:
      ReadChar();
      break;
    default:
      Name();
  }
}

void Lexer::Types()  {
  if (TokenQueue->front().Type == Token_Type)
  {
    ReadToken(Token_Type);
    int count = 1;
    Type();
    ReadToken(TokenSemiColon);
    while (TokenQueue->front().Type == TokenIdentifier)
    {
      Type();
      ReadToken(TokenSemiColon);
      count++;
    }
    BuildTree("types", count);
  }
  else
  {
    BuildTree("types", 0);
  }
}

void Lexer::Type() {
  Name();
  ReadToken(TokenEquals);
  LitList();
  BuildTree("type", 2);
}

void Lexer::LitList()  {

  ReadToken(TokenOpenParenthesis);
  int count = 1;
  Name();
  while (TokenQueue->front().Type == TokenComma)
  {
    ReadToken(TokenComma);
    Name();
    count++;
  }
  ReadToken(TokenCloseParenthesis);
  BuildTree("lit", count);
}

void Lexer::SubProgs()  {
  int count = 0;
  while (TokenQueue->front().Type == Token_Function)
  {
    Fcn();
    count++;
  }
  BuildTree("subprogs", count);
}

void Lexer::Params()  {
  int count = 1;
  Dcln();
  while (TokenQueue->front().Type == TokenSemiColon)
  {
    ReadToken(TokenSemiColon);
    Dcln();
    count++;
  }
  BuildTree("params", count);
}

void Lexer::Dcln()  {
  int count = 1;
  Name();
  while (TokenQueue->front().Type == TokenComma)
  {
    ReadToken(TokenComma);
    Name();
    count++;
  }
  ReadToken(TokenColon);
  Name();
  BuildTree("var", count + 1);
}

void Lexer::Dclns() {
  if (TokenQueue->front().Type == Token_Var)
  {
    ReadToken(Token_Var);
    int count = 1;
    Dcln();
    ReadToken(TokenSemiColon);
    while (TokenQueue->front().Type == TokenIdentifier)
    {
      Dcln();
      ReadToken(TokenSemiColon);
      count++;
    }
    BuildTree("dclns", count);
  }
  else
  {
    BuildTree("dclns", 0);
  }
}

void Lexer::Body()  {
  ReadToken(Token_Begin);
  int count = 1;
  Statement();
  while (TokenQueue->front().Type == TokenSemiColon)
  {
    ReadToken(TokenSemiColon);
    Statement();
    count++;
  }
  ReadToken(Token_End);
  BuildTree("block", count);
}

void Lexer::Fcn() {
  ReadToken(Token_Function);
  Name();
  ReadToken(TokenOpenParenthesis);
  Params();
  ReadToken(TokenCloseParenthesis);
  ReadToken(TokenColon);
  Name();
  ReadToken(TokenSemiColon);
  Consts();
  Types();
  Dclns();
  Body();
  Name();
  ReadToken(TokenSemiColon);
  BuildTree("fcn", 8);
}

void Lexer::StrNode()  {
  ReadString();
}

int Lexer::Caseclauses()  {
  int count = 1;
  Caseclause();
  ReadToken(TokenSemiColon);
  while (TokenQueue->front().Type == TokenInteger || TokenQueue->front().Type == TokenChar || TokenQueue->front().Type == TokenIdentifier)
  {
    count++;
    Caseclause();
    ReadToken(TokenSemiColon);
  }
  return count;
}

void Lexer::Caseclause()  {
  int count = 1;
  CaseExpression();
  while (TokenQueue->front().Type == TokenComma)
  {
    ReadToken(TokenComma);
    CaseExpression();
    count++;
  }
  ReadToken(TokenColon);
  Statement();
  BuildTree("case_clause", count + 1);
}

void Lexer::ReadIdentifier()  {
  Token token = TokenQueue->front();

  if (token.Type != TokenIdentifier)
  {
    string message = "Expected: <identifier>. Found: " + to_string(token.Type);
    throw logic_error(message);
  }

  TokenQueue->pop();

  Tree* internal = new Tree(token.value);

  Tree* identifier = new Tree("<identifier>");
  identifier->children.push_back(internal);

  Trees->push(identifier);
}

void Lexer::ReadString() {
  Token token = TokenQueue->front();

  if (token.Type != TokenString)
  {
    string message = "Expected: <string>. Found: " + to_string(token.Type);
    throw logic_error(message);
  }

  TokenQueue->pop();

  Tree* internal = new Tree(token.value);

  Tree* identifier = new Tree("<string>");
  identifier->children.push_back(internal);

  Trees->push(identifier);
}

void Lexer::ReadChar() {

  Token token = TokenQueue->front();

  if (token.Type != TokenChar)
  {
    string message = "Expected: <char>. Found: " + to_string(token.Type);
    throw logic_error(message);
  }

  TokenQueue->pop();

  Tree* id = new Tree("<char>");
  Tree* tempTree = new Tree(token.value);

  id->children.push_back(tempTree);
  Trees->push(id);
}

void Lexer::ReadInt() {

  Token token = TokenQueue->front();

  if (token.Type != TokenInteger)
  {

    string message = "Expected: <integer>. Found: " + to_string(token.Type);
    throw logic_error(message);
  }
  TokenQueue->pop();

  Tree* id = new Tree("<integer>");
  Tree* inner = new Tree(token.value);

  id->children.push_back(inner);
  Trees->push(id);
}

void Lexer::CaseExpression()  {
  ConstVal();
  if (TokenQueue->front().Type == TokenDoubleDot)
  {
    ReadToken(TokenDoubleDot);
    ConstVal();
    BuildTree("..", 2);
  }
}

void Lexer::OutExp() {
  if (TokenQueue->front().Type == TokenString)
  {
    StrNode();
    BuildTree("string", 1);
  }
  else
  {
    Expression();
    BuildTree("integer", 1);
  }
}

void Lexer::OtherwiseClause()  {
  if (TokenQueue->front().Type == Token_Otherwise)
  {
    ReadToken(Token_Otherwise);
    Statement();
    BuildTree("otherwise", 1);
  }
}

void Lexer::Assignment()  {

  Name();
  if (TokenQueue->front().Type == TokenAssign)
  {
    ReadToken(TokenAssign);
    Expression();
    BuildTree("assign", 2);
  }
  else if (TokenQueue->front().Type == TokenSwap)
  {
    ReadToken(TokenSwap);
    Name();
    BuildTree("swap", 2);
  }
  else
  {
    string message = "Expected: TokenAssign/TokenSwap. Found: " + to_string(TokenQueue->front().Type);
    throw logic_error(message);
  }
}

void Lexer::ForStat()  {
  if (TokenQueue->front().Type == TokenIdentifier)
  {
    Assignment();
  }
  else
  {
    BuildTree("<null>", 0);
  }
}

void Lexer::ForExp() {

  if (TokenQueue->front().Type == TokenMinus ||
    TokenQueue->front().Type == TokenPlus ||
    TokenQueue->front().Type == TokenNot ||
    TokenQueue->front().Type == Token_EOF ||
    TokenQueue->front().Type == TokenIdentifier ||
    TokenQueue->front().Type == TokenInteger ||
    TokenQueue->front().Type == TokenChar ||
    TokenQueue->front().Type == TokenOpenParenthesis ||
    TokenQueue->front().Type == Token_Succ ||
    TokenQueue->front().Type == Token_Pred ||
    TokenQueue->front().Type == Token_Chr ||
    TokenQueue->front().Type == Token_Ord)
  {
    Expression();
  }
  else
  {
    BuildTree("true", 0);
  }
}

void Lexer::Expression()  {

  Term();
  switch (TokenQueue->front().Type) {
    case  TokenLessThanEquals:
      ReadToken(TokenLessThanEquals);
      Term();
      BuildTree("<=", 2);
      break;
    case  TokenLessThan:
      ReadToken(TokenLessThan);
      Term();
      BuildTree("<", 2);
      break;
    case TokenGreaterThanEquals:
      ReadToken(TokenGreaterThanEquals);
      Term();
      BuildTree(">=", 2);
      break;
    case TokenGreaterThan:
      ReadToken(TokenGreaterThan);
      Term();
      BuildTree(">", 2);
      break;
    case TokenEquals:
      ReadToken(TokenEquals);
      Term();
      BuildTree("=", 2);
      break;
    case TokenNotEquals:
      ReadToken(TokenNotEquals);
      Term();
      BuildTree("<>", 2);
      break;
    default:
      break;
  }
}

void Lexer::Term()  {
  Factor();
  while(TokenQueue->front().Type == TokenPlus || TokenQueue->front().Type == TokenMinus || TokenQueue->front().Type == TokenOr)
  {
    if (TokenQueue->front().Type == TokenPlus)
    {
      ReadToken(TokenPlus);
      Factor();
      BuildTree("+", 2);
    }
    else if (TokenQueue->front().Type == TokenMinus)
    {
      ReadToken(TokenMinus);
      Factor();
      BuildTree("-", 2);
    }
    else if (TokenQueue->front().Type == TokenOr)
    {
      ReadToken(TokenOr);
      Factor();
      BuildTree("or", 2);
    }
  }
}

void Lexer::Factor()  {
  Primary();
  if (TokenQueue->front().Type == TokenMultiply)
  {
    ReadToken(TokenMultiply);
    Factor();
    BuildTree("*", 2);
  }
  else if (TokenQueue->front().Type == TokenDivide)
  {
    ReadToken(TokenDivide);
    Factor();
    BuildTree("/", 2);
  }
  else if (TokenQueue->front().Type == TokenAnd)
  {
    ReadToken(TokenAnd);
    Factor();
    BuildTree("and", 2);
  }
  else if (TokenQueue->front().Type == TokenMod)
  {
    ReadToken(TokenMod);
    Factor();
    BuildTree("mod", 2);
  }
}

void Lexer::Statement() {
  int count = 0;

  switch (TokenQueue->front().Type) {
    case TokenIdentifier:
      Assignment();
      break;
    case Token_Output:
      ReadToken(Token_Output);
      ReadToken(TokenOpenParenthesis);
      count = 1;
      OutExp();
      while (TokenQueue->front().Type == TokenComma)
      {
        ReadToken(TokenComma);
        OutExp();
        count++;
      }
      ReadToken(TokenCloseParenthesis);
      BuildTree("output", count);
      break;
    case Token_If:
      ReadToken(Token_If);
      Expression();
      ReadToken(Token_Then);
      Statement();
      if (TokenQueue->front().Type == Token_Else)
      {
        ReadToken(Token_Else);
        Statement();
        BuildTree("if", 3);
      }
      else
      {
        BuildTree("if", 2);
      }
      break;
    case Token_While:
      ReadToken(Token_While);
      Expression();
      ReadToken(Token_Do);
      Statement();
      BuildTree("while", 2);
      break;
    case Token_Repeat:
      ReadToken(Token_Repeat);
      count = 1;
      Statement();
      while (TokenQueue->front().Type == TokenSemiColon)
      {
        ReadToken(TokenSemiColon);
        Statement();
        count++;
      }
      ReadToken(Token_Until);
      Expression();
      BuildTree("repeat", count + 1);
      break;
    case Token_For:
      ReadToken(Token_For);
      ReadToken(TokenOpenParenthesis);
      ForStat();
      ReadToken(TokenSemiColon);
      ForExp();
      ReadToken(TokenSemiColon);
      ForStat();
      ReadToken(TokenCloseParenthesis);
      Statement();
      BuildTree("for", 4);
      break;
    case Token_Loop:
      ReadToken(Token_Loop);
      count = 1;
      Statement();
      while (TokenQueue->front().Type == TokenSemiColon)
      {
        ReadToken(TokenSemiColon);
        Statement();
        count++;
      }
      ReadToken(Token_Pool);
      BuildTree("loop", count);
      break;
    case Token_Case:
      ReadToken(Token_Case);
      Expression();
      ReadToken(Token_Of);
      count = Caseclauses();
      if (TokenQueue->front().Type == Token_Otherwise)
      {
        OtherwiseClause();
        ReadToken(Token_End);
        BuildTree("case", 2 + count);
      }
      else
      {
        ReadToken(Token_End);
        BuildTree("case", 1 + count);
      }
      break;
    case Token_Read:
      ReadToken(Token_Read);
      ReadToken(TokenOpenParenthesis);
      count = 1;
      Name();
      while (TokenQueue->front().Type == TokenComma)
      {
        ReadToken(TokenComma);
        Name();
        count++;
      }
      ReadToken(TokenCloseParenthesis);
      BuildTree("read", count);
      break;
    case Token_Exit:
      ReadToken(Token_Exit);
      BuildTree("exit",  0);
      break;
    case Token_Return:
      ReadToken(Token_Return);
      Expression();
      BuildTree("return", 1);
      break;
    case Token_Begin:
      Body();
      break;
    default:
      BuildTree("<null>", 0);
  }
}

void Lexer::Primary() {
  switch (TokenQueue->front().Type) {
    case TokenInteger:
      ReadInt();
      break;
    case TokenChar:
      ReadChar();
      break;
    case TokenMinus:
      ReadToken(TokenMinus);
      Primary();
      BuildTree("-", 1);
      break;
    case TokenPlus:
      ReadToken(TokenPlus);
      Primary();
      break;
    case TokenNot:
      ReadToken(TokenNot);
      Primary();
      BuildTree("not", 1);
      break;
    case Token_EOF:
      ReadToken(Token_EOF);
      BuildTree("eof", 0);
      break;
    case TokenIdentifier:
      Name();
      if (TokenQueue->front().Type == TokenOpenParenthesis)
      {
        ReadToken(TokenOpenParenthesis);
        int count = 1;
        Expression();
        while (TokenQueue->front().Type == TokenComma)
        {
          ReadToken(TokenComma);
          Expression();
          count++;
        }
        ReadToken(TokenCloseParenthesis);
        BuildTree("call", count + 1);
      }
      break;
    case TokenOpenParenthesis:
      ReadToken(TokenOpenParenthesis);
      Expression();
      ReadToken(TokenCloseParenthesis);
      break;
    case Token_Succ:
      ReadToken(Token_Succ);
      ReadToken(TokenOpenParenthesis);
      Expression();
      ReadToken(TokenCloseParenthesis);
      BuildTree("succ", 1);
      break;
    case Token_Pred:
      ReadToken(Token_Pred);
      ReadToken(TokenOpenParenthesis);
      Expression();
      ReadToken(TokenCloseParenthesis);
      BuildTree("pred", 1);
      break;
    case Token_Chr:
      ReadToken(Token_Chr);
      ReadToken(TokenOpenParenthesis);
      Expression();
      ReadToken(TokenCloseParenthesis);
      BuildTree("chr", 1);
      break;
    case Token_Ord:
      ReadToken(Token_Ord);
      ReadToken(TokenOpenParenthesis);
      Expression();
      ReadToken(TokenCloseParenthesis);
      BuildTree("ord", 1);
      break;
    default:
    throw logic_error("Expected: Primary");
  }
}

void Lexer::Initialize() {

    char read_char = fileReader->GetNext();

    while(true) {

        Token myToken = GetToken(read_char);
        if(myToken.Type != 0 && myToken.Type != 1 && myToken.Type != 2 && myToken.Type != 3 && myToken.Type != 4)  {
          TokenQueue->push(myToken);
        }

        if(myToken.Type == 4)  {
          string message = "Invalid Token found, program exit!";
          throw logic_error(message);
        }

        if(myToken.Type == 100)  {
          return;
        }
        read_char = fileReader->GetNext();
    }
}

Token Lexer::GetToken(char read_char) {

  if(isdigit(read_char)) {
    Token digit_token = ReadintegerToken(read_char);
    return digit_token;
  }
  else if(IsOperator(read_char)){
    Token operator_token = ReadOperatorToken(read_char);
    return operator_token;
  }
  else if(IsPunctuationOp(read_char)) {
    Token punctuation_token = ReadPunctuationToken(read_char);
    return punctuation_token;
  }

  else if(IsSingleQuoteCharacter(read_char))  {
    Token char_token = ReadCharacterToken();
    return char_token;
  }
  else if(IsWhitespace(read_char)){
    Token whiteSpace_token = ReadWhiteSpaceToken(read_char);
    return whiteSpace_token;
  }
  else if(IsOpenCurly(read_char)) {
    Token comment_token = ReadCommentType1Token();
    return comment_token;
  }
  else if(IsHashTag(read_char)) {
    Token comment_token = ReadCommentType3Token();
    return comment_token;
  }
  else if(IsDoubleQuouteChar(read_char)) {
    Token string_token = ReadStringToken();
    return string_token;
  }
  else if(IsOpenParenthesis(read_char)) {
    Token par_token = ReadOpenParenthesisToken();
    return par_token;
  }
  else if(IsCloseParenthesis(read_char)) {
    Token par_token = ReadCloseParenthesisToken();
    return par_token;
  }
  else if(IsPossibleIdentifier(read_char))  {
    Token temp_token = ReadPossibleKeyOrId(read_char);
    return temp_token;
  }
  else  {
    TokenType temp_type = TokenInvalidToken;
    Token token_toReturn (temp_type, "InvaliddfdgfsgToken");
    return token_toReturn;
  }
}

Token Lexer::ReadCommentType3Token()  {
  char read_next = fileReader->GetNext();

  string comment_string = "";

  while(read_next != '\n') {
    comment_string += read_next;
    read_next = fileReader->GetNext();
  }
  TokenType temp_type = TokenCommentType3;
  Token token_toReturn (temp_type, comment_string);
  return token_toReturn;
}

Token Lexer::ReadKeywordToken(string keyWord) {

  if(keyWord.compare("program") == 0) {
    TokenType temp_type = Token_Program;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("var") == 0) {
    TokenType temp_type = Token_Var;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("const") == 0 ){
    TokenType temp_type = Token_Const;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("type") == 0)  {
    TokenType temp_type = Token_Type;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("function") == 0)  {
    TokenType temp_type = Token_Function;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("return") == 0)  {
    TokenType temp_type = Token_Return;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("begin") == 0) {
    TokenType temp_type = Token_Begin;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("end") == 0) {
    TokenType temp_type = Token_End;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("output") == 0) {
    TokenType temp_type = Token_Output;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("if") == 0){
    TokenType temp_type = Token_If;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("then") == 0)  {
    TokenType temp_type = Token_Then;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("else") == 0)  {
    TokenType temp_type = Token_Else;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("while") == 0) {
    TokenType temp_type = Token_While;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("do") == 0)  {
    TokenType temp_type = Token_Do;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("case") == 0)  {
    TokenType temp_type = Token_Case;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("of") == 0)  {
    TokenType temp_type = Token_Of;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("otherwise") == 0)  {
    TokenType temp_type = Token_Otherwise;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("repeat") == 0)  {
    TokenType temp_type = Token_Repeat;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("for") == 0){
    TokenType temp_type = Token_For;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("until") == 0) {
    TokenType temp_type = Token_Until;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("loop") == 0)  {
    TokenType temp_type = Token_Loop;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("pool") == 0)  {
    TokenType temp_type = Token_Pool;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("exit") == 0)  {
    TokenType temp_type = Token_Exit;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("mod") == 0) {
    TokenType temp_type = TokenMod;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("and") == 0) {
    TokenType temp_type = TokenAnd;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("or") == 0)  {
    TokenType temp_type = TokenOr;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("not") == 0) {
    TokenType temp_type = TokenNot;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("read") == 0)  {
    TokenType temp_type = Token_Read;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("succ") == 0)  {
    TokenType temp_type = Token_Succ;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("pred") == 0)  {
    TokenType temp_type = Token_Pred;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("chr") == 0) {
    TokenType temp_type = Token_Chr;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("ord") == 0) {
    TokenType temp_type = Token_Ord;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }
  if(keyWord.compare("eof") == 0) {
    TokenType temp_type = Token_EOF;
    Token temp_tok(temp_type, keyWord);
    return temp_tok;
  }

  TokenType temp_type = TokenInvalidToken;
  Token temp_tok(temp_type, "Invalid Token");
  return temp_tok;
}

Token Lexer::ReadPossibleKeyOrId(char read_char) {

  char read_next = fileReader->GetNext();
  string target = "";
  target += read_char;

  while(IsPossibleIdentifier(read_next) || isdigit(read_next))  {
    target += read_next;
    read_next = fileReader->GetNext();
  }
  fileReader->PutBack(read_next);

  if(IsKeyWord(target)) {
    return ReadKeywordToken(target);
  }
  else {
    TokenType temp_type = TokenIdentifier;
    Token token_toReturn (temp_type, target);
    return token_toReturn;
  }

}

Token Lexer::ReadOpenParenthesisToken()  {

  TokenType temp_type = TokenOpenParenthesis;
  Token token_toReturn (temp_type, "(");
  return token_toReturn;
}

Token Lexer::ReadCloseParenthesisToken()  {

  TokenType temp_type = TokenCloseParenthesis;
  Token token_toReturn (temp_type, ")");
  return token_toReturn;
}

Token Lexer::ReadStringToken()  {

  char read_next = fileReader->GetNext();

  string str = "";

  while(!IsDoubleQuouteChar(read_next)) {
    str += read_next;
    read_next = fileReader->GetNext();
  }
  TokenType temp_type = TokenString;
  Token token_toReturn (temp_type, str);
  return token_toReturn;;
}

Token Lexer::ReadCommentType2Token()  {

  char read_next = fileReader->GetNext();
  char read_next_next = fileReader->GetNext();

  string comment_string = "";

  while(!(IsStar(read_next) && IsDivide(read_next_next))) {
    comment_string += read_next;
    read_next = read_next_next;
    read_next_next = fileReader->GetNext();
  }

  TokenType temp_type = TokenCommentType2;
  Token token_toReturn (temp_type, comment_string);
  return token_toReturn;
}

Token Lexer::ReadCommentType1Token()  {
  char read_next = fileReader->GetNext();

  string comment_string = "";

  while(!IsCloseCurly(read_next)) {
    comment_string += read_next;
    read_next = fileReader->GetNext();
  }
  TokenType temp_type = TokenCommentType1;
  Token token_toReturn (temp_type, comment_string);
  return token_toReturn;
}

Token Lexer::ReadWhiteSpaceToken(char read_char)  {

  TokenType temp_type = TokenWhiteSpace;
  Token token_toReturn (temp_type, "WhiteSpaceChar");
  return token_toReturn;
}

Token Lexer::ReadCharacterToken()  {
  char read_next = fileReader->GetNext();
  if(IsValidCharValue(read_next)) {
    char read_next_next = fileReader->GetNext();
      if(IsSingleQuoteCharacter(read_next_next))  {
        TokenType temp_type = TokenChar;
        stringstream ss;
        string target;
        ss << read_next;
        ss >> target;
        Token token_toReturn (temp_type, target);
        return token_toReturn;
      }
  }
  TokenType temp_type = TokenInvalidToken;
  Token token_toReturn (temp_type, "InvalidToken");
  return token_toReturn;
}

Token Lexer::ReadPunctuationToken(char read_char)  {
  if(read_char == ';')  {
    TokenType temp_type = TokenSemiColon;
    Token token_toReturn (temp_type, ";");
    return token_toReturn;
  }
  if(read_char == ',')  {
    TokenType temp_type = TokenComma;
    Token token_toReturn (temp_type, ",");
    return token_toReturn;
  }
  if(read_char == '.')  {
    char read_next = fileReader->GetNext();
    if(IsDoublePunctuationDot(read_next))  {
      TokenType temp_type = TokenDoubleDot;
      Token token_toReturn (temp_type, "..");
      return token_toReturn;
    }
    else  {
      fileReader->PutBack(read_next);
      TokenType temp_type = TokenSingleDot;
      Token token_toReturn (temp_type, ".");
      return token_toReturn;
    }
  }
  if(read_char == ':')  {

    char read_next = fileReader->GetNext();
    if(IsSwapOrAssignment(read_next)) {
      char read_next_next = fileReader->GetNext();
      if(IsSwap(read_next_next))  {
        TokenType temp_type = TokenSwap;
        Token token_toReturn (temp_type, ":=:");
        return token_toReturn;
      }
      else {
        fileReader->PutBack(read_next_next);
        TokenType temp_type = TokenAssign;
        Token token_toReturn (temp_type, ":=");
        return token_toReturn;
      }
    }
    else {
      fileReader->PutBack(read_next);
      TokenType temp_type = TokenColon;
      Token token_toReturn (temp_type, ":");
      return token_toReturn;
    }
  }
  TokenType temp_type = TokenInvalidToken;
  Token token_toReturn (temp_type, "InvalidToken");
  return token_toReturn;
}

Token Lexer::ReadOperatorToken(char read_char) {
  if(read_char == '+')  {
    TokenType temp_type = TokenPlus;
    Token token_toReturn (temp_type, "+");
    return token_toReturn;
  }
  if(read_char == '-')  {
    TokenType temp_type = TokenMinus;
    Token token_toReturn (temp_type, "-");
    return token_toReturn;
  }
  if(read_char == '*')  {
    TokenType temp_type = TokenMultiply;
    Token token_toReturn (temp_type, "*");
    return token_toReturn;
  }
  if(read_char == '/')  {
    char read_next = fileReader->GetNext();
    if(IsStar(read_next)) {
      Token token_toReturn = ReadCommentType2Token();
      return token_toReturn;
    }
    else{
      fileReader->PutBack(read_next);
      TokenType temp_type = TokenDivide;
      Token token_toReturn (temp_type, "/");
      return token_toReturn;
    }
  }
  if(read_char == '=')  {
    TokenType temp_type = TokenEquals;
    Token token_toReturn (temp_type, "=");
    return token_toReturn;
  }
  if(read_char == '<')  {
    char read_next = fileReader->GetNext();
    if(IsDoubleCompareOperatorForLessThan(read_next))  {
      if(read_next == '>') {
        TokenType temp_type = TokenNotEquals;
        Token token_toReturn (temp_type, "<>");
        return token_toReturn;
      }
      else{
        TokenType temp_type = TokenLessThanEquals;
        Token token_toReturn (temp_type, "<=");
        return token_toReturn;
      }
    }
    else{
      fileReader->PutBack(read_next);
      TokenType temp_type = TokenLessThan;
      Token token_toReturn (temp_type, "<");
      return token_toReturn;
    }
  }
  if(read_char == '>')  {
    char read_next = fileReader->GetNext();

    if(IsDoubleCompareOperator(read_next))  {
      TokenType temp_type = TokenGreaterThanEquals;
      Token token_toReturn (temp_type, ">=");
      return token_toReturn;
    }
    else{
      fileReader->PutBack(read_next);
      TokenType temp_type = TokenGreaterThan;
      Token token_toReturn (temp_type, ">");
      return token_toReturn;
    }
  }
  TokenType temp_type = TokenInvalidToken;
  Token token_toReturn (temp_type, "InvalidToken");
  return token_toReturn;
}

Token Lexer::ReadintegerToken(char read_char) {

  string integer_string = "";
  integer_string += read_char;

  char next_read = fileReader->GetNext();

  while(isdigit(next_read)) {
    integer_string += next_read;
    next_read = fileReader->GetNext();
  }
  fileReader->PutBack(next_read);

  TokenType temp_type = TokenInteger;
  Token token_toReturn (temp_type, integer_string);

  return token_toReturn;
}

void Lexer::PrintQueue()  {

  while(!TokenQueue->empty()) {
    Token temp = TokenQueue->front();
    TokenQueue->pop();
    cout << "TokenType: " << temp.GetTokenString() << " TokenValue: " << temp.value << endl;
  }
}

bool Lexer::IsOperator(char read_char)  {
  if (read_char == '+'|| read_char == '-' || read_char == '*'||
      read_char == '/' || read_char == '=' || read_char == '<' ||
      read_char == '>') return true;

  return false;
}

bool Lexer::IsDoubleCompareOperator(char read_char)  {
  if (read_char == '=')return true;
  return false;
}

bool Lexer::IsDoubleCompareOperatorForLessThan(char read_char)  {
  if (read_char == '=' || read_char == '>')return true;
  return false;
}

bool Lexer::IsPunctuationOp(char read_char) {

  if (read_char == ':' || read_char == '.' || read_char == ';' ||
      read_char == ',') return true;
  return false;
}

bool Lexer::IsDoublePunctuationDot(char read_char) {
  if(read_char == '.') return true;
  return false;
}

bool Lexer::IsSwapOrAssignment(char read_char)  {
  if(read_char == '=') return true;
  return false;
}

bool Lexer::IsSwap(char read_char)  {
  if(read_char == ':') return true;
  return false;
}

bool Lexer::IsWhitespace(char read_char)  {
  if(read_char == '\t' || read_char == ' ' || read_char == '\n' || read_char == '\f' || read_char == '\v') return true;
  return false;
}

bool Lexer::IsSingleQuoteCharacter(char read_char)  {
  if(read_char == '\'') return true;
  return false;
}

bool Lexer::IsValidCharValue(char read_char)  {
  if(read_char != '\'') return true;
  return false;
}

bool Lexer::IsOpenCurly(char read_char) {
  if(read_char == '{') return true;
  return false;
}

bool Lexer::IsCloseCurly(char read_char) {
  if(read_char == '}') return true;
  return false;
}

bool Lexer::IsStar(char read_char)  {
  if(read_char == '*') return true;
  return false;
}

bool Lexer::IsDivide(char read_char)  {
  if(read_char == '/') return true;
  return false;
}

bool Lexer::IsDoubleQuouteChar(char read_char) {
  if(read_char == '"') return true;
  return false;
}

bool Lexer::IsValidStringValue(char read_char)  {
  if(read_char != '"') return true;
  return false;
}

bool Lexer::IsOpenParenthesis(char read_char)  {
  if(read_char == '(') return true;
  return false;
}

bool Lexer::IsCloseParenthesis(char read_char){
  if(read_char == ')') return true;
  return false;
}

bool Lexer::IsPossibleIdentifier(char read_char)  {

  if(read_char == '_' || read_char == 'a' || read_char == 'A' || read_char == 'b' || read_char == 'B' ||
    read_char == 'a' || read_char == 'A' || read_char == 'b' || read_char == 'B' ||
    read_char == 'c' || read_char == 'C' || read_char == 'd' || read_char == 'D' ||
    read_char == 'e' || read_char == 'E' || read_char == 'f' || read_char == 'F' ||
    read_char == 'g' || read_char == 'G' || read_char == 'h' || read_char == 'H' ||
    read_char == 'i' || read_char == 'I' || read_char == 'j' || read_char == 'J' ||
    read_char == 'k' || read_char == 'K' || read_char == 'l' || read_char == 'L' ||
    read_char == 'm' || read_char == 'M' || read_char == 'n' || read_char == 'N' ||
    read_char == 'o' || read_char == 'O' || read_char == 'p' || read_char == 'P' ||
    read_char == 'q' || read_char == 'Q' || read_char == 'r' || read_char == 'R' ||
    read_char == 's' || read_char == 'S' || read_char == 't' || read_char == 'T' ||
    read_char == 'u' || read_char == 'U' || read_char == 'v' || read_char == 'V' ||
    read_char == 'w' || read_char == 'W' || read_char == 'x' || read_char == 'X' ||
    read_char == 'y' || read_char == 'Y' || read_char == 'z' || read_char == 'Z') return true;
    return false;
}

bool Lexer::IsHashTag(char read_char) {
  if(read_char == '#')  return true;
  return false;
}

bool Lexer::IsKeyWord(string str_key) {

  if  (str_key.compare("program") == 0 || str_key.compare("var") == 0 || str_key.compare("const") == 0 ||
      str_key.compare("type") == 0 || str_key.compare("function") == 0 || str_key.compare("return") == 0 ||
      str_key.compare("begin") == 0 || str_key.compare("end") == 0 || str_key.compare("output") == 0 ||
      str_key.compare("if") == 0 || str_key.compare("then") == 0 || str_key.compare("else") == 0 ||
      str_key.compare("while") == 0 || str_key.compare("do") == 0 || str_key.compare("case") == 0 ||
      str_key.compare("of") == 0 || str_key.compare("otherwise") == 0 || str_key.compare("repeat") == 0 ||
      str_key.compare("for") == 0 || str_key.compare("until") == 0 || str_key.compare("loop") == 0 ||
      str_key.compare("pool") == 0 || str_key.compare("exit") == 0 || str_key.compare("mod") == 0 ||
      str_key.compare("and") == 0 || str_key.compare("or") == 0 || str_key.compare("not") == 0 ||
      str_key.compare("read") == 0 || str_key.compare("succ") == 0 || str_key.compare("pred") == 0 ||
      str_key.compare("chr") == 0 || str_key.compare("ord") == 0 || str_key.compare("eof") == 0) return true;
      return false;
}


void Lexer::BuildTree(string name, int count)  {

  Tree* result = new Tree(name);
  stack<Tree*> temp;


  for (int i = 0; i < count; i++) {
    temp.push(Trees->top());
    Trees->pop();
  }

  for (int i = 0; i < count; i++) {
    result->children.push_back(temp.top());
    temp.pop();
  }

  Trees->push(result);
}
