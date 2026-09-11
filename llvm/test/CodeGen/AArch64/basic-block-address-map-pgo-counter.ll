; RUN: llc < %s -mtriple=aarch64-unknown-linux-gnu -O0 -basic-block-address-map -filetype=obj | llvm-readobj --bb-addr-map - | FileCheck %s

; Verify that bb_addr_map encodes the counter index in the BB ID for blocks with !prof_counter,
; and UINT32_MAX (4294967295) for uninstrumented blocks.

define i32 @foo(i1 %c) {
entry:
  br i1 %c, label %bb1, label %bb2

bb1:
  ret i32 1, !prof_counter !0

bb2:
  ret i32 2, !prof_counter !1
}

!0 = !{i32 0}
!1 = !{i32 1}

; CHECK:      BBAddrMap [
; CHECK-NEXT:   Function {
; CHECK-NEXT:     At: 0x0
; CHECK-NEXT:     Name: foo
; CHECK:            BB Entries [
; CHECK-NEXT:         {
; CHECK-NEXT:           ID: 4294967295
; CHECK:              {
; CHECK-NEXT:           ID: 0
; CHECK:              {
; CHECK-NEXT:           ID: 1
