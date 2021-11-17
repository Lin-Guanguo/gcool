#pragma once
#include <string>

namespace llvm {
    class raw_ostream;
}

namespace gcool {
namespace basic {

class Diag {
public:
    enum DiagKind {
        #define ERROR_KIND_DEF(ID, LEVEL, MESSAGE) ID,
        #include "ErrorKindDef.def"
    };
    static constexpr const char* DiagKindMsg[] = {
        #define ERROR_KIND_DEF(ID, LEVEL, MESSAGE) MESSAGE,
        #include "ErrorKindDef.def"
    };
    DiagKind TheDiagKind;
    std::string AdditionalMsg;
public:
    Diag(DiagKind theDiagKind, std::string additionalMsg)
        : TheDiagKind(theDiagKind), AdditionalMsg(additionalMsg) {}
    
    bool operator==(const Diag& t) const;
};

llvm::raw_ostream& operator<<(llvm::raw_ostream& os, const Diag& d);

}
}