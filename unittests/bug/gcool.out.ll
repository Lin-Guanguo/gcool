; ModuleID = 'Main'
source_filename = "Main"

%ClassInfo = type <{ %VTable*, i64, i32*, i32* }>
%VTable = type <{ %ClassInfo, [0 x i32 (...)*] }>
%FatPointer = type <{ %VTable*, [0 x %FatPointer]* }>

@ObjectVT = constant <{ %ClassInfo, [2 x i32 (...)*] }> <{ %ClassInfo zeroinitializer, [2 x i32 (...)*] [i32 (...)* bitcast (%FatPointer ()* @Object.0new to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Object.opisvoid to i32 (...)*)] }>
@MainVT = constant <{ %ClassInfo, [3 x i32 (...)*] }> <{ %ClassInfo <{ %VTable* bitcast (<{ %ClassInfo, [2 x i32 (...)*] }>* @ObjectVT to %VTable*), i64 1, i32* null, i32* null }>, [3 x i32 (...)*] [i32 (...)* bitcast (%FatPointer ()* @Main.0new to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Object.opisvoid to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Main.main to i32 (...)*)] }>
@IntVT = constant <{ %ClassInfo, [11 x i32 (...)*] }> <{ %ClassInfo <{ %VTable* bitcast (<{ %ClassInfo, [2 x i32 (...)*] }>* @ObjectVT to %VTable*), i64 1, i32* null, i32* null }>, [11 x i32 (...)*] [i32 (...)* bitcast (%FatPointer ()* @Int.0new to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Object.opisvoid to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Int.opadd to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Int.opsub to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Int.opmul to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Int.opdiv to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Int.opeq to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Int.opge to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Int.opgt to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Int.ople to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Int.oplt to i32 (...)*)] }>
@FloatVT = constant <{ %ClassInfo, [11 x i32 (...)*] }> <{ %ClassInfo <{ %VTable* bitcast (<{ %ClassInfo, [2 x i32 (...)*] }>* @ObjectVT to %VTable*), i64 1, i32* null, i32* null }>, [11 x i32 (...)*] [i32 (...)* bitcast (%FatPointer ()* @Float.0new to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Object.opisvoid to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Float.opadd to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Float.opsub to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Float.opmul to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Float.opdiv to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Float.opeq to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Float.opge to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Float.opgt to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Float.ople to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Float.oplt to i32 (...)*)] }>
@BoolVT = constant <{ %ClassInfo, [6 x i32 (...)*] }> <{ %ClassInfo <{ %VTable* bitcast (<{ %ClassInfo, [2 x i32 (...)*] }>* @ObjectVT to %VTable*), i64 1, i32* null, i32* null }>, [6 x i32 (...)*] [i32 (...)* bitcast (%FatPointer ()* @Bool.0new to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Object.opisvoid to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Bool.opadd to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Bool.opmul to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Bool.opeq to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Bool.opnot to i32 (...)*)] }>
@StringVT = constant <{ %ClassInfo, [8 x i32 (...)*] }> <{ %ClassInfo <{ %VTable* bitcast (<{ %ClassInfo, [2 x i32 (...)*] }>* @ObjectVT to %VTable*), i64 1, i32* null, i32* null }>, [8 x i32 (...)*] [i32 (...)* bitcast (%FatPointer ()* @String.0new to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Object.opisvoid to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @String.opadd to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @String.opeq to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @String.opge to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @String.opgt to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @String.ople to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @String.oplt to i32 (...)*)] }>
@Main2VT = constant <{ %ClassInfo, [3 x i32 (...)*] }> <{ %ClassInfo <{ %VTable* bitcast (<{ %ClassInfo, [3 x i32 (...)*] }>* @MainVT to %VTable*), i64 2, i32* null, i32* null }>, [3 x i32 (...)*] [i32 (...)* bitcast (%FatPointer ()* @Main2.0new to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Object.opisvoid to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Main.main to i32 (...)*)] }>
@Main4VT = constant <{ %ClassInfo, [4 x i32 (...)*] }> <{ %ClassInfo <{ %VTable* bitcast (<{ %ClassInfo, [3 x i32 (...)*] }>* @Main2VT to %VTable*), i64 3, i32* null, i32* null }>, [4 x i32 (...)*] [i32 (...)* bitcast (%FatPointer ()* @Main4.0new to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Object.opisvoid to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer)* @Main.main to i32 (...)*), i32 (...)* bitcast (%FatPointer (%FatPointer, %FatPointer)* @Main4.hello to i32 (...)*)] }>

define %FatPointer @Object.0new() {
entry:
  %obj = call i8* @gcool_malloc(i64 0)
  %0 = bitcast i8* %obj to [0 x %FatPointer]*
  %1 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [2 x i32 (...)*] }>* @ObjectVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %0, 1
  ret %FatPointer %1
}

define void @Object.0init(%FatPointer %0) {
entry:
  ret void
}

define %FatPointer @Object.opisvoid(%FatPointer %0) {
entry:
  ret %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* inttoptr (i64 1 to [0 x %FatPointer]*) }>
}

define %FatPointer @Main.0new() {
entry:
  %heapObj = call i8* @gcool_malloc(i64 48)
  %0 = bitcast i8* %heapObj to [0 x %FatPointer]*
  %1 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [3 x i32 (...)*] }>* @MainVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %0, 1
  call void @Main.0init(%FatPointer %1)
  ret %FatPointer %1
}

define void @Main.0init(%FatPointer %0) {
entry:
  call void @Object.0init(%FatPointer %0)
  %1 = extractvalue %FatPointer %0, 1
  %2 = getelementptr [0 x %FatPointer], [0 x %FatPointer]* %1, i32 0, i32 0
  store %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @IntVT to %VTable*), [0 x %FatPointer]* inttoptr (i64 10 to [0 x %FatPointer]*) }>, %FatPointer* %2, align 1
  %3 = getelementptr [0 x %FatPointer], [0 x %FatPointer]* %1, i32 0, i32 1
  store %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @IntVT to %VTable*), [0 x %FatPointer]* inttoptr (i64 10 to [0 x %FatPointer]*) }>, %FatPointer* %3, align 1
  %4 = getelementptr [0 x %FatPointer], [0 x %FatPointer]* %1, i32 0, i32 2
  store %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @FloatVT to %VTable*), [0 x %FatPointer]* inttoptr (i64 4626322717216342016 to [0 x %FatPointer]*) }>, %FatPointer* %4, align 1
  ret void
}

define %FatPointer @Main.main(%FatPointer %0) {
entry:
  %Main4.val = call %FatPointer @Main4.0new()
  %self.heapObj = extractvalue %FatPointer %0, 1
  %1 = getelementptr [0 x %FatPointer], [0 x %FatPointer]* %self.heapObj, i32 0, i32 1
  %d.val = load %FatPointer, %FatPointer* %1, align 1
  %2 = extractvalue %FatPointer %Main4.val, 0
  %3 = getelementptr %VTable, %VTable* %2, i32 0, i32 1, i32 3
  %4 = bitcast i32 (...)** %3 to %FatPointer (%FatPointer, %FatPointer)**
  %5 = load %FatPointer (%FatPointer, %FatPointer)*, %FatPointer (%FatPointer, %FatPointer)** %4, align 8
  %6 = call %FatPointer %5(%FatPointer %Main4.val, %FatPointer %d.val)
  ret %FatPointer %6
}

define %FatPointer @Int.0new() {
entry:
  ret %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @IntVT to %VTable*), [0 x %FatPointer]* undef }>
}

define %FatPointer @Int.opadd(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = add i64 %4, %5
  %7 = inttoptr i64 %6 to [0 x %FatPointer]*
  %8 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @IntVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %7, 1
  ret %FatPointer %8
}

define %FatPointer @Int.opsub(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = sub i64 %4, %5
  %7 = inttoptr i64 %6 to [0 x %FatPointer]*
  %8 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @IntVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %7, 1
  ret %FatPointer %8
}

define %FatPointer @Int.opmul(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = mul i64 %4, %5
  %7 = inttoptr i64 %6 to [0 x %FatPointer]*
  %8 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @IntVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %7, 1
  ret %FatPointer %8
}

define %FatPointer @Int.opdiv(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = sdiv i64 %4, %5
  %7 = inttoptr i64 %6 to [0 x %FatPointer]*
  %8 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @IntVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %7, 1
  ret %FatPointer %8
}

define %FatPointer @Int.opeq(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = icmp eq i64 %4, %5
  %7 = zext i1 %6 to i64
  %8 = inttoptr i64 %7 to [0 x %FatPointer]*
  %9 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %8, 1
  ret %FatPointer %9
}

define %FatPointer @Int.opge(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = icmp sge i64 %4, %5
  %7 = zext i1 %6 to i64
  %8 = inttoptr i64 %7 to [0 x %FatPointer]*
  %9 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %8, 1
  ret %FatPointer %9
}

define %FatPointer @Int.opgt(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = icmp sgt i64 %4, %5
  %7 = zext i1 %6 to i64
  %8 = inttoptr i64 %7 to [0 x %FatPointer]*
  %9 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %8, 1
  ret %FatPointer %9
}

define %FatPointer @Int.ople(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = icmp sle i64 %4, %5
  %7 = zext i1 %6 to i64
  %8 = inttoptr i64 %7 to [0 x %FatPointer]*
  %9 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %8, 1
  ret %FatPointer %9
}

define %FatPointer @Int.oplt(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = icmp slt i64 %4, %5
  %7 = zext i1 %6 to i64
  %8 = inttoptr i64 %7 to [0 x %FatPointer]*
  %9 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %8, 1
  ret %FatPointer %9
}

define %FatPointer @Float.0new() {
entry:
  ret %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @FloatVT to %VTable*), [0 x %FatPointer]* undef }>
}

define %FatPointer @Float.opadd(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = bitcast i64 %4 to double
  %6 = ptrtoint [0 x %FatPointer]* %3 to i64
  %7 = bitcast i64 %6 to double
  %8 = fadd double %5, %7
  %9 = bitcast double %8 to i64
  %10 = inttoptr i64 %9 to [0 x %FatPointer]*
  %11 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @FloatVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %10, 1
  ret %FatPointer %11
}

define %FatPointer @Float.opsub(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = bitcast i64 %4 to double
  %6 = ptrtoint [0 x %FatPointer]* %3 to i64
  %7 = bitcast i64 %6 to double
  %8 = fsub double %5, %7
  %9 = bitcast double %8 to i64
  %10 = inttoptr i64 %9 to [0 x %FatPointer]*
  %11 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @FloatVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %10, 1
  ret %FatPointer %11
}

define %FatPointer @Float.opmul(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = bitcast i64 %4 to double
  %6 = ptrtoint [0 x %FatPointer]* %3 to i64
  %7 = bitcast i64 %6 to double
  %8 = fmul double %5, %7
  %9 = bitcast double %8 to i64
  %10 = inttoptr i64 %9 to [0 x %FatPointer]*
  %11 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @FloatVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %10, 1
  ret %FatPointer %11
}

define %FatPointer @Float.opdiv(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = bitcast i64 %4 to double
  %6 = ptrtoint [0 x %FatPointer]* %3 to i64
  %7 = bitcast i64 %6 to double
  %8 = fdiv double %5, %7
  %9 = bitcast double %8 to i64
  %10 = inttoptr i64 %9 to [0 x %FatPointer]*
  %11 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @FloatVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %10, 1
  ret %FatPointer %11
}

define %FatPointer @Float.opeq(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = bitcast i64 %4 to double
  %6 = ptrtoint [0 x %FatPointer]* %3 to i64
  %7 = bitcast i64 %6 to double
  %8 = fcmp oeq double %5, %7
  %9 = zext i1 %8 to i64
  %10 = inttoptr i64 %9 to [0 x %FatPointer]*
  %11 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %10, 1
  ret %FatPointer %11
}

define %FatPointer @Float.opge(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = bitcast i64 %4 to double
  %6 = ptrtoint [0 x %FatPointer]* %3 to i64
  %7 = bitcast i64 %6 to double
  %8 = fcmp oge double %5, %7
  %9 = zext i1 %8 to i64
  %10 = inttoptr i64 %9 to [0 x %FatPointer]*
  %11 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %10, 1
  ret %FatPointer %11
}

define %FatPointer @Float.opgt(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = bitcast i64 %4 to double
  %6 = ptrtoint [0 x %FatPointer]* %3 to i64
  %7 = bitcast i64 %6 to double
  %8 = fcmp ogt double %5, %7
  %9 = zext i1 %8 to i64
  %10 = inttoptr i64 %9 to [0 x %FatPointer]*
  %11 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %10, 1
  ret %FatPointer %11
}

define %FatPointer @Float.ople(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = bitcast i64 %4 to double
  %6 = ptrtoint [0 x %FatPointer]* %3 to i64
  %7 = bitcast i64 %6 to double
  %8 = fcmp ole double %5, %7
  %9 = zext i1 %8 to i64
  %10 = inttoptr i64 %9 to [0 x %FatPointer]*
  %11 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %10, 1
  ret %FatPointer %11
}

define %FatPointer @Float.oplt(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = bitcast i64 %4 to double
  %6 = ptrtoint [0 x %FatPointer]* %3 to i64
  %7 = bitcast i64 %6 to double
  %8 = fcmp olt double %5, %7
  %9 = zext i1 %8 to i64
  %10 = inttoptr i64 %9 to [0 x %FatPointer]*
  %11 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %10, 1
  ret %FatPointer %11
}

define %FatPointer @Bool.0new() {
entry:
  ret %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>
}

define %FatPointer @Bool.opadd(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = or i64 %4, %5
  %7 = inttoptr i64 %6 to [0 x %FatPointer]*
  %8 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %7, 1
  ret %FatPointer %8
}

define %FatPointer @Bool.opmul(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = and i64 %4, %5
  %7 = inttoptr i64 %6 to [0 x %FatPointer]*
  %8 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %7, 1
  ret %FatPointer %8
}

define %FatPointer @Bool.opeq(%FatPointer %0, %FatPointer %1) {
entry:
  %2 = extractvalue %FatPointer %0, 1
  %3 = extractvalue %FatPointer %1, 1
  %4 = ptrtoint [0 x %FatPointer]* %2 to i64
  %5 = ptrtoint [0 x %FatPointer]* %3 to i64
  %6 = trunc i64 %4 to i1
  %7 = trunc i64 %5 to i1
  %8 = icmp eq i1 %6, %7
  %9 = inttoptr i1 %8 to [0 x %FatPointer]*
  %10 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %9, 1
  ret %FatPointer %10
}

define %FatPointer @Bool.opnot(%FatPointer %0) {
entry:
  %1 = extractvalue %FatPointer %0, 1
  %2 = ptrtoint [0 x %FatPointer]* %1 to i64
  %3 = xor i64 %2, 1
  %4 = inttoptr i64 %3 to [0 x %FatPointer]*
  %5 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [6 x i32 (...)*] }>* @BoolVT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %4, 1
  ret %FatPointer %5
}

define %FatPointer @String.0new() {
entry:
  ret %FatPointer undef
}

define %FatPointer @String.opadd(%FatPointer %0, %FatPointer %1) {
entry:
  ret %FatPointer undef
}

define %FatPointer @String.opeq(%FatPointer %0, %FatPointer %1) {
entry:
  ret %FatPointer undef
}

define %FatPointer @String.opge(%FatPointer %0, %FatPointer %1) {
entry:
  ret %FatPointer undef
}

define %FatPointer @String.opgt(%FatPointer %0, %FatPointer %1) {
entry:
  ret %FatPointer undef
}

define %FatPointer @String.ople(%FatPointer %0, %FatPointer %1) {
entry:
  ret %FatPointer undef
}

define %FatPointer @String.oplt(%FatPointer %0, %FatPointer %1) {
entry:
  ret %FatPointer undef
}

define %FatPointer @Main2.0new() {
entry:
  %heapObj = call i8* @gcool_malloc(i64 64)
  %0 = bitcast i8* %heapObj to [0 x %FatPointer]*
  %1 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [3 x i32 (...)*] }>* @Main2VT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %0, 1
  call void @Main2.0init(%FatPointer %1)
  ret %FatPointer %1
}

define void @Main2.0init(%FatPointer %0) {
entry:
  call void @Main.0init(%FatPointer %0)
  %1 = extractvalue %FatPointer %0, 1
  %2 = getelementptr [0 x %FatPointer], [0 x %FatPointer]* %1, i32 0, i32 3
  store %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @FloatVT to %VTable*), [0 x %FatPointer]* inttoptr (i64 4621267426634618634 to [0 x %FatPointer]*) }>, %FatPointer* %2, align 1
  ret void
}

define %FatPointer @Main4.0new() {
entry:
  %heapObj = call i8* @gcool_malloc(i64 96)
  %0 = bitcast i8* %heapObj to [0 x %FatPointer]*
  %1 = insertvalue %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [4 x i32 (...)*] }>* @Main4VT to %VTable*), [0 x %FatPointer]* undef }>, [0 x %FatPointer]* %0, 1
  call void @Main4.0init(%FatPointer %1)
  ret %FatPointer %1
}

define void @Main4.0init(%FatPointer %0) {
entry:
  call void @Main2.0init(%FatPointer %0)
  %1 = extractvalue %FatPointer %0, 1
  %2 = getelementptr [0 x %FatPointer], [0 x %FatPointer]* %1, i32 0, i32 4
  store %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @FloatVT to %VTable*), [0 x %FatPointer]* inttoptr (i64 4626379012211684147 to [0 x %FatPointer]*) }>, %FatPointer* %2, align 1
  %3 = getelementptr [0 x %FatPointer], [0 x %FatPointer]* %1, i32 0, i32 5
  store %FatPointer <{ %VTable* bitcast (<{ %ClassInfo, [11 x i32 (...)*] }>* @IntVT to %VTable*), [0 x %FatPointer]* inttoptr (i64 5 to [0 x %FatPointer]*) }>, %FatPointer* %3, align 1
  ret void
}

define %FatPointer @Main4.hello(%FatPointer %0, %FatPointer %1) {
entry:
  %LocalVars = alloca %FatPointer, align 8, addrspace(1)
  %i = getelementptr %FatPointer, %FatPointer addrspace(1)* %LocalVars, i32 0
  store %FatPointer %1, %FatPointer addrspace(1)* %i, align 1
  %i1 = getelementptr %FatPointer, %FatPointer addrspace(1)* %LocalVars, i32 0
  %i.val = load %FatPointer, %FatPointer addrspace(1)* %i1, align 1
  ret %FatPointer %i.val
}

declare i8* @gcool_malloc(i64)

define i32 @main(i32 %0, i8** %1) {
entry:
  %2 = call %FatPointer @Main.0new()
  %3 = call %FatPointer @Main.main(%FatPointer %2)
  %4 = extractvalue %FatPointer %3, 1
  %5 = ptrtoint [0 x %FatPointer]* %4 to i64
  %6 = trunc i64 %5 to i32
  ret i32 %6
}
