; RUN: opt < %s -passes=instrprof -profile-correlate=binary-all -S | FileCheck %s --check-prefixes=CHECK,OFFLOAD
; RUN: opt < %s -passes=instrprof -profile-correlate=binary-all | llc -filetype=obj | llvm-readelf -S - | FileCheck %s --check-prefix=SECTIONS

target triple = "aarch64-unknown-linux-gnu"

@__profn_foo = private constant [3 x i8] c"foo"
; CHECK: @__profc_foo = private global [1 x i8] c"\FF", section "__llvm_covcnts", comdat, align 1
; CHECK: @__profd_foo = private global { i64, i64, i64, i64, i64, ptr, ptr, i32, [3 x i16], i16, i32 } { i64 {{.*}}, i64 {{.*}}, i64 ptrtoint (ptr @__profc_foo to i64), {{.*}} }, section "__llvm_covdata", comdat($__profc_foo), align 8
@__profn_bar = private constant [3 x i8] c"bar"
; CHECK: @__profc_bar = private global [1 x i8] c"\FF", section "__llvm_covcnts", comdat, align 1
; CHECK: @__profd_bar = private global { i64, i64, i64, i64, i64, ptr, ptr, i32, [3 x i16], i16, i32 } { i64 {{.*}}, i64 {{.*}}, i64 ptrtoint (ptr @__profc_bar to i64), {{.*}} }, section "__llvm_covdata", comdat($__profc_bar), align 8

; CHECK: @__llvm_prf_nm = {{.*}} section "__llvm_covnames"
; CHECK-DAG: @__profc_sites__Z3foov = private constant [1 x { ptr, i32, i32, i64 }] [{ ptr, i32, i32, i64 } { ptr @_Z3foov, i32 0, i32 0, i64 12345678 }], section "__llvm_covsites", comdat($__profc_foo), align 8
; CHECK-DAG: @__profc_sites__Z3barv = private constant [1 x { ptr, i32, i32, i64 }] [{ ptr, i32, i32, i64 } { ptr @_Z3barv, i32 0, i32 0, i64 87654321 }], section "__llvm_covsites", comdat($__profc_bar), align 8

define void @_Z3foov() {
  call void @llvm.instrprof.cover(ptr @__profn_foo, i64 12345678, i32 1, i32 0)
  ; OFFLOAD-NOT: store
  ; OFFLOAD: ret void
  ret void
}

%class.A = type { ptr }
define dso_local void @_Z3barv(ptr nocapture nonnull align 8 %0) unnamed_addr #0 align 2 {
  call void @llvm.instrprof.cover(ptr @__profn_bar, i64 87654321, i32 1, i32 0)
  ; OFFLOAD-NOT: store
  ; OFFLOAD: ret void
  ret void
}

declare void @llvm.instrprof.cover(ptr, i64, i32, i32)

; Verify that the generated ELF sections are non-allocated (no 'A' flag).
; SECTIONS:      Name           Type     Address  Off    Size   ES Flg
; SECTIONS:      __llvm_covcnts PROGBITS {{[0-9a-f]+}} {{[0-9a-f]+}} {{[0-9a-f]+}} 00   G
; SECTIONS:      __llvm_covdata PROGBITS {{[0-9a-f]+}} {{[0-9a-f]+}} {{[0-9a-f]+}} 00   G
; SECTIONS:      __llvm_covnames PROGBITS {{[0-9a-f]+}} {{[0-9a-f]+}} {{[0-9a-f]+}} 00   R
; SECTIONS:      __llvm_covsites PROGBITS {{[0-9a-f]+}} {{[0-9a-f]+}} {{[0-9a-f]+}} 00   G
