%{
#include "ast.hpp"
#include "parser.tab.hpp"
%}

%%

[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
"produce"       { return PLUS; }
"deplete"      { return MINUS; }
"forge"        { return STAR; }
"divide"       { return SLASH; }
"claimeth"     { return EQ; }
"lesser"       { return LT; }
"greater"      { return GT; }
"below"        { return LEQ; }
"above"        { return GEQ; }
"reject"       { return NEQ; }
"allied"       { return AND; }
"or"           { return OR; }
"deny"         { return NOT; }
"gather"       { return OP; }
"release"      { return CP; }
"summon"       { return OB; }
"banish"       { return CB; }
"prithee"      { return IF; }
"elsewise"     { return ELSE; }
"whilst"       { return WHILE; }
"henceforth"   { return VAR; }
"loyal"        { return TRUE; }
"traitor"      { return FALSE; }
"declare"      { return PRINT; }
"proclaim"     { return ASSIGN; }
\n             { return EOL; }
[ \t]          {}

[a-zA-Z_][a-zA-Z_0-9]* { yylval.str = strdup(yytext); return IDENTIFIER; }
\"[^\"]*\"  { yylval.str = strdup(yytext + 1); yylval.str[strlen(yylval.str) - 1] = '\0'; return STRING; }
.           { return 0; }

%%

int yywrap() {
    return 1;
}

