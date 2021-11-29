	.text
	.file	"Main"
	.globl	Object.0new                     # -- Begin function Object.0new
	.p2align	4, 0x90
	.type	Object.0new,@function
Object.0new:                            # @Object.0new
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	movl	%eax, %edi
	callq	gcool_malloc@PLT
	movq	%rax, %rdx
	movq	ObjectVT@GOTPCREL(%rip), %rax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	Object.0new, .Lfunc_end0-Object.0new
	.cfi_endproc
                                        # -- End function
	.globl	Object.0init                    # -- Begin function Object.0init
	.p2align	4, 0x90
	.type	Object.0init,@function
Object.0init:                           # @Object.0init
	.cfi_startproc
# %bb.0:                                # %entry
	retq
.Lfunc_end1:
	.size	Object.0init, .Lfunc_end1-Object.0init
	.cfi_endproc
                                        # -- End function
	.globl	Object.opisvoid                 # -- Begin function Object.opisvoid
	.p2align	4, 0x90
	.type	Object.opisvoid,@function
Object.opisvoid:                        # @Object.opisvoid
	.cfi_startproc
# %bb.0:                                # %entry
	movq	BoolVT@GOTPCREL(%rip), %rax
	movl	$1, %edx
	retq
.Lfunc_end2:
	.size	Object.opisvoid, .Lfunc_end2-Object.opisvoid
	.cfi_endproc
                                        # -- End function
	.globl	Main.0new                       # -- Begin function Main.0new
	.p2align	4, 0x90
	.type	Main.0new,@function
Main.0new:                              # @Main.0new
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$48, %edi
	callq	gcool_malloc@PLT
	movq	%rax, %rsi
	movq	%rsi, 16(%rsp)                  # 8-byte Spill
	movq	MainVT@GOTPCREL(%rip), %rdi
	movq	%rdi, 8(%rsp)                   # 8-byte Spill
	callq	Main.0init@PLT
	movq	8(%rsp), %rax                   # 8-byte Reload
	movq	16(%rsp), %rdx                  # 8-byte Reload
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end3:
	.size	Main.0new, .Lfunc_end3-Main.0new
	.cfi_endproc
                                        # -- End function
	.globl	Main.0init                      # -- Begin function Main.0init
	.p2align	4, 0x90
	.type	Main.0init,@function
Main.0init:                             # @Main.0init
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	%rsi, (%rsp)                    # 8-byte Spill
	callq	Object.0init@PLT
	movq	(%rsp), %rsi                    # 8-byte Reload
	movq	IntVT@GOTPCREL(%rip), %rax
	movq	%rax, (%rsi)
	movq	$10, 8(%rsi)
	movq	%rax, 16(%rsi)
	movq	$10, 24(%rsi)
	movabsq	$4626322717216342016, %rax      # imm = 0x4034000000000000
	movq	%rax, 40(%rsi)
	movq	FloatVT@GOTPCREL(%rip), %rax
	movq	%rax, 32(%rsi)
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end4:
	.size	Main.0init, .Lfunc_end4-Main.0init
	.cfi_endproc
                                        # -- End function
	.globl	Main.main                       # -- Begin function Main.main
	.p2align	4, 0x90
	.type	Main.main,@function
Main.main:                              # @Main.main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	%rsi, (%rsp)                    # 8-byte Spill
	callq	Main4.0new@PLT
	movq	%rax, %rdi
	movq	(%rsp), %rax                    # 8-byte Reload
	movq	%rdx, %rsi
	movq	16(%rax), %r8
	movq	24(%rax), %r9
	movq	56(%rdi), %rax
	movq	%r8, %rdx
	movq	%r9, %rcx
	callq	*%rax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end5:
	.size	Main.main, .Lfunc_end5-Main.main
	.cfi_endproc
                                        # -- End function
	.globl	Int.0new                        # -- Begin function Int.0new
	.p2align	4, 0x90
	.type	Int.0new,@function
Int.0new:                               # @Int.0new
	.cfi_startproc
# %bb.0:                                # %entry
	movq	IntVT@GOTPCREL(%rip), %rax
                                        # implicit-def: $rdx
	retq
.Lfunc_end6:
	.size	Int.0new, .Lfunc_end6-Int.0new
	.cfi_endproc
                                        # -- End function
	.globl	Int.opadd                       # -- Begin function Int.opadd
	.p2align	4, 0x90
	.type	Int.opadd,@function
Int.opadd:                              # @Int.opadd
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdx, %rax
	movq	%rsi, %rdx
	addq	%rcx, %rdx
	movq	IntVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end7:
	.size	Int.opadd, .Lfunc_end7-Int.opadd
	.cfi_endproc
                                        # -- End function
	.globl	Int.opsub                       # -- Begin function Int.opsub
	.p2align	4, 0x90
	.type	Int.opsub,@function
Int.opsub:                              # @Int.opsub
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdx, %rax
	movq	%rsi, %rdx
	subq	%rcx, %rdx
	movq	IntVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end8:
	.size	Int.opsub, .Lfunc_end8-Int.opsub
	.cfi_endproc
                                        # -- End function
	.globl	Int.opmul                       # -- Begin function Int.opmul
	.p2align	4, 0x90
	.type	Int.opmul,@function
Int.opmul:                              # @Int.opmul
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdx, %rax
	movq	%rsi, %rdx
	imulq	%rcx, %rdx
	movq	IntVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end9:
	.size	Int.opmul, .Lfunc_end9-Int.opmul
	.cfi_endproc
                                        # -- End function
	.globl	Int.opdiv                       # -- Begin function Int.opdiv
	.p2align	4, 0x90
	.type	Int.opdiv,@function
Int.opdiv:                              # @Int.opdiv
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %rax
	cqto
	idivq	%rcx
	movq	%rax, %rdx
	movq	IntVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end10:
	.size	Int.opdiv, .Lfunc_end10-Int.opdiv
	.cfi_endproc
                                        # -- End function
	.globl	Int.opeq                        # -- Begin function Int.opeq
	.p2align	4, 0x90
	.type	Int.opeq,@function
Int.opeq:                               # @Int.opeq
	.cfi_startproc
# %bb.0:                                # %entry
	subq	%rcx, %rsi
	sete	%al
	movzbl	%al, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end11:
	.size	Int.opeq, .Lfunc_end11-Int.opeq
	.cfi_endproc
                                        # -- End function
	.globl	Int.opge                        # -- Begin function Int.opge
	.p2align	4, 0x90
	.type	Int.opge,@function
Int.opge:                               # @Int.opge
	.cfi_startproc
# %bb.0:                                # %entry
	subq	%rcx, %rsi
	setge	%al
	movzbl	%al, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end12:
	.size	Int.opge, .Lfunc_end12-Int.opge
	.cfi_endproc
                                        # -- End function
	.globl	Int.opgt                        # -- Begin function Int.opgt
	.p2align	4, 0x90
	.type	Int.opgt,@function
Int.opgt:                               # @Int.opgt
	.cfi_startproc
# %bb.0:                                # %entry
	subq	%rcx, %rsi
	setg	%al
	movzbl	%al, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end13:
	.size	Int.opgt, .Lfunc_end13-Int.opgt
	.cfi_endproc
                                        # -- End function
	.globl	Int.ople                        # -- Begin function Int.ople
	.p2align	4, 0x90
	.type	Int.ople,@function
Int.ople:                               # @Int.ople
	.cfi_startproc
# %bb.0:                                # %entry
	subq	%rcx, %rsi
	setle	%al
	movzbl	%al, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end14:
	.size	Int.ople, .Lfunc_end14-Int.ople
	.cfi_endproc
                                        # -- End function
	.globl	Int.oplt                        # -- Begin function Int.oplt
	.p2align	4, 0x90
	.type	Int.oplt,@function
Int.oplt:                               # @Int.oplt
	.cfi_startproc
# %bb.0:                                # %entry
	subq	%rcx, %rsi
	setl	%al
	movzbl	%al, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end15:
	.size	Int.oplt, .Lfunc_end15-Int.oplt
	.cfi_endproc
                                        # -- End function
	.globl	Float.0new                      # -- Begin function Float.0new
	.p2align	4, 0x90
	.type	Float.0new,@function
Float.0new:                             # @Float.0new
	.cfi_startproc
# %bb.0:                                # %entry
	movq	FloatVT@GOTPCREL(%rip), %rax
                                        # implicit-def: $rdx
	retq
.Lfunc_end16:
	.size	Float.0new, .Lfunc_end16-Float.0new
	.cfi_endproc
                                        # -- End function
	.globl	Float.opadd                     # -- Begin function Float.opadd
	.p2align	4, 0x90
	.type	Float.opadd,@function
Float.opadd:                            # @Float.opadd
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %xmm0
	movq	%rcx, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rdx
	movq	FloatVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end17:
	.size	Float.opadd, .Lfunc_end17-Float.opadd
	.cfi_endproc
                                        # -- End function
	.globl	Float.opsub                     # -- Begin function Float.opsub
	.p2align	4, 0x90
	.type	Float.opsub,@function
Float.opsub:                            # @Float.opsub
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %xmm0
	movq	%rcx, %xmm1
	subsd	%xmm1, %xmm0
	movq	%xmm0, %rdx
	movq	FloatVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end18:
	.size	Float.opsub, .Lfunc_end18-Float.opsub
	.cfi_endproc
                                        # -- End function
	.globl	Float.opmul                     # -- Begin function Float.opmul
	.p2align	4, 0x90
	.type	Float.opmul,@function
Float.opmul:                            # @Float.opmul
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %xmm0
	movq	%rcx, %xmm1
	mulsd	%xmm1, %xmm0
	movq	%xmm0, %rdx
	movq	FloatVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end19:
	.size	Float.opmul, .Lfunc_end19-Float.opmul
	.cfi_endproc
                                        # -- End function
	.globl	Float.opdiv                     # -- Begin function Float.opdiv
	.p2align	4, 0x90
	.type	Float.opdiv,@function
Float.opdiv:                            # @Float.opdiv
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %xmm0
	movq	%rcx, %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rdx
	movq	FloatVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end20:
	.size	Float.opdiv, .Lfunc_end20-Float.opdiv
	.cfi_endproc
                                        # -- End function
	.globl	Float.opeq                      # -- Begin function Float.opeq
	.p2align	4, 0x90
	.type	Float.opeq,@function
Float.opeq:                             # @Float.opeq
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %xmm0
	movq	%rcx, %xmm1
	cmpeqsd	%xmm1, %xmm0
	movq	%xmm0, %rax
                                        # kill: def $eax killed $eax killed $rax
	andl	$1, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end21:
	.size	Float.opeq, .Lfunc_end21-Float.opeq
	.cfi_endproc
                                        # -- End function
	.globl	Float.opge                      # -- Begin function Float.opge
	.p2align	4, 0x90
	.type	Float.opge,@function
Float.opge:                             # @Float.opge
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %xmm0
	movq	%rcx, %xmm1
	ucomisd	%xmm1, %xmm0
	setae	%al
	movzbl	%al, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end22:
	.size	Float.opge, .Lfunc_end22-Float.opge
	.cfi_endproc
                                        # -- End function
	.globl	Float.opgt                      # -- Begin function Float.opgt
	.p2align	4, 0x90
	.type	Float.opgt,@function
Float.opgt:                             # @Float.opgt
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %xmm0
	movq	%rcx, %xmm1
	ucomisd	%xmm1, %xmm0
	seta	%al
	movzbl	%al, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end23:
	.size	Float.opgt, .Lfunc_end23-Float.opgt
	.cfi_endproc
                                        # -- End function
	.globl	Float.ople                      # -- Begin function Float.ople
	.p2align	4, 0x90
	.type	Float.ople,@function
Float.ople:                             # @Float.ople
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %xmm1
	movq	%rcx, %xmm0
	ucomisd	%xmm1, %xmm0
	setae	%al
	movzbl	%al, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end24:
	.size	Float.ople, .Lfunc_end24-Float.ople
	.cfi_endproc
                                        # -- End function
	.globl	Float.oplt                      # -- Begin function Float.oplt
	.p2align	4, 0x90
	.type	Float.oplt,@function
Float.oplt:                             # @Float.oplt
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %xmm1
	movq	%rcx, %xmm0
	ucomisd	%xmm1, %xmm0
	seta	%al
	movzbl	%al, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end25:
	.size	Float.oplt, .Lfunc_end25-Float.oplt
	.cfi_endproc
                                        # -- End function
	.globl	Bool.0new                       # -- Begin function Bool.0new
	.p2align	4, 0x90
	.type	Bool.0new,@function
Bool.0new:                              # @Bool.0new
	.cfi_startproc
# %bb.0:                                # %entry
	movq	BoolVT@GOTPCREL(%rip), %rax
                                        # implicit-def: $rdx
	retq
.Lfunc_end26:
	.size	Bool.0new, .Lfunc_end26-Bool.0new
	.cfi_endproc
                                        # -- End function
	.globl	Bool.opadd                      # -- Begin function Bool.opadd
	.p2align	4, 0x90
	.type	Bool.opadd,@function
Bool.opadd:                             # @Bool.opadd
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdx, %rax
	movq	%rsi, %rdx
	orq	%rcx, %rdx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end27:
	.size	Bool.opadd, .Lfunc_end27-Bool.opadd
	.cfi_endproc
                                        # -- End function
	.globl	Bool.opmul                      # -- Begin function Bool.opmul
	.p2align	4, 0x90
	.type	Bool.opmul,@function
Bool.opmul:                             # @Bool.opmul
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdx, %rax
	movq	%rsi, %rdx
	andq	%rcx, %rdx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end28:
	.size	Bool.opmul, .Lfunc_end28-Bool.opmul
	.cfi_endproc
                                        # -- End function
	.globl	Bool.opeq                       # -- Begin function Bool.opeq
	.p2align	4, 0x90
	.type	Bool.opeq,@function
Bool.opeq:                              # @Bool.opeq
	.cfi_startproc
# %bb.0:                                # %entry
                                        # kill: def $ecx killed $ecx killed $rcx
	movl	%esi, %eax
	xorl	%ecx, %eax
                                        # kill: def $al killed $al killed $eax
	notb	%al
	movzbl	%al, %eax
                                        # kill: def $rax killed $eax
                                        # kill: def $eax killed $eax killed $rax
	andl	$1, %eax
	movl	%eax, %edx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end29:
	.size	Bool.opeq, .Lfunc_end29-Bool.opeq
	.cfi_endproc
                                        # -- End function
	.globl	Bool.opnot                      # -- Begin function Bool.opnot
	.p2align	4, 0x90
	.type	Bool.opnot,@function
Bool.opnot:                             # @Bool.opnot
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rsi, %rdx
	xorq	$1, %rdx
	movq	BoolVT@GOTPCREL(%rip), %rax
	retq
.Lfunc_end30:
	.size	Bool.opnot, .Lfunc_end30-Bool.opnot
	.cfi_endproc
                                        # -- End function
	.globl	String.0new                     # -- Begin function String.0new
	.p2align	4, 0x90
	.type	String.0new,@function
String.0new:                            # @String.0new
	.cfi_startproc
# %bb.0:                                # %entry
                                        # implicit-def: $rax
                                        # implicit-def: $rdx
	retq
.Lfunc_end31:
	.size	String.0new, .Lfunc_end31-String.0new
	.cfi_endproc
                                        # -- End function
	.globl	String.opadd                    # -- Begin function String.opadd
	.p2align	4, 0x90
	.type	String.opadd,@function
String.opadd:                           # @String.opadd
	.cfi_startproc
# %bb.0:                                # %entry
                                        # implicit-def: $rax
                                        # implicit-def: $rdx
	retq
.Lfunc_end32:
	.size	String.opadd, .Lfunc_end32-String.opadd
	.cfi_endproc
                                        # -- End function
	.globl	String.opeq                     # -- Begin function String.opeq
	.p2align	4, 0x90
	.type	String.opeq,@function
String.opeq:                            # @String.opeq
	.cfi_startproc
# %bb.0:                                # %entry
                                        # implicit-def: $rax
                                        # implicit-def: $rdx
	retq
.Lfunc_end33:
	.size	String.opeq, .Lfunc_end33-String.opeq
	.cfi_endproc
                                        # -- End function
	.globl	String.opge                     # -- Begin function String.opge
	.p2align	4, 0x90
	.type	String.opge,@function
String.opge:                            # @String.opge
	.cfi_startproc
# %bb.0:                                # %entry
                                        # implicit-def: $rax
                                        # implicit-def: $rdx
	retq
.Lfunc_end34:
	.size	String.opge, .Lfunc_end34-String.opge
	.cfi_endproc
                                        # -- End function
	.globl	String.opgt                     # -- Begin function String.opgt
	.p2align	4, 0x90
	.type	String.opgt,@function
String.opgt:                            # @String.opgt
	.cfi_startproc
# %bb.0:                                # %entry
                                        # implicit-def: $rax
                                        # implicit-def: $rdx
	retq
.Lfunc_end35:
	.size	String.opgt, .Lfunc_end35-String.opgt
	.cfi_endproc
                                        # -- End function
	.globl	String.ople                     # -- Begin function String.ople
	.p2align	4, 0x90
	.type	String.ople,@function
String.ople:                            # @String.ople
	.cfi_startproc
# %bb.0:                                # %entry
                                        # implicit-def: $rax
                                        # implicit-def: $rdx
	retq
.Lfunc_end36:
	.size	String.ople, .Lfunc_end36-String.ople
	.cfi_endproc
                                        # -- End function
	.globl	String.oplt                     # -- Begin function String.oplt
	.p2align	4, 0x90
	.type	String.oplt,@function
String.oplt:                            # @String.oplt
	.cfi_startproc
# %bb.0:                                # %entry
                                        # implicit-def: $rax
                                        # implicit-def: $rdx
	retq
.Lfunc_end37:
	.size	String.oplt, .Lfunc_end37-String.oplt
	.cfi_endproc
                                        # -- End function
	.globl	Main2.0new                      # -- Begin function Main2.0new
	.p2align	4, 0x90
	.type	Main2.0new,@function
Main2.0new:                             # @Main2.0new
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$64, %edi
	callq	gcool_malloc@PLT
	movq	%rax, %rsi
	movq	%rsi, 16(%rsp)                  # 8-byte Spill
	movq	Main2VT@GOTPCREL(%rip), %rdi
	movq	%rdi, 8(%rsp)                   # 8-byte Spill
	callq	Main2.0init@PLT
	movq	8(%rsp), %rax                   # 8-byte Reload
	movq	16(%rsp), %rdx                  # 8-byte Reload
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end38:
	.size	Main2.0new, .Lfunc_end38-Main2.0new
	.cfi_endproc
                                        # -- End function
	.globl	Main2.0init                     # -- Begin function Main2.0init
	.p2align	4, 0x90
	.type	Main2.0init,@function
Main2.0init:                            # @Main2.0init
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	%rsi, (%rsp)                    # 8-byte Spill
	callq	Main.0init@PLT
	movq	(%rsp), %rsi                    # 8-byte Reload
	movabsq	$4621267426634618634, %rax      # imm = 0x40220A3D70A3D70A
	movq	%rax, 56(%rsi)
	movq	FloatVT@GOTPCREL(%rip), %rax
	movq	%rax, 48(%rsi)
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end39:
	.size	Main2.0init, .Lfunc_end39-Main2.0init
	.cfi_endproc
                                        # -- End function
	.globl	Main4.0new                      # -- Begin function Main4.0new
	.p2align	4, 0x90
	.type	Main4.0new,@function
Main4.0new:                             # @Main4.0new
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$96, %edi
	callq	gcool_malloc@PLT
	movq	%rax, %rsi
	movq	%rsi, 16(%rsp)                  # 8-byte Spill
	movq	Main4VT@GOTPCREL(%rip), %rdi
	movq	%rdi, 8(%rsp)                   # 8-byte Spill
	callq	Main4.0init@PLT
	movq	8(%rsp), %rax                   # 8-byte Reload
	movq	16(%rsp), %rdx                  # 8-byte Reload
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end40:
	.size	Main4.0new, .Lfunc_end40-Main4.0new
	.cfi_endproc
                                        # -- End function
	.globl	Main4.0init                     # -- Begin function Main4.0init
	.p2align	4, 0x90
	.type	Main4.0init,@function
Main4.0init:                            # @Main4.0init
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	%rsi, (%rsp)                    # 8-byte Spill
	callq	Main2.0init@PLT
	movq	(%rsp), %rsi                    # 8-byte Reload
	movabsq	$4626379012211684147, %rax      # imm = 0x4034333333333333
	movq	%rax, 72(%rsi)
	movq	FloatVT@GOTPCREL(%rip), %rax
	movq	%rax, 64(%rsi)
	movq	IntVT@GOTPCREL(%rip), %rax
	movq	%rax, 80(%rsi)
	movq	$5, 88(%rsi)
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end41:
	.size	Main4.0init, .Lfunc_end41-Main4.0init
	.cfi_endproc
                                        # -- End function
	.globl	Main4.hello                     # -- Begin function Main4.hello
	.p2align	4, 0x90
	.type	Main4.hello,@function
Main4.hello:                            # @Main4.hello
	.cfi_startproc
# %bb.0:                                # %entry
	movq	%rdx, -16(%rsp)
	movq	%rcx, -8(%rsp)
	movq	%r9, 8(%rsp)
	movq	%r8, (%rsp)
	movq	-16(%rsp), %rax
	movq	-8(%rsp), %rdx
	retq
.Lfunc_end42:
	.size	Main4.hello, .Lfunc_end42-Main4.hello
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	callq	Main.0new@PLT
	movq	%rax, %rdi
	movq	%rdx, %rsi
	callq	Main.main@PLT
	movl	%edx, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end43:
	.size	main, .Lfunc_end43-main
	.cfi_endproc
                                        # -- End function
	.type	ObjectVT,@object                # @ObjectVT
	.section	.rodata,"a",@progbits
	.globl	ObjectVT
	.p2align	4
ObjectVT:
	.zero	32
	.quad	Object.0new
	.quad	Object.opisvoid
	.size	ObjectVT, 48

	.type	MainVT,@object                  # @MainVT
	.globl	MainVT
	.p2align	4
MainVT:
	.quad	ObjectVT
	.quad	1                               # 0x1
	.quad	0
	.quad	0
	.quad	Main.0new
	.quad	Object.opisvoid
	.quad	Main.main
	.size	MainVT, 56

	.type	IntVT,@object                   # @IntVT
	.globl	IntVT
	.p2align	4
IntVT:
	.quad	ObjectVT
	.quad	1                               # 0x1
	.quad	0
	.quad	0
	.quad	Int.0new
	.quad	Object.opisvoid
	.quad	Int.opadd
	.quad	Int.opsub
	.quad	Int.opmul
	.quad	Int.opdiv
	.quad	Int.opeq
	.quad	Int.opge
	.quad	Int.opgt
	.quad	Int.ople
	.quad	Int.oplt
	.size	IntVT, 120

	.type	FloatVT,@object                 # @FloatVT
	.globl	FloatVT
	.p2align	4
FloatVT:
	.quad	ObjectVT
	.quad	1                               # 0x1
	.quad	0
	.quad	0
	.quad	Float.0new
	.quad	Object.opisvoid
	.quad	Float.opadd
	.quad	Float.opsub
	.quad	Float.opmul
	.quad	Float.opdiv
	.quad	Float.opeq
	.quad	Float.opge
	.quad	Float.opgt
	.quad	Float.ople
	.quad	Float.oplt
	.size	FloatVT, 120

	.type	BoolVT,@object                  # @BoolVT
	.globl	BoolVT
	.p2align	4
BoolVT:
	.quad	ObjectVT
	.quad	1                               # 0x1
	.quad	0
	.quad	0
	.quad	Bool.0new
	.quad	Object.opisvoid
	.quad	Bool.opadd
	.quad	Bool.opmul
	.quad	Bool.opeq
	.quad	Bool.opnot
	.size	BoolVT, 80

	.type	StringVT,@object                # @StringVT
	.globl	StringVT
	.p2align	4
StringVT:
	.quad	ObjectVT
	.quad	1                               # 0x1
	.quad	0
	.quad	0
	.quad	String.0new
	.quad	Object.opisvoid
	.quad	String.opadd
	.quad	String.opeq
	.quad	String.opge
	.quad	String.opgt
	.quad	String.ople
	.quad	String.oplt
	.size	StringVT, 96

	.type	Main2VT,@object                 # @Main2VT
	.globl	Main2VT
	.p2align	4
Main2VT:
	.quad	MainVT
	.quad	2                               # 0x2
	.quad	0
	.quad	0
	.quad	Main2.0new
	.quad	Object.opisvoid
	.quad	Main.main
	.size	Main2VT, 56

	.type	Main4VT,@object                 # @Main4VT
	.globl	Main4VT
	.p2align	4
Main4VT:
	.quad	Main2VT
	.quad	3                               # 0x3
	.quad	0
	.quad	0
	.quad	Main4.0new
	.quad	Object.opisvoid
	.quad	Main.main
	.quad	Main4.hello
	.size	Main4VT, 64

	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym Object.0new
	.addrsig_sym Object.0init
	.addrsig_sym Object.opisvoid
	.addrsig_sym Main.0new
	.addrsig_sym Main.0init
	.addrsig_sym Main.main
	.addrsig_sym Int.0new
	.addrsig_sym Int.opadd
	.addrsig_sym Int.opsub
	.addrsig_sym Int.opmul
	.addrsig_sym Int.opdiv
	.addrsig_sym Int.opeq
	.addrsig_sym Int.opge
	.addrsig_sym Int.opgt
	.addrsig_sym Int.ople
	.addrsig_sym Int.oplt
	.addrsig_sym Float.0new
	.addrsig_sym Float.opadd
	.addrsig_sym Float.opsub
	.addrsig_sym Float.opmul
	.addrsig_sym Float.opdiv
	.addrsig_sym Float.opeq
	.addrsig_sym Float.opge
	.addrsig_sym Float.opgt
	.addrsig_sym Float.ople
	.addrsig_sym Float.oplt
	.addrsig_sym Bool.0new
	.addrsig_sym Bool.opadd
	.addrsig_sym Bool.opmul
	.addrsig_sym Bool.opeq
	.addrsig_sym Bool.opnot
	.addrsig_sym String.0new
	.addrsig_sym String.opadd
	.addrsig_sym String.opeq
	.addrsig_sym String.opge
	.addrsig_sym String.opgt
	.addrsig_sym String.ople
	.addrsig_sym String.oplt
	.addrsig_sym Main2.0new
	.addrsig_sym Main2.0init
	.addrsig_sym Main4.0new
	.addrsig_sym Main4.0init
	.addrsig_sym Main4.hello
	.addrsig_sym gcool_malloc
	.addrsig_sym ObjectVT
	.addrsig_sym MainVT
	.addrsig_sym IntVT
	.addrsig_sym FloatVT
	.addrsig_sym BoolVT
	.addrsig_sym Main2VT
	.addrsig_sym Main4VT
