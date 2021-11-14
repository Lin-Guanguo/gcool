#include <algorithm>
#include "gcool/AST/Symbol.h"

gcool::ast::Symbol gcool::ast::SymbolTable::get(std::string_view literal)
{
    auto p = Table.find(literal);
    if (p != Table.end())
        return { p->data() };
    auto len = literal.length();
    char* s = new char[len + 1];
    std::copy(literal.begin(), literal.end(), s);
    s[len] = 0;
    Store.push_back(s);
    Table.insert({s});
    return { s };
}

gcool::ast::SymbolTable::~SymbolTable()
{
    for (auto* i : Store) {
        delete[] i;
    }
}
