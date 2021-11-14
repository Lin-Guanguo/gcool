#pragma once
#include <string_view>
#include <unordered_set>
#include <vector>

namespace gcool{
namespace ast{


class Symbol {
private:
    const char* s;
    Symbol(const char* s_) : s(s_) { }
    friend class SymbolTable;
public:
    using SymbolID = std::intptr_t;
    std::string_view get_name() const { return { s }; }
    SymbolID get_id() const { return reinterpret_cast<SymbolID>(s); };
    bool operator==(const Symbol& t) const = default;
};

class SymbolTable {
private:
    std::unordered_set<std::string_view> Table;
    std::vector<const char*> Store;
public:
    SymbolTable() { }
    Symbol get(std::string_view literal);
    Symbol get_Int() { return get("Int"); }
    Symbol get_Float() { return get("Float"); }
    Symbol get_Bool() { return get("Bool"); }
    Symbol get_String() { return get("String"); }
    Symbol get_Object() { return get("Object"); }
    ~SymbolTable();
};

}
}