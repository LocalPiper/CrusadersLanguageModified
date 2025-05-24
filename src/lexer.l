%{
#include "ast.hpp"
#include "parser.tab.hpp"
#include <cstdlib>
#include <cstring>
#include <cstdio>

extern int yylineno;

extern int last_good_line;
extern char* last_good_text;

#define UPDATE_GOOD_TOKEN() do { \
    if (last_good_text) free(last_good_text); \
    last_good_line = yylineno; \
    last_good_text = strdup(yytext); \
} while(0)

%}

%%

[0-9]+\.[0-9]+ { UPDATE_GOOD_TOKEN(); yylval.dnum = atof(yytext); return DOUBLE; }
[0-9]+      { UPDATE_GOOD_TOKEN(); yylval.num = atoi(yytext); return NUMBER; }
"amass"       { UPDATE_GOOD_TOKEN(); return PLUS; }
"sacrifice"      { UPDATE_GOOD_TOKEN(); return MINUS; }
"conjure"        { UPDATE_GOOD_TOKEN(); return STAR; }
"split"       { UPDATE_GOOD_TOKEN(); return SLASH; }
"remnant"     { UPDATE_GOOD_TOKEN(); return MOD; }
"claimeth"     { UPDATE_GOOD_TOKEN(); return EQ; }
"unworthy"       { UPDATE_GOOD_TOKEN(); return LT; }
"mightier"      { UPDATE_GOOD_TOKEN(); return GT; }
"nohigher"        { UPDATE_GOOD_TOKEN(); return LEQ; }
"nobelow"        { UPDATE_GOOD_TOKEN(); return GEQ; }
"reject"       { UPDATE_GOOD_TOKEN(); return NEQ; }
"united"       { UPDATE_GOOD_TOKEN(); return AND; }
"either"           { UPDATE_GOOD_TOKEN(); return OR; }
"deny"         { UPDATE_GOOD_TOKEN(); return NOT; }
"invoke"       { UPDATE_GOOD_TOKEN(); return OP; }
"dismiss"      { UPDATE_GOOD_TOKEN(); return CP; }
"commence"       { UPDATE_GOOD_TOKEN(); return OB; }
"conclude"       { UPDATE_GOOD_TOKEN(); return CB; }
"suppose"      { UPDATE_GOOD_TOKEN(); return IF; }
"elsewise"     { UPDATE_GOOD_TOKEN(); return ELSE; }
"aslongas"       { UPDATE_GOOD_TOKEN(); return WHILE; }
"upon"         { UPDATE_GOOD_TOKEN(); return FOR; }
"flee"         { UPDATE_GOOD_TOKEN(); return BREAK; }
"onward"       { UPDATE_GOOD_TOKEN(); return CONTINUE; }
"of"           { UPDATE_GOOD_TOKEN(); return COLON; }
"henceforth"   { UPDATE_GOOD_TOKEN(); return VAR; }
"aye"        { UPDATE_GOOD_TOKEN(); return TRUE; }
"nay"      { UPDATE_GOOD_TOKEN(); return FALSE; }
"proclaim"      { UPDATE_GOOD_TOKEN(); return PRINT; }
"bestow"     { UPDATE_GOOD_TOKEN(); return ASSIGN; }
"inscribe"   { UPDATE_GOOD_TOKEN(); return FUNCTION; }
"whisper"    { UPDATE_GOOD_TOKEN(); return LAMBDA; }
"also"     { UPDATE_GOOD_TOKEN(); return COMMA; }
"yield"   { UPDATE_GOOD_TOKEN(); return RETURN; }
"perchance" { UPDATE_GOOD_TOKEN(); return QUESTION; }
\n             { ++yylineno; return EOL; }
[ \t]          {}

[a-zA-Z_][a-zA-Z_0-9]* { UPDATE_GOOD_TOKEN(); yylval.str = strdup(yytext); return IDENTIFIER; }
\"[^\"]*\"  { UPDATE_GOOD_TOKEN(); yylval.str = strdup(yytext + 1); yylval.str[strlen(yylval.str) - 1] = '\0'; return STRING; }
"//".*        { /* skip single-line comment */ }
"/*"([^*]|\*+[^*/])*\*+\/    { /* skip multi-line comment */ }
.           { UPDATE_GOOD_TOKEN(); return yytext[0]; }

%%

int yywrap() {
    return 1;
}
