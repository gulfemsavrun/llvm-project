// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// REQUIRES: aarch64-registered-target
// RUN: %clang_cc1 -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s
// RUN: %clang_cc1 -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - -x c++ %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s -check-prefix=CPP-CHECK
// RUN: %clang_cc1 -DSVE_OVERLOADED_FORMS -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s
// RUN: %clang_cc1 -DSVE_OVERLOADED_FORMS -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - -x c++ %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s -check-prefix=CPP-CHECK
// RUN: %clang_cc1 -fclang-abi-compat=latest -triple aarch64 -target-feature +sve -S -disable-O0-optnone -Werror -Wall -o /dev/null %s
// RUN: %clang_cc1 -fclang-abi-compat=latest -triple aarch64 -target-feature +sme -S -disable-O0-optnone -Werror -Wall -o /dev/null %s

#include <arm_sve.h>

#if defined __ARM_FEATURE_SME
#define MODE_ATTR __arm_streaming
#else
#define MODE_ATTR
#endif


#ifdef SVE_OVERLOADED_FORMS
// A simple used,unused... macro, long enough to represent any SVE builtin.
#define SVE_ACLE_FUNC(A1,A2_UNUSED,A3,A4_UNUSED) A1##A3
#else
#define SVE_ACLE_FUNC(A1,A2,A3,A4) A1##A2##A3##A4
#endif
// CHECK-LABEL: @test_svst2_bf16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[DATA_COERCE0:%.*]], 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[DATA_COERCE1:%.*]], 1
// CHECK-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], 0
// CHECK-NEXT:    [[TMP3:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], 1
// CHECK-NEXT:    [[TMP4:%.*]] = tail call <vscale x 8 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv8i1(<vscale x 16 x i1> [[PG:%.*]])
// CHECK-NEXT:    tail call void @llvm.aarch64.sve.st2.nxv8bf16(<vscale x 8 x bfloat> [[TMP2]], <vscale x 8 x bfloat> [[TMP3]], <vscale x 8 x i1> [[TMP4]], ptr [[BASE:%.*]])
// CHECK-NEXT:    ret void
//
// CPP-CHECK-LABEL: @_Z15test_svst2_bf16u10__SVBool_tPu6__bf1614svbfloat16x2_t(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[DATA_COERCE0:%.*]], 0
// CPP-CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[DATA_COERCE1:%.*]], 1
// CPP-CHECK-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], 0
// CPP-CHECK-NEXT:    [[TMP3:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], 1
// CPP-CHECK-NEXT:    [[TMP4:%.*]] = tail call <vscale x 8 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv8i1(<vscale x 16 x i1> [[PG:%.*]])
// CPP-CHECK-NEXT:    tail call void @llvm.aarch64.sve.st2.nxv8bf16(<vscale x 8 x bfloat> [[TMP2]], <vscale x 8 x bfloat> [[TMP3]], <vscale x 8 x i1> [[TMP4]], ptr [[BASE:%.*]])
// CPP-CHECK-NEXT:    ret void
//
void test_svst2_bf16(svbool_t pg, bfloat16_t *base, svbfloat16x2_t data) MODE_ATTR
{
  return SVE_ACLE_FUNC(svst2,_bf16,,)(pg, base, data);
}

// CHECK-LABEL: @test_svst2_vnum_bf16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[DATA_COERCE0:%.*]], 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[DATA_COERCE1:%.*]], 1
// CHECK-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], 0
// CHECK-NEXT:    [[TMP3:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], 1
// CHECK-NEXT:    [[TMP4:%.*]] = tail call <vscale x 8 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv8i1(<vscale x 16 x i1> [[PG:%.*]])
// CHECK-NEXT:    [[TMP5:%.*]] = getelementptr <vscale x 8 x bfloat>, ptr [[BASE:%.*]], i64 [[VNUM:%.*]]
// CHECK-NEXT:    tail call void @llvm.aarch64.sve.st2.nxv8bf16(<vscale x 8 x bfloat> [[TMP2]], <vscale x 8 x bfloat> [[TMP3]], <vscale x 8 x i1> [[TMP4]], ptr [[TMP5]])
// CHECK-NEXT:    ret void
//
// CPP-CHECK-LABEL: @_Z20test_svst2_vnum_bf16u10__SVBool_tPu6__bf16l14svbfloat16x2_t(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[DATA_COERCE0:%.*]], 0
// CPP-CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[DATA_COERCE1:%.*]], 1
// CPP-CHECK-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], 0
// CPP-CHECK-NEXT:    [[TMP3:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], 1
// CPP-CHECK-NEXT:    [[TMP4:%.*]] = tail call <vscale x 8 x i1> @llvm.aarch64.sve.convert.from.svbool.nxv8i1(<vscale x 16 x i1> [[PG:%.*]])
// CPP-CHECK-NEXT:    [[TMP5:%.*]] = getelementptr <vscale x 8 x bfloat>, ptr [[BASE:%.*]], i64 [[VNUM:%.*]]
// CPP-CHECK-NEXT:    tail call void @llvm.aarch64.sve.st2.nxv8bf16(<vscale x 8 x bfloat> [[TMP2]], <vscale x 8 x bfloat> [[TMP3]], <vscale x 8 x i1> [[TMP4]], ptr [[TMP5]])
// CPP-CHECK-NEXT:    ret void
//
void test_svst2_vnum_bf16(svbool_t pg, bfloat16_t *base, int64_t vnum, svbfloat16x2_t data) MODE_ATTR
{
  return SVE_ACLE_FUNC(svst2_vnum,_bf16,,)(pg, base, vnum, data);
}
