// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -O3 -triple powerpc64le-unknown-unknown -target-cpu pwr10 \
// RUN: -emit-llvm %s -o - | FileCheck %s --check-prefix=CHECK-LE
// RUN: %clang_cc1 -O3 -triple powerpc64-unknown-unknown -target-cpu pwr10 \
// RUN: -emit-llvm %s -o - | FileCheck %s --check-prefix=CHECK-BE
// RUN: %clang_cc1 -O0 -triple powerpc64le-unknown-unknown -target-cpu pwr10 \
// RUN: -emit-llvm %s -o - | FileCheck %s --check-prefix=CHECK-LE-NOOPT

// CHECK-LE-LABEL: @test1(
// CHECK-LE-NEXT:  entry:
// CHECK-LE-NEXT:    [[TMP0:%.*]] = tail call <512 x i1> @llvm.ppc.mma.assemble.acc(<16 x i8> [[VC4:%.*]], <16 x i8> [[VC3:%.*]], <16 x i8> [[VC2:%.*]], <16 x i8> [[VC1:%.*]])
// CHECK-LE-NEXT:    store <512 x i1> [[TMP0]], ptr [[RESP:%.*]], align 64, !tbaa [[TBAA2:![0-9]+]]
// CHECK-LE-NEXT:    ret void
//
// CHECK-BE-LABEL: @test1(
// CHECK-BE-NEXT:  entry:
// CHECK-BE-NEXT:    [[TMP0:%.*]] = tail call <512 x i1> @llvm.ppc.mma.assemble.acc(<16 x i8> [[VC1:%.*]], <16 x i8> [[VC2:%.*]], <16 x i8> [[VC3:%.*]], <16 x i8> [[VC4:%.*]])
// CHECK-BE-NEXT:    store <512 x i1> [[TMP0]], ptr [[RESP:%.*]], align 64, !tbaa [[TBAA2:![0-9]+]]
// CHECK-BE-NEXT:    ret void
//
// CHECK-LE-NOOPT-LABEL: @test1(
// CHECK-LE-NOOPT-NEXT:  entry:
// CHECK-LE-NOOPT-NEXT:    [[VQP_ADDR:%.*]] = alloca ptr, align 8
// CHECK-LE-NOOPT-NEXT:    [[VPP_ADDR:%.*]] = alloca ptr, align 8
// CHECK-LE-NOOPT-NEXT:    [[VC1_ADDR:%.*]] = alloca <16 x i8>, align 16
// CHECK-LE-NOOPT-NEXT:    [[VC2_ADDR:%.*]] = alloca <16 x i8>, align 16
// CHECK-LE-NOOPT-NEXT:    [[VC3_ADDR:%.*]] = alloca <16 x i8>, align 16
// CHECK-LE-NOOPT-NEXT:    [[VC4_ADDR:%.*]] = alloca <16 x i8>, align 16
// CHECK-LE-NOOPT-NEXT:    [[RESP_ADDR:%.*]] = alloca ptr, align 8
// CHECK-LE-NOOPT-NEXT:    [[VQ:%.*]] = alloca <512 x i1>, align 64
// CHECK-LE-NOOPT-NEXT:    [[VP:%.*]] = alloca <256 x i1>, align 32
// CHECK-LE-NOOPT-NEXT:    [[RES:%.*]] = alloca <512 x i1>, align 64
// CHECK-LE-NOOPT-NEXT:    store ptr [[VQP:%.*]], ptr [[VQP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    store ptr [[VPP:%.*]], ptr [[VPP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    store <16 x i8> [[VC1:%.*]], ptr [[VC1_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    store <16 x i8> [[VC2:%.*]], ptr [[VC2_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    store <16 x i8> [[VC3:%.*]], ptr [[VC3_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    store <16 x i8> [[VC4:%.*]], ptr [[VC4_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    store ptr [[RESP:%.*]], ptr [[RESP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[VQP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    [[TMP1:%.*]] = load <512 x i1>, ptr [[TMP0]], align 64
// CHECK-LE-NOOPT-NEXT:    store <512 x i1> [[TMP1]], ptr [[VQ]], align 64
// CHECK-LE-NOOPT-NEXT:    [[TMP2:%.*]] = load ptr, ptr [[VPP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    [[TMP3:%.*]] = load <256 x i1>, ptr [[TMP2]], align 32
// CHECK-LE-NOOPT-NEXT:    store <256 x i1> [[TMP3]], ptr [[VP]], align 32
// CHECK-LE-NOOPT-NEXT:    [[TMP4:%.*]] = load <16 x i8>, ptr [[VC1_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    [[TMP5:%.*]] = load <16 x i8>, ptr [[VC2_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    [[TMP6:%.*]] = load <16 x i8>, ptr [[VC3_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    [[TMP7:%.*]] = load <16 x i8>, ptr [[VC4_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    [[TMP8:%.*]] = call <512 x i1> @llvm.ppc.mma.assemble.acc(<16 x i8> [[TMP7]], <16 x i8> [[TMP6]], <16 x i8> [[TMP5]], <16 x i8> [[TMP4]])
// CHECK-LE-NOOPT-NEXT:    store <512 x i1> [[TMP8]], ptr [[RES]], align 64
// CHECK-LE-NOOPT-NEXT:    [[TMP9:%.*]] = load <512 x i1>, ptr [[RES]], align 64
// CHECK-LE-NOOPT-NEXT:    [[TMP10:%.*]] = load ptr, ptr [[RESP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    store <512 x i1> [[TMP9]], ptr [[TMP10]], align 64
// CHECK-LE-NOOPT-NEXT:    ret void
//
void test1(unsigned char *vqp, unsigned char *vpp, vector unsigned char vc1, vector unsigned char vc2,
            vector unsigned char vc3, vector unsigned char vc4, unsigned char *resp) {
  __vector_quad vq = *((__vector_quad *)vqp);
  __vector_pair vp = *((__vector_pair *)vpp);
  __vector_quad res;
  __builtin_mma_build_acc(&res, vc1, vc2, vc3, vc4);
  *((__vector_quad *)resp) = res;
}

// CHECK-LE-LABEL: @test2(
// CHECK-LE-NEXT:  entry:
// CHECK-LE-NEXT:    [[TMP0:%.*]] = tail call <256 x i1> @llvm.ppc.vsx.assemble.pair(<16 x i8> [[VC2:%.*]], <16 x i8> [[VC1:%.*]])
// CHECK-LE-NEXT:    store <256 x i1> [[TMP0]], ptr [[RESP:%.*]], align 32, !tbaa [[TBAA6:![0-9]+]]
// CHECK-LE-NEXT:    ret void
//
// CHECK-BE-LABEL: @test2(
// CHECK-BE-NEXT:  entry:
// CHECK-BE-NEXT:    [[TMP0:%.*]] = tail call <256 x i1> @llvm.ppc.vsx.assemble.pair(<16 x i8> [[VC1:%.*]], <16 x i8> [[VC2:%.*]])
// CHECK-BE-NEXT:    store <256 x i1> [[TMP0]], ptr [[RESP:%.*]], align 32, !tbaa [[TBAA6:![0-9]+]]
// CHECK-BE-NEXT:    ret void
//
// CHECK-LE-NOOPT-LABEL: @test2(
// CHECK-LE-NOOPT-NEXT:  entry:
// CHECK-LE-NOOPT-NEXT:    [[VQP_ADDR:%.*]] = alloca ptr, align 8
// CHECK-LE-NOOPT-NEXT:    [[VPP_ADDR:%.*]] = alloca ptr, align 8
// CHECK-LE-NOOPT-NEXT:    [[VC1_ADDR:%.*]] = alloca <16 x i8>, align 16
// CHECK-LE-NOOPT-NEXT:    [[VC2_ADDR:%.*]] = alloca <16 x i8>, align 16
// CHECK-LE-NOOPT-NEXT:    [[RESP_ADDR:%.*]] = alloca ptr, align 8
// CHECK-LE-NOOPT-NEXT:    [[VQ:%.*]] = alloca <512 x i1>, align 64
// CHECK-LE-NOOPT-NEXT:    [[VP:%.*]] = alloca <256 x i1>, align 32
// CHECK-LE-NOOPT-NEXT:    [[RES:%.*]] = alloca <256 x i1>, align 32
// CHECK-LE-NOOPT-NEXT:    store ptr [[VQP:%.*]], ptr [[VQP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    store ptr [[VPP:%.*]], ptr [[VPP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    store <16 x i8> [[VC1:%.*]], ptr [[VC1_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    store <16 x i8> [[VC2:%.*]], ptr [[VC2_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    store ptr [[RESP:%.*]], ptr [[RESP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[VQP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    [[TMP1:%.*]] = load <512 x i1>, ptr [[TMP0]], align 64
// CHECK-LE-NOOPT-NEXT:    store <512 x i1> [[TMP1]], ptr [[VQ]], align 64
// CHECK-LE-NOOPT-NEXT:    [[TMP2:%.*]] = load ptr, ptr [[VPP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    [[TMP3:%.*]] = load <256 x i1>, ptr [[TMP2]], align 32
// CHECK-LE-NOOPT-NEXT:    store <256 x i1> [[TMP3]], ptr [[VP]], align 32
// CHECK-LE-NOOPT-NEXT:    [[TMP4:%.*]] = load <16 x i8>, ptr [[VC1_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    [[TMP5:%.*]] = load <16 x i8>, ptr [[VC2_ADDR]], align 16
// CHECK-LE-NOOPT-NEXT:    [[TMP6:%.*]] = call <256 x i1> @llvm.ppc.vsx.assemble.pair(<16 x i8> [[TMP5]], <16 x i8> [[TMP4]])
// CHECK-LE-NOOPT-NEXT:    store <256 x i1> [[TMP6]], ptr [[RES]], align 32
// CHECK-LE-NOOPT-NEXT:    [[TMP7:%.*]] = load <256 x i1>, ptr [[RES]], align 32
// CHECK-LE-NOOPT-NEXT:    [[TMP8:%.*]] = load ptr, ptr [[RESP_ADDR]], align 8
// CHECK-LE-NOOPT-NEXT:    store <256 x i1> [[TMP7]], ptr [[TMP8]], align 32
// CHECK-LE-NOOPT-NEXT:    ret void
//
void test2(unsigned char *vqp, unsigned char *vpp, vector unsigned char vc1,
            vector unsigned char vc2, unsigned char *resp) {
  __vector_quad vq = *((__vector_quad *)vqp);
  __vector_pair vp = *((__vector_pair *)vpp);
  __vector_pair res;
  __builtin_vsx_build_pair(&res, vc1, vc2);
  *((__vector_pair *)resp) = res;
}
