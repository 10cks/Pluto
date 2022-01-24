// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// REQUIRES: aarch64-registered-target
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve -target-feature +bf16 -msve-vector-bits=128 -fallow-half-arguments-and-returns -S -O1 -emit-llvm -o - %s | FileCheck %s --check-prefix=CHECK-128
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve -target-feature +bf16 -msve-vector-bits=256 -fallow-half-arguments-and-returns -S -O1 -emit-llvm -o - %s | FileCheck %s --check-prefix=CHECK-256
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve -target-feature +bf16 -msve-vector-bits=512 -fallow-half-arguments-and-returns -S -O1 -emit-llvm -o - %s | FileCheck %s --check-prefix=CHECK-512

#include <arm_sve.h>

#define N __ARM_FEATURE_SVE_BITS

typedef svint64_t fixed_int64_t __attribute__((arm_sve_vector_bits(N)));
typedef svfloat64_t fixed_float64_t __attribute__((arm_sve_vector_bits(N)));
typedef svbfloat16_t fixed_bfloat16_t __attribute__((arm_sve_vector_bits(N)));
typedef svbool_t fixed_bool_t __attribute__((arm_sve_vector_bits(N)));

#define DEFINE_STRUCT(ty)   \
  struct struct_##ty {      \
    fixed_##ty##_t x, y[3]; \
  } struct_##ty;

DEFINE_STRUCT(int64)
DEFINE_STRUCT(float64)
DEFINE_STRUCT(bfloat16)
DEFINE_STRUCT(bool)

//===----------------------------------------------------------------------===//
// int64
//===----------------------------------------------------------------------===//

// CHECK-128-LABEL: @read_int64(
// CHECK-128-NEXT:  entry:
// CHECK-128-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_INT64:%.*]], %struct.struct_int64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-128-NEXT:    [[TMP0:%.*]] = load <2 x i64>, <2 x i64>* [[ARRAYIDX]], align 16, [[TBAA6:!tbaa !.*]]
// CHECK-128-NEXT:    [[CASTSCALABLESVE:%.*]] = call <vscale x 2 x i64> @llvm.experimental.vector.insert.nxv2i64.v2i64(<vscale x 2 x i64> undef, <2 x i64> [[TMP0]], i64 0)
// CHECK-128-NEXT:    ret <vscale x 2 x i64> [[CASTSCALABLESVE]]
//
// CHECK-256-LABEL: @read_int64(
// CHECK-256-NEXT:  entry:
// CHECK-256-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_INT64:%.*]], %struct.struct_int64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-256-NEXT:    [[TMP0:%.*]] = load <4 x i64>, <4 x i64>* [[ARRAYIDX]], align 16, [[TBAA6:!tbaa !.*]]
// CHECK-256-NEXT:    [[CASTSCALABLESVE:%.*]] = call <vscale x 2 x i64> @llvm.experimental.vector.insert.nxv2i64.v4i64(<vscale x 2 x i64> undef, <4 x i64> [[TMP0]], i64 0)
// CHECK-256-NEXT:    ret <vscale x 2 x i64> [[CASTSCALABLESVE]]
//
// CHECK-512-LABEL: @read_int64(
// CHECK-512-NEXT:  entry:
// CHECK-512-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_INT64:%.*]], %struct.struct_int64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-512-NEXT:    [[TMP0:%.*]] = load <8 x i64>, <8 x i64>* [[ARRAYIDX]], align 16, [[TBAA6:!tbaa !.*]]
// CHECK-512-NEXT:    [[CASTSCALABLESVE:%.*]] = call <vscale x 2 x i64> @llvm.experimental.vector.insert.nxv2i64.v8i64(<vscale x 2 x i64> undef, <8 x i64> [[TMP0]], i64 0)
// CHECK-512-NEXT:    ret <vscale x 2 x i64> [[CASTSCALABLESVE]]
//
svint64_t read_int64(struct struct_int64 *s) {
  return s->y[0];
}

// CHECK-128-LABEL: @write_int64(
// CHECK-128-NEXT:  entry:
// CHECK-128-NEXT:    [[CASTFIXEDSVE:%.*]] = call <2 x i64> @llvm.experimental.vector.extract.v2i64.nxv2i64(<vscale x 2 x i64> [[X:%.*]], i64 0)
// CHECK-128-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_INT64:%.*]], %struct.struct_int64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-128-NEXT:    store <2 x i64> [[CASTFIXEDSVE]], <2 x i64>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-128-NEXT:    ret void
//
// CHECK-256-LABEL: @write_int64(
// CHECK-256-NEXT:  entry:
// CHECK-256-NEXT:    [[CASTFIXEDSVE:%.*]] = call <4 x i64> @llvm.experimental.vector.extract.v4i64.nxv2i64(<vscale x 2 x i64> [[X:%.*]], i64 0)
// CHECK-256-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_INT64:%.*]], %struct.struct_int64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-256-NEXT:    store <4 x i64> [[CASTFIXEDSVE]], <4 x i64>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-256-NEXT:    ret void
//
// CHECK-512-LABEL: @write_int64(
// CHECK-512-NEXT:  entry:
// CHECK-512-NEXT:    [[CASTFIXEDSVE:%.*]] = call <8 x i64> @llvm.experimental.vector.extract.v8i64.nxv2i64(<vscale x 2 x i64> [[X:%.*]], i64 0)
// CHECK-512-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_INT64:%.*]], %struct.struct_int64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-512-NEXT:    store <8 x i64> [[CASTFIXEDSVE]], <8 x i64>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-512-NEXT:    ret void
//
void write_int64(struct struct_int64 *s, svint64_t x) {
  s->y[0] = x;
}

//===----------------------------------------------------------------------===//
// float64
//===----------------------------------------------------------------------===//

// CHECK-128-LABEL: @read_float64(
// CHECK-128-NEXT:  entry:
// CHECK-128-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_FLOAT64:%.*]], %struct.struct_float64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-128-NEXT:    [[TMP0:%.*]] = load <2 x double>, <2 x double>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-128-NEXT:    [[CASTSCALABLESVE:%.*]] = call <vscale x 2 x double> @llvm.experimental.vector.insert.nxv2f64.v2f64(<vscale x 2 x double> undef, <2 x double> [[TMP0]], i64 0)
// CHECK-128-NEXT:    ret <vscale x 2 x double> [[CASTSCALABLESVE]]
//
// CHECK-256-LABEL: @read_float64(
// CHECK-256-NEXT:  entry:
// CHECK-256-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_FLOAT64:%.*]], %struct.struct_float64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-256-NEXT:    [[TMP0:%.*]] = load <4 x double>, <4 x double>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-256-NEXT:    [[CASTSCALABLESVE:%.*]] = call <vscale x 2 x double> @llvm.experimental.vector.insert.nxv2f64.v4f64(<vscale x 2 x double> undef, <4 x double> [[TMP0]], i64 0)
// CHECK-256-NEXT:    ret <vscale x 2 x double> [[CASTSCALABLESVE]]
//
// CHECK-512-LABEL: @read_float64(
// CHECK-512-NEXT:  entry:
// CHECK-512-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_FLOAT64:%.*]], %struct.struct_float64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-512-NEXT:    [[TMP0:%.*]] = load <8 x double>, <8 x double>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-512-NEXT:    [[CASTSCALABLESVE:%.*]] = call <vscale x 2 x double> @llvm.experimental.vector.insert.nxv2f64.v8f64(<vscale x 2 x double> undef, <8 x double> [[TMP0]], i64 0)
// CHECK-512-NEXT:    ret <vscale x 2 x double> [[CASTSCALABLESVE]]
//
svfloat64_t read_float64(struct struct_float64 *s) {
  return s->y[0];
}

// CHECK-128-LABEL: @write_float64(
// CHECK-128-NEXT:  entry:
// CHECK-128-NEXT:    [[CASTFIXEDSVE:%.*]] = call <2 x double> @llvm.experimental.vector.extract.v2f64.nxv2f64(<vscale x 2 x double> [[X:%.*]], i64 0)
// CHECK-128-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_FLOAT64:%.*]], %struct.struct_float64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-128-NEXT:    store <2 x double> [[CASTFIXEDSVE]], <2 x double>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-128-NEXT:    ret void
//
// CHECK-256-LABEL: @write_float64(
// CHECK-256-NEXT:  entry:
// CHECK-256-NEXT:    [[CASTFIXEDSVE:%.*]] = call <4 x double> @llvm.experimental.vector.extract.v4f64.nxv2f64(<vscale x 2 x double> [[X:%.*]], i64 0)
// CHECK-256-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_FLOAT64:%.*]], %struct.struct_float64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-256-NEXT:    store <4 x double> [[CASTFIXEDSVE]], <4 x double>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-256-NEXT:    ret void
//
// CHECK-512-LABEL: @write_float64(
// CHECK-512-NEXT:  entry:
// CHECK-512-NEXT:    [[CASTFIXEDSVE:%.*]] = call <8 x double> @llvm.experimental.vector.extract.v8f64.nxv2f64(<vscale x 2 x double> [[X:%.*]], i64 0)
// CHECK-512-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_FLOAT64:%.*]], %struct.struct_float64* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-512-NEXT:    store <8 x double> [[CASTFIXEDSVE]], <8 x double>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-512-NEXT:    ret void
//
void write_float64(struct struct_float64 *s, svfloat64_t x) {
  s->y[0] = x;
}

//===----------------------------------------------------------------------===//
// bfloat16
//===----------------------------------------------------------------------===//

// CHECK-128-LABEL: @read_bfloat16(
// CHECK-128-NEXT:  entry:
// CHECK-128-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BFLOAT16:%.*]], %struct.struct_bfloat16* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-128-NEXT:    [[TMP0:%.*]] = load <8 x bfloat>, <8 x bfloat>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-128-NEXT:    [[CASTSCALABLESVE:%.*]] = call <vscale x 8 x bfloat> @llvm.experimental.vector.insert.nxv8bf16.v8bf16(<vscale x 8 x bfloat> undef, <8 x bfloat> [[TMP0]], i64 0)
// CHECK-128-NEXT:    ret <vscale x 8 x bfloat> [[CASTSCALABLESVE]]
//
// CHECK-256-LABEL: @read_bfloat16(
// CHECK-256-NEXT:  entry:
// CHECK-256-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BFLOAT16:%.*]], %struct.struct_bfloat16* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-256-NEXT:    [[TMP0:%.*]] = load <16 x bfloat>, <16 x bfloat>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-256-NEXT:    [[CASTSCALABLESVE:%.*]] = call <vscale x 8 x bfloat> @llvm.experimental.vector.insert.nxv8bf16.v16bf16(<vscale x 8 x bfloat> undef, <16 x bfloat> [[TMP0]], i64 0)
// CHECK-256-NEXT:    ret <vscale x 8 x bfloat> [[CASTSCALABLESVE]]
//
// CHECK-512-LABEL: @read_bfloat16(
// CHECK-512-NEXT:  entry:
// CHECK-512-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BFLOAT16:%.*]], %struct.struct_bfloat16* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-512-NEXT:    [[TMP0:%.*]] = load <32 x bfloat>, <32 x bfloat>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-512-NEXT:    [[CASTSCALABLESVE:%.*]] = call <vscale x 8 x bfloat> @llvm.experimental.vector.insert.nxv8bf16.v32bf16(<vscale x 8 x bfloat> undef, <32 x bfloat> [[TMP0]], i64 0)
// CHECK-512-NEXT:    ret <vscale x 8 x bfloat> [[CASTSCALABLESVE]]
//
svbfloat16_t read_bfloat16(struct struct_bfloat16 *s) {
  return s->y[0];
}

// CHECK-128-LABEL: @write_bfloat16(
// CHECK-128-NEXT:  entry:
// CHECK-128-NEXT:    [[CASTFIXEDSVE:%.*]] = call <8 x bfloat> @llvm.experimental.vector.extract.v8bf16.nxv8bf16(<vscale x 8 x bfloat> [[X:%.*]], i64 0)
// CHECK-128-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BFLOAT16:%.*]], %struct.struct_bfloat16* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-128-NEXT:    store <8 x bfloat> [[CASTFIXEDSVE]], <8 x bfloat>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-128-NEXT:    ret void
//
// CHECK-256-LABEL: @write_bfloat16(
// CHECK-256-NEXT:  entry:
// CHECK-256-NEXT:    [[CASTFIXEDSVE:%.*]] = call <16 x bfloat> @llvm.experimental.vector.extract.v16bf16.nxv8bf16(<vscale x 8 x bfloat> [[X:%.*]], i64 0)
// CHECK-256-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BFLOAT16:%.*]], %struct.struct_bfloat16* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-256-NEXT:    store <16 x bfloat> [[CASTFIXEDSVE]], <16 x bfloat>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-256-NEXT:    ret void
//
// CHECK-512-LABEL: @write_bfloat16(
// CHECK-512-NEXT:  entry:
// CHECK-512-NEXT:    [[CASTFIXEDSVE:%.*]] = call <32 x bfloat> @llvm.experimental.vector.extract.v32bf16.nxv8bf16(<vscale x 8 x bfloat> [[X:%.*]], i64 0)
// CHECK-512-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BFLOAT16:%.*]], %struct.struct_bfloat16* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-512-NEXT:    store <32 x bfloat> [[CASTFIXEDSVE]], <32 x bfloat>* [[ARRAYIDX]], align 16, [[TBAA6]]
// CHECK-512-NEXT:    ret void
//
void write_bfloat16(struct struct_bfloat16 *s, svbfloat16_t x) {
  s->y[0] = x;
}

//===----------------------------------------------------------------------===//
// bool
//===----------------------------------------------------------------------===//

// CHECK-128-LABEL: @read_bool(
// CHECK-128-NEXT:  entry:
// CHECK-128-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BOOL:%.*]], %struct.struct_bool* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-128-NEXT:    [[TMP0:%.*]] = bitcast <2 x i8>* [[ARRAYIDX]] to <vscale x 16 x i1>*
// CHECK-128-NEXT:    [[TMP1:%.*]] = load <vscale x 16 x i1>, <vscale x 16 x i1>* [[TMP0]], align 2, [[TBAA6]]
// CHECK-128-NEXT:    ret <vscale x 16 x i1> [[TMP1]]
//
// CHECK-256-LABEL: @read_bool(
// CHECK-256-NEXT:  entry:
// CHECK-256-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BOOL:%.*]], %struct.struct_bool* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-256-NEXT:    [[TMP0:%.*]] = bitcast <4 x i8>* [[ARRAYIDX]] to <vscale x 16 x i1>*
// CHECK-256-NEXT:    [[TMP1:%.*]] = load <vscale x 16 x i1>, <vscale x 16 x i1>* [[TMP0]], align 2, [[TBAA6]]
// CHECK-256-NEXT:    ret <vscale x 16 x i1> [[TMP1]]
//
// CHECK-512-LABEL: @read_bool(
// CHECK-512-NEXT:  entry:
// CHECK-512-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BOOL:%.*]], %struct.struct_bool* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-512-NEXT:    [[TMP0:%.*]] = bitcast <8 x i8>* [[ARRAYIDX]] to <vscale x 16 x i1>*
// CHECK-512-NEXT:    [[TMP1:%.*]] = load <vscale x 16 x i1>, <vscale x 16 x i1>* [[TMP0]], align 2, [[TBAA6]]
// CHECK-512-NEXT:    ret <vscale x 16 x i1> [[TMP1]]
//
svbool_t read_bool(struct struct_bool *s) {
  return s->y[0];
}

// CHECK-128-LABEL: @write_bool(
// CHECK-128-NEXT:  entry:
// CHECK-128-NEXT:    [[X_ADDR:%.*]] = alloca <vscale x 16 x i1>, align 16
// CHECK-128-NEXT:    store <vscale x 16 x i1> [[X:%.*]], <vscale x 16 x i1>* [[X_ADDR]], align 16, [[TBAA9:!tbaa !.*]]
// CHECK-128-NEXT:    [[TMP0:%.*]] = bitcast <vscale x 16 x i1>* [[X_ADDR]] to <2 x i8>*
// CHECK-128-NEXT:    [[TMP1:%.*]] = load <2 x i8>, <2 x i8>* [[TMP0]], align 16, [[TBAA6]]
// CHECK-128-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BOOL:%.*]], %struct.struct_bool* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-128-NEXT:    store <2 x i8> [[TMP1]], <2 x i8>* [[ARRAYIDX]], align 2, [[TBAA6]]
// CHECK-128-NEXT:    ret void
//
// CHECK-256-LABEL: @write_bool(
// CHECK-256-NEXT:  entry:
// CHECK-256-NEXT:    [[X_ADDR:%.*]] = alloca <vscale x 16 x i1>, align 16
// CHECK-256-NEXT:    store <vscale x 16 x i1> [[X:%.*]], <vscale x 16 x i1>* [[X_ADDR]], align 16, [[TBAA9:!tbaa !.*]]
// CHECK-256-NEXT:    [[TMP0:%.*]] = bitcast <vscale x 16 x i1>* [[X_ADDR]] to <4 x i8>*
// CHECK-256-NEXT:    [[TMP1:%.*]] = load <4 x i8>, <4 x i8>* [[TMP0]], align 16, [[TBAA6]]
// CHECK-256-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BOOL:%.*]], %struct.struct_bool* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-256-NEXT:    store <4 x i8> [[TMP1]], <4 x i8>* [[ARRAYIDX]], align 2, [[TBAA6]]
// CHECK-256-NEXT:    ret void
//
// CHECK-512-LABEL: @write_bool(
// CHECK-512-NEXT:  entry:
// CHECK-512-NEXT:    [[X_ADDR:%.*]] = alloca <vscale x 16 x i1>, align 16
// CHECK-512-NEXT:    store <vscale x 16 x i1> [[X:%.*]], <vscale x 16 x i1>* [[X_ADDR]], align 16, [[TBAA9:!tbaa !.*]]
// CHECK-512-NEXT:    [[TMP0:%.*]] = bitcast <vscale x 16 x i1>* [[X_ADDR]] to <8 x i8>*
// CHECK-512-NEXT:    [[TMP1:%.*]] = load <8 x i8>, <8 x i8>* [[TMP0]], align 16, [[TBAA6]]
// CHECK-512-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [[STRUCT_STRUCT_BOOL:%.*]], %struct.struct_bool* [[S:%.*]], i64 0, i32 1, i64 0
// CHECK-512-NEXT:    store <8 x i8> [[TMP1]], <8 x i8>* [[ARRAYIDX]], align 2, [[TBAA6]]
// CHECK-512-NEXT:    ret void
//
void write_bool(struct struct_bool *s, svbool_t x) {
  s->y[0] = x;
}
