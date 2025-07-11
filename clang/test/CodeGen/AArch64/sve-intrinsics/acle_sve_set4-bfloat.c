// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// REQUIRES: aarch64-registered-target
// RUN: %clang_cc1 -fclang-abi-compat=latest -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s
// RUN: %clang_cc1 -fclang-abi-compat=latest -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - -x c++ %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s -check-prefix=CPP-CHECK
// RUN: %clang_cc1 -fclang-abi-compat=latest -DSVE_OVERLOADED_FORMS -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s
// RUN: %clang_cc1 -fclang-abi-compat=latest -DSVE_OVERLOADED_FORMS -triple aarch64 -target-feature +sve -disable-O0-optnone -Werror -Wall -emit-llvm -o - -x c++ %s | opt -S -passes=mem2reg,tailcallelim | FileCheck %s -check-prefix=CPP-CHECK
// RUN: %clang_cc1 -fclang-abi-compat=latest -triple aarch64 -target-feature +sve -target-feature +sme -S -disable-O0-optnone -Werror -Wall -o /dev/null %s
// RUN: %clang_cc1 -fclang-abi-compat=latest -triple aarch64 -target-feature +sme -S -disable-O0-optnone -Werror -Wall -o /dev/null %s

#include <arm_sve.h>

#ifdef SVE_OVERLOADED_FORMS
// A simple used,unused... macro, long enough to represent any SVE builtin.
#define SVE_ACLE_FUNC(A1,A2_UNUSED,A3,A4_UNUSED) A1##A3
#else
#define SVE_ACLE_FUNC(A1,A2,A3,A4) A1##A2##A3##A4
#endif

#ifdef __ARM_FEATURE_SME
#define ATTR __arm_streaming
#else
#define ATTR
#endif

// CHECK-LABEL: @test_svset4_bf16_0(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[TUPLE_COERCE0:%.*]], 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[TUPLE_COERCE1:%.*]], 1
// CHECK-NEXT:    [[TMP2:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], <vscale x 8 x bfloat> [[TUPLE_COERCE2:%.*]], 2
// CHECK-NEXT:    [[TMP3:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP2]], <vscale x 8 x bfloat> [[TUPLE_COERCE3:%.*]], 3
// CHECK-NEXT:    [[TMP4:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP3]], <vscale x 8 x bfloat> [[X:%.*]], 0
// CHECK-NEXT:    ret { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP4]]
//
// CPP-CHECK-LABEL: @_Z18test_svset4_bf16_014svbfloat16x4_tu14__SVBfloat16_t(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[TUPLE_COERCE0:%.*]], 0
// CPP-CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[TUPLE_COERCE1:%.*]], 1
// CPP-CHECK-NEXT:    [[TMP2:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], <vscale x 8 x bfloat> [[TUPLE_COERCE2:%.*]], 2
// CPP-CHECK-NEXT:    [[TMP3:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP2]], <vscale x 8 x bfloat> [[TUPLE_COERCE3:%.*]], 3
// CPP-CHECK-NEXT:    [[TMP4:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP3]], <vscale x 8 x bfloat> [[X:%.*]], 0
// CPP-CHECK-NEXT:    ret { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP4]]
//
svbfloat16x4_t test_svset4_bf16_0(svbfloat16x4_t tuple, svbfloat16_t x) ATTR
{
  return SVE_ACLE_FUNC(svset4,_bf16,,)(tuple, 0, x);
}

// CHECK-LABEL: @test_svset4_bf16_1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[TUPLE_COERCE0:%.*]], 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[TUPLE_COERCE1:%.*]], 1
// CHECK-NEXT:    [[TMP2:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], <vscale x 8 x bfloat> [[TUPLE_COERCE2:%.*]], 2
// CHECK-NEXT:    [[TMP3:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP2]], <vscale x 8 x bfloat> [[TUPLE_COERCE3:%.*]], 3
// CHECK-NEXT:    [[TMP4:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP3]], <vscale x 8 x bfloat> [[X:%.*]], 1
// CHECK-NEXT:    ret { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP4]]
//
// CPP-CHECK-LABEL: @_Z18test_svset4_bf16_114svbfloat16x4_tu14__SVBfloat16_t(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[TUPLE_COERCE0:%.*]], 0
// CPP-CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[TUPLE_COERCE1:%.*]], 1
// CPP-CHECK-NEXT:    [[TMP2:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], <vscale x 8 x bfloat> [[TUPLE_COERCE2:%.*]], 2
// CPP-CHECK-NEXT:    [[TMP3:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP2]], <vscale x 8 x bfloat> [[TUPLE_COERCE3:%.*]], 3
// CPP-CHECK-NEXT:    [[TMP4:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP3]], <vscale x 8 x bfloat> [[X:%.*]], 1
// CPP-CHECK-NEXT:    ret { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP4]]
//
svbfloat16x4_t test_svset4_bf16_1(svbfloat16x4_t tuple, svbfloat16_t x) ATTR
{
  return SVE_ACLE_FUNC(svset4,_bf16,,)(tuple, 1, x);
}

// CHECK-LABEL: @test_svset4_bf16_2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[TUPLE_COERCE0:%.*]], 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[TUPLE_COERCE1:%.*]], 1
// CHECK-NEXT:    [[TMP2:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], <vscale x 8 x bfloat> [[TUPLE_COERCE2:%.*]], 2
// CHECK-NEXT:    [[TMP3:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP2]], <vscale x 8 x bfloat> [[TUPLE_COERCE3:%.*]], 3
// CHECK-NEXT:    [[TMP4:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP3]], <vscale x 8 x bfloat> [[X:%.*]], 2
// CHECK-NEXT:    ret { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP4]]
//
// CPP-CHECK-LABEL: @_Z18test_svset4_bf16_214svbfloat16x4_tu14__SVBfloat16_t(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[TUPLE_COERCE0:%.*]], 0
// CPP-CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[TUPLE_COERCE1:%.*]], 1
// CPP-CHECK-NEXT:    [[TMP2:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], <vscale x 8 x bfloat> [[TUPLE_COERCE2:%.*]], 2
// CPP-CHECK-NEXT:    [[TMP3:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP2]], <vscale x 8 x bfloat> [[TUPLE_COERCE3:%.*]], 3
// CPP-CHECK-NEXT:    [[TMP4:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP3]], <vscale x 8 x bfloat> [[X:%.*]], 2
// CPP-CHECK-NEXT:    ret { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP4]]
//
svbfloat16x4_t test_svset4_bf16_2(svbfloat16x4_t tuple, svbfloat16_t x) ATTR
{
  return SVE_ACLE_FUNC(svset4,_bf16,,)(tuple, 2, x);
}

// CHECK-LABEL: @test_svset4_bf16_3(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[TUPLE_COERCE0:%.*]], 0
// CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[TUPLE_COERCE1:%.*]], 1
// CHECK-NEXT:    [[TMP2:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], <vscale x 8 x bfloat> [[TUPLE_COERCE2:%.*]], 2
// CHECK-NEXT:    [[TMP3:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP2]], <vscale x 8 x bfloat> [[TUPLE_COERCE3:%.*]], 3
// CHECK-NEXT:    [[TMP4:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP3]], <vscale x 8 x bfloat> [[X:%.*]], 3
// CHECK-NEXT:    ret { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP4]]
//
// CPP-CHECK-LABEL: @_Z18test_svset4_bf16_314svbfloat16x4_tu14__SVBfloat16_t(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } poison, <vscale x 8 x bfloat> [[TUPLE_COERCE0:%.*]], 0
// CPP-CHECK-NEXT:    [[TMP1:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP0]], <vscale x 8 x bfloat> [[TUPLE_COERCE1:%.*]], 1
// CPP-CHECK-NEXT:    [[TMP2:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP1]], <vscale x 8 x bfloat> [[TUPLE_COERCE2:%.*]], 2
// CPP-CHECK-NEXT:    [[TMP3:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP2]], <vscale x 8 x bfloat> [[TUPLE_COERCE3:%.*]], 3
// CPP-CHECK-NEXT:    [[TMP4:%.*]] = insertvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP3]], <vscale x 8 x bfloat> [[X:%.*]], 3
// CPP-CHECK-NEXT:    ret { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[TMP4]]
//
svbfloat16x4_t test_svset4_bf16_3(svbfloat16x4_t tuple, svbfloat16_t x) ATTR
{
  return SVE_ACLE_FUNC(svset4,_bf16,,)(tuple, 3, x);
}
