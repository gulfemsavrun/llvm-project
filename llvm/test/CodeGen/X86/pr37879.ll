; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -O3 < %s -mtriple=x86_64-apple-darwin -mattr=+avx512bw | FileCheck %s

define double @foo(ptr nocapture readonly) #0 {
; CHECK-LABEL: foo:
; CHECK:       ## %bb.0:
; CHECK-NEXT:    movq (%rax), %rax
; CHECK-NEXT:    vcvtsi2sd %rax, %xmm15, %xmm1
; CHECK-NEXT:    kmovd %eax, %k1
; CHECK-NEXT:    vmovsd {{.*#+}} xmm0 = [1.0E+0,0.0E+0]
; CHECK-NEXT:    vmovsd %xmm1, %xmm0, %xmm0 {%k1}
; CHECK-NEXT:    retq
  %2 = load i64, ptr undef, align 8
  %3 = and i64 %2, 1
  %4 = icmp eq i64 %3, 0
  %5 = sitofp i64 %2 to double
  %6 = select i1 %4, double 1.000000e+00, double %5
  ret double %6
}
