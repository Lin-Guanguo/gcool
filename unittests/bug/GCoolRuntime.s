	.text
	.file	"GCoolRuntime.c"
	.globl	gcool_malloc                    # -- Begin function gcool_malloc
	.p2align	4, 0x90
	.type	gcool_malloc,@function
gcool_malloc:                           # @gcool_malloc
	.cfi_startproc
# %bb.0:                                # %entry
	jmp	malloc                          # TAILCALL
.Lfunc_end0:
	.size	gcool_malloc, .Lfunc_end0-gcool_malloc
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 14.0.0"
	.section	".note.GNU-stack","",@progbits
	.addrsig
