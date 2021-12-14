#include <iostream>
#include "y.tab.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    yyparse();
    
    return 0;
}