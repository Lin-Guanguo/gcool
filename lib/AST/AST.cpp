#include "gcool/AST/AST.h"

gcool::ast::ASTContext::ASTContext() {
    Classes.push_back( Class{Symtbl.getObject(), Symbol::EmptySymbol} );
    Classes.push_back( Class{Symtbl.getInt(), Symtbl.getObject()} );
    Classes.push_back( Class{Symtbl.getFloat(), Symtbl.getObject()} );
    Classes.push_back( Class{Symtbl.getBool(), Symtbl.getObject()} );
    Classes.push_back( Class{Symtbl.getString(), Symtbl.getObject()} );
}