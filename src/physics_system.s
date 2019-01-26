	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14
	.globl	__ZN13PhysicsSystemC2Ev ## -- Begin function _ZN13PhysicsSystemC2Ev
	.p2align	4, 0x90
__ZN13PhysicsSystemC2Ev:                ## @_ZN13PhysicsSystemC2Ev
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN13PhysicsSystemC1Ev ## -- Begin function _ZN13PhysicsSystemC1Ev
	.p2align	4, 0x90
__ZN13PhysicsSystemC1Ev:                ## @_ZN13PhysicsSystemC1Ev
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	__ZN13PhysicsSystemC2Ev
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN13PhysicsSystem25UpdateAngularAccelerationERK6Entity ## -- Begin function _ZN13PhysicsSystem25UpdateAngularAccelerationERK6Entity
	.p2align	4, 0x90
__ZN13PhysicsSystem25UpdateAngularAccelerationERK6Entity: ## @_ZN13PhysicsSystem25UpdateAngularAccelerationERK6Entity
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -80(%rbp)
	movq	%rsi, -88(%rbp)
	movq	-88(%rbp), %rsi
	addq	$40, %rsi
	movq	%rsi, -72(%rbp)
	movq	-72(%rbp), %rsi
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rsi
	movq	%rsi, -56(%rbp)
	movq	-56(%rbp), %rsi
	movq	(%rsi), %rsi
	movsd	40(%rsi), %xmm0         ## xmm0 = mem[0],zero
	movq	-88(%rbp), %rsi
	addq	$40, %rsi
	movq	%rsi, -24(%rbp)
	movq	-24(%rbp), %rsi
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movq	%rsi, -8(%rbp)
	movq	-8(%rbp), %rsi
	movq	(%rsi), %rsi
	divsd	48(%rsi), %xmm0
	movq	-88(%rbp), %rsi
	addq	$40, %rsi
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rsi
	movq	%rsi, -40(%rbp)
	movq	-40(%rbp), %rsi
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rsi
	movq	(%rsi), %rsi
	movsd	%xmm0, 32(%rsi)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN13PhysicsSystem21UpdateAngularVelocityERKxRK6Entity ## -- Begin function _ZN13PhysicsSystem21UpdateAngularVelocityERKxRK6Entity
	.p2align	4, 0x90
__ZN13PhysicsSystem21UpdateAngularVelocityERKxRK6Entity: ## @_ZN13PhysicsSystem21UpdateAngularVelocityERKxRK6Entity
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$88, %rsp
	movq	%rdi, -200(%rbp)
	movq	%rsi, -208(%rbp)
	movq	%rdx, -216(%rbp)
	movq	-216(%rbp), %rdx
	addq	$40, %rdx
	movq	%rdx, -192(%rbp)
	movq	-192(%rbp), %rdx
	movq	%rdx, -184(%rbp)
	movq	-184(%rbp), %rdx
	movq	%rdx, -176(%rbp)
	movq	-176(%rbp), %rdx
	movq	(%rdx), %rdx
	testb	$1, 137(%rdx)
	jne	LBB3_4
## %bb.1:
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movsd	32(%rax), %xmm0         ## xmm0 = mem[0],zero
	movq	-208(%rbp), %rax
	movq	(%rax), %rax
	cvtsi2sdq	%rax, %xmm1
	mulsd	%xmm1, %xmm0
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	addsd	16(%rax), %xmm0
	movsd	%xmm0, 16(%rax)
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movsd	16(%rax), %xmm0         ## xmm0 = mem[0],zero
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	(%rax), %rax
	ucomisd	24(%rax), %xmm0
	jbe	LBB3_3
## %bb.2:
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	(%rax), %rax
	movsd	24(%rax), %xmm0         ## xmm0 = mem[0],zero
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	movq	(%rax), %rax
	movsd	%xmm0, 16(%rax)
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	movb	$1, 137(%rax)
LBB3_3:
	jmp	LBB3_4
LBB3_4:
	addq	$88, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__literal8,8byte_literals
	.p2align	3               ## -- Begin function _ZN13PhysicsSystem26UpdateDeltaRotationDegreesERKxRK6Entity
LCPI4_0:
	.quad	4602678819172646912     ## double 0.5
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__ZN13PhysicsSystem26UpdateDeltaRotationDegreesERKxRK6Entity
	.p2align	4, 0x90
__ZN13PhysicsSystem26UpdateDeltaRotationDegreesERKxRK6Entity: ## @_ZN13PhysicsSystem26UpdateDeltaRotationDegreesERKxRK6Entity
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$128, %rsp
	movsd	LCPI4_0(%rip), %xmm0    ## xmm0 = mem[0],zero
	movq	%rdi, -96(%rbp)
	movq	%rsi, -104(%rbp)
	movq	%rdx, -112(%rbp)
	movq	-112(%rbp), %rdx
	addq	$40, %rdx
	movq	%rdx, -88(%rbp)
	movq	-88(%rbp), %rdx
	movq	%rdx, -80(%rbp)
	movq	-80(%rbp), %rdx
	movq	%rdx, -72(%rbp)
	movq	-72(%rbp), %rdx
	movq	(%rdx), %rdx
	movsd	16(%rdx), %xmm1         ## xmm1 = mem[0],zero
	movq	-104(%rbp), %rdx
	movq	(%rdx), %rdx
	cvtsi2sdq	%rdx, %xmm2
	mulsd	%xmm2, %xmm1
	movq	-112(%rbp), %rdx
	addq	$40, %rdx
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	%rdx, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rdx
	mulsd	32(%rdx), %xmm0
	movq	-104(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, -32(%rbp)
	movl	$2, -36(%rbp)
	movq	-32(%rbp), %rdx
	cvtsi2sdq	%rdx, %xmm2
	movl	-36(%rbp), %eax
	cvtsi2sdl	%eax, %xmm3
	movsd	%xmm0, -120(%rbp)       ## 8-byte Spill
	movaps	%xmm2, %xmm0
	movsd	%xmm1, -128(%rbp)       ## 8-byte Spill
	movaps	%xmm3, %xmm1
	callq	_pow
	movsd	-120(%rbp), %xmm1       ## 8-byte Reload
                                        ## xmm1 = mem[0],zero
	mulsd	%xmm0, %xmm1
	movsd	-128(%rbp), %xmm0       ## 8-byte Reload
                                        ## xmm0 = mem[0],zero
	addsd	%xmm1, %xmm0
	movq	-112(%rbp), %rdx
	addq	$40, %rdx
	movq	%rdx, -64(%rbp)
	movq	-64(%rbp), %rdx
	movq	%rdx, -56(%rbp)
	movq	-56(%rbp), %rdx
	movq	%rdx, -48(%rbp)
	movq	-48(%rbp), %rdx
	movq	(%rdx), %rdx
	movsd	%xmm0, 96(%rdx)
	addq	$128, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN13PhysicsSystem11UpdateForceERK6Entity ## -- Begin function _ZN13PhysicsSystem11UpdateForceERK6Entity
	.p2align	4, 0x90
__ZN13PhysicsSystem11UpdateForceERK6Entity: ## @_ZN13PhysicsSystem11UpdateForceERK6Entity
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rsi
	addq	$40, %rsi
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rsi
	movq	%rsi, -40(%rbp)
	movq	-40(%rbp), %rsi
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rsi
	movq	(%rsi), %rsi
	addq	$80, %rsi
	movq	-64(%rbp), %rdi
	addq	$40, %rdi
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdi
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	(%rdi), %rdi
	movsd	96(%rdi), %xmm0         ## xmm0 = mem[0],zero
	movq	%rsi, %rdi
	callq	__ZN8Vector2D13RotateDegreesEd
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN13PhysicsSystem18UpdateAccelerationERK6Entity ## -- Begin function _ZN13PhysicsSystem18UpdateAccelerationERK6Entity
	.p2align	4, 0x90
__ZN13PhysicsSystem18UpdateAccelerationERK6Entity: ## @_ZN13PhysicsSystem18UpdateAccelerationERK6Entity
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$112, %rsp
	movq	%rdi, -80(%rbp)
	movq	%rsi, -88(%rbp)
	movq	-88(%rbp), %rsi
	addq	$40, %rsi
	movq	%rsi, -72(%rbp)
	movq	-72(%rbp), %rsi
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rsi
	movq	%rsi, -56(%rbp)
	movq	-56(%rbp), %rsi
	movq	(%rsi), %rsi
	addq	$80, %rsi
	movq	-88(%rbp), %rdi
	addq	$40, %rdi
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdi
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movq	(%rdi), %rdi
	movsd	104(%rdi), %xmm0        ## xmm0 = mem[0],zero
	movq	%rsi, %rdi
	callq	__ZNK8Vector2DdvEd
	movsd	%xmm0, -104(%rbp)
	movsd	%xmm1, -96(%rbp)
	movq	-88(%rbp), %rsi
	addq	$40, %rsi
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rsi
	movq	%rsi, -40(%rbp)
	movq	-40(%rbp), %rsi
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rsi
	movq	(%rsi), %rsi
	movq	-104(%rbp), %rdi
	movq	%rdi, 56(%rsi)
	movq	-96(%rbp), %rdi
	movq	%rdi, 64(%rsi)
	addq	$112, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN13PhysicsSystem14UpdateVelocityERKxRK6Entity ## -- Begin function _ZN13PhysicsSystem14UpdateVelocityERKxRK6Entity
	.p2align	4, 0x90
__ZN13PhysicsSystem14UpdateVelocityERKxRK6Entity: ## @_ZN13PhysicsSystem14UpdateVelocityERKxRK6Entity
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$240, %rsp
	movq	%rdi, -200(%rbp)
	movq	%rsi, -208(%rbp)
	movq	%rdx, -216(%rbp)
	movq	-216(%rbp), %rdx
	addq	$40, %rdx
	movq	%rdx, -192(%rbp)
	movq	-192(%rbp), %rdx
	movq	%rdx, -184(%rbp)
	movq	-184(%rbp), %rdx
	movq	%rdx, -176(%rbp)
	movq	-176(%rbp), %rdx
	movq	(%rdx), %rdx
	testb	$1, 136(%rdx)
	jne	LBB7_4
## %bb.1:
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	addq	$56, %rax
	movq	-208(%rbp), %rcx
	movq	(%rcx), %rcx
	cvtsi2sdq	%rcx, %xmm0
	movq	%rax, %rdi
	callq	__ZNK8Vector2DmlEd
	leaq	-232(%rbp), %rsi
	movsd	%xmm0, -232(%rbp)
	movsd	%xmm1, -224(%rbp)
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rdi
	callq	__ZN8Vector2DpLERKS_
	movq	-216(%rbp), %rcx
	addq	$40, %rcx
	movq	%rcx, -72(%rbp)
	movq	-72(%rbp), %rcx
	movq	%rcx, -64(%rbp)
	movq	-64(%rbp), %rcx
	movq	%rcx, -56(%rbp)
	movq	-56(%rbp), %rcx
	movq	(%rcx), %rdi
	movq	%rax, -240(%rbp)        ## 8-byte Spill
	callq	__ZNK8Vector2D9MagnitudeEv
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	(%rax), %rax
	ucomisd	72(%rax), %xmm0
	jbe	LBB7_3
## %bb.2:
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	movq	(%rax), %rdi
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	movq	(%rax), %rax
	movsd	72(%rax), %xmm0         ## xmm0 = mem[0],zero
	callq	__ZN8Vector2D12SetMagnitudeEd
	movq	-216(%rbp), %rax
	addq	$40, %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	movq	%rax, -152(%rbp)
	movq	-152(%rbp), %rax
	movq	(%rax), %rax
	movb	$1, 136(%rax)
LBB7_3:
	jmp	LBB7_4
LBB7_4:
	addq	$240, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN13PhysicsSystem21UpdateVelocityDegreesERK6Entity ## -- Begin function _ZN13PhysicsSystem21UpdateVelocityDegreesERK6Entity
	.p2align	4, 0x90
__ZN13PhysicsSystem21UpdateVelocityDegreesERK6Entity: ## @_ZN13PhysicsSystem21UpdateVelocityDegreesERK6Entity
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-64(%rbp), %rsi
	addq	$40, %rsi
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rsi
	movq	%rsi, -40(%rbp)
	movq	-40(%rbp), %rsi
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rsi
	movq	(%rsi), %rdi
	movq	-64(%rbp), %rsi
	addq	$40, %rsi
	movq	%rsi, -24(%rbp)
	movq	-24(%rbp), %rsi
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movq	%rsi, -8(%rbp)
	movq	-8(%rbp), %rsi
	movq	(%rsi), %rsi
	movsd	96(%rsi), %xmm0         ## xmm0 = mem[0],zero
	callq	__ZN8Vector2D13RotateDegreesEd
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN13PhysicsSystem14UpdatePositionERKxRK6Entity ## -- Begin function _ZN13PhysicsSystem14UpdatePositionERKxRK6Entity
	.p2align	4, 0x90
__ZN13PhysicsSystem14UpdatePositionERKxRK6Entity: ## @_ZN13PhysicsSystem14UpdatePositionERKxRK6Entity
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$96, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	movq	-72(%rbp), %rdx
	addq	$40, %rdx
	movq	%rdx, -48(%rbp)
	movq	-48(%rbp), %rdx
	movq	%rdx, -40(%rbp)
	movq	-40(%rbp), %rdx
	movq	%rdx, -32(%rbp)
	movq	-32(%rbp), %rdx
	movq	(%rdx), %rdi
	movq	-64(%rbp), %rdx
	movq	(%rdx), %rdx
	cvtsi2sdq	%rdx, %xmm0
	callq	__ZNK8Vector2DmlEd
	leaq	-88(%rbp), %rsi
	movsd	%xmm0, -88(%rbp)
	movsd	%xmm1, -80(%rbp)
	movq	-72(%rbp), %rdx
	addq	$40, %rdx
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	%rdx, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	%rdx, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rdx
	addq	$112, %rdx
	movq	%rdx, %rdi
	callq	__ZN8Vector2DpLERKS_
	movq	%rax, -96(%rbp)         ## 8-byte Spill
	addq	$96, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEE ## -- Begin function _ZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEE
	.p2align	4, 0x90
__ZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEE: ## @_ZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEE
Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception0
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$512, %rsp              ## imm = 0x200
	movq	%rcx, -296(%rbp)
	movq	%rdi, -304(%rbp)
	movq	%rsi, -312(%rbp)
	movq	%rdx, -320(%rbp)
	movq	-304(%rbp), %rcx
	cmpb	$0, __ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform(%rip)
	movq	%rcx, -456(%rbp)        ## 8-byte Spill
	jne	LBB10_4
## %bb.1:
	leaq	__ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform(%rip), %rdi
	callq	___cxa_guard_acquire
	cmpl	$0, %eax
	je	LBB10_4
## %bb.2:
Ltmp0:
	leaq	__ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform(%rip), %rdi
	callq	__ZN18TransformComponentC1Ev
Ltmp1:
	jmp	LBB10_3
LBB10_3:
	movq	__ZN18TransformComponentD1Ev@GOTPCREL(%rip), %rax
	leaq	__ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform(%rip), %rcx
	leaq	___dso_handle(%rip), %rdx
	movq	%rax, %rdi
	movq	%rcx, %rsi
	callq	___cxa_atexit
	leaq	__ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform(%rip), %rdi
	movl	%eax, -460(%rbp)        ## 4-byte Spill
	callq	___cxa_guard_release
LBB10_4:
	cmpb	$0, __ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody(%rip)
	jne	LBB10_8
## %bb.5:
	leaq	__ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody(%rip), %rdi
	callq	___cxa_guard_acquire
	cmpl	$0, %eax
	je	LBB10_8
## %bb.6:
Ltmp3:
	leaq	__ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody(%rip), %rdi
	callq	__ZN20RigidBody2DComponentC1Ev
Ltmp4:
	jmp	LBB10_7
LBB10_7:
	leaq	__ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody(%rip), %rdi
	callq	___cxa_guard_release
LBB10_8:
	movq	-320(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -288(%rbp)
	movq	-288(%rbp), %rax
	movq	%rax, -280(%rbp)
	movq	-280(%rbp), %rax
	movq	%rax, -272(%rbp)
	movq	-272(%rbp), %rax
	movq	(%rax), %rsi
	leaq	-384(%rbp), %rax
	movq	%rax, %rdi
	movq	%rax, -472(%rbp)        ## 8-byte Spill
	callq	__ZN18TransformComponentC1ERKS_
Ltmp6:
	leaq	__ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform(%rip), %rdi
	movq	-472(%rbp), %rsi        ## 8-byte Reload
	callq	__ZN18TransformComponentaSES_
Ltmp7:
	movq	%rax, -480(%rbp)        ## 8-byte Spill
	jmp	LBB10_9
LBB10_9:
	leaq	-384(%rbp), %rdi
	callq	__ZN18TransformComponentD1Ev
	leaq	__ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody(%rip), %rdi
	movl	$138, %eax
	movl	%eax, %edx
	movq	-320(%rbp), %rcx
	addq	$40, %rcx
	movq	%rcx, -264(%rbp)
	movq	-264(%rbp), %rcx
	movq	%rcx, -256(%rbp)
	movq	-256(%rbp), %rcx
	movq	%rcx, -248(%rbp)
	movq	-248(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	%rcx, %rsi
	callq	_memcpy
	movq	-320(%rbp), %rsi
	movq	-456(%rbp), %rdi        ## 8-byte Reload
	callq	__ZN13PhysicsSystem25UpdateAngularAccelerationERK6Entity
	movq	-312(%rbp), %rsi
	movq	-320(%rbp), %rdx
	movq	-456(%rbp), %rdi        ## 8-byte Reload
	callq	__ZN13PhysicsSystem21UpdateAngularVelocityERKxRK6Entity
	movq	-312(%rbp), %rsi
	movq	-320(%rbp), %rdx
	movq	-456(%rbp), %rdi        ## 8-byte Reload
	callq	__ZN13PhysicsSystem26UpdateDeltaRotationDegreesERKxRK6Entity
	movq	-320(%rbp), %rsi
	movq	-456(%rbp), %rdi        ## 8-byte Reload
	callq	__ZN13PhysicsSystem11UpdateForceERK6Entity
	movq	-320(%rbp), %rsi
	movq	-456(%rbp), %rdi        ## 8-byte Reload
	callq	__ZN13PhysicsSystem18UpdateAccelerationERK6Entity
	movq	-312(%rbp), %rsi
	movq	-320(%rbp), %rdx
	movq	-456(%rbp), %rdi        ## 8-byte Reload
	callq	__ZN13PhysicsSystem14UpdateVelocityERKxRK6Entity
	movq	-320(%rbp), %rsi
	movq	-456(%rbp), %rdi        ## 8-byte Reload
	callq	__ZN13PhysicsSystem21UpdateVelocityDegreesERK6Entity
	movq	-312(%rbp), %rsi
	movq	-320(%rbp), %rdx
	movq	-456(%rbp), %rdi        ## 8-byte Reload
	callq	__ZN13PhysicsSystem14UpdatePositionERKxRK6Entity
	movq	-320(%rbp), %rcx
	addq	$40, %rcx
	movq	%rcx, -240(%rbp)
	movq	-240(%rbp), %rcx
	movq	%rcx, -232(%rbp)
	movq	-232(%rbp), %rcx
	movq	%rcx, -224(%rbp)
	movq	-224(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	-320(%rbp), %rdx
	addq	$8, %rdx
	movq	%rdx, -192(%rbp)
	movq	-192(%rbp), %rdx
	movq	%rdx, -184(%rbp)
	movq	-184(%rbp), %rdx
	movq	%rdx, -176(%rbp)
	movq	-176(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	112(%rcx), %rsi
	movq	%rsi, (%rdx)
	movq	120(%rcx), %rcx
	movq	%rcx, 8(%rdx)
	movq	-320(%rbp), %rcx
	addq	$40, %rcx
	movq	%rcx, -24(%rbp)
	movq	-24(%rbp), %rcx
	movq	%rcx, -16(%rbp)
	movq	-16(%rbp), %rcx
	movq	%rcx, -8(%rbp)
	movq	-8(%rbp), %rcx
	movq	(%rcx), %rcx
	movsd	96(%rcx), %xmm0         ## xmm0 = mem[0],zero
	movq	-320(%rbp), %rcx
	addq	$8, %rcx
	movq	%rcx, -48(%rbp)
	movq	-48(%rbp), %rcx
	movq	%rcx, -40(%rbp)
	movq	-40(%rbp), %rcx
	movq	%rcx, -32(%rbp)
	movq	-32(%rbp), %rcx
	movq	(%rcx), %rcx
	addsd	32(%rcx), %xmm0
	movsd	%xmm0, 32(%rcx)
	movq	-320(%rbp), %rcx
	addq	$8, %rcx
	movq	%rcx, -72(%rbp)
	movq	-72(%rbp), %rcx
	movq	%rcx, -64(%rbp)
	movq	-64(%rbp), %rcx
	movq	%rcx, -56(%rbp)
	movq	-56(%rbp), %rcx
	movq	(%rcx), %rcx
	movsd	32(%rcx), %xmm0         ## xmm0 = mem[0],zero
	movq	-320(%rbp), %rcx
	addq	$40, %rcx
	movq	%rcx, -96(%rbp)
	movq	-96(%rbp), %rcx
	movq	%rcx, -88(%rbp)
	movq	-88(%rbp), %rcx
	movq	%rcx, -80(%rbp)
	movq	-80(%rbp), %rcx
	movq	(%rcx), %rcx
	movsd	%xmm0, 128(%rcx)
	movq	-320(%rbp), %rcx
	addq	$48, %rcx
	movq	%rcx, -120(%rbp)
	movq	-120(%rbp), %rcx
	movq	%rcx, -112(%rbp)
	movq	-112(%rbp), %rcx
	movq	%rcx, -104(%rbp)
	movq	-104(%rbp), %rcx
	cmpq	$0, (%rcx)
	je	LBB10_20
## %bb.10:
	movq	-320(%rbp), %rax
	addq	$48, %rax
	movq	%rax, -144(%rbp)
	movq	-144(%rbp), %rax
	movq	%rax, -136(%rbp)
	movq	-136(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	-128(%rbp), %rax
	movq	(%rax), %rax
	testb	$1, 24(%rax)
	je	LBB10_20
## %bb.11:
	movq	-320(%rbp), %rdi
	movq	-296(%rbp), %rax
	movq	%rax, -400(%rbp)
	movq	-400(%rbp), %rsi
	callq	__ZN15CollisionSystem16DetectAndRespondERK6EntityNSt3__111__wrap_iterIPNS3_10unique_ptrIS0_NS3_14default_deleteIS0_EEEEEE
	movl	%eax, -388(%rbp)
	cmpl	$1, -388(%rbp)
	jne	LBB10_19
## %bb.12:
	leaq	-448(%rbp), %rdi
	leaq	__ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform(%rip), %rsi
	callq	__ZN18TransformComponentC1ERKS_
	movq	-320(%rbp), %rsi
	addq	$8, %rsi
	movq	%rsi, -168(%rbp)
	movq	-168(%rbp), %rsi
	movq	%rsi, -160(%rbp)
	movq	-160(%rbp), %rsi
	movq	%rsi, -152(%rbp)
	movq	-152(%rbp), %rsi
	movq	(%rsi), %rdi
	movq	%rdi, -488(%rbp)        ## 8-byte Spill
## %bb.13:
Ltmp9:
	leaq	-448(%rbp), %rsi
	movq	-488(%rbp), %rdi        ## 8-byte Reload
	callq	__ZN18TransformComponentaSES_
Ltmp10:
	movq	%rax, -496(%rbp)        ## 8-byte Spill
	jmp	LBB10_14
LBB10_14:
	leaq	-448(%rbp), %rdi
	callq	__ZN18TransformComponentD1Ev
	leaq	__ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody(%rip), %rdi
	movl	$138, %eax
	movl	%eax, %edx
	movq	-320(%rbp), %rcx
	addq	$40, %rcx
	movq	%rcx, -216(%rbp)
	movq	-216(%rbp), %rcx
	movq	%rcx, -208(%rbp)
	movq	-208(%rbp), %rcx
	movq	%rcx, -200(%rbp)
	movq	-200(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	%rdi, -504(%rbp)        ## 8-byte Spill
	movq	%rcx, %rdi
	movq	-504(%rbp), %rsi        ## 8-byte Reload
	callq	_memcpy
	jmp	LBB10_19
LBB10_15:
Ltmp2:
	leaq	__ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform(%rip), %rdi
	movl	%edx, %ecx
	movq	%rax, -328(%rbp)
	movl	%ecx, -332(%rbp)
	callq	___cxa_guard_abort
	jmp	LBB10_21
LBB10_16:
Ltmp5:
	leaq	__ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody(%rip), %rdi
	movl	%edx, %ecx
	movq	%rax, -328(%rbp)
	movl	%ecx, -332(%rbp)
	callq	___cxa_guard_abort
	jmp	LBB10_21
LBB10_17:
Ltmp8:
	leaq	-384(%rbp), %rdi
	movl	%edx, %ecx
	movq	%rax, -328(%rbp)
	movl	%ecx, -332(%rbp)
	callq	__ZN18TransformComponentD1Ev
	jmp	LBB10_21
LBB10_18:
Ltmp11:
	leaq	-448(%rbp), %rdi
	movl	%edx, %ecx
	movq	%rax, -328(%rbp)
	movl	%ecx, -332(%rbp)
	callq	__ZN18TransformComponentD1Ev
	jmp	LBB10_21
LBB10_19:
	jmp	LBB10_20
LBB10_20:
	addq	$512, %rsp              ## imm = 0x200
	popq	%rbp
	retq
LBB10_21:
	movq	-328(%rbp), %rdi
	callq	__Unwind_Resume
	ud2
Lfunc_end0:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table10:
Lexception0:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.byte	93                      ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	91                      ## Call site table length
Lset0 = Ltmp0-Lfunc_begin0              ## >> Call Site 1 <<
	.long	Lset0
Lset1 = Ltmp1-Ltmp0                     ##   Call between Ltmp0 and Ltmp1
	.long	Lset1
Lset2 = Ltmp2-Lfunc_begin0              ##     jumps to Ltmp2
	.long	Lset2
	.byte	0                       ##   On action: cleanup
Lset3 = Ltmp3-Lfunc_begin0              ## >> Call Site 2 <<
	.long	Lset3
Lset4 = Ltmp4-Ltmp3                     ##   Call between Ltmp3 and Ltmp4
	.long	Lset4
Lset5 = Ltmp5-Lfunc_begin0              ##     jumps to Ltmp5
	.long	Lset5
	.byte	0                       ##   On action: cleanup
Lset6 = Ltmp4-Lfunc_begin0              ## >> Call Site 3 <<
	.long	Lset6
Lset7 = Ltmp6-Ltmp4                     ##   Call between Ltmp4 and Ltmp6
	.long	Lset7
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset8 = Ltmp6-Lfunc_begin0              ## >> Call Site 4 <<
	.long	Lset8
Lset9 = Ltmp7-Ltmp6                     ##   Call between Ltmp6 and Ltmp7
	.long	Lset9
Lset10 = Ltmp8-Lfunc_begin0             ##     jumps to Ltmp8
	.long	Lset10
	.byte	0                       ##   On action: cleanup
Lset11 = Ltmp7-Lfunc_begin0             ## >> Call Site 5 <<
	.long	Lset11
Lset12 = Ltmp9-Ltmp7                    ##   Call between Ltmp7 and Ltmp9
	.long	Lset12
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset13 = Ltmp9-Lfunc_begin0             ## >> Call Site 6 <<
	.long	Lset13
Lset14 = Ltmp10-Ltmp9                   ##   Call between Ltmp9 and Ltmp10
	.long	Lset14
Lset15 = Ltmp11-Lfunc_begin0            ##     jumps to Ltmp11
	.long	Lset15
	.byte	0                       ##   On action: cleanup
Lset16 = Ltmp10-Lfunc_begin0            ## >> Call Site 7 <<
	.long	Lset16
Lset17 = Lfunc_end0-Ltmp10              ##   Call between Ltmp10 and Lfunc_end0
	.long	Lset17
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.p2align	2
                                        ## -- End function
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__ZN18TransformComponentD1Ev ## -- Begin function _ZN18TransformComponentD1Ev
	.weak_def_can_be_hidden	__ZN18TransformComponentD1Ev
	.p2align	4, 0x90
__ZN18TransformComponentD1Ev:           ## @_ZN18TransformComponentD1Ev
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	__ZN18TransformComponentD2Ev
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN18TransformComponentD2Ev ## -- Begin function _ZN18TransformComponentD2Ev
	.weak_def_can_be_hidden	__ZN18TransformComponentD2Ev
	.p2align	4, 0x90
__ZN18TransformComponentD2Ev:           ## @_ZN18TransformComponentD2Ev
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$128, %rsp
	movq	%rdi, -112(%rbp)
	movq	-112(%rbp), %rdi
	addq	$40, %rdi
	movq	%rdi, -104(%rbp)
	movq	-104(%rbp), %rdi
	movq	%rdi, -96(%rbp)
	movq	-96(%rbp), %rdi
	movq	%rdi, -72(%rbp)
	movq	$0, -80(%rbp)
	movq	-72(%rbp), %rdi
	movq	%rdi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -88(%rbp)
	movq	-80(%rbp), %rax
	movq	%rdi, -48(%rbp)
	movq	-48(%rbp), %rcx
	movq	%rcx, -40(%rbp)
	movq	-40(%rbp), %rcx
	movq	%rax, (%rcx)
	cmpq	$0, -88(%rbp)
	movq	%rdi, -120(%rbp)        ## 8-byte Spill
	je	LBB12_4
## %bb.1:
	movq	-120(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rcx
	movq	%rcx, -56(%rbp)
	movq	-56(%rbp), %rcx
	movq	-88(%rbp), %rdx
	movq	%rcx, -8(%rbp)
	movq	%rdx, -16(%rbp)
	movq	-16(%rbp), %rcx
	cmpq	$0, %rcx
	movq	%rcx, -128(%rbp)        ## 8-byte Spill
	je	LBB12_3
## %bb.2:
	movq	-128(%rbp), %rdi        ## 8-byte Reload
	callq	__ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED1Ev
	movq	-128(%rbp), %rdi        ## 8-byte Reload
	callq	__ZdlPv
LBB12_3:
	jmp	LBB12_4
LBB12_4:
	addq	$128, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED1Ev ## -- Begin function _ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED1Ev
	.weak_def_can_be_hidden	__ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED1Ev
	.p2align	4, 0x90
__ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED1Ev: ## @_ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED1Ev
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	__ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev ## -- Begin function _ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev
	.weak_def_can_be_hidden	__ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev
	.p2align	4, 0x90
__ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev: ## @_ZNSt3__16vectorINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	__ZNSt3__113__vector_baseINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZNSt3__113__vector_baseINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev ## -- Begin function _ZNSt3__113__vector_baseINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev
	.weak_def_can_be_hidden	__ZNSt3__113__vector_baseINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev
	.p2align	4, 0x90
__ZNSt3__113__vector_baseINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev: ## @_ZNSt3__113__vector_baseINS_10unique_ptrI18TransformComponentNS_14default_deleteIS2_EEEENS_9allocatorIS5_EEED2Ev
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$400, %rsp              ## imm = 0x190
	movq	%rdi, -360(%rbp)
	movq	-360(%rbp), %rdi
	cmpq	$0, (%rdi)
	movq	%rdi, -368(%rbp)        ## 8-byte Spill
	je	LBB15_10
## %bb.1:
	movq	-368(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -240(%rbp)
	movq	-240(%rbp), %rcx
	movq	(%rcx), %rdx
	movq	%rcx, -216(%rbp)
	movq	%rdx, -224(%rbp)
	movq	-216(%rbp), %rcx
	movq	8(%rcx), %rdx
	movq	%rdx, -232(%rbp)
	movq	%rcx, -376(%rbp)        ## 8-byte Spill
LBB15_2:                                ## =>This Inner Loop Header: Depth=1
	movq	-224(%rbp), %rax
	cmpq	-232(%rbp), %rax
	je	LBB15_9
## %bb.3:                               ##   in Loop: Header=BB15_2 Depth=1
	movq	-376(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rcx
	addq	$16, %rcx
	movq	%rcx, -200(%rbp)
	movq	-200(%rbp), %rcx
	movq	%rcx, -192(%rbp)
	movq	-192(%rbp), %rcx
	movq	-232(%rbp), %rdx
	addq	$-8, %rdx
	movq	%rdx, -232(%rbp)
	movq	%rdx, -184(%rbp)
	movq	-184(%rbp), %rdx
	movq	%rcx, -152(%rbp)
	movq	%rdx, -160(%rbp)
	movq	-152(%rbp), %rcx
	movq	-160(%rbp), %rdx
	movq	%rcx, -136(%rbp)
	movq	%rdx, -144(%rbp)
	movq	-136(%rbp), %rcx
	movq	-144(%rbp), %rdx
	movq	%rcx, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	-120(%rbp), %rcx
	movq	%rcx, -104(%rbp)
	movq	-104(%rbp), %rcx
	movq	%rcx, -96(%rbp)
	movq	-96(%rbp), %rcx
	movq	%rcx, -72(%rbp)
	movq	$0, -80(%rbp)
	movq	-72(%rbp), %rcx
	movq	%rcx, -64(%rbp)
	movq	-64(%rbp), %rdx
	movq	%rdx, -56(%rbp)
	movq	-56(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, -88(%rbp)
	movq	-80(%rbp), %rdx
	movq	%rcx, -48(%rbp)
	movq	-48(%rbp), %rsi
	movq	%rsi, -40(%rbp)
	movq	-40(%rbp), %rsi
	movq	%rdx, (%rsi)
	cmpq	$0, -88(%rbp)
	movq	%rcx, -384(%rbp)        ## 8-byte Spill
	je	LBB15_7
## %bb.4:                               ##   in Loop: Header=BB15_2 Depth=1
	movq	-384(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rcx
	movq	%rcx, -24(%rbp)
	movq	-24(%rbp), %rcx
	movq	-88(%rbp), %rdx
	movq	%rcx, -8(%rbp)
	movq	%rdx, -16(%rbp)
	movq	-16(%rbp), %rcx
	cmpq	$0, %rcx
	movq	%rcx, -392(%rbp)        ## 8-byte Spill
	je	LBB15_6
## %bb.5:                               ##   in Loop: Header=BB15_2 Depth=1
	movq	-392(%rbp), %rdi        ## 8-byte Reload
	callq	__ZN18TransformComponentD1Ev
	movq	-392(%rbp), %rdi        ## 8-byte Reload
	callq	__ZdlPv
LBB15_6:                                ##   in Loop: Header=BB15_2 Depth=1
	jmp	LBB15_7
LBB15_7:                                ##   in Loop: Header=BB15_2 Depth=1
	jmp	LBB15_8
LBB15_8:                                ##   in Loop: Header=BB15_2 Depth=1
	jmp	LBB15_2
LBB15_9:
	movq	-224(%rbp), %rax
	movq	-376(%rbp), %rcx        ## 8-byte Reload
	movq	%rax, 8(%rcx)
	movq	-368(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -264(%rbp)
	movq	-264(%rbp), %rdx
	addq	$16, %rdx
	movq	%rdx, -256(%rbp)
	movq	-256(%rbp), %rdx
	movq	%rdx, -248(%rbp)
	movq	-248(%rbp), %rdx
	movq	(%rax), %rsi
	movq	%rax, -296(%rbp)
	movq	-296(%rbp), %rdi
	movq	%rdi, -288(%rbp)
	movq	-288(%rbp), %r8
	addq	$16, %r8
	movq	%r8, -280(%rbp)
	movq	-280(%rbp), %r8
	movq	%r8, -272(%rbp)
	movq	-272(%rbp), %r8
	movq	(%r8), %r8
	movq	(%rdi), %rdi
	subq	%rdi, %r8
	sarq	$3, %r8
	movq	%rdx, -336(%rbp)
	movq	%rsi, -344(%rbp)
	movq	%r8, -352(%rbp)
	movq	-336(%rbp), %rdx
	movq	-344(%rbp), %rsi
	movq	-352(%rbp), %rdi
	movq	%rdx, -312(%rbp)
	movq	%rsi, -320(%rbp)
	movq	%rdi, -328(%rbp)
	movq	-320(%rbp), %rdx
	movq	%rdx, -304(%rbp)
	movq	-304(%rbp), %rdi
	callq	__ZdlPv
LBB15_10:
	addq	$400, %rsp              ## imm = 0x190
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.private_extern	___clang_call_terminate ## -- Begin function __clang_call_terminate
	.globl	___clang_call_terminate
	.weak_definition	___clang_call_terminate
	.p2align	4, 0x90
___clang_call_terminate:                ## @__clang_call_terminate
## %bb.0:
	pushq	%rax
	callq	___cxa_begin_catch
	movq	%rax, (%rsp)            ## 8-byte Spill
	callq	__ZSt9terminatev
                                        ## -- End function
.zerofill __DATA,__bss,__ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform,48,3 ## @_ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform
.zerofill __DATA,__bss,__ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform,8,3 ## @_ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevTransform
.zerofill __DATA,__bss,__ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody,144,3 ## @_ZZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody
.zerofill __DATA,__bss,__ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody,8,3 ## @_ZGVZN13PhysicsSystem6UpdateERKxRK6EntityNSt3__111__wrap_iterIPNS5_10unique_ptrIS2_NS5_14default_deleteIS2_EEEEEEE13prevRigidbody

.subsections_via_symbols
