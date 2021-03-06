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
    const char* getName() const { return s; }
    SymbolID getID() const { return reinterpret_cast<SymbolID>(s); };
    bool isEmpty() const { return s == nullptr; }
    bool operator==(const Symbol& t) const = default;
    
    static const Symbol EmptySymbol;
};

class SymbolTable {
private:
    std::unordered_set<std::string_view> Table;
    std::vector<const char*> Store;
public:
    SymbolTable() { }
    Symbol get(std::string_view literal);
    Symbol getInt() { return get("Int"); }
    Symbol getFloat() { return get("Float"); }
    Symbol getBool() { return get("Bool"); }
    Symbol getString() { return get("String"); }
    Symbol getObject() { return get("Object"); }
    Symbol getSelf() { return get("self"); }
    Symbol getSelfType() { return get("SelfType"); }
    Symbol getNull() { return get("null"); }
    Symbol getNullType() { return get("NullType"); } 
    Symbol getNewMethod() { return get("0new"); } // programer can't use this method (0 start)
    Symbol getInitMethod() { return get("0init"); } // programer can't use this method (0 start)
    Symbol getStd() { return get("Std"); }  // Standard library Class
    Symbol getMainClass() { return get("Main"); }
    Symbol getMainMethod() { return get("main"); }
    ~SymbolTable();
};

}
}

namespace std {
template<> struct hash<gcool::ast::Symbol> {
    std::size_t operator()(const gcool::ast::Symbol& s) const noexcept {
        return std::hash<void*>{}(reinterpret_cast<void*>(s.getID()));
    }
};
}