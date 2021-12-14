#include <iostream>
#include <fstream>
#include <vector>
#include "ast/symtab.hpp"
#include "y.tab.h"


int main() {
    extern SymbolTable globalSymTab;
    std::cout << "Hello, Crust!" << std::endl;
    
    yyparse();

    std::ofstream outfile("output.cpp");
    for (const auto& func : globalSymTab._funcTable)
    {
        auto code = func.second->codeGen(&globalSymTab);
        for (const auto& line : code)
        {
            outfile << line;
        }
    }
    outfile.close();
    return 0;
}