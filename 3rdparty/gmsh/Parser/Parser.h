// Gmsh - Copyright (C) 1997-2014 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@geuz.org>.

#ifndef _PARSER_H_
#define _PARSER_H_

#include <map>
#include <string>
#include <vector>

int gmsh_yyparse();
int gmsh_yylex();
void gmsh_yyflush();

class gmsh_yysymbol{
 public:
  bool list;
  std::vector<double> value;
  gmsh_yysymbol() : list(false) {}
};

// global parser variables that need to be exported
extern FILE *gmsh_yyin;
extern int gmsh_yylineno;
extern char *gmsh_yytext;
extern int gmsh_yyviewindex;
extern std::string gmsh_yyname;
extern int gmsh_yyerrorstate;
extern std::map<std::string, gmsh_yysymbol> gmsh_yysymbols;
extern std::map<std::string, std::string> gmsh_yystringsymbols;

#endif