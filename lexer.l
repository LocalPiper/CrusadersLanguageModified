%{
#include "ast.hpp"
#include "parser.tab.hpp"
%}

%%

[0-9]+\.[0-9]+ { yylval.dnum = atof(yytext); return DOUBLE; }
[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
"amass"       { return PLUS; }
"sacrifice"      { return MINUS; }
"conjure"        { return STAR; }
"split"       { return SLASH; }
"claimeth"     { return EQ; }
"unworthy"       { return LT; }
"mightier"      { return GT; }
"nohigher"        { return LEQ; }
"nobelow"        { return GEQ; }
"reject"       { return NEQ; }
"united"       { return AND; }
"either"           { return OR; }
"deny"         { return NOT; }
"invoke"       { return OP; }
"dismiss"      { return CP; }
"commence"       { return OB; }
"conclude"       { return CB; }
"suppose"      { return IF; }
"elsewise"     { return ELSE; }
"aslongas"       { return WHILE; }
"henceforth"   { return VAR; }
"aye"        { return TRUE; }
"nay"      { return FALSE; }
"proclaim"      { return PRINT; }
"bestow"     { return ASSIGN; }
"inscribe"   { return FUNCTION; }
"also"     { return COMMA; }
\n             { return EOL; }
[ \t]          {}

[a-zA-Z_][a-zA-Z_0-9]* { yylval.str = strdup(yytext); return IDENTIFIER; }
\"[^\"]*\"  { yylval.str = strdup(yytext + 1); yylval.str[strlen(yylval.str) - 1] = '\0'; return STRING; }
.           { return 0; }

%%

int yywrap() {
    return 1;
}

