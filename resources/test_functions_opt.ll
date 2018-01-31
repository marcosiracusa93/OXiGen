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

; <label>:6:                                      ; preds = %20, %4
  %.02 = phi i32 [ 0, %4 ], [ %21, %20 ]
  %7 = icmp slt i32 %.02, 100
  br i1 %7, label %8, label %22

; <label>:8:                                      ; preds = %6
  %9 = sext i32 %.02 to i64
  %10 = getelementptr inbounds i32, i32* %0, i64 %9
  %11 = load i32, i32* %10, align 4
  %12 = sext i32 %.02 to i64
  %13 = getelementptr inbounds i32, i32* %1, i64 %12
  %14 = load i32, i32* %13, align 4
  %15 = sub nsw i32 %11, %14
  %16 = sext i32 %.02 to i64
  %17 = getelementptr inbounds i32, i32* %2, i64 %16
  store i32 %15, i32* %17, align 4
  %18 = sext i32 %.02 to i64
  %19 = getelementptr inbounds i32, i32* %3, i64 %18
  store i32 15, i32* %19, align 4
  br label %20

; <label>:20:                                     ; preds = %8
  %21 = add nsw i32 %.02, 1
  br label %6

; <label>:22:                                     ; preds = %6
  br label %23

; <label>:23:                                     ; preds = %33, %22
  %.01 = phi i32 [ 0, %22 ], [ %34, %33 ]
  %24 = icmp slt i32 %.01, 100
  br i1 %24, label %25, label %35

; <label>:25:                                     ; preds = %23
  %26 = sext i32 %.01 to i64
  %27 = getelementptr inbounds i32, i32* %3, i64 %26
  %28 = load i32, i32* %27, align 4
  %29 = sdiv i32 10, 15
  %30 = add nsw i32 %28, %29
  %31 = sext i32 %.01 to i64
  %32 = getelementptr inbounds [100 x i32], [100 x i32]* %5, i64 0, i64 %31
  store i32 %30, i32* %32, align 4
  br label %33

; <label>:33:                                     ; preds = %25
  %34 = add nsw i32 %.01, 1
  br label %23

; <label>:35:                                     ; preds = %23
  br label %36

; <label>:36:                                     ; preds = %45, %35
  %.0 = phi i32 [ 0, %35 ], [ %46, %45 ]
  %37 = icmp slt i32 %.0, 100
  br i1 %37, label %38, label %47

; <label>:38:                                     ; preds = %36
  %39 = sext i32 %.0 to i64
  %40 = getelementptr inbounds [100 x i32], [100 x i32]* %5, i64 0, i64 %39
  %41 = load i32, i32* %40, align 4
  %42 = mul nsw i32 %41, 2
  %43 = sext i32 %.0 to i64
  %44 = getelementptr inbounds i32, i32* %2, i64 %43
  store i32 %42, i32* %44, align 4
  br label %45

; <label>:45:                                     ; preds = %38
  %46 = add nsw i32 %.0, 1
  br label %36

; <label>:47:                                     ; preds = %36
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_2(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %18, %2
  %.01 = phi i32 [ 0, %2 ], [ %19, %18 ]
  %4 = icmp slt i32 %.01, 100
  br i1 %4, label %5, label %20

; <label>:5:                                      ; preds = %3
  %6 = sext i32 %.01 to i64
  %7 = getelementptr inbounds i32, i32* %0, i64 %6
  %8 = load i32, i32* %7, align 4
  %9 = add nsw i32 %8, 10
  %10 = sext i32 %.01 to i64
  %11 = getelementptr inbounds i32, i32* %1, i64 %10
  store i32 %9, i32* %11, align 4
  %12 = sext i32 %.01 to i64
  %13 = getelementptr inbounds i32, i32* %0, i64 %12
  %14 = load i32, i32* %13, align 4
  %15 = mul nsw i32 2, %14
  %16 = sext i32 %.01 to i64
  %17 = getelementptr inbounds i32, i32* %1, i64 %16
  store i32 %15, i32* %17, align 4
  br label %18

; <label>:18:                                     ; preds = %5
  %19 = add nsw i32 %.01, 1
  br label %3

; <label>:20:                                     ; preds = %3
  br label %21

; <label>:21:                                     ; preds = %30, %20
  %.0 = phi i32 [ 0, %20 ], [ %31, %30 ]
  %22 = icmp slt i32 %.0, 100
  br i1 %22, label %23, label %32

; <label>:23:                                     ; preds = %21
  %24 = sext i32 %.0 to i64
  %25 = getelementptr inbounds i32, i32* %0, i64 %24
  %26 = load i32, i32* %25, align 4
  %27 = mul nsw i32 3, %26
  %28 = sext i32 %.0 to i64
  %29 = getelementptr inbounds i32, i32* %1, i64 %28
  store i32 %27, i32* %29, align 4
  br label %30

; <label>:30:                                     ; preds = %23
  %31 = add nsw i32 %.0, 1
  br label %21

; <label>:32:                                     ; preds = %21
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_3(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %12, %2
  %.01 = phi i32 [ 0, %2 ], [ %13, %12 ]
  %4 = icmp slt i32 %.01, 100
  br i1 %4, label %5, label %14

; <label>:5:                                      ; preds = %3
  %6 = sext i32 %.01 to i64
  %7 = getelementptr inbounds i32, i32* %0, i64 %6
  %8 = load i32, i32* %7, align 4
  %9 = add nsw i32 %8, 5
  %10 = sext i32 %.01 to i64
  %11 = getelementptr inbounds i32, i32* %1, i64 %10
  store i32 %9, i32* %11, align 4
  br label %12

; <label>:12:                                     ; preds = %5
  %13 = add nsw i32 %.01, 1
  br label %3

; <label>:14:                                     ; preds = %3
  br label %15

; <label>:15:                                     ; preds = %28, %14
  %.0 = phi i32 [ 0, %14 ], [ %29, %28 ]
  %16 = icmp slt i32 %.0, 100
  br i1 %16, label %17, label %30

; <label>:17:                                     ; preds = %15
  %18 = sext i32 %.0 to i64
  %19 = getelementptr inbounds i32, i32* %1, i64 %18
  %20 = load i32, i32* %19, align 4
  %21 = sext i32 %.0 to i64
  %22 = getelementptr inbounds i32, i32* %0, i64 %21
  %23 = load i32, i32* %22, align 4
  %24 = mul nsw i32 %23, 2
  %25 = add nsw i32 %20, %24
  %26 = sext i32 %.0 to i64
  %27 = getelementptr inbounds i32, i32* %1, i64 %26
  store i32 %25, i32* %27, align 4
  br label %28

; <label>:28:                                     ; preds = %17
  %29 = add nsw i32 %.0, 1
  br label %15

; <label>:30:                                     ; preds = %15
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_4(i32*, i32*) #0 {
  %3 = alloca [100 x i32], align 16
  %4 = alloca [100 x i32], align 16
  br label %5

; <label>:5:                                      ; preds = %14, %2
  %.01 = phi i32 [ 0, %2 ], [ %15, %14 ]
  %6 = icmp slt i32 %.01, 100
  br i1 %6, label %7, label %16

; <label>:7:                                      ; preds = %5
  %8 = sext i32 %.01 to i64
  %9 = getelementptr inbounds i32, i32* %0, i64 %8
  %10 = load i32, i32* %9, align 4
  %11 = add nsw i32 %10, 5
  %12 = sext i32 %.01 to i64
  %13 = getelementptr inbounds i32, i32* %1, i64 %12
  store i32 %11, i32* %13, align 4
  br label %14

; <label>:14:                                     ; preds = %7
  %15 = add nsw i32 %.01, 1
  br label %5

; <label>:16:                                     ; preds = %5
  br label %17

; <label>:17:                                     ; preds = %36, %16
  %.0 = phi i32 [ 0, %16 ], [ %37, %36 ]
  %18 = icmp slt i32 %.0, 100
  br i1 %18, label %19, label %38

; <label>:19:                                     ; preds = %17
  %20 = sext i32 %.0 to i64
  %21 = getelementptr inbounds i32, i32* %1, i64 %20
  %22 = load i32, i32* %21, align 4
  %23 = sext i32 %.0 to i64
  %24 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %23
  store i32 %22, i32* %24, align 4
  %25 = sext i32 %.0 to i64
  %26 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %25
  %27 = load i32, i32* %26, align 4
  %28 = sext i32 %.0 to i64
  %29 = getelementptr inbounds [100 x i32], [100 x i32]* %4, i64 0, i64 %28
  store i32 %27, i32* %29, align 4
  %30 = sext i32 %.0 to i64
  %31 = getelementptr inbounds [100 x i32], [100 x i32]* %4, i64 0, i64 %30
  %32 = load i32, i32* %31, align 4
  %33 = mul nsw i32 %32, 5
  %34 = sext i32 %.0 to i64
  %35 = getelementptr inbounds i32, i32* %1, i64 %34
  store i32 %33, i32* %35, align 4
  br label %36

; <label>:36:                                     ; preds = %19
  %37 = add nsw i32 %.0, 1
  br label %17

; <label>:38:                                     ; preds = %17
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_5(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %13, %2
  %.0 = phi i32 [ 0, %2 ], [ %14, %13 ]
  %4 = icmp slt i32 %.0, 99
  br i1 %4, label %5, label %15

; <label>:5:                                      ; preds = %3
  %6 = sext i32 %.0 to i64
  %7 = getelementptr inbounds i32, i32* %0, i64 %6
  %8 = load i32, i32* %7, align 4
  %9 = add nsw i32 %8, 5
  %10 = add nsw i32 %.0, 1
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds i32, i32* %1, i64 %11
  store i32 %9, i32* %12, align 4
  br label %13

; <label>:13:                                     ; preds = %5
  %14 = add nsw i32 %.0, 1
  br label %3

; <label>:15:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_6(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %18, %2
  %.0 = phi i32 [ 0, %2 ], [ %19, %18 ]
  %4 = icmp slt i32 %.0, 98
  br i1 %4, label %5, label %20

; <label>:5:                                      ; preds = %3
  %6 = add nsw i32 %.0, 1
  %7 = sext i32 %6 to i64
  %8 = getelementptr inbounds i32, i32* %0, i64 %7
  %9 = load i32, i32* %8, align 4
  %10 = add nsw i32 %.0, 2
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds i32, i32* %0, i64 %11
  %13 = load i32, i32* %12, align 4
  %14 = add nsw i32 %9, %13
  %15 = add nsw i32 %.0, 1
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds i32, i32* %1, i64 %16
  store i32 %14, i32* %17, align 4
  br label %18

; <label>:18:                                     ; preds = %5
  %19 = add nsw i32 %.0, 1
  br label %3

; <label>:20:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_7(i32*, i32*) #0 {
  %3 = alloca [100 x i32], align 16
  br label %4

; <label>:4:                                      ; preds = %14, %2
  %.01 = phi i32 [ 0, %2 ], [ %15, %14 ]
  %5 = icmp slt i32 %.01, 99
  br i1 %5, label %6, label %16

; <label>:6:                                      ; preds = %4
  %7 = sext i32 %.01 to i64
  %8 = getelementptr inbounds i32, i32* %0, i64 %7
  %9 = load i32, i32* %8, align 4
  %10 = add nsw i32 %9, 5
  %11 = add nsw i32 %.01, 1
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %12
  store i32 %10, i32* %13, align 4
  br label %14

; <label>:14:                                     ; preds = %6
  %15 = add nsw i32 %.01, 1
  br label %4

; <label>:16:                                     ; preds = %4
  br label %17

; <label>:17:                                     ; preds = %26, %16
  %.0 = phi i32 [ 0, %16 ], [ %27, %26 ]
  %18 = icmp slt i32 %.0, 99
  br i1 %18, label %19, label %28

; <label>:19:                                     ; preds = %17
  %20 = sext i32 %.0 to i64
  %21 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %20
  %22 = load i32, i32* %21, align 4
  %23 = add nsw i32 %22, 3
  %24 = sext i32 %.0 to i64
  %25 = getelementptr inbounds i32, i32* %1, i64 %24
  store i32 %23, i32* %25, align 4
  br label %26

; <label>:26:                                     ; preds = %19
  %27 = add nsw i32 %.0, 1
  br label %17

; <label>:28:                                     ; preds = %17
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_8(i32*, i32*) #0 {
  %3 = alloca [100 x i32], align 16
  br label %4

; <label>:4:                                      ; preds = %14, %2
  %.01 = phi i32 [ 1, %2 ], [ %15, %14 ]
  %5 = icmp slt i32 %.01, 99
  br i1 %5, label %6, label %16

; <label>:6:                                      ; preds = %4
  %7 = sub nsw i32 %.01, 1
  %8 = sext i32 %7 to i64
  %9 = getelementptr inbounds i32, i32* %0, i64 %8
  %10 = load i32, i32* %9, align 4
  %11 = add nsw i32 %10, 5
  %12 = sext i32 %.01 to i64
  %13 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %12
  store i32 %11, i32* %13, align 4
  br label %14

; <label>:14:                                     ; preds = %6
  %15 = add nsw i32 %.01, 1
  br label %4

; <label>:16:                                     ; preds = %4
  br label %17

; <label>:17:                                     ; preds = %31, %16
  %.0 = phi i32 [ 1, %16 ], [ %32, %31 ]
  %18 = icmp slt i32 %.0, 99
  br i1 %18, label %19, label %33

; <label>:19:                                     ; preds = %17
  %20 = add nsw i32 %.0, 1
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds [100 x i32], [100 x i32]* %3, i64 0, i64 %21
  %23 = load i32, i32* %22, align 4
  %24 = sub nsw i32 %.0, 1
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i32, i32* %0, i64 %25
  %27 = load i32, i32* %26, align 4
  %28 = add nsw i32 %23, %27
  %29 = sext i32 %.0 to i64
  %30 = getelementptr inbounds i32, i32* %1, i64 %29
  store i32 %28, i32* %30, align 4
  br label %31

; <label>:31:                                     ; preds = %19
  %32 = add nsw i32 %.0, 1
  br label %17

; <label>:33:                                     ; preds = %17
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_9(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %12, %2
  %.02 = phi i32 [ 0, %2 ], [ %13, %12 ]
  %4 = icmp slt i32 %.02, 100
  br i1 %4, label %5, label %14

; <label>:5:                                      ; preds = %3
  %6 = sext i32 %.02 to i64
  %7 = getelementptr inbounds i32, i32* %0, i64 %6
  %8 = load i32, i32* %7, align 4
  %9 = add nsw i32 %8, 1
  %10 = sext i32 %.02 to i64
  %11 = getelementptr inbounds i32, i32* %1, i64 %10
  store i32 %9, i32* %11, align 4
  br label %12

; <label>:12:                                     ; preds = %5
  %13 = add nsw i32 %.02, 1
  br label %3

; <label>:14:                                     ; preds = %3
  br label %15

; <label>:15:                                     ; preds = %24, %14
  %.01 = phi i32 [ 1, %14 ], [ %25, %24 ]
  %16 = icmp slt i32 %.01, 99
  br i1 %16, label %17, label %26

; <label>:17:                                     ; preds = %15
  %18 = sext i32 %.01 to i64
  %19 = getelementptr inbounds i32, i32* %0, i64 %18
  %20 = load i32, i32* %19, align 4
  %21 = add nsw i32 %20, 10
  %22 = sext i32 %.01 to i64
  %23 = getelementptr inbounds i32, i32* %1, i64 %22
  store i32 %21, i32* %23, align 4
  br label %24

; <label>:24:                                     ; preds = %17
  %25 = add nsw i32 %.01, 1
  br label %15

; <label>:26:                                     ; preds = %15
  br label %27

; <label>:27:                                     ; preds = %36, %26
  %.0 = phi i32 [ 2, %26 ], [ %37, %36 ]
  %28 = icmp slt i32 %.0, 98
  br i1 %28, label %29, label %38

; <label>:29:                                     ; preds = %27
  %30 = sext i32 %.0 to i64
  %31 = getelementptr inbounds i32, i32* %0, i64 %30
  %32 = load i32, i32* %31, align 4
  %33 = add nsw i32 %32, 100
  %34 = sext i32 %.0 to i64
  %35 = getelementptr inbounds i32, i32* %1, i64 %34
  store i32 %33, i32* %35, align 4
  br label %36

; <label>:36:                                     ; preds = %29
  %37 = add nsw i32 %.0, 1
  br label %27

; <label>:38:                                     ; preds = %27
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_10(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %25, %2
  %.0 = phi i32 [ 0, %2 ], [ %26, %25 ]
  %4 = icmp slt i32 %.0, 100
  br i1 %4, label %5, label %27

; <label>:5:                                      ; preds = %3
  %6 = add nsw i32 %.0, 1
  %7 = sext i32 %6 to i64
  %8 = getelementptr inbounds i32, i32* %1, i64 %7
  %9 = load i32, i32* %8, align 4
  %10 = add nsw i32 %.0, 2
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds i32, i32* %1, i64 %11
  %13 = load i32, i32* %12, align 4
  %14 = add nsw i32 %9, %13
  %15 = sext i32 %.0 to i64
  %16 = getelementptr inbounds i32, i32* %1, i64 %15
  store i32 %14, i32* %16, align 4
  %17 = add nsw i32 %.0, 1
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds i32, i32* %1, i64 %18
  %20 = load i32, i32* %19, align 4
  %21 = add nsw i32 %20, 3
  %22 = add nsw i32 %.0, 1
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds i32, i32* %1, i64 %23
  store i32 %21, i32* %24, align 4
  br label %25

; <label>:25:                                     ; preds = %5
  %26 = add nsw i32 %.0, 1
  br label %3

; <label>:27:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @mov_avg(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %22, %2
  %.0 = phi i32 [ 1, %2 ], [ %23, %22 ]
  %4 = icmp slt i32 %.0, 99
  br i1 %4, label %5, label %24

; <label>:5:                                      ; preds = %3
  %6 = sub nsw i32 %.0, 1
  %7 = sext i32 %6 to i64
  %8 = getelementptr inbounds i32, i32* %0, i64 %7
  %9 = load i32, i32* %8, align 4
  %10 = sext i32 %.0 to i64
  %11 = getelementptr inbounds i32, i32* %0, i64 %10
  %12 = load i32, i32* %11, align 4
  %13 = add nsw i32 %9, %12
  %14 = add nsw i32 %.0, 1
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds i32, i32* %0, i64 %15
  %17 = load i32, i32* %16, align 4
  %18 = add nsw i32 %13, %17
  %19 = sdiv i32 %18, 3
  %20 = sext i32 %.0 to i64
  %21 = getelementptr inbounds i32, i32* %1, i64 %20
  store i32 %19, i32* %21, align 4
  br label %22

; <label>:22:                                     ; preds = %5
  %23 = add nsw i32 %.0, 1
  br label %3

; <label>:24:                                     ; preds = %3
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

; <label>:10:                                     ; preds = %29, %2
  %.0 = phi i32 [ 1, %2 ], [ %30, %29 ]
  %11 = icmp slt i32 %.0, 99
  br i1 %11, label %12, label %31

; <label>:12:                                     ; preds = %10
  %13 = sub nsw i32 %.0, 1
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds float, float* %0, i64 %14
  %16 = load float, float* %15, align 4
  %17 = sext i32 %.0 to i64
  %18 = getelementptr inbounds float, float* %0, i64 %17
  %19 = load float, float* %18, align 4
  %20 = fadd float %16, %19
  %21 = add nsw i32 %.0, 1
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds float, float* %0, i64 %22
  %24 = load float, float* %23, align 4
  %25 = fadd float %20, %24
  %26 = fdiv float %25, 3.000000e+00
  %27 = sext i32 %.0 to i64
  %28 = getelementptr inbounds float, float* %1, i64 %27
  store float %26, float* %28, align 4
  br label %29

; <label>:29:                                     ; preds = %12
  %30 = add nsw i32 %.0, 1
  br label %10

; <label>:31:                                     ; preds = %10
  %32 = getelementptr inbounds float, float* %0, i64 98
  %33 = load float, float* %32, align 4
  %34 = getelementptr inbounds float, float* %0, i64 99
  %35 = load float, float* %34, align 4
  %36 = fadd float %33, %35
  %37 = fdiv float %36, 2.000000e+00
  %38 = getelementptr inbounds float, float* %1, i64 99
  store float %37, float* %38, align 4
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @test_cast(float*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %13, %2
  %.0 = phi i32 [ 0, %2 ], [ %14, %13 ]
  %4 = icmp slt i32 %.0, 100
  br i1 %4, label %5, label %15

; <label>:5:                                      ; preds = %3
  %6 = sext i32 %.0 to i64
  %7 = getelementptr inbounds float, float* %0, i64 %6
  %8 = load float, float* %7, align 4
  %9 = fptosi float %8 to i32
  %10 = add nsw i32 %9, 2
  %11 = sext i32 %.0 to i64
  %12 = getelementptr inbounds i32, i32* %1, i64 %11
  store i32 %10, i32* %12, align 4
  br label %13

; <label>:13:                                     ; preds = %5
  %14 = add nsw i32 %.0, 1
  br label %3

; <label>:15:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @func_test(float*, float*) #0 {
  br label %3

; <label>:3:                                      ; preds = %13, %2
  %.0 = phi i32 [ 0, %2 ], [ %14, %13 ]
  %4 = icmp slt i32 %.0, 100
  br i1 %4, label %5, label %15

; <label>:5:                                      ; preds = %3
  %6 = sext i32 %.0 to i64
  %7 = getelementptr inbounds float, float* %0, i64 %6
  %8 = load float, float* %7, align 4
  %9 = call float @exp(float %8)
  %10 = call float @log(float %9)
  %11 = sext i32 %.0 to i64
  %12 = getelementptr inbounds float, float* %1, i64 %11
  store float %10, float* %12, align 4
  br label %13

; <label>:13:                                     ; preds = %5
  %14 = add nsw i32 %.0, 1
  br label %3

; <label>:15:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @cond_test(i32, i32*, i32*) #0 {
  br label %4

; <label>:4:                                      ; preds = %11, %3
  %.0 = phi i32 [ 0, %3 ], [ %12, %11 ]
  %5 = icmp slt i32 %.0, 100
  br i1 %5, label %6, label %13

; <label>:6:                                      ; preds = %4
  %7 = icmp sgt i32 %0, 3
  %8 = select i1 %7, i32 5, i32 10
  %9 = sext i32 %.0 to i64
  %10 = getelementptr inbounds i32, i32* %2, i64 %9
  store i32 %8, i32* %10, align 4
  br label %11

; <label>:11:                                     ; preds = %6
  %12 = add nsw i32 %.0, 1
  br label %4

; <label>:13:                                     ; preds = %4
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @nested_test_1(i32*, i32*, i32*) #0 {
  br label %4

; <label>:4:                                      ; preds = %22, %3
  %.01 = phi i32 [ 0, %3 ], [ %23, %22 ]
  %5 = icmp slt i32 %.01, 100
  br i1 %5, label %6, label %24

; <label>:6:                                      ; preds = %4
  br label %7

; <label>:7:                                      ; preds = %19, %6
  %.0 = phi i32 [ 0, %6 ], [ %20, %19 ]
  %8 = icmp slt i32 %.0, 10
  br i1 %8, label %9, label %21

; <label>:9:                                      ; preds = %7
  %10 = sext i32 %.01 to i64
  %11 = getelementptr inbounds i32, i32* %0, i64 %10
  %12 = load i32, i32* %11, align 4
  %13 = sext i32 %.0 to i64
  %14 = getelementptr inbounds i32, i32* %1, i64 %13
  %15 = load i32, i32* %14, align 4
  %16 = add nsw i32 %12, %15
  %17 = sext i32 %.01 to i64
  %18 = getelementptr inbounds i32, i32* %2, i64 %17
  store i32 %16, i32* %18, align 4
  br label %19

; <label>:19:                                     ; preds = %9
  %20 = add nsw i32 %.0, 1
  br label %7

; <label>:21:                                     ; preds = %7
  br label %22

; <label>:22:                                     ; preds = %21
  %23 = add nsw i32 %.01, 1
  br label %4

; <label>:24:                                     ; preds = %4
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @unroll_test(i32*, i32*, i32*) #0 {
  br label %4

; <label>:4:                                      ; preds = %11, %3
  %.0 = phi i32 [ 0, %3 ], [ %12, %11 ]
  %5 = icmp slt i32 %.0, 1000
  br i1 %5, label %6, label %13

; <label>:6:                                      ; preds = %4
  %7 = sext i32 %.0 to i64
  %8 = getelementptr inbounds i32, i32* %1, i64 %7
  %9 = load i32, i32* %8, align 4
  %10 = add nsw i32 %9, 3
  store i32 %10, i32* %0, align 4
  br label %11

; <label>:11:                                     ; preds = %6
  %12 = add nsw i32 %.0, 1
  br label %4

; <label>:13:                                     ; preds = %4
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @counter_test(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %18, %2
  %.01 = phi i32 [ 0, %2 ], [ %19, %18 ]
  %4 = icmp slt i32 %.01, 100
  br i1 %4, label %5, label %20

; <label>:5:                                      ; preds = %3
  br label %6

; <label>:6:                                      ; preds = %15, %5
  %.0 = phi i32 [ 0, %5 ], [ %16, %15 ]
  %7 = icmp slt i32 %.0, 4
  br i1 %7, label %8, label %17

; <label>:8:                                      ; preds = %6
  %9 = sext i32 %.01 to i64
  %10 = getelementptr inbounds i32, i32* %0, i64 %9
  %11 = load i32, i32* %10, align 4
  %12 = add nsw i32 %11, %.0
  %13 = sext i32 %.01 to i64
  %14 = getelementptr inbounds i32, i32* %1, i64 %13
  store i32 %12, i32* %14, align 4
  br label %15

; <label>:15:                                     ; preds = %8
  %16 = add nsw i32 %.0, 1
  br label %6

; <label>:17:                                     ; preds = %6
  br label %18

; <label>:18:                                     ; preds = %17
  %19 = add nsw i32 %.01, 1
  br label %3

; <label>:20:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @acc_test(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %13, %2
  %.01 = phi i32 [ 3, %2 ], [ %12, %13 ]
  %.0 = phi i32 [ 0, %2 ], [ %14, %13 ]
  %4 = icmp slt i32 %.0, 100
  br i1 %4, label %5, label %15

; <label>:5:                                      ; preds = %3
  %6 = sext i32 %.0 to i64
  %7 = getelementptr inbounds i32, i32* %0, i64 %6
  %8 = load i32, i32* %7, align 4
  %9 = mul nsw i32 %8, %.01
  %10 = sext i32 %.0 to i64
  %11 = getelementptr inbounds i32, i32* %1, i64 %10
  store i32 %9, i32* %11, align 4
  %12 = mul nsw i32 2, %.01
  br label %13

; <label>:13:                                     ; preds = %5
  %14 = add nsw i32 %.0, 1
  br label %3

; <label>:15:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @acc_test_2(i32*, i32*) #0 {
  br label %3

; <label>:3:                                      ; preds = %13, %2
  %.01 = phi i32 [ 0, %2 ], [ %9, %13 ]
  %.0 = phi i32 [ 0, %2 ], [ %14, %13 ]
  %4 = icmp slt i32 %.0, 100
  br i1 %4, label %5, label %15

; <label>:5:                                      ; preds = %3
  %6 = sext i32 %.0 to i64
  %7 = getelementptr inbounds i32, i32* %0, i64 %6
  %8 = load i32, i32* %7, align 4
  %9 = add nsw i32 %.01, %8
  %10 = mul nsw i32 %9, 2
  %11 = sext i32 %.0 to i64
  %12 = getelementptr inbounds i32, i32* %1, i64 %11
  store i32 %10, i32* %12, align 4
  br label %13

; <label>:13:                                     ; preds = %5
  %14 = add nsw i32 %.0, 1
  br label %3

; <label>:15:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @newton_raphson(float*, float*) #0 {
  br label %3

; <label>:3:                                      ; preds = %30, %2
  %.02 = phi i32 [ 0, %2 ], [ %31, %30 ]
  %4 = icmp slt i32 %.02, 100
  br i1 %4, label %5, label %32

; <label>:5:                                      ; preds = %3
  %6 = sext i32 %.02 to i64
  %7 = getelementptr inbounds float, float* %0, i64 %6
  %8 = load float, float* %7, align 4
  %9 = fmul float 2.000000e+00, %8
  %10 = fpext float %9 to double
  %11 = fsub double 2.914200e+00, %10
  %12 = fptrunc double %11 to float
  br label %13

; <label>:13:                                     ; preds = %25, %5
  %.01 = phi float [ %12, %5 ], [ %24, %25 ]
  %.0 = phi i32 [ 0, %5 ], [ %26, %25 ]
  %14 = icmp slt i32 %.0, 4
  br i1 %14, label %15, label %27

; <label>:15:                                     ; preds = %13
  %16 = fpext float %.01 to double
  %17 = sext i32 %.02 to i64
  %18 = getelementptr inbounds float, float* %0, i64 %17
  %19 = load float, float* %18, align 4
  %20 = fmul float %19, %.01
  %21 = fpext float %20 to double
  %22 = fsub double 2.000000e+00, %21
  %23 = fmul double %16, %22
  %24 = fptrunc double %23 to float
  br label %25

; <label>:25:                                     ; preds = %15
  %26 = add nsw i32 %.0, 1
  br label %13

; <label>:27:                                     ; preds = %13
  %28 = sext i32 %.02 to i64
  %29 = getelementptr inbounds float, float* %1, i64 %28
  store float %.01, float* %29, align 4
  br label %30

; <label>:30:                                     ; preds = %27
  %31 = add nsw i32 %.02, 1
  br label %3

; <label>:32:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @two_loops(float*, float*, float*) #0 {
  br label %4

; <label>:4:                                      ; preds = %31, %3
  %.02 = phi i32 [ 0, %3 ], [ %32, %31 ]
  %5 = icmp slt i32 %.02, 100
  br i1 %5, label %6, label %33

; <label>:6:                                      ; preds = %4
  br label %7

; <label>:7:                                      ; preds = %16, %6
  %.01 = phi i32 [ 0, %6 ], [ %17, %16 ]
  %8 = icmp slt i32 %.01, 4
  br i1 %8, label %9, label %18

; <label>:9:                                      ; preds = %7
  %10 = sext i32 %.02 to i64
  %11 = getelementptr inbounds float, float* %0, i64 %10
  %12 = load float, float* %11, align 4
  %13 = fadd float %12, 4.000000e+00
  %14 = sext i32 %.02 to i64
  %15 = getelementptr inbounds float, float* %2, i64 %14
  store float %13, float* %15, align 4
  br label %16

; <label>:16:                                     ; preds = %9
  %17 = add nsw i32 %.01, 1
  br label %7

; <label>:18:                                     ; preds = %7
  br label %19

; <label>:19:                                     ; preds = %28, %18
  %.0 = phi i32 [ 0, %18 ], [ %29, %28 ]
  %20 = icmp slt i32 %.0, 4
  br i1 %20, label %21, label %30

; <label>:21:                                     ; preds = %19
  %22 = sext i32 %.02 to i64
  %23 = getelementptr inbounds float, float* %2, i64 %22
  %24 = load float, float* %23, align 4
  %25 = fadd float %24, 5.000000e+00
  %26 = sext i32 %.02 to i64
  %27 = getelementptr inbounds float, float* %1, i64 %26
  store float %25, float* %27, align 4
  br label %28

; <label>:28:                                     ; preds = %21
  %29 = add nsw i32 %.0, 1
  br label %19

; <label>:30:                                     ; preds = %19
  br label %31

; <label>:31:                                     ; preds = %30
  %32 = add nsw i32 %.02, 1
  br label %4

; <label>:33:                                     ; preds = %4
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @two_d_test([3 x i8]*, [3 x i8]*) #0 {
  %3 = alloca [100 x float], align 16
  br label %4

; <label>:4:                                      ; preds = %27, %2
  %.02 = phi i32 [ 0, %2 ], [ %28, %27 ]
  %5 = icmp slt i32 %.02, 100
  br i1 %5, label %6, label %29

; <label>:6:                                      ; preds = %4
  %7 = sext i32 %.02 to i64
  %8 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %7
  %9 = getelementptr inbounds [3 x i8], [3 x i8]* %8, i64 0, i64 0
  %10 = load i8, i8* %9, align 1
  %11 = zext i8 %10 to i32
  %12 = sext i32 %.02 to i64
  %13 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %12
  %14 = getelementptr inbounds [3 x i8], [3 x i8]* %13, i64 0, i64 1
  %15 = load i8, i8* %14, align 1
  %16 = zext i8 %15 to i32
  %17 = add nsw i32 %11, %16
  %18 = sext i32 %.02 to i64
  %19 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %18
  %20 = getelementptr inbounds [3 x i8], [3 x i8]* %19, i64 0, i64 2
  %21 = load i8, i8* %20, align 1
  %22 = zext i8 %21 to i32
  %23 = add nsw i32 %17, %22
  %24 = sitofp i32 %23 to float
  %25 = sext i32 %.02 to i64
  %26 = getelementptr inbounds [100 x float], [100 x float]* %3, i64 0, i64 %25
  store float %24, float* %26, align 4
  br label %27

; <label>:27:                                     ; preds = %6
  %28 = add nsw i32 %.02, 1
  br label %4

; <label>:29:                                     ; preds = %4
  br label %30

; <label>:30:                                     ; preds = %55, %29
  %.01 = phi i32 [ 0, %29 ], [ %56, %55 ]
  %31 = icmp slt i32 %.01, 100
  br i1 %31, label %32, label %57

; <label>:32:                                     ; preds = %30
  br label %33

; <label>:33:                                     ; preds = %52, %32
  %.0 = phi i32 [ 0, %32 ], [ %53, %52 ]
  %34 = icmp slt i32 %.0, 3
  br i1 %34, label %35, label %54

; <label>:35:                                     ; preds = %33
  %36 = sext i32 %.01 to i64
  %37 = getelementptr inbounds [100 x float], [100 x float]* %3, i64 0, i64 %36
  %38 = load float, float* %37, align 4
  %39 = sext i32 %.01 to i64
  %40 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %39
  %41 = sext i32 %.0 to i64
  %42 = getelementptr inbounds [3 x i8], [3 x i8]* %40, i64 0, i64 %41
  %43 = load i8, i8* %42, align 1
  %44 = zext i8 %43 to i32
  %45 = sitofp i32 %44 to float
  %46 = fadd float %38, %45
  %47 = fptoui float %46 to i8
  %48 = sext i32 %.01 to i64
  %49 = getelementptr inbounds [3 x i8], [3 x i8]* %1, i64 %48
  %50 = sext i32 %.0 to i64
  %51 = getelementptr inbounds [3 x i8], [3 x i8]* %49, i64 0, i64 %50
  store i8 %47, i8* %51, align 1
  br label %52

; <label>:52:                                     ; preds = %35
  %53 = add nsw i32 %.0, 1
  br label %33

; <label>:54:                                     ; preds = %33
  br label %55

; <label>:55:                                     ; preds = %54
  %56 = add nsw i32 %.01, 1
  br label %30

; <label>:57:                                     ; preds = %30
  ret void
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline nounwind readnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (tags/RELEASE_400/final)"}
