#include "gcool/Basic/Diag.h"
#include "llvm/Support/raw_ostream.h"

llvm::raw_ostream& gcool::basic::operator<<(llvm::raw_ostream& os, const gcool::basic::Diag& d) {
    os << gcool::basic::Diag::DiagKindName[d.TheDiagKind] << ": " << d.AdditionalMsg;
    return os;
}

bool gcool::basic::Diag::operator==(const Diag& t) const { 
    return TheDiagKind == t.TheDiagKind 
        && AdditionalMsg == t.AdditionalMsg;
}