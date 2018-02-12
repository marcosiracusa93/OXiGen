; ModuleID = '../resources/sharpener/3_sharpener_pseudo_linearized_no_branches.ll'
source_filename = "3_sharpener_pseudo_linearized_no_branches.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@.str = private unnamed_addr constant [76 x i8] c"missing arguments: input_file.bmp output_file.bmp [golden_output_file.bmp]\0A\00", align 1
@write_bmp.header = private unnamed_addr constant [54 x i8] c"BM8\F9\15\00\00\00\00\006\00\00\00(\00\00\00X\02\00\00 \03\00\00\01\00\18\00\00\00\00\00\02\F9\15\00\12\0B\00\00\12\0B\00\00\00\00\00\00\00\00\00\00", align 16
@.str.1 = private unnamed_addr constant [3 x i8] c"wb\00", align 1
@.str.2 = private unnamed_addr constant [33 x i8] c"Unable to open: '%s0 for writing\00", align 1
@.str.3 = private unnamed_addr constant [3 x i8] c"rb\00", align 1
@.str.4 = private unnamed_addr constant [33 x i8] c"Unable to open: '%s0 for reading\00", align 1
@.str.5 = private unnamed_addr constant [20 x i8] c"Invalid input file\0A\00", align 1
@.str.6 = private unnamed_addr constant [24 x i8] c"Image size is: %d X %d\0A\00", align 1
@.str.7 = private unnamed_addr constant [19 x i8] c"Expected: %d X %d\0A\00", align 1
@.str.8 = private unnamed_addr constant [71 x i8] c"Validation failed. Detected %d missmatching pixels. Maximum error: %d\0A\00", align 1
@.str.9 = private unnamed_addr constant [20 x i8] c"Validation passed!\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define float @exp(float) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = fmul float %3, %4
  %6 = load float, float* %2, align 4
  %7 = fadd float %5, %6
  ret float %7
}

; Function Attrs: noinline nounwind uwtable
define float @log(float) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = fmul float %3, %4
  %6 = load float, float* %2, align 4
  %7 = fadd float %5, %6
  ret float %7
}

; Function Attrs: noinline nounwind uwtable
define float @sqrt(float) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = fmul float %3, %4
  %6 = load float, float* %2, align 4
  %7 = fadd float %5, %6
  ret float %7
}

; Function Attrs: noinline nounwind uwtable
define float @log2(float) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = fmul float %3, %4
  %6 = load float, float* %2, align 4
  %7 = fadd float %5, %6
  ret float %7
}

; Function Attrs: noinline nounwind uwtable
define float @pow2(float) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = fmul float %3, %4
  %6 = load float, float* %2, align 4
  %7 = fadd float %5, %6
  ret float %7
}

; Function Attrs: noinline nounwind uwtable
define float @ceil(float) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = fmul float %3, %4
  %6 = load float, float* %2, align 4
  %7 = fadd float %5, %6
  ret float %7
}

; Function Attrs: noinline nounwind uwtable
define float @floor(float) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = fmul float %3, %4
  %6 = load float, float* %2, align 4
  %7 = fadd float %5, %6
  ret float %7
}

; Function Attrs: noinline nounwind uwtable
define float @fabs(float) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = fmul float %3, %4
  %6 = load float, float* %2, align 4
  %7 = fadd float %5, %6
  ret float %7
}

; Function Attrs: noinline nounwind readnone uwtable
define i32 @abs(i32) #1 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = load i32, i32* %2, align 4
  %5 = mul nsw i32 %3, %4
  %6 = load i32, i32* %2, align 4
  %7 = add nsw i32 %5, %6
  ret i32 %7
}

; Function Attrs: noinline nounwind uwtable
define float @Ncdf(float) #0 {
  %2 = alloca float, align 4
  store float %0, float* %2, align 4
  %3 = load float, float* %2, align 4
  %4 = load float, float* %2, align 4
  %5 = fmul float %3, %4
  %6 = load float, float* %2, align 4
  %7 = fadd float %5, %6
  ret float %7
}

; Function Attrs: noinline nounwind uwtable
define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca [172800 x [3 x i8]], align 16
  %7 = alloca [172800 x [3 x i8]], align 16
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i8*, align 8
  %11 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  %12 = load i32, i32* %4, align 4
  %13 = icmp slt i32 %12, 3
  br i1 %13, label %14, label %16

; <label>:14:                                     ; preds = %2
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str, i32 0, i32 0))
  call void @exit(i32 1) #5
  unreachable

; <label>:16:                                     ; preds = %2
  %17 = load i8**, i8*** %5, align 8
  %18 = getelementptr inbounds i8*, i8** %17, i64 1
  %19 = load i8*, i8** %18, align 8
  store i8* %19, i8** %8, align 8
  %20 = load i8**, i8*** %5, align 8
  %21 = getelementptr inbounds i8*, i8** %20, i64 2
  %22 = load i8*, i8** %21, align 8
  store i8* %22, i8** %9, align 8
  %23 = load i8*, i8** %8, align 8
  %24 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %6, i32 0, i32 0
  %25 = bitcast [3 x i8]* %24 to i8*
  call void @read_bmp(i8* %23, i8* %25)
  %26 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %6, i32 0, i32 0
  %27 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %7, i32 0, i32 0
  call void @sharpen([3 x i8]* %26, [3 x i8]* %27)
  %28 = load i8*, i8** %9, align 8
  %29 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %7, i32 0, i32 0
  %30 = bitcast [3 x i8]* %29 to i8*
  call void @write_bmp(i8* %28, i8* %30)
  %31 = load i32, i32* %4, align 4
  %32 = icmp sge i32 %31, 4
  br i1 %32, label %33, label %44

; <label>:33:                                     ; preds = %16
  %34 = load i8**, i8*** %5, align 8
  %35 = getelementptr inbounds i8*, i8** %34, i64 3
  %36 = load i8*, i8** %35, align 8
  store i8* %36, i8** %10, align 8
  %37 = load i8*, i8** %10, align 8
  %38 = load i8*, i8** %9, align 8
  %39 = call i32 @validate_result(i8* %37, i8* %38, i32 1)
  store i32 %39, i32* %11, align 4
  %40 = load i32, i32* %11, align 4
  %41 = icmp ne i32 %40, 0
  br i1 %41, label %43, label %42

; <label>:42:                                     ; preds = %33
  store i32 1, i32* %3, align 4
  br label %45

; <label>:43:                                     ; preds = %33
  br label %44

; <label>:44:                                     ; preds = %43, %16
  store i32 0, i32* %3, align 4
  br label %45

; <label>:45:                                     ; preds = %44, %42
  %46 = load i32, i32* %3, align 4
  ret i32 %46
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: noreturn nounwind
declare void @exit(i32) #3

; Function Attrs: noinline nounwind uwtable
define void @read_bmp(i8*, i8*) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca %struct._IO_FILE*, align 8
  %6 = alloca [54 x i8], align 16
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %10 = load i8*, i8** %3, align 8
  %11 = call %struct._IO_FILE* @fopen(i8* %10, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0))
  store %struct._IO_FILE* %11, %struct._IO_FILE** %5, align 8
  %12 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8
  %13 = icmp ne %struct._IO_FILE* %12, null
  br i1 %13, label %17, label %14

; <label>:14:                                     ; preds = %2
  %15 = load i8*, i8** %3, align 8
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.4, i32 0, i32 0), i8* %15)
  call void @exit(i32 1) #5
  unreachable

; <label>:17:                                     ; preds = %2
  %18 = getelementptr inbounds [54 x i8], [54 x i8]* %6, i32 0, i32 0
  %19 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8
  %20 = call i64 @fread(i8* %18, i64 1, i64 54, %struct._IO_FILE* %19)
  %21 = getelementptr inbounds [54 x i8], [54 x i8]* %6, i64 0, i64 18
  %22 = bitcast i8* %21 to i32*
  %23 = load i32, i32* %22, align 2
  store i32 %23, i32* %7, align 4
  %24 = getelementptr inbounds [54 x i8], [54 x i8]* %6, i64 0, i64 22
  %25 = bitcast i8* %24 to i32*
  %26 = load i32, i32* %25, align 2
  store i32 %26, i32* %8, align 4
  %27 = load i32, i32* %7, align 4
  %28 = icmp ne i32 %27, 360
  br i1 %28, label %32, label %29

; <label>:29:                                     ; preds = %17
  %30 = load i32, i32* %8, align 4
  %31 = icmp ne i32 %30, 480
  br i1 %31, label %32, label %38

; <label>:32:                                     ; preds = %29, %17
  %33 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.5, i32 0, i32 0))
  %34 = load i32, i32* %7, align 4
  %35 = load i32, i32* %8, align 4
  %36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.6, i32 0, i32 0), i32 %34, i32 %35)
  %37 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.7, i32 0, i32 0), i32 360, i32 480)
  call void @exit(i32 1) #5
  unreachable

; <label>:38:                                     ; preds = %29
  %39 = load i32, i32* %7, align 4
  %40 = mul nsw i32 3, %39
  %41 = load i32, i32* %8, align 4
  %42 = mul nsw i32 %40, %41
  store i32 %42, i32* %9, align 4
  %43 = load i8*, i8** %4, align 8
  %44 = load i32, i32* %9, align 4
  %45 = sext i32 %44 to i64
  %46 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8
  %47 = call i64 @fread(i8* %43, i64 1, i64 %45, %struct._IO_FILE* %46)
  %48 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8
  %49 = call i32 @fclose(%struct._IO_FILE* %48)
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @sharpen([3 x i8]*, [3 x i8]*) #0 {
  %3 = alloca [172800 x float], align 16
  %4 = alloca [172800 x float], align 16
  %5 = alloca [172800 x float], align 16
  %6 = alloca [172800 x float], align 16
  %7 = alloca [172800 x float], align 16
  %8 = alloca [172800 x [3 x float]], align 16
  br label %9

; <label>:9:                                      ; preds = %38, %2
  %.02 = phi i32 [ 0, %2 ], [ %39, %38 ]
  %10 = icmp slt i32 %.02, 172800
  br i1 %10, label %11, label %40

; <label>:11:                                     ; preds = %9
  %12 = sext i32 %.02 to i64
  %13 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %12
  %14 = getelementptr inbounds [3 x i8], [2 x [3 x i8]]* %13, i64 0, i64 0
  %15 = load i8, i8* %14, align 1
  %16 = zext i8 %15 to i32
  %17 = sitofp i32 %16 to double
  %18 = fmul double 1.000000e-01, %17
  %19 = sext i32 %.02 to i64
  %20 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %19
  %21 = getelementptr inbounds [3 x i8], [2 x [3 x i8]]* %20, i64 0, i64 1
  %22 = load i8, i8* %21, align 1
  %23 = zext i8 %22 to i32
  %24 = sitofp i32 %23 to double
  %25 = fmul double 6.000000e-01, %24
  %26 = fadd double %18, %25
  %27 = sext i32 %.02 to i64
  %28 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %27
  %29 = getelementptr inbounds [3 x i8], [2 x [3 x i8]]* %28, i64 0, i64 2
  %30 = load i8, i8* %29, align 1
  %31 = zext i8 %30 to i32
  %32 = sitofp i32 %31 to double
  %33 = fmul double 3.000000e-01, %32
  %34 = fadd double %26, %33
  %35 = fptrunc double %34 to float
  %36 = sext i32 %.02 to i64
  %37 = getelementptr inbounds [172800 x float], [172800 x float]* %3, i64 0, i64 %36
  store float %35, float* %37, align 4
  br label %38

; <label>:38:                                     ; preds = %11
  %39 = add nsw i32 %.02, 1
  br label %9

; <label>:40:                                     ; preds = %9
  br label %41

; <label>:41:                                     ; preds = %60, %40
  %.03 = phi i32 [ 360, %40 ], [ %61, %60 ]
  %42 = icmp slt i32 %.03, 172440
  br i1 %42, label %43, label %62

; <label>:43:                                     ; preds = %41
  %44 = sub nsw i32 %.03, 360
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds [172800 x float], [172800 x float]* %3, i64 0, i64 %45
  %47 = load float, float* %46, align 4
  %48 = sext i32 %.03 to i64
  %49 = getelementptr inbounds [172800 x float], [172800 x float]* %3, i64 0, i64 %48
  %50 = load float, float* %49, align 4
  %51 = fadd float %47, %50
  %52 = add nsw i32 %.03, 360
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds [172800 x float], [172800 x float]* %3, i64 0, i64 %53
  %55 = load float, float* %54, align 4
  %56 = fadd float %51, %55
  %57 = fdiv float %56, 3.000000e+00
  %58 = sext i32 %.03 to i64
  %59 = getelementptr inbounds [172800 x float], [172800 x float]* %4, i64 0, i64 %58
  store float %57, float* %59, align 4
  br label %60

; <label>:60:                                     ; preds = %43
  %61 = add nsw i32 %.03, 1
  br label %41

; <label>:62:                                     ; preds = %41
  br label %63

; <label>:63:                                     ; preds = %82, %62
  %.04 = phi i32 [ 360, %62 ], [ %83, %82 ]
  %64 = icmp slt i32 %.04, 172440
  br i1 %64, label %65, label %84

; <label>:65:                                     ; preds = %63
  %66 = sub nsw i32 %.04, 1
  %67 = sext i32 %66 to i64
  %68 = getelementptr inbounds [172800 x float], [172800 x float]* %4, i64 0, i64 %67
  %69 = load float, float* %68, align 4
  %70 = sext i32 %.04 to i64
  %71 = getelementptr inbounds [172800 x float], [172800 x float]* %4, i64 0, i64 %70
  %72 = load float, float* %71, align 4
  %73 = fadd float %69, %72
  %74 = add nsw i32 %.04, 1
  %75 = sext i32 %74 to i64
  %76 = getelementptr inbounds [172800 x float], [172800 x float]* %4, i64 0, i64 %75
  %77 = load float, float* %76, align 4
  %78 = fadd float %73, %77
  %79 = fdiv float %78, 3.000000e+00
  %80 = sext i32 %.04 to i64
  %81 = getelementptr inbounds [172800 x float], [172800 x float]* %5, i64 0, i64 %80
  store float %79, float* %81, align 4
  br label %82

; <label>:82:                                     ; preds = %65
  %83 = add nsw i32 %.04, 1
  br label %63

; <label>:84:                                     ; preds = %63
  br label %85

; <label>:85:                                     ; preds = %99, %84
  %.05 = phi i32 [ 0, %84 ], [ %100, %99 ]
  %86 = icmp slt i32 %.05, 172800
  br i1 %86, label %87, label %101

; <label>:87:                                     ; preds = %85
  %88 = sext i32 %.05 to i64
  %89 = getelementptr inbounds [172800 x float], [172800 x float]* %3, i64 0, i64 %88
  %90 = load float, float* %89, align 4
  %91 = fmul float 2.000000e+00, %90
  %92 = sext i32 %.05 to i64
  %93 = getelementptr inbounds [172800 x float], [172800 x float]* %5, i64 0, i64 %92
  %94 = load float, float* %93, align 4
  %95 = fsub float %91, %94
  %96 = call float @fabs(float %95)
  %97 = sext i32 %.05 to i64
  %98 = getelementptr inbounds [172800 x float], [172800 x float]* %6, i64 0, i64 %97
  store float %96, float* %98, align 4
  br label %99

; <label>:99:                                     ; preds = %87
  %100 = add nsw i32 %.05, 1
  br label %85

; <label>:101:                                    ; preds = %85
  br label %102

; <label>:102:                                    ; preds = %115, %101
  %.06 = phi i32 [ 0, %101 ], [ %116, %115 ]
  %103 = icmp slt i32 %.06, 172800
  br i1 %103, label %104, label %117

; <label>:104:                                    ; preds = %102
  %105 = sext i32 %.06 to i64
  %106 = getelementptr inbounds [172800 x float], [172800 x float]* %6, i64 0, i64 %105
  %107 = load float, float* %106, align 4
  %108 = sext i32 %.06 to i64
  %109 = getelementptr inbounds [172800 x float], [172800 x float]* %3, i64 0, i64 %108
  %110 = load float, float* %109, align 4
  %111 = fadd float %110, 1.000000e+00
  %112 = fdiv float %107, %111
  %113 = sext i32 %.06 to i64
  %114 = getelementptr inbounds [172800 x float], [172800 x float]* %7, i64 0, i64 %113
  store float %112, float* %114, align 4
  br label %115

; <label>:115:                                    ; preds = %104
  %116 = add nsw i32 %.06, 1
  br label %102

; <label>:117:                                    ; preds = %102
  br label %118

; <label>:118:                                    ; preds = %142, %117
  %.07 = phi i32 [ 0, %117 ], [ %143, %142 ]
  %119 = icmp slt i32 %.07, 172800
  br i1 %119, label %120, label %144

; <label>:120:                                    ; preds = %118
  br label %121

; <label>:121:                                    ; preds = %139, %120
  %.08 = phi i32 [ 0, %120 ], [ %140, %139 ]
  %122 = icmp slt i32 %.08, 3
  br i1 %122, label %123, label %141

; <label>:123:                                    ; preds = %121
  %124 = sext i32 %.07 to i64
  %125 = getelementptr inbounds [172800 x float], [172800 x float]* %7, i64 0, i64 %124
  %126 = load float, float* %125, align 4
  %127 = sext i32 %.07 to i64
  %128 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %127
  %129 = sext i32 %.08 to i64
  %130 = getelementptr inbounds [3 x i8], [2 x [3 x i8]]* %128, i64 0, i64 %129
  %131 = load i8, i8* %130, align 1
  %132 = zext i8 %131 to i32
  %133 = sitofp i32 %132 to float
  %134 = fmul float %126, %133
  %135 = sext i32 %.07 to i64
  %136 = getelementptr inbounds [172800 x [3 x float]], [172800 x [3 x float]]* %8, i64 0, i64 %135
  %137 = sext i32 %.08 to i64
  %138 = getelementptr inbounds [3 x float], [3 x float]* %136, i64 0, i64 %137
  store float %134, float* %138, align 4
  br label %139

; <label>:139:                                    ; preds = %123
  %140 = add nsw i32 %.08, 1
  br label %121

; <label>:141:                                    ; preds = %121
  br label %142

; <label>:142:                                    ; preds = %141
  %143 = add nsw i32 %.07, 1
  br label %118

; <label>:144:                                    ; preds = %118
  br label %145

; <label>:145:                                    ; preds = %165, %144
  %.01 = phi i32 [ 0, %144 ], [ %166, %165 ]
  %146 = icmp slt i32 %.01, 172800
  br i1 %146, label %147, label %167

; <label>:147:                                    ; preds = %145
  br label %148

; <label>:148:                                    ; preds = %162, %147
  %.0 = phi i32 [ 0, %147 ], [ %163, %162 ]
  %149 = icmp slt i32 %.0, 3
  br i1 %149, label %150, label %164

; <label>:150:                                    ; preds = %148
  %151 = sext i32 %.01 to i64
  %152 = getelementptr inbounds [172800 x [3 x float]], [172800 x [3 x float]]* %8, i64 0, i64 %151
  %153 = sext i32 %.0 to i64
  %154 = getelementptr inbounds [3 x float], [3 x float]* %152, i64 0, i64 %153
  %155 = load float, float* %154, align 4
  %156 = call float @fmin(float %155, float 2.550000e+02)
  %157 = fptoui float %156 to i8
  %158 = sext i32 %.01 to i64
  %159 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %1, i64 %158
  %160 = sext i32 %.0 to i64
  %161 = getelementptr inbounds [3 x i8], [2 x [3 x i8]]* %159, i64 0, i64 %160
  store i8 %157, i8* %161, align 1
  br label %162

; <label>:162:                                    ; preds = %150
  %163 = add nsw i32 %.0, 1
  br label %148

; <label>:164:                                    ; preds = %148
  br label %165

; <label>:165:                                    ; preds = %164
  %166 = add nsw i32 %.01, 1
  br label %145

; <label>:167:                                    ; preds = %145
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @write_bmp(i8*, i8*) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca [54 x i8], align 16
  %6 = alloca %struct._IO_FILE*, align 8
  %7 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %8 = bitcast [54 x i8]* %5 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %8, i8* getelementptr inbounds ([54 x i8], [54 x i8]* @write_bmp.header, i32 0, i32 0), i64 54, i32 16, i1 false)
  %9 = getelementptr inbounds [54 x i8], [54 x i8]* %5, i64 0, i64 18
  %10 = bitcast i8* %9 to i32*
  store i32 360, i32* %10, align 2
  %11 = getelementptr inbounds [54 x i8], [54 x i8]* %5, i64 0, i64 22
  %12 = bitcast i8* %11 to i32*
  store i32 480, i32* %12, align 2
  %13 = load i8*, i8** %3, align 8
  %14 = call %struct._IO_FILE* @fopen(i8* %13, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0))
  store %struct._IO_FILE* %14, %struct._IO_FILE** %6, align 8
  %15 = load %struct._IO_FILE*, %struct._IO_FILE** %6, align 8
  %16 = icmp ne %struct._IO_FILE* %15, null
  br i1 %16, label %20, label %17

; <label>:17:                                     ; preds = %2
  %18 = load i8*, i8** %3, align 8
  %19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.2, i32 0, i32 0), i8* %18)
  call void @exit(i32 1) #5
  unreachable

; <label>:20:                                     ; preds = %2
  %21 = getelementptr inbounds [54 x i8], [54 x i8]* %5, i32 0, i32 0
  %22 = load %struct._IO_FILE*, %struct._IO_FILE** %6, align 8
  %23 = call i64 @fwrite(i8* %21, i64 1, i64 54, %struct._IO_FILE* %22)
  store i32 518400, i32* %7, align 4
  %24 = load i8*, i8** %4, align 8
  %25 = load i32, i32* %7, align 4
  %26 = sext i32 %25 to i64
  %27 = load %struct._IO_FILE*, %struct._IO_FILE** %6, align 8
  %28 = call i64 @fwrite(i8* %24, i64 1, i64 %26, %struct._IO_FILE* %27)
  %29 = load %struct._IO_FILE*, %struct._IO_FILE** %6, align 8
  %30 = call i32 @fclose(%struct._IO_FILE* %29)
  ret void
}

; Function Attrs: noinline nounwind uwtable
define i32 @validate_result(i8*, i8*, i32) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca [518400 x i8], align 16
  %9 = alloca [518400 x i8], align 16
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  store i8* %0, i8** %5, align 8
  store i8* %1, i8** %6, align 8
  store i32 %2, i32* %7, align 4
  %16 = load i8*, i8** %6, align 8
  %17 = getelementptr inbounds [518400 x i8], [518400 x i8]* %8, i32 0, i32 0
  call void @read_bmp(i8* %16, i8* %17)
  %18 = load i8*, i8** %5, align 8
  %19 = getelementptr inbounds [518400 x i8], [518400 x i8]* %9, i32 0, i32 0
  call void @read_bmp(i8* %18, i8* %19)
  store i32 0, i32* %10, align 4
  store i32 0, i32* %11, align 4
  store i32 0, i32* %12, align 4
  br label %20

; <label>:20:                                     ; preds = %72, %3
  %21 = load i32, i32* %12, align 4
  %22 = icmp slt i32 %21, 518400
  br i1 %22, label %23, label %75

; <label>:23:                                     ; preds = %20
  %24 = load i32, i32* %12, align 4
  %25 = sdiv i32 %24, 3
  %26 = srem i32 %25, 360
  store i32 %26, i32* %13, align 4
  %27 = load i32, i32* %12, align 4
  %28 = sdiv i32 %27, 3
  %29 = sdiv i32 %28, 360
  store i32 %29, i32* %14, align 4
  %30 = load i32, i32* %7, align 4
  %31 = icmp ne i32 %30, 0
  br i1 %31, label %32, label %45

; <label>:32:                                     ; preds = %23
  %33 = load i32, i32* %13, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %44, label %35

; <label>:35:                                     ; preds = %32
  %36 = load i32, i32* %14, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %44, label %38

; <label>:38:                                     ; preds = %35
  %39 = load i32, i32* %13, align 4
  %40 = icmp eq i32 %39, 359
  br i1 %40, label %44, label %41

; <label>:41:                                     ; preds = %38
  %42 = load i32, i32* %14, align 4
  %43 = icmp eq i32 %42, 479
  br i1 %43, label %44, label %45

; <label>:44:                                     ; preds = %41, %38, %35, %32
  br label %72

; <label>:45:                                     ; preds = %41, %23
  %46 = getelementptr inbounds [518400 x i8], [518400 x i8]* %8, i32 0, i32 0
  %47 = load i32, i32* %12, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds i8, i8* %46, i64 %48
  %50 = load i8, i8* %49, align 1
  %51 = zext i8 %50 to i32
  %52 = getelementptr inbounds [518400 x i8], [518400 x i8]* %9, i32 0, i32 0
  %53 = load i32, i32* %12, align 4
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds i8, i8* %52, i64 %54
  %56 = load i8, i8* %55, align 1
  %57 = zext i8 %56 to i32
  %58 = sub nsw i32 %51, %57
  %59 = call i32 @abs(i32 %58) #6
  store i32 %59, i32* %15, align 4
  %60 = load i32, i32* %15, align 4
  %61 = icmp sgt i32 %60, 0
  br i1 %61, label %62, label %71

; <label>:62:                                     ; preds = %45
  %63 = load i32, i32* %11, align 4
  %64 = add nsw i32 %63, 1
  store i32 %64, i32* %11, align 4
  %65 = load i32, i32* %15, align 4
  %66 = load i32, i32* %10, align 4
  %67 = icmp sgt i32 %65, %66
  br i1 %67, label %68, label %70

; <label>:68:                                     ; preds = %62
  %69 = load i32, i32* %15, align 4
  store i32 %69, i32* %10, align 4
  br label %70

; <label>:70:                                     ; preds = %68, %62
  br label %71

; <label>:71:                                     ; preds = %70, %45
  br label %72

; <label>:72:                                     ; preds = %71, %44
  %73 = load i32, i32* %12, align 4
  %74 = add nsw i32 %73, 1
  store i32 %74, i32* %12, align 4
  br label %20

; <label>:75:                                     ; preds = %20
  %76 = load i32, i32* %11, align 4
  %77 = icmp sgt i32 %76, 0
  br i1 %77, label %78, label %82

; <label>:78:                                     ; preds = %75
  %79 = load i32, i32* %11, align 4
  %80 = load i32, i32* %10, align 4
  %81 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.8, i32 0, i32 0), i32 %79, i32 %80)
  store i32 0, i32* %4, align 4
  br label %84

; <label>:82:                                     ; preds = %75
  %83 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.9, i32 0, i32 0))
  store i32 1, i32* %4, align 4
  br label %84

; <label>:84:                                     ; preds = %82, %78
  %85 = load i32, i32* %4, align 4
  ret i32 %85
}

declare float @fmin(float, float) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #4

declare %struct._IO_FILE* @fopen(i8*, i8*) #2

declare i64 @fwrite(i8*, i64, i64, %struct._IO_FILE*) #2

declare i32 @fclose(%struct._IO_FILE*) #2

declare i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #2

; Function Attrs: noinline nounwind uwtable
define void @vectorized_sharpen([2 x [3 x i8]]*, [2 x [3 x i8]]*) #0 {
  %3 = alloca [86400 x [2 x float]], align 16
  %4 = alloca [86400 x [2 x float]], align 16
  %5 = alloca [86400 x [2 x float]], align 16
  %6 = alloca [86400 x [2 x float]], align 16
  %7 = alloca [86400 x [2 x float]], align 16
  %8 = alloca [86400 x [2 x [3 x float]]], align 16
  br label %9

; <label>:9:                                      ; preds = %.split13.split, %2
  %.02 = phi i32 [ 0, %2 ], [ %39, %.split13.split ]
  %10 = icmp slt i32 %.02, 86400
  br i1 %10, label %11, label %40

; <label>:11:                                     ; preds = %9
  br label %.split12

.split12:                                         ; preds = %38, %11
  %vectPhi_6 = phi i32 [ 0, %11 ], [ %v_step6, %38 ]
  %v_icmp_6 = icmp slt i32 %vectPhi_6, 2
  br i1 %v_icmp_6, label %.split12.split, label %.split13

.split12.split:                                   ; preds = %.split12
  %12 = sext i32 %.02 to i64
  %13 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %12
  %v_idx_ext_0 = sext i32 %vectPhi_6 to i64
  %v_access_0 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %13, i64 0, i64 %v_idx_ext_0
  %14 = getelementptr inbounds [3 x i8], [3 x i8]* %v_access_0, i64 0, i64 0
  %15 = load i8, i8* %14, align 1
  %16 = zext i8 %15 to i32
  %17 = sitofp i32 %16 to double
  %18 = fmul double 1.000000e-01, %17
  %19 = sext i32 %.02 to i64
  %20 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %19
  %v_idx_ext_1 = sext i32 %vectPhi_6 to i64
  %v_access_1 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %20, i64 0, i64 %v_idx_ext_1
  %21 = getelementptr inbounds [3 x i8], [3 x i8]* %v_access_1, i64 0, i64 1
  %22 = load i8, i8* %21, align 1
  %23 = zext i8 %22 to i32
  %24 = sitofp i32 %23 to double
  %25 = fmul double 6.000000e-01, %24
  %26 = fadd double %18, %25
  %27 = sext i32 %.02 to i64
  %28 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %27
  %v_idx_ext_2 = sext i32 %vectPhi_6 to i64
  %v_access_2 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %28, i64 0, i64 %v_idx_ext_2
  %29 = getelementptr inbounds [3 x i8], [3 x i8]* %v_access_2, i64 0, i64 2
  %30 = load i8, i8* %29, align 1
  %31 = zext i8 %30 to i32
  %32 = sitofp i32 %31 to double
  %33 = fmul double 3.000000e-01, %32
  %34 = fadd double %26, %33
  %35 = fptrunc double %34 to float
  %36 = sext i32 %.02 to i64
  %37 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %36
  %v_idx_ext_3 = sext i32 %vectPhi_6 to i64
  %v_access_3 = getelementptr inbounds [2 x float], [2 x float]* %37, i64 0, i64 %v_idx_ext_3
  store float %35, float* %v_access_3, align 4
  br label %38

; <label>:38:                                     ; preds = %.split12.split
  %v_step6 = add nsw i32 %vectPhi_6, 1
  br label %.split12

.split13:                                         ; preds = %.split12
  br label %.split13.split

.split13.split:                                   ; preds = %.split13
  %39 = add nsw i32 %.02, 1
  br label %9

; <label>:40:                                     ; preds = %9
  br label %41

; <label>:41:                                     ; preds = %.split11.split, %40
  %.03 = phi i32 [ 180, %40 ], [ %61, %.split11.split ]
  %42 = icmp slt i32 %.03, 86220
  br i1 %42, label %43, label %62

; <label>:43:                                     ; preds = %41
  br label %.split10

.split10:                                         ; preds = %60, %43
  %vectPhi_5 = phi i32 [ 0, %43 ], [ %v_step5, %60 ]
  %v_icmp_5 = icmp slt i32 %vectPhi_5, 2
  br i1 %v_icmp_5, label %.split10.split, label %.split11

.split10.split:                                   ; preds = %.split10
  %44 = sub nsw i32 %.03, 360
  %45 = sext i32 %44 to i64
  %46 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %45
  %47 = load float, [2 x float]* %46, align 4
  %48 = sext i32 %.03 to i64
  %49 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %48
  %v_idx_ext_4 = sext i32 %vectPhi_5 to i64
  %v_access_4 = getelementptr inbounds [2 x float], [2 x float]* %49, i64 0, i64 %v_idx_ext_4
  %50 = load float, float* %v_access_4, align 4
  %51 = fadd float %47, %50
  %52 = add nsw i32 %.03, 360
  %53 = sext i32 %52 to i64
  %54 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %53
  %55 = load float, [2 x float]* %54, align 4
  %56 = fadd float %51, %55
  %57 = fdiv float %56, 3.000000e+00
  %58 = sext i32 %.03 to i64
  %59 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %58
  %v_idx_ext_5 = sext i32 %vectPhi_5 to i64
  %v_access_5 = getelementptr inbounds [2 x float], [2 x float]* %59, i64 0, i64 %v_idx_ext_5
  store float %57, float* %v_access_5, align 4
  br label %60

; <label>:60:                                     ; preds = %.split10.split
  %v_step5 = add nsw i32 %vectPhi_5, 1
  br label %.split10

.split11:                                         ; preds = %.split10
  br label %.split11.split

.split11.split:                                   ; preds = %.split11
  %61 = add nsw i32 %.03, 1
  br label %41

; <label>:62:                                     ; preds = %41
  br label %63

; <label>:63:                                     ; preds = %.split9.split, %62
  %.04 = phi i32 [ 180, %62 ], [ %83, %.split9.split ]
  %64 = icmp slt i32 %.04, 86220
  br i1 %64, label %65, label %84

; <label>:65:                                     ; preds = %63
  br label %.split8

.split8:                                          ; preds = %82, %65
  %vectPhi_4 = phi i32 [ 0, %65 ], [ %v_step4, %82 ]
  %v_icmp_4 = icmp slt i32 %vectPhi_4, 2
  br i1 %v_icmp_4, label %.split8.split, label %.split9

.split8.split:                                    ; preds = %.split8
  %66 = sub nsw i32 %.04, 1
  %67 = sext i32 %66 to i64
  %68 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %67
  %69 = load float, [2 x float]* %68, align 4
  %70 = sext i32 %.04 to i64
  %71 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %70
  %v_idx_ext_6 = sext i32 %vectPhi_4 to i64
  %v_access_6 = getelementptr inbounds [2 x float], [2 x float]* %71, i64 0, i64 %v_idx_ext_6
  %72 = load float, float* %v_access_6, align 4
  %73 = fadd float %69, %72
  %74 = add nsw i32 %.04, 1
  %75 = sext i32 %74 to i64
  %76 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %75
  %77 = load float, [2 x float]* %76, align 4
  %78 = fadd float %73, %77
  %79 = fdiv float %78, 3.000000e+00
  %80 = sext i32 %.04 to i64
  %81 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %80
  %v_idx_ext_7 = sext i32 %vectPhi_4 to i64
  %v_access_7 = getelementptr inbounds [2 x float], [2 x float]* %81, i64 0, i64 %v_idx_ext_7
  store float %79, float* %v_access_7, align 4
  br label %82

; <label>:82:                                     ; preds = %.split8.split
  %v_step4 = add nsw i32 %vectPhi_4, 1
  br label %.split8

.split9:                                          ; preds = %.split8
  br label %.split9.split

.split9.split:                                    ; preds = %.split9
  %83 = add nsw i32 %.04, 1
  br label %63

; <label>:84:                                     ; preds = %63
  br label %85

; <label>:85:                                     ; preds = %.split7.split, %84
  %.05 = phi i32 [ 0, %84 ], [ %100, %.split7.split ]
  %86 = icmp slt i32 %.05, 86400
  br i1 %86, label %87, label %101

; <label>:87:                                     ; preds = %85
  br label %.split6

.split6:                                          ; preds = %99, %87
  %vectPhi_3 = phi i32 [ 0, %87 ], [ %v_step3, %99 ]
  %v_icmp_3 = icmp slt i32 %vectPhi_3, 2
  br i1 %v_icmp_3, label %.split6.split, label %.split7

.split6.split:                                    ; preds = %.split6
  %88 = sext i32 %.05 to i64
  %89 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %88
  %v_idx_ext_8 = sext i32 %vectPhi_3 to i64
  %v_access_8 = getelementptr inbounds [2 x float], [2 x float]* %89, i64 0, i64 %v_idx_ext_8
  %90 = load float, float* %v_access_8, align 4
  %91 = fmul float 2.000000e+00, %90
  %92 = sext i32 %.05 to i64
  %93 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %92
  %v_idx_ext_9 = sext i32 %vectPhi_3 to i64
  %v_access_9 = getelementptr inbounds [2 x float], [2 x float]* %93, i64 0, i64 %v_idx_ext_9
  %94 = load float, float* %v_access_9, align 4
  %95 = fsub float %91, %94
  %96 = call float @fabs(float %95)
  %97 = sext i32 %.05 to i64
  %98 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %97
  %v_idx_ext_10 = sext i32 %vectPhi_3 to i64
  %v_access_10 = getelementptr inbounds [2 x float], [2 x float]* %98, i64 0, i64 %v_idx_ext_10
  store float %96, float* %v_access_10, align 4
  br label %99

; <label>:99:                                     ; preds = %.split6.split
  %v_step3 = add nsw i32 %vectPhi_3, 1
  br label %.split6

.split7:                                          ; preds = %.split6
  br label %.split7.split

.split7.split:                                    ; preds = %.split7
  %100 = add nsw i32 %.05, 1
  br label %85

; <label>:101:                                    ; preds = %85
  br label %102

; <label>:102:                                    ; preds = %.split5.split, %101
  %.06 = phi i32 [ 0, %101 ], [ %116, %.split5.split ]
  %103 = icmp slt i32 %.06, 86400
  br i1 %103, label %104, label %117

; <label>:104:                                    ; preds = %102
  br label %.split4

.split4:                                          ; preds = %115, %104
  %vectPhi_2 = phi i32 [ 0, %104 ], [ %v_step2, %115 ]
  %v_icmp_2 = icmp slt i32 %vectPhi_2, 2
  br i1 %v_icmp_2, label %.split4.split, label %.split5

.split4.split:                                    ; preds = %.split4
  %105 = sext i32 %.06 to i64
  %106 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %105
  %v_idx_ext_11 = sext i32 %vectPhi_2 to i64
  %v_access_11 = getelementptr inbounds [2 x float], [2 x float]* %106, i64 0, i64 %v_idx_ext_11
  %107 = load float, float* %v_access_11, align 4
  %108 = sext i32 %.06 to i64
  %109 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %108
  %v_idx_ext_12 = sext i32 %vectPhi_2 to i64
  %v_access_12 = getelementptr inbounds [2 x float], [2 x float]* %109, i64 0, i64 %v_idx_ext_12
  %110 = load float, float* %v_access_12, align 4
  %111 = fadd float %110, 1.000000e+00
  %112 = fdiv float %107, %111
  %113 = sext i32 %.06 to i64
  %114 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %7, i64 0, i64 %113
  %v_idx_ext_13 = sext i32 %vectPhi_2 to i64
  %v_access_13 = getelementptr inbounds [2 x float], [2 x float]* %114, i64 0, i64 %v_idx_ext_13
  store float %112, float* %v_access_13, align 4
  br label %115

; <label>:115:                                    ; preds = %.split4.split
  %v_step2 = add nsw i32 %vectPhi_2, 1
  br label %.split4

.split5:                                          ; preds = %.split4
  br label %.split5.split

.split5.split:                                    ; preds = %.split5
  %116 = add nsw i32 %.06, 1
  br label %102

; <label>:117:                                    ; preds = %102
  br label %118

; <label>:118:                                    ; preds = %.split3.split, %117
  %.07 = phi i32 [ 0, %117 ], [ %143, %.split3.split ]
  %119 = icmp slt i32 %.07, 86400
  br i1 %119, label %120, label %144

; <label>:120:                                    ; preds = %118
  br label %.split2

.split2:                                          ; preds = %142, %120
  %vectPhi_1 = phi i32 [ 0, %120 ], [ %v_step1, %142 ]
  %v_icmp_1 = icmp slt i32 %vectPhi_1, 2
  br i1 %v_icmp_1, label %.split2.split, label %.split3

.split2.split:                                    ; preds = %.split2
  br label %121

; <label>:121:                                    ; preds = %139, %.split2.split
  %.08 = phi i32 [ 0, %.split2.split ], [ %140, %139 ]
  %122 = icmp slt i32 %.08, 3
  br i1 %122, label %123, label %141

; <label>:123:                                    ; preds = %121
  %124 = sext i32 %.07 to i64
  %125 = getelementptr [86400 x [2 x float]], [86400 x [2 x float]]* %7, i64 0, i64 %124
  %v_idx_ext_14 = sext i32 %vectPhi_1 to i64
  %v_access_14 = getelementptr inbounds [2 x float], [2 x float]* %125, i64 0, i64 %v_idx_ext_14
  %126 = load float, float* %v_access_14, align 4
  %127 = sext i32 %.07 to i64
  %128 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %127
  %v_idx_ext_15 = sext i32 %vectPhi_1 to i64
  %v_access_15 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %128, i64 0, i64 %v_idx_ext_15
  %129 = sext i32 %.08 to i64
  %130 = getelementptr inbounds [3 x i8], [3 x i8]* %v_access_15, i64 0, i64 %129
  %131 = load i8, i8* %130, align 1
  %132 = zext i8 %131 to i32
  %133 = sitofp i32 %132 to float
  %134 = fmul float %126, %133
  %135 = sext i32 %.07 to i64
  %136 = getelementptr [86400 x [2 x [3 x float]]], [86400 x [2 x [3 x float]]]* %8, i64 0, i64 %135
  %v_idx_ext_16 = sext i32 %vectPhi_1 to i64
  %v_access_16 = getelementptr inbounds [2 x [3 x float]], [2 x [3 x float]]* %136, i64 0, i64 %v_idx_ext_16
  %137 = sext i32 %.08 to i64
  %138 = getelementptr inbounds [3 x float], [3 x float]* %v_access_16, i64 0, i64 %137
  store float %134, float* %138, align 4
  br label %139

; <label>:139:                                    ; preds = %123
  %140 = add nsw i32 %.08, 1
  br label %121

; <label>:141:                                    ; preds = %121
  br label %142

; <label>:142:                                    ; preds = %141
  %v_step1 = add nsw i32 %vectPhi_1, 1
  br label %.split2

.split3:                                          ; preds = %.split2
  br label %.split3.split

.split3.split:                                    ; preds = %.split3
  %143 = add nsw i32 %.07, 1
  br label %118

; <label>:144:                                    ; preds = %118
  br label %145

; <label>:145:                                    ; preds = %.split1.split, %144
  %.01 = phi i32 [ 0, %144 ], [ %166, %.split1.split ]
  %146 = icmp slt i32 %.01, 86400
  br i1 %146, label %147, label %167

; <label>:147:                                    ; preds = %145
  br label %.split

.split:                                           ; preds = %165, %147
  %vectPhi_0 = phi i32 [ 0, %147 ], [ %v_step0, %165 ]
  %v_icmp_0 = icmp slt i32 %vectPhi_0, 2
  br i1 %v_icmp_0, label %.split.split, label %.split1

.split.split:                                     ; preds = %.split
  br label %148

; <label>:148:                                    ; preds = %162, %.split.split
  %.0 = phi i32 [ 0, %.split.split ], [ %163, %162 ]
  %149 = icmp slt i32 %.0, 3
  br i1 %149, label %150, label %164

; <label>:150:                                    ; preds = %148
  %151 = sext i32 %.01 to i64
  %152 = getelementptr [86400 x [2 x [3 x float]]], [86400 x [2 x [3 x float]]]* %8, i64 0, i64 %151
  %v_idx_ext_17 = sext i32 %vectPhi_0 to i64
  %v_access_17 = getelementptr inbounds [2 x [3 x float]], [2 x [3 x float]]* %152, i64 0, i64 %v_idx_ext_17
  %153 = sext i32 %.0 to i64
  %154 = getelementptr inbounds [3 x float], [3 x float]* %v_access_17, i64 0, i64 %153
  %155 = load float, float* %154, align 4
  %156 = call float @fmin(float %155, float 2.550000e+02)
  %157 = fptoui float %156 to i8
  %158 = sext i32 %.01 to i64
  %159 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %1, i64 %158
  %v_idx_ext_18 = sext i32 %vectPhi_0 to i64
  %v_access_18 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %159, i64 0, i64 %v_idx_ext_18
  %160 = sext i32 %.0 to i64
  %161 = getelementptr inbounds [3 x i8], [3 x i8]* %v_access_18, i64 0, i64 %160
  store i8 %157, i8* %161, align 1
  br label %162

; <label>:162:                                    ; preds = %150
  %163 = add nsw i32 %.0, 1
  br label %148

; <label>:164:                                    ; preds = %148
  br label %165

; <label>:165:                                    ; preds = %164
  %v_step0 = add nsw i32 %vectPhi_0, 1
  br label %.split

.split1:                                          ; preds = %.split
  br label %.split1.split

.split1.split:                                    ; preds = %.split1
  %166 = add nsw i32 %.01, 1
  br label %145

; <label>:167:                                    ; preds = %145
  ret void
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline nounwind readnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { noreturn nounwind }
attributes #6 = { nounwind readnone }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (tags/RELEASE_400/final)"}
