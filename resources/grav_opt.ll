; ModuleID = 'grav.ll'
source_filename = "grav.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@main.x = private unnamed_addr constant [10 x float] [float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00], align 16
@main.y = private unnamed_addr constant [10 x float] [float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00], align 16

; Function Attrs: noinline nounwind uwtable
define i32 @gravitational_force(float*, float*, float, float, float, float*) #0 {
  br label %7

; <label>:7:                                      ; preds = %30, %6
  %.0 = phi i32 [ 0, %6 ], [ %31, %30 ]
  %8 = icmp slt i32 %.0, 10
  br i1 %8, label %9, label %32

; <label>:9:                                      ; preds = %7
  %10 = fmul float %4, %2
  %11 = fmul float %10, %3
  %12 = sext i32 %.0 to i64
  %13 = getelementptr inbounds float, float* %0, i64 %12
  %14 = load float, float* %13, align 4
  %15 = sext i32 %.0 to i64
  %16 = getelementptr inbounds float, float* %1, i64 %15
  %17 = load float, float* %16, align 4
  %18 = fsub float %14, %17
  %19 = sext i32 %.0 to i64
  %20 = getelementptr inbounds float, float* %0, i64 %19
  %21 = load float, float* %20, align 4
  %22 = sext i32 %.0 to i64
  %23 = getelementptr inbounds float, float* %1, i64 %22
  %24 = load float, float* %23, align 4
  %25 = fsub float %21, %24
  %26 = fmul float %18, %25
  %27 = fdiv float %11, %26
  %28 = sext i32 %.0 to i64
  %29 = getelementptr inbounds float, float* %5, i64 %28
  store float %27, float* %29, align 4
  br label %30

; <label>:30:                                     ; preds = %9
  %31 = add nsw i32 %.0, 1
  br label %7

; <label>:32:                                     ; preds = %7
  ret i32 0
}

; Function Attrs: noinline nounwind uwtable
define i32 @main() #0 {
  %1 = alloca [10 x float], align 16
  %2 = alloca [10 x float], align 16
  %3 = alloca [10 x float], align 16
  %4 = bitcast [10 x float]* %1 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %4, i8* bitcast ([10 x float]* @main.x to i8*), i64 40, i32 16, i1 false)
  %5 = bitcast [10 x float]* %2 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* bitcast ([10 x float]* @main.y to i8*), i64 40, i32 16, i1 false)
  %6 = bitcast [10 x float]* %3 to i8*
  call void @llvm.memset.p0i8.i64(i8* %6, i8 0, i64 40, i32 16, i1 false)
  %7 = getelementptr inbounds [10 x float], [10 x float]* %1, i32 0, i32 0
  %8 = getelementptr inbounds [10 x float], [10 x float]* %2, i32 0, i32 0
  %9 = getelementptr inbounds [10 x float], [10 x float]* %3, i32 0, i32 0
  %10 = call i32 @gravitational_force(float* %7, float* %8, float 2.000000e+01, float 1.500000e+01, float 0x40239EB860000000, float* %9)
  ret i32 %10
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i32, i1) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (tags/RELEASE_400/final)"}
