; ModuleID = 'circle.c'
source_filename = "circle.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@main.x = private unnamed_addr constant [10 x float] [float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00, float 1.000000e+00], align 16
@main.y = private unnamed_addr constant [10 x float] [float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00, float 2.000000e+00], align 16

; Function Attrs: noinline nounwind uwtable
define i32 @circleError(float*, float*, float*) #0 {
  %4 = alloca float*, align 8
  %5 = alloca float*, align 8
  %6 = alloca float*, align 8
  %7 = alloca i32, align 4
  store float* %0, float** %4, align 8
  store float* %1, float** %5, align 8
  store float* %2, float** %6, align 8
  store i32 0, i32* %7, align 4
  br label %8

; <label>:8:                                      ; preds = %40, %3
  %9 = load i32, i32* %7, align 4
  %10 = icmp slt i32 %9, 10
  br i1 %10, label %11, label %43

; <label>:11:                                     ; preds = %8
  %12 = load float*, float** %4, align 8
  %13 = load i32, i32* %7, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds float, float* %12, i64 %14
  %16 = load float, float* %15, align 4
  %17 = load float*, float** %5, align 8
  %18 = load i32, i32* %7, align 4
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds float, float* %17, i64 %19
  %21 = load float, float* %20, align 4
  %22 = fsub float %16, %21
  %23 = load float*, float** %4, align 8
  %24 = load i32, i32* %7, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds float, float* %23, i64 %25
  %27 = load float, float* %26, align 4
  %28 = load float*, float** %5, align 8
  %29 = load i32, i32* %7, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds float, float* %28, i64 %30
  %32 = load float, float* %31, align 4
  %33 = fsub float %27, %32
  %34 = fmul float %22, %33
  %35 = fdiv float 2.000000e+02, %34
  %36 = load float*, float** %6, align 8
  %37 = load i32, i32* %7, align 4
  %38 = sext i32 %37 to i64
  %39 = getelementptr inbounds float, float* %36, i64 %38
  store float %35, float* %39, align 4
  br label %40

; <label>:40:                                     ; preds = %11
  %41 = load i32, i32* %7, align 4
  %42 = add nsw i32 %41, 1
  store i32 %42, i32* %7, align 4
  br label %8

; <label>:43:                                     ; preds = %8
  ret i32 0
}

; Function Attrs: noinline nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [10 x float], align 16
  %3 = alloca [10 x float], align 16
  %4 = alloca [10 x float], align 16
  store i32 0, i32* %1, align 4
  %5 = bitcast [10 x float]* %2 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* bitcast ([10 x float]* @main.x to i8*), i64 40, i32 16, i1 false)
  %6 = bitcast [10 x float]* %3 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %6, i8* bitcast ([10 x float]* @main.y to i8*), i64 40, i32 16, i1 false)
  %7 = bitcast [10 x float]* %4 to i8*
  call void @llvm.memset.p0i8.i64(i8* %7, i8 0, i64 40, i32 16, i1 false)
  %8 = getelementptr inbounds [10 x float], [10 x float]* %2, i32 0, i32 0
  %9 = getelementptr inbounds [10 x float], [10 x float]* %3, i32 0, i32 0
  %10 = getelementptr inbounds [10 x float], [10 x float]* %4, i32 0, i32 0
  %11 = call i32 @circleError(float* %8, float* %9, float* %10)
  ret i32 %11
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i32, i1) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (tags/RELEASE_400/final)"}