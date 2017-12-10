; ModuleID = 'test_functions.ll'
source_filename = "test_functions.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define float @exp(float) #0 {
  %2 = fmul float %0, %0
  %3 = fadd float %2, %0
  ret float %3
}

; Function Attrs: noinline nounwind uwtable
define float @log(float) #0 {
  %2 = fmul float %0, %0
  %3 = fadd float %2, %0
  ret float %3
}

; Function Attrs: noinline nounwind uwtable
define float @sqrt(float) #0 {
  %2 = fmul float %0, %0
  %3 = fadd float %2, %0
  ret float %3
}

; Function Attrs: noinline nounwind uwtable
define float @log2(float) #0 {
  %2 = fmul float %0, %0
  %3 = fadd float %2, %0
  ret float %3
}

; Function Attrs: noinline nounwind uwtable
define float @pow2(float) #0 {
  %2 = fmul float %0, %0
  %3 = fadd float %2, %0
  ret float %3
}

; Function Attrs: noinline nounwind uwtable
define float @ceil(float) #0 {
  %2 = fmul float %0, %0
  %3 = fadd float %2, %0
  ret float %3
}

; Function Attrs: noinline nounwind uwtable
define float @floor(float) #0 {
  %2 = fmul float %0, %0
  %3 = fadd float %2, %0
  ret float %3
}

; Function Attrs: noinline nounwind uwtable
define float @fabs(float) #0 {
  %2 = fmul float %0, %0
  %3 = fadd float %2, %0
  ret float %3
}

; Function Attrs: noinline nounwind readnone uwtable
define i32 @abs(i32) #1 {
  %2 = mul nsw i32 %0, %0
  %3 = add nsw i32 %2, %0
  ret i32 %3
}

; Function Attrs: noinline nounwind uwtable
define float @Ncdf(float) #0 {
  %2 = fmul float %0, %0
  %3 = fadd float %2, %0
  ret float %3
}

; Function Attrs: noinline nounwind uwtable
define void @test_1(i32*, i32*, i32*, i32*) #0 {
  %5 = alloca [100 x i32], align 16
  br label %6

.preheader3:                                      ; preds = %6
  %.01.ph = phi i32 [ 0, %6 ]
  br label %32

; <label>:6:                                      ; preds = %6, %4
  %.026 = phi i32 [ 0, %4 ], [ %30, %6 ]
  %7 = sext i32 %.026 to i64
  %8 = getelementptr inbounds i32, i32* %0, i64 %7
  %9 = load i32, i32* %8, align 4
  %10 = sext i32 %.026 to i64
  %11 = getelementptr inbounds i32, i32* %1, i64 %10
  %12 = load i32, i32* %11, align 4
  %13 = sub nsw i32 %9, %12
  %14 = sext i32 %.026 to i64
  %15 = getelementptr inbounds i32, i32* %2, i64 %14
  store i32 %13, i32* %15, align 4
  %16 = sext i32 %.026 to i64
  %17 = getelementptr inbounds i32, i32* %3, i64 %16
  store i32 15, i32* %17, align 4
  %18 = add nuw nsw i32 %.026, 1
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds i32, i32* %0, i64 %19
  %21 = load i32, i32* %20, align 4
  %22 = sext i32 %18 to i64
  %23 = getelementptr inbounds i32, i32* %1, i64 %22
  %24 = load i32, i32* %23, align 4
  %25 = sub nsw i32 %21, %24
  %26 = sext i32 %18 to i64
  %27 = getelementptr inbounds i32, i32* %2, i64 %26
  store i32 %25, i32* %27, align 4
  %28 = sext i32 %18 to i64
  %29 = getelementptr inbounds i32, i32* %3, i64 %28
  store i32 15, i32* %29, align 4
  %30 = add nuw nsw i32 %18, 1
  %31 = icmp slt i32 %30, 100
  br i1 %31, label %6, label %.preheader3

.preheader:                                       ; preds = %32
  %.0.ph = phi i32 [ 0, %32 ]
  br label %46

; <label>:32:                                     ; preds = %32, %.preheader3
  %.015 = phi i32 [ %.01.ph, %.preheader3 ], [ %44, %32 ]
  %33 = sext i32 %.015 to i64
  %34 = getelementptr inbounds i32, i32* %3, i64 %33
  %35 = load i32, i32* %34, align 4
  %36 = sext i32 %.015 to i64
  %37 = getelementptr inbounds [100 x i32], [100 x i32]* %5, i64 0, i64 %36
  store i32 %35, i32* %37, align 4
  %38 = add nuw nsw i32 %.015, 1
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds i32, i32* %3, i64 %39
  %41 = load i32, i32* %40, align 4
  %42 = sext i32 %38 to i64
  %43 = getelementptr inbounds [100 x i32], [100 x i32]* %5, i64 0, i64 %42
  store i32 %41, i32* %43, align 4
  %44 = add nuw nsw i32 %38, 1
  %45 = icmp slt i32 %44, 100
  br i1 %45, label %32, label %.preheader

; <label>:46:                                     ; preds = %46, %.preheader
  %.04 = phi i32 [ %.0.ph, %.preheader ], [ %74, %46 ]
  %47 = sext i32 %.04 to i64
  %48 = getelementptr inbounds [100 x i32], [100 x i32]* %5, i64 0, i64 %47
  %49 = load i32, i32* %48, align 4
  %50 = mul nsw i32 %49, 2
  %51 = sext i32 %.04 to i64
  %52 = getelementptr inbounds i32, i32* %2, i64 %51
  store i32 %50, i32* %52, align 4
  %53 = add nuw nsw i32 %.04, 1
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds [100 x i32], [100 x i32]* %5, i64 0, i64 %54
  %56 = load i32, i32* %55, align 4
  %57 = mul nsw i32 %56, 2
  %58 = sext i32 %53 to i64
  %59 = getelementptr inbounds i32, i32* %2, i64 %58
  store i32 %57, i32* %59, align 4
  %60 = add nuw nsw i32 %53, 1
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds [100 x i32], [100 x i32]* %5, i64 0, i64 %61
  %63 = load i32, i32* %62, align 4
  %64 = mul nsw i32 %63, 2
  %65 = sext i32 %60 to i64
  %66 = getelementptr inbounds i32, i32* %2, i64 %65
  store i32 %64, i32* %66, align 4
  %67 = add nuw nsw i32 %60, 1
  %68 = sext i32 %67 to i64
  %69 = getelementptr inbounds [100 x i32], [100 x i32]* %5, i64 0, i64 %68
  %70 = load i32, i32* %69, align 4
  %71 = mul nsw i32 %70, 2
  %72 = sext i32 %67 to i64
  %73 = getelementptr inbounds i32, i32* %2, i64 %72
  store i32 %71, i32* %73, align 4
  %74 = add nuw nsw i32 %67, 1
  %75 = icmp slt i32 %74, 100
  br i1 %75, label %46, label %76

; <label>:76:                                     ; preds = %46
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_2(i32*, i32*) #0 {
  br label %3

.preheader:                                       ; preds = %3
  %.0.ph = phi i32 [ 0, %3 ]
  br label %31

; <label>:3:                                      ; preds = %3, %2
  %.013 = phi i32 [ 0, %2 ], [ %29, %3 ]
  %4 = sext i32 %.013 to i64
  %5 = getelementptr inbounds i32, i32* %0, i64 %4
  %6 = load i32, i32* %5, align 4
  %7 = add nsw i32 %6, 10
  %8 = sext i32 %.013 to i64
  %9 = getelementptr inbounds i32, i32* %1, i64 %8
  store i32 %7, i32* %9, align 4
  %10 = sext i32 %.013 to i64
  %11 = getelementptr inbounds i32, i32* %0, i64 %10
  %12 = load i32, i32* %11, align 4
  %13 = mul nsw i32 2, %12
  %14 = sext i32 %.013 to i64
  %15 = getelementptr inbounds i32, i32* %1, i64 %14
  store i32 %13, i32* %15, align 4
  %16 = add nuw nsw i32 %.013, 1
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds i32, i32* %0, i64 %17
  %19 = load i32, i32* %18, align 4
  %20 = add nsw i32 %19, 10
  %21 = sext i32 %16 to i64
  %22 = getelementptr inbounds i32, i32* %1, i64 %21
  store i32 %20, i32* %22, align 4
  %23 = sext i32 %16 to i64
  %24 = getelementptr inbounds i32, i32* %0, i64 %23
  %25 = load i32, i32* %24, align 4
  %26 = mul nsw i32 2, %25
  %27 = sext i32 %16 to i64
  %28 = getelementptr inbounds i32, i32* %1, i64 %27
  store i32 %26, i32* %28, align 4
  %29 = add nuw nsw i32 %16, 1
  %30 = icmp slt i32 %29, 100
  br i1 %30, label %3, label %.preheader

; <label>:31:                                     ; preds = %31, %.preheader
  %.02 = phi i32 [ %.0.ph, %.preheader ], [ %59, %31 ]
  %32 = sext i32 %.02 to i64
  %33 = getelementptr inbounds i32, i32* %0, i64 %32
  %34 = load i32, i32* %33, align 4
  %35 = mul nsw i32 3, %34
  %36 = sext i32 %.02 to i64
  %37 = getelementptr inbounds i32, i32* %1, i64 %36
  store i32 %35, i32* %37, align 4
  %38 = add nuw nsw i32 %.02, 1
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds i32, i32* %0, i64 %39
  %41 = load i32, i32* %40, align 4
  %42 = mul nsw i32 3, %41
  %43 = sext i32 %38 to i64
  %44 = getelementptr inbounds i32, i32* %1, i64 %43
  store i32 %42, i32* %44, align 4
  %45 = add nuw nsw i32 %38, 1
  %46 = sext i32 %45 to i64
  %47 = getelementptr inbounds i32, i32* %0, i64 %46
  %48 = load i32, i32* %47, align 4
  %49 = mul nsw i32 3, %48
  %50 = sext i32 %45 to i64
  %51 = getelementptr inbounds i32, i32* %1, i64 %50
  store i32 %49, i32* %51, align 4
  %52 = add nuw nsw i32 %45, 1
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds i32, i32* %0, i64 %53
  %55 = load i32, i32* %54, align 4
  %56 = mul nsw i32 3, %55
  %57 = sext i32 %52 to i64
  %58 = getelementptr inbounds i32, i32* %1, i64 %57
  store i32 %56, i32* %58, align 4
  %59 = add nuw nsw i32 %52, 1
  %60 = icmp slt i32 %59, 100
  br i1 %60, label %31, label %61

; <label>:61:                                     ; preds = %31
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_3(i32*, i32*) #0 {
  br label %3

.preheader:                                       ; preds = %3
  %.0.ph = phi i32 [ 0, %3 ]
  br label %33

; <label>:3:                                      ; preds = %3, %2
  %.013 = phi i32 [ 0, %2 ], [ %31, %3 ]
  %4 = sext i32 %.013 to i64
  %5 = getelementptr inbounds i32, i32* %0, i64 %4
  %6 = load i32, i32* %5, align 4
  %7 = add nsw i32 %6, 5
  %8 = sext i32 %.013 to i64
  %9 = getelementptr inbounds i32, i32* %1, i64 %8
  store i32 %7, i32* %9, align 4
  %10 = add nuw nsw i32 %.013, 1
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds i32, i32* %0, i64 %11
  %13 = load i32, i32* %12, align 4
  %14 = add nsw i32 %13, 5
  %15 = sext i32 %10 to i64
  %16 = getelementptr inbounds i32, i32* %1, i64 %15
  store i32 %14, i32* %16, align 4
  %17 = add nuw nsw i32 %10, 1
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds i32, i32* %0, i64 %18
  %20 = load i32, i32* %19, align 4
  %21 = add nsw i32 %20, 5
  %22 = sext i32 %17 to i64
  %23 = getelementptr inbounds i32, i32* %1, i64 %22
  store i32 %21, i32* %23, align 4
  %24 = add nuw nsw i32 %17, 1
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i32, i32* %0, i64 %25
  %27 = load i32, i32* %26, align 4
  %28 = add nsw i32 %27, 5
  %29 = sext i32 %24 to i64
  %30 = getelementptr inbounds i32, i32* %1, i64 %29
  store i32 %28, i32* %30, align 4
  %31 = add nuw nsw i32 %24, 1
  %32 = icmp slt i32 %31, 100
  br i1 %32, label %3, label %.preheader

; <label>:33:                                     ; preds = %33, %.preheader
  %.02 = phi i32 [ %.0.ph, %.preheader ], [ %55, %33 ]
  %34 = sext i32 %.02 to i64
  %35 = getelementptr inbounds i32, i32* %1, i64 %34
  %36 = load i32, i32* %35, align 4
  %37 = sext i32 %.02 to i64
  %38 = getelementptr inbounds i32, i32* %0, i64 %37
  %39 = load i32, i32* %38, align 4
  %40 = mul nsw i32 %39, 2
  %41 = add nsw i32 %36, %40
  %42 = sext i32 %.02 to i64
  %43 = getelementptr inbounds i32, i32* %1, i64 %42
  store i32 %41, i32* %43, align 4
  %44 = add nuw nsw i32 %.02, 1
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds i32, i32* %1, i64 %45
  %47 = load i32, i32* %46, align 4
  %48 = sext i32 %44 to i64
  %49 = getelementptr inbounds i32, i32* %0, i64 %48
  %50 = load i32, i32* %49, align 4
  %51 = mul nsw i32 %50, 2
  %52 = add nsw i32 %47, %51
  %53 = sext i32 %44 to i64
  %54 = getelementptr inbounds i32, i32* %1, i64 %53
  store i32 %52, i32* %54, align 4
  %55 = add nuw nsw i32 %44, 1
  %56 = icmp slt i32 %55, 100
  br i1 %56, label %33, label %57

; <label>:57:                                     ; preds = %33
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_4(i32*, i32*) #0 {
  %3 = alloca [100 x i32], align 16
  %4 = alloca [100 x i32], align 16
  br label %5

.preheader:                                       ; preds = %5
  %.0.ph = phi i32 [ 0, %5 ]
  br label %35

; <label>:5:                                      ; preds = %5, %2
  %.013 = phi i32 [ 0, %2 ], [ %33, %5 ]
  %6 = sext i32 %.013 to i64
  %7 = getelementptr inbounds i32, i32* %0, i64 %6
  %8 = load i32, i32* %7, align 4
  %9 = add nsw i32 %8, 5
  %10 = sext i32 %.013 to i64
  %11 = getelementptr inbounds i32, i32* %1, i64 %10
  store i32 %9, i32* %11, align 4
  %12 = add nuw nsw i32 %.013, 1
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds i32, i32* %0, i64 %13
  %15 = load i32, i32* %14, align 4
  %16 = add nsw i32 %15, 5
  %17 = sext i32 %12 to i64
  %18 = getelementptr inbounds i32, i32* %1, i64 %17
  store i32 %16, i32* %18, align 4
  %19 = add nuw nsw i32 %12, 1
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds i32, i32* %0, i64 %20
  %22 = load i32, i32* %21, align 4
  %23 = add nsw i32 %22, 5
  %24 = sext i32 %19 to i64
  %25 = getelementptr inbounds i32, i32* %1, i64 %24
  store i32 %23, i32* %25, align 4
  %26 = add nuw nsw i32 %19, 1
  %27 = sext i32 %26 to i64
  %28 = getelementptr inbounds i32, i32* %0, i64 %27
  %29 = load i32, i32* %28, align 4
  %30 = add nsw i32 %29, 5
  %31 = sext i32 %26 to i64
  %32 = getelementptr inbounds i32, i32* %1, i64 %31
  store i32 %30, i32* %32, align 4
  %33 = add nuw nsw i32 %26, 1
  %34 = icmp slt i32 %33, 100
  br i1 %34, label %5, label %.preheader

; <label>:35:                                     ; preds = %.preheader, %35
  %.02 = phi i32 [ %.0.ph, %.preheader ], [ %52, %35 ]
  %36 = sext i32 %.02 to i64
  %37 = getelementptr inbounds i32, i32* %1, i64 %36
  %38 = load i32, i32* %37, align 4
  %39 = sext i32 %.02 to i64
  %40 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %39
  store i32 %38, i32* %40, align 4
  %41 = sext i32 %.02 to i64
  %42 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %41
  %43 = load i32, i32* %42, align 4
  %44 = sext i32 %.02 to i64
  %45 = getelementptr inbounds [100 x i32], [100 x i32]* %4, i64 0, i64 %44
  store i32 %43, i32* %45, align 4
  %46 = sext i32 %.02 to i64
  %47 = getelementptr inbounds [100 x i32], [100 x i32]* %4, i64 0, i64 %46
  %48 = load i32, i32* %47, align 4
  %49 = mul nsw i32 %48, 5
  %50 = sext i32 %.02 to i64
  %51 = getelementptr inbounds i32, i32* %1, i64 %50
  store i32 %49, i32* %51, align 4
  %52 = add nsw i32 %.02, 1
  %53 = icmp slt i32 %52, 100
  br i1 %53, label %35, label %54

; <label>:54:                                     ; preds = %35
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_5(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %3, %2
  %.01 = phi i32 [ 0, %2 ], [ %27, %3 ]
  %4 = sext i32 %.01 to i64
  %5 = getelementptr inbounds i32, i32* %0, i64 %4
  %6 = load i32, i32* %5, align 4
  %7 = add nsw i32 %6, 5
  %8 = add nuw nsw i32 %.01, 1
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds i32, i32* %1, i64 %9
  store i32 %7, i32* %10, align 4
  %11 = add nuw nsw i32 %.01, 1
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds i32, i32* %0, i64 %12
  %14 = load i32, i32* %13, align 4
  %15 = add nsw i32 %14, 5
  %16 = add nuw nsw i32 %11, 1
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds i32, i32* %1, i64 %17
  store i32 %15, i32* %18, align 4
  %19 = add nuw nsw i32 %11, 1
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds i32, i32* %0, i64 %20
  %22 = load i32, i32* %21, align 4
  %23 = add nsw i32 %22, 5
  %24 = add nuw nsw i32 %19, 1
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i32, i32* %1, i64 %25
  store i32 %23, i32* %26, align 4
  %27 = add nuw nsw i32 %19, 1
  %28 = icmp slt i32 %27, 99
  br i1 %28, label %3, label %29

; <label>:29:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_6(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %3, %2
  %.01 = phi i32 [ 0, %2 ], [ %29, %3 ]
  %4 = add nuw nsw i32 %.01, 1
  %5 = sext i32 %4 to i64
  %6 = getelementptr inbounds i32, i32* %0, i64 %5
  %7 = load i32, i32* %6, align 4
  %8 = add nuw nsw i32 %.01, 2
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds i32, i32* %0, i64 %9
  %11 = load i32, i32* %10, align 4
  %12 = add nsw i32 %7, %11
  %13 = add nuw nsw i32 %.01, 1
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds i32, i32* %1, i64 %14
  store i32 %12, i32* %15, align 4
  %16 = add nuw nsw i32 %.01, 1
  %17 = add nuw nsw i32 %16, 1
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds i32, i32* %0, i64 %18
  %20 = load i32, i32* %19, align 4
  %21 = add nuw nsw i32 %16, 2
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds i32, i32* %0, i64 %22
  %24 = load i32, i32* %23, align 4
  %25 = add nsw i32 %20, %24
  %26 = add nuw nsw i32 %16, 1
  %27 = sext i32 %26 to i64
  %28 = getelementptr inbounds i32, i32* %1, i64 %27
  store i32 %25, i32* %28, align 4
  %29 = add nuw nsw i32 %16, 1
  %30 = icmp slt i32 %29, 98
  br i1 %30, label %3, label %31

; <label>:31:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_7(i32*, i32*) #0 {
  %3 = alloca [100 x i32], align 16
  br label %4

.preheader:                                       ; preds = %4
  %.0.ph = phi i32 [ 0, %4 ]
  br label %30

; <label>:4:                                      ; preds = %4, %2
  %.013 = phi i32 [ 0, %2 ], [ %28, %4 ]
  %5 = sext i32 %.013 to i64
  %6 = getelementptr inbounds i32, i32* %0, i64 %5
  %7 = load i32, i32* %6, align 4
  %8 = add nsw i32 %7, 5
  %9 = add nuw nsw i32 %.013, 1
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %10
  store i32 %8, i32* %11, align 4
  %12 = add nuw nsw i32 %.013, 1
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds i32, i32* %0, i64 %13
  %15 = load i32, i32* %14, align 4
  %16 = add nsw i32 %15, 5
  %17 = add nuw nsw i32 %12, 1
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %18
  store i32 %16, i32* %19, align 4
  %20 = add nuw nsw i32 %12, 1
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds i32, i32* %0, i64 %21
  %23 = load i32, i32* %22, align 4
  %24 = add nsw i32 %23, 5
  %25 = add nuw nsw i32 %20, 1
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %26
  store i32 %24, i32* %27, align 4
  %28 = add nuw nsw i32 %20, 1
  %29 = icmp slt i32 %28, 99
  br i1 %29, label %4, label %.preheader

; <label>:30:                                     ; preds = %30, %.preheader
  %.02 = phi i32 [ %.0.ph, %.preheader ], [ %51, %30 ]
  %31 = sext i32 %.02 to i64
  %32 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %31
  %33 = load i32, i32* %32, align 4
  %34 = add nsw i32 %33, 3
  %35 = sext i32 %.02 to i64
  %36 = getelementptr inbounds i32, i32* %1, i64 %35
  store i32 %34, i32* %36, align 4
  %37 = add nuw nsw i32 %.02, 1
  %38 = sext i32 %37 to i64
  %39 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %38
  %40 = load i32, i32* %39, align 4
  %41 = add nsw i32 %40, 3
  %42 = sext i32 %37 to i64
  %43 = getelementptr inbounds i32, i32* %1, i64 %42
  store i32 %41, i32* %43, align 4
  %44 = add nuw nsw i32 %37, 1
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %45
  %47 = load i32, i32* %46, align 4
  %48 = add nsw i32 %47, 3
  %49 = sext i32 %44 to i64
  %50 = getelementptr inbounds i32, i32* %1, i64 %49
  store i32 %48, i32* %50, align 4
  %51 = add nuw nsw i32 %44, 1
  %52 = icmp slt i32 %51, 99
  br i1 %52, label %30, label %53

; <label>:53:                                     ; preds = %30
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_8(i32*, i32*) #0 {
  %3 = alloca [100 x i32], align 16
  br label %4

.preheader:                                       ; preds = %4
  %.0.ph = phi i32 [ 1, %4 ]
  br label %21

; <label>:4:                                      ; preds = %4, %2
  %.013 = phi i32 [ 1, %2 ], [ %19, %4 ]
  %5 = sub nuw nsw i32 %.013, 1
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds i32, i32* %0, i64 %6
  %8 = load i32, i32* %7, align 4
  %9 = add nsw i32 %8, 5
  %10 = sext i32 %.013 to i64
  %11 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %10
  store i32 %9, i32* %11, align 4
  %12 = add nuw nsw i32 %.013, 1
  %13 = sext i32 %.013 to i64
  %14 = getelementptr inbounds i32, i32* %0, i64 %13
  %15 = load i32, i32* %14, align 4
  %16 = add nsw i32 %15, 5
  %17 = sext i32 %12 to i64
  %18 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %17
  store i32 %16, i32* %18, align 4
  %19 = add nuw nsw i32 %12, 1
  %20 = icmp slt i32 %19, 99
  br i1 %20, label %4, label %.preheader

; <label>:21:                                     ; preds = %21, %.preheader
  %.02 = phi i32 [ %.0.ph, %.preheader ], [ %44, %21 ]
  %22 = add nuw nsw i32 %.02, 1
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %23
  %25 = load i32, i32* %24, align 4
  %26 = sub nuw nsw i32 %.02, 1
  %27 = sext i32 %26 to i64
  %28 = getelementptr inbounds i32, i32* %0, i64 %27
  %29 = load i32, i32* %28, align 4
  %30 = add nsw i32 %25, %29
  %31 = sext i32 %.02 to i64
  %32 = getelementptr inbounds i32, i32* %1, i64 %31
  store i32 %30, i32* %32, align 4
  %33 = add nuw nsw i32 %.02, 1
  %34 = add nuw nsw i32 %33, 1
  %35 = sext i32 %34 to i64
  %36 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %35
  %37 = load i32, i32* %36, align 4
  %38 = sext i32 %.02 to i64
  %39 = getelementptr inbounds i32, i32* %0, i64 %38
  %40 = load i32, i32* %39, align 4
  %41 = add nsw i32 %37, %40
  %42 = sext i32 %33 to i64
  %43 = getelementptr inbounds i32, i32* %1, i64 %42
  store i32 %41, i32* %43, align 4
  %44 = add nuw nsw i32 %33, 1
  %45 = icmp slt i32 %44, 99
  br i1 %45, label %21, label %46

; <label>:46:                                     ; preds = %21
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_9(i32*, i32*) #0 {
  br label %3

.preheader3:                                      ; preds = %3
  %.01.ph = phi i32 [ 1, %3 ]
  br label %33

; <label>:3:                                      ; preds = %3, %2
  %.026 = phi i32 [ 0, %2 ], [ %31, %3 ]
  %4 = sext i32 %.026 to i64
  %5 = getelementptr inbounds i32, i32* %0, i64 %4
  %6 = load i32, i32* %5, align 4
  %7 = add nsw i32 %6, 1
  %8 = sext i32 %.026 to i64
  %9 = getelementptr inbounds i32, i32* %1, i64 %8
  store i32 %7, i32* %9, align 4
  %10 = add nuw nsw i32 %.026, 1
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds i32, i32* %0, i64 %11
  %13 = load i32, i32* %12, align 4
  %14 = add nsw i32 %13, 1
  %15 = sext i32 %10 to i64
  %16 = getelementptr inbounds i32, i32* %1, i64 %15
  store i32 %14, i32* %16, align 4
  %17 = add nuw nsw i32 %10, 1
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds i32, i32* %0, i64 %18
  %20 = load i32, i32* %19, align 4
  %21 = add nsw i32 %20, 1
  %22 = sext i32 %17 to i64
  %23 = getelementptr inbounds i32, i32* %1, i64 %22
  store i32 %21, i32* %23, align 4
  %24 = add nuw nsw i32 %17, 1
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i32, i32* %0, i64 %25
  %27 = load i32, i32* %26, align 4
  %28 = add nsw i32 %27, 1
  %29 = sext i32 %24 to i64
  %30 = getelementptr inbounds i32, i32* %1, i64 %29
  store i32 %28, i32* %30, align 4
  %31 = add nuw nsw i32 %24, 1
  %32 = icmp slt i32 %31, 100
  br i1 %32, label %3, label %.preheader3

.preheader:                                       ; preds = %33
  %.0.ph = phi i32 [ 2, %33 ]
  br label %49

; <label>:33:                                     ; preds = %33, %.preheader3
  %.015 = phi i32 [ %.01.ph, %.preheader3 ], [ %47, %33 ]
  %34 = sext i32 %.015 to i64
  %35 = getelementptr inbounds i32, i32* %0, i64 %34
  %36 = load i32, i32* %35, align 4
  %37 = add nsw i32 %36, 10
  %38 = sext i32 %.015 to i64
  %39 = getelementptr inbounds i32, i32* %1, i64 %38
  store i32 %37, i32* %39, align 4
  %40 = add nuw nsw i32 %.015, 1
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds i32, i32* %0, i64 %41
  %43 = load i32, i32* %42, align 4
  %44 = add nsw i32 %43, 10
  %45 = sext i32 %40 to i64
  %46 = getelementptr inbounds i32, i32* %1, i64 %45
  store i32 %44, i32* %46, align 4
  %47 = add nuw nsw i32 %40, 1
  %48 = icmp slt i32 %47, 99
  br i1 %48, label %33, label %.preheader

; <label>:49:                                     ; preds = %49, %.preheader
  %.04 = phi i32 [ %.0.ph, %.preheader ], [ %77, %49 ]
  %50 = sext i32 %.04 to i64
  %51 = getelementptr inbounds i32, i32* %0, i64 %50
  %52 = load i32, i32* %51, align 4
  %53 = add nsw i32 %52, 100
  %54 = sext i32 %.04 to i64
  %55 = getelementptr inbounds i32, i32* %1, i64 %54
  store i32 %53, i32* %55, align 4
  %56 = add nuw nsw i32 %.04, 1
  %57 = sext i32 %56 to i64
  %58 = getelementptr inbounds i32, i32* %0, i64 %57
  %59 = load i32, i32* %58, align 4
  %60 = add nsw i32 %59, 100
  %61 = sext i32 %56 to i64
  %62 = getelementptr inbounds i32, i32* %1, i64 %61
  store i32 %60, i32* %62, align 4
  %63 = add nuw nsw i32 %56, 1
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds i32, i32* %0, i64 %64
  %66 = load i32, i32* %65, align 4
  %67 = add nsw i32 %66, 100
  %68 = sext i32 %63 to i64
  %69 = getelementptr inbounds i32, i32* %1, i64 %68
  store i32 %67, i32* %69, align 4
  %70 = add nuw nsw i32 %63, 1
  %71 = sext i32 %70 to i64
  %72 = getelementptr inbounds i32, i32* %0, i64 %71
  %73 = load i32, i32* %72, align 4
  %74 = add nsw i32 %73, 100
  %75 = sext i32 %70 to i64
  %76 = getelementptr inbounds i32, i32* %1, i64 %75
  store i32 %74, i32* %76, align 4
  %77 = add nuw nsw i32 %70, 1
  %78 = icmp slt i32 %77, 98
  br i1 %78, label %49, label %79

; <label>:79:                                     ; preds = %49
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_10(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %2, %3
  %.01 = phi i32 [ 0, %2 ], [ %23, %3 ]
  %4 = add nsw i32 %.01, 1
  %5 = sext i32 %4 to i64
  %6 = getelementptr inbounds i32, i32* %1, i64 %5
  %7 = load i32, i32* %6, align 4
  %8 = add nsw i32 %.01, 2
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds i32, i32* %1, i64 %9
  %11 = load i32, i32* %10, align 4
  %12 = add nsw i32 %7, %11
  %13 = sext i32 %.01 to i64
  %14 = getelementptr inbounds i32, i32* %1, i64 %13
  store i32 %12, i32* %14, align 4
  %15 = add nsw i32 %.01, 1
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds i32, i32* %1, i64 %16
  %18 = load i32, i32* %17, align 4
  %19 = add nsw i32 %18, 3
  %20 = add nsw i32 %.01, 1
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds i32, i32* %1, i64 %21
  store i32 %19, i32* %22, align 4
  %23 = add nsw i32 %.01, 1
  %24 = icmp slt i32 %23, 100
  br i1 %24, label %3, label %25

; <label>:25:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @mov_avg(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %2, %3
  %.01 = phi i32 [ 1, %2 ], [ %20, %3 ]
  %4 = sub nsw i32 %.01, 1
  %5 = sext i32 %4 to i64
  %6 = getelementptr inbounds i32, i32* %0, i64 %5
  %7 = load i32, i32* %6, align 4
  %8 = sext i32 %.01 to i64
  %9 = getelementptr inbounds i32, i32* %0, i64 %8
  %10 = load i32, i32* %9, align 4
  %11 = add nsw i32 %7, %10
  %12 = add nsw i32 %.01, 1
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds i32, i32* %0, i64 %13
  %15 = load i32, i32* %14, align 4
  %16 = add nsw i32 %11, %15
  %17 = sdiv i32 %16, 3
  %18 = sext i32 %.01 to i64
  %19 = getelementptr inbounds i32, i32* %1, i64 %18
  store i32 %17, i32* %19, align 4
  %20 = add nsw i32 %.01, 1
  %21 = icmp slt i32 %20, 99
  br i1 %21, label %3, label %22

; <label>:22:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @averageKernel(float*, float*) #0 {
  %3 = getelementptr inbounds float, float* %0, i64 0
  %4 = load float, float* %3, align 4
  %5 = getelementptr inbounds float, float* %0, i64 1
  %6 = load float, float* %5, align 4
  %7 = fadd float %4, %6
  %8 = fdiv float %7, 2.000000e+00
  %9 = getelementptr inbounds float, float* %1, i64 0
  store float %8, float* %9, align 4
  br label %10

; <label>:10:                                     ; preds = %2, %10
  %.01 = phi i32 [ 1, %2 ], [ %27, %10 ]
  %11 = sub nsw i32 %.01, 1
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds float, float* %0, i64 %12
  %14 = load float, float* %13, align 4
  %15 = sext i32 %.01 to i64
  %16 = getelementptr inbounds float, float* %0, i64 %15
  %17 = load float, float* %16, align 4
  %18 = fadd float %14, %17
  %19 = add nsw i32 %.01, 1
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds float, float* %0, i64 %20
  %22 = load float, float* %21, align 4
  %23 = fadd float %18, %22
  %24 = fdiv float %23, 3.000000e+00
  %25 = sext i32 %.01 to i64
  %26 = getelementptr inbounds float, float* %1, i64 %25
  store float %24, float* %26, align 4
  %27 = add nsw i32 %.01, 1
  %28 = icmp slt i32 %27, 99
  br i1 %28, label %10, label %29

; <label>:29:                                     ; preds = %10
  %30 = getelementptr inbounds float, float* %0, i64 98
  %31 = load float, float* %30, align 4
  %32 = getelementptr inbounds float, float* %0, i64 99
  %33 = load float, float* %32, align 4
  %34 = fadd float %31, %33
  %35 = fdiv float %34, 2.000000e+00
  %36 = getelementptr inbounds float, float* %1, i64 99
  store float %35, float* %36, align 4
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_cast(float*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %3, %2
  %.01 = phi i32 [ 0, %2 ], [ %19, %3 ]
  %4 = sext i32 %.01 to i64
  %5 = getelementptr inbounds float, float* %0, i64 %4
  %6 = load float, float* %5, align 4
  %7 = fptosi float %6 to i32
  %8 = add nsw i32 %7, 2
  %9 = sext i32 %.01 to i64
  %10 = getelementptr inbounds i32, i32* %1, i64 %9
  store i32 %8, i32* %10, align 4
  %11 = add nuw nsw i32 %.01, 1
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds float, float* %0, i64 %12
  %14 = load float, float* %13, align 4
  %15 = fptosi float %14 to i32
  %16 = add nsw i32 %15, 2
  %17 = sext i32 %11 to i64
  %18 = getelementptr inbounds i32, i32* %1, i64 %17
  store i32 %16, i32* %18, align 4
  %19 = add nuw nsw i32 %11, 1
  %20 = icmp slt i32 %19, 100
  br i1 %20, label %3, label %21

; <label>:21:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @func_test(float*, float*) #0 {
  br label %3

; <label>:3:                                      ; preds = %3, %2
  %.01 = phi i32 [ 0, %2 ], [ %83, %3 ]
  %4 = sext i32 %.01 to i64
  %5 = getelementptr inbounds float, float* %0, i64 %4
  %6 = load float, float* %5, align 4
  %7 = call float @exp(float %6)
  %8 = call float @log(float %7)
  %9 = sext i32 %.01 to i64
  %10 = getelementptr inbounds float, float* %1, i64 %9
  store float %8, float* %10, align 4
  %11 = add nuw nsw i32 %.01, 1
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds float, float* %0, i64 %12
  %14 = load float, float* %13, align 4
  %15 = call float @exp(float %14)
  %16 = call float @log(float %15)
  %17 = sext i32 %11 to i64
  %18 = getelementptr inbounds float, float* %1, i64 %17
  store float %16, float* %18, align 4
  %19 = add nuw nsw i32 %11, 1
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds float, float* %0, i64 %20
  %22 = load float, float* %21, align 4
  %23 = call float @exp(float %22)
  %24 = call float @log(float %23)
  %25 = sext i32 %19 to i64
  %26 = getelementptr inbounds float, float* %1, i64 %25
  store float %24, float* %26, align 4
  %27 = add nuw nsw i32 %19, 1
  %28 = sext i32 %27 to i64
  %29 = getelementptr inbounds float, float* %0, i64 %28
  %30 = load float, float* %29, align 4
  %31 = call float @exp(float %30)
  %32 = call float @log(float %31)
  %33 = sext i32 %27 to i64
  %34 = getelementptr inbounds float, float* %1, i64 %33
  store float %32, float* %34, align 4
  %35 = add nuw nsw i32 %27, 1
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds float, float* %0, i64 %36
  %38 = load float, float* %37, align 4
  %39 = call float @exp(float %38)
  %40 = call float @log(float %39)
  %41 = sext i32 %35 to i64
  %42 = getelementptr inbounds float, float* %1, i64 %41
  store float %40, float* %42, align 4
  %43 = add nuw nsw i32 %35, 1
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds float, float* %0, i64 %44
  %46 = load float, float* %45, align 4
  %47 = call float @exp(float %46)
  %48 = call float @log(float %47)
  %49 = sext i32 %43 to i64
  %50 = getelementptr inbounds float, float* %1, i64 %49
  store float %48, float* %50, align 4
  %51 = add nuw nsw i32 %43, 1
  %52 = sext i32 %51 to i64
  %53 = getelementptr inbounds float, float* %0, i64 %52
  %54 = load float, float* %53, align 4
  %55 = call float @exp(float %54)
  %56 = call float @log(float %55)
  %57 = sext i32 %51 to i64
  %58 = getelementptr inbounds float, float* %1, i64 %57
  store float %56, float* %58, align 4
  %59 = add nuw nsw i32 %51, 1
  %60 = sext i32 %59 to i64
  %61 = getelementptr inbounds float, float* %0, i64 %60
  %62 = load float, float* %61, align 4
  %63 = call float @exp(float %62)
  %64 = call float @log(float %63)
  %65 = sext i32 %59 to i64
  %66 = getelementptr inbounds float, float* %1, i64 %65
  store float %64, float* %66, align 4
  %67 = add nuw nsw i32 %59, 1
  %68 = sext i32 %67 to i64
  %69 = getelementptr inbounds float, float* %0, i64 %68
  %70 = load float, float* %69, align 4
  %71 = call float @exp(float %70)
  %72 = call float @log(float %71)
  %73 = sext i32 %67 to i64
  %74 = getelementptr inbounds float, float* %1, i64 %73
  store float %72, float* %74, align 4
  %75 = add nuw nsw i32 %67, 1
  %76 = sext i32 %75 to i64
  %77 = getelementptr inbounds float, float* %0, i64 %76
  %78 = load float, float* %77, align 4
  %79 = call float @exp(float %78)
  %80 = call float @log(float %79)
  %81 = sext i32 %75 to i64
  %82 = getelementptr inbounds float, float* %1, i64 %81
  store float %80, float* %82, align 4
  %83 = add nuw nsw i32 %75, 1
  %84 = icmp slt i32 %83, 100
  br i1 %84, label %3, label %85

; <label>:85:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @cond_test(i32, i32*, i32*) #0 {
  br label %4

; <label>:4:                                      ; preds = %4, %3
  %.01 = phi i32 [ 0, %3 ], [ %29, %4 ]
  %5 = icmp sgt i32 %0, 3
  %6 = select i1 %5, i32 5, i32 10
  %7 = sext i32 %.01 to i64
  %8 = getelementptr inbounds i32, i32* %2, i64 %7
  store i32 %6, i32* %8, align 4
  %9 = add nuw nsw i32 %.01, 1
  %10 = icmp sgt i32 %0, 3
  %11 = select i1 %10, i32 5, i32 10
  %12 = sext i32 %9 to i64
  %13 = getelementptr inbounds i32, i32* %2, i64 %12
  store i32 %11, i32* %13, align 4
  %14 = add nuw nsw i32 %9, 1
  %15 = icmp sgt i32 %0, 3
  %16 = select i1 %15, i32 5, i32 10
  %17 = sext i32 %14 to i64
  %18 = getelementptr inbounds i32, i32* %2, i64 %17
  store i32 %16, i32* %18, align 4
  %19 = add nuw nsw i32 %14, 1
  %20 = icmp sgt i32 %0, 3
  %21 = select i1 %20, i32 5, i32 10
  %22 = sext i32 %19 to i64
  %23 = getelementptr inbounds i32, i32* %2, i64 %22
  store i32 %21, i32* %23, align 4
  %24 = add nuw nsw i32 %19, 1
  %25 = icmp sgt i32 %0, 3
  %26 = select i1 %25, i32 5, i32 10
  %27 = sext i32 %24 to i64
  %28 = getelementptr inbounds i32, i32* %2, i64 %27
  store i32 %26, i32* %28, align 4
  %29 = add nuw nsw i32 %24, 1
  %30 = icmp slt i32 %29, 100
  br i1 %30, label %4, label %31

; <label>:31:                                     ; preds = %4
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @nested_test_1(i32*, i32*, i32*) #0 {
  br label %.preheader

.preheader:                                       ; preds = %3, %4
  %.013 = phi i32 [ 0, %3 ], [ %19, %4 ]
  br label %4

; <label>:4:                                      ; preds = %.preheader
  %5 = load i32, i32* %1, align 4
  %6 = add nsw i32 %5, 3
  %7 = sext i32 %.013 to i64
  %8 = getelementptr inbounds i32, i32* %0, i64 %7
  store i32 %6, i32* %8, align 4
  %9 = getelementptr inbounds i32, i32* %1, i64 1
  %10 = load i32, i32* %9, align 4
  %11 = add nsw i32 %10, 3
  %12 = sext i32 %.013 to i64
  %13 = getelementptr inbounds i32, i32* %0, i64 %12
  store i32 %11, i32* %13, align 4
  %14 = getelementptr inbounds i32, i32* %1, i64 2
  %15 = load i32, i32* %14, align 4
  %16 = add nsw i32 %15, 3
  %17 = sext i32 %.013 to i64
  %18 = getelementptr inbounds i32, i32* %0, i64 %17
  store i32 %16, i32* %18, align 4
  %19 = add nsw i32 %.013, 1
  %20 = icmp slt i32 %19, 100
  br i1 %20, label %.preheader, label %21

; <label>:21:                                     ; preds = %4
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @unroll_test(i32*, i32*, i32*) #0 {
  br label %4

; <label>:4:                                      ; preds = %4, %3
  %.01 = phi i32 [ 0, %3 ], [ %29, %4 ]
  %5 = sext i32 %.01 to i64
  %6 = getelementptr inbounds i32, i32* %1, i64 %5
  %7 = load i32, i32* %6, align 4
  %8 = add nsw i32 %7, 3
  store i32 %8, i32* %0, align 4
  %9 = add nuw nsw i32 %.01, 1
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds i32, i32* %1, i64 %10
  %12 = load i32, i32* %11, align 4
  %13 = add nsw i32 %12, 3
  store i32 %13, i32* %0, align 4
  %14 = add nuw nsw i32 %9, 1
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds i32, i32* %1, i64 %15
  %17 = load i32, i32* %16, align 4
  %18 = add nsw i32 %17, 3
  store i32 %18, i32* %0, align 4
  %19 = add nuw nsw i32 %14, 1
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds i32, i32* %1, i64 %20
  %22 = load i32, i32* %21, align 4
  %23 = add nsw i32 %22, 3
  store i32 %23, i32* %0, align 4
  %24 = add nuw nsw i32 %19, 1
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i32, i32* %1, i64 %25
  %27 = load i32, i32* %26, align 4
  %28 = add nsw i32 %27, 3
  store i32 %28, i32* %0, align 4
  %29 = add nuw nsw i32 %24, 1
  %30 = icmp slt i32 %29, 100
  br i1 %30, label %4, label %31

; <label>:31:                                     ; preds = %4
  ret void
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline nounwind readnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (tags/RELEASE_400/final)"}
