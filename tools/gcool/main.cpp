#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/STLExtras.h"
#include <iostream>

class Base
{
public: 
    enum BaseKind
    {
        BK_D1,
        BK_D2
    };
    BaseKind getKind() const { return __TheKind; }
private:
    BaseKind __TheKind;
protected:
    Base(BaseKind TheKind_) : __TheKind(TheKind_) { }
};

template<typename T>
class BaseFacility : public Base
{
protected:
    BaseFacility() : Base(T::TheKind) { }
public:
    static bool classof(const Base* D)
    {
        return D->getKind() == T::TheKind;
    }
};

class Derive1 : public BaseFacility<Derive1>
{
public:
    static constexpr BaseKind TheKind = BK_D1;
    Derive1() { } 
};

class Derive2 : public BaseFacility<Derive2>
{
public:
    static constexpr BaseKind TheKind = BK_D2;
    Derive2() { } 
};

int main(int argc, char** argv) {
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder(context);
    llvm::Module theModule("module", context);

    Base* b1 = new Derive1();
    Base* b2 = new Derive2();
    
    for(auto b : {b1, b2}){
        switch(b->getKind()){
        case Base::BK_D1:
            llvm::outs() << "D1 ";
            llvm::outs() << llvm::cast<Derive1>(b)->TheKind << "\n";
            break;
        case Base::BK_D2:
            llvm::outs() << "D2 ";
            llvm::outs() << llvm::cast<Derive2>(b)->TheKind << "\n";
            break;
        }
    }


    int i = 10;
    

    return 0;
}