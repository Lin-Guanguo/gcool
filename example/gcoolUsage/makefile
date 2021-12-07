Dir = ../..
Runtime = $(Dir)/lib/RunTime/GCoolRuntime.c
Gcool = $(Dir)/build/tools/gcool/gcool

program: program.ll GCoolRuntime.ll
	clang program.ll GCoolRuntime.ll -o program

program.ll: program.cl
	$(Gcool) program.cl > program.ll

GCoolRuntime.ll: $(Runtime)
	clang -S -emit-llvm $(Runtime)

.PHONY: clean
clean:
	rm -f *.ll program