//Гм... Это очень простой компилятор... эээ... калькулятор... :)
//Если что-то кому-то непонятно, то можете обращаться. ILikeLSD@yandex.ru
//---------------------------------------------------------------------------
#include <iostream.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
//---------------------------------------------------------------------------
const int Name = 256;
struct name
{
  char   string[Name];
  name*  pNext;
  double value;
};
name*pHead = 0;
enum token_value{NAME, NUMBER, END, PLUS = '+', DEGREE = '^',
                 MINUS = '-',MUL = '*',DIV = '/',PRINT
                 = ';',ASSIGN = '=', LP = '(',RP = ')'};
enum token_funct{SIN, COS , TAN, CTG, LN, LOG, SQRT, ZERO};
token_value curr_tok;
token_funct curr_funct;
double number_value;
int no_of_errors;
char name_string[Name];
double expr();
double term();
double prim();
double MathFunct(token_funct NameFunct, double dValue);
token_value get_token();
token_funct ViewFunct(char*s);
double error(char*s);
//---------------------------------------------------------------------------
name*look(char*p, int ins = 0)
{
  name*pCurrent = pHead;
  if(ins)
  {
    name*nn = new name;
    strcpy(nn->string,p);
    nn->value = 1;
    nn->pNext = 0;
    if(pHead == 0)
    {
      pHead = nn;
    }
    else if(pHead)
    {
      while(pCurrent->pNext)
      {
        if(strcmp(pCurrent->string,p) == 0)
        {
          delete nn;
          return pCurrent;
        }
        pCurrent = pCurrent->pNext;
      }
      pCurrent->pNext = nn;
    }
    return nn;
  }
  else
  {
    if(pHead == 0)
    {
      error("Name don't search");
      return 0;
    }
    while(1)
    {
      if(strcmp(pCurrent->string,p) == 0)
        return pCurrent;
      if(!pCurrent->pNext)
        break;
      pCurrent = pCurrent->pNext;
    }
    return 0;
  }
}
//---------------------------------------------------------------------------
inline name*insert(char*s){return look(s,1);}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  insert("pi")->value = 3.1415926535897932385;
  insert("e")->value = 2.7182818284590452354;
  while(cin)
  {
    get_token();
    if(curr_tok == END)
      break;
    if(curr_tok == PRINT)
      continue;
    cout << expr() <<"\n";
  }
  return no_of_errors;
}
//---------------------------------------------------------------------------
double expr()
{
  double left = term();
  for(;;)
  {
    switch(curr_tok)
    {
    case PLUS:
      get_token();
      left += term();
      break;
    case MINUS:
      get_token();
      left -= term();
      break;
    default:
      return left;
    }
  }
}
//-------------------------------------------------------------------------
double term()
{
  double left = prim();
  for(;;)
  {
    switch(curr_tok)
    {
    case MUL:
      get_token();
      left *= prim();
      break;
    case DIV:
    {
      get_token();
      double d = prim();
      if(d == 0)
        return error("Division by zero");
      left /= d;
      break;
    }
    case DEGREE:
      get_token();
      left = pow(left, prim());
      break;
    default:
      return left;
    }
  }
}
//---------------------------------------------------------------------------
double prim()
{
  switch(curr_tok)
  {
  case NUMBER:
    get_token();
    return number_value;
  case NAME:
  {
    get_token();
    if(curr_tok == ASSIGN)
    {
      if(look(name_string) == 0)
      {
        get_token();
        if(curr_tok == NUMBER)
        {
          insert(name_string)->value = number_value;
          return number_value;
        }
      }
    }
    if(curr_tok == LP)
    {
      if(ViewFunct(name_string) != ZERO)
      {
        get_token();
        double e = expr();
        if(curr_tok != RP)
          return error("Probably ')'");
        get_token();
        return MathFunct(curr_funct,e);
      }
    }
    if(look(name_string) == 0)
      return error("Understand sumbol");
    return look(name_string)->value;
  }
  case MINUS:
    get_token();
    return -prim();
  case LP:
  {
    get_token();
    double e = expr();
    if(curr_tok != RP)
      return error("Probably ')'");
    get_token();
    return e;
  }
  case END:
    return 1;
  default:
    return error("Probably 'primary'");
  }
}
//---------------------------------------------------------------------------
token_value get_token()
{
  char ch;
  do
  {
    if(!cin.get(ch))
      return curr_tok = END;
  }while(ch != '\n' && isspace(ch));
  switch(ch)
  {
  case ';':
    cin >> ws;
    return curr_tok = PRINT;
  case '\n':
    return curr_tok = PRINT;
  case '*':
  case '/':
  case '+':
  case '-':
  case '(':
  case ')':
  case '=':
  case '^':
    return curr_tok = (token_value)ch;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '.':
    cin.putback(ch);
    cin >> number_value;
    return curr_tok = NUMBER;
  default:
    if(isalpha(ch))
    {
      int i;
      for(i = 0; i <= Name; i++)
      {
        name_string[i] = '\0';
      }
      name_string[0] = ch;
      for(i = 1; cin.get(ch) && isalnum(ch); i++)
      {
        name_string[i] = ch;
      }
      cin.putback(ch);
      return curr_tok = NAME;
    }
    error("Bad sumbol");
    return curr_tok = PRINT;
  }
}
//---------------------------------------------------------------------------
double error(char*s)
{
  cerr << "error: " << s << "\n";
  no_of_errors++;
  return 1;
}
//---------------------------------------------------------------------------
double MathFunct(token_funct NameFunct, double dValue)
{
  switch(NameFunct)
  {
    case LN:
      return log(dValue);
    case LOG:
      return log10(dValue);
    case SIN:              \
      return sin(dValue);
    case COS:
      return cos(dValue);
    case TAN:
      return tan(dValue);
    case CTG:
      return cos(dValue)/sin(dValue);
    case SQRT:
      return sqrt(dValue);
    default:
      return error("Uknow error");
  }
}
//---------------------------------------------------------------------------
token_funct ViewFunct(char*s)
{
  if(strcmp("sin",s) == 0)
    return curr_funct = SIN;
  else if(strcmp("cos",s) == 0)
    return curr_funct = COS;
  else if(strcmp("tan",s) == 0)
    return curr_funct = TAN;
  else if(strcmp("ctg",s) == 0)
    return curr_funct = CTG;
  else if(strcmp("sqrt",s) == 0)
    return curr_funct = SQRT;
  else if(strcmp("ln",s) == 0)
    return curr_funct = LN;
  else if(strcmp("log",s) == 0)
    return curr_funct = LOG;
  else
    return curr_funct = ZERO;
}
//----------------------------EOF 21.04.2001---------------------------------