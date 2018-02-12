; ModuleID = '6_sharpen_linearized_vectorized_1.c'
source_filename = "6_sharpen_linearized_vectorized_1.c"
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
define float @fmin(float, float) #0 {
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  store float %0, float* %3, align 4
  store float %1, float* %4, align 4
  %5 = load float, float* %3, align 4
  %6 = load float, float* %3, align 4
  %7 = fmul float %5, %6
  %8 = load float, float* %3, align 4
  %9 = fadd float %7, %8
  ret float %9
}

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
  %6 = alloca [86400 x [6 x i8]], align 16
  %7 = alloca [86400 x [6 x i8]], align 16
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
  %24 = getelementptr inbounds [86400 x [6 x i8]], [86400 x [6 x i8]]* %6, i32 0, i32 0
  %25 = bitcast [6 x i8]* %24 to i8*
  call void @read_bmp(i8* %23, i8* %25)
  %26 = getelementptr inbounds [86400 x [6 x i8]], [86400 x [6 x i8]]* %6, i32 0, i32 0
  %27 = getelementptr inbounds [86400 x [6 x i8]], [86400 x [6 x i8]]* %7, i32 0, i32 0
  call void @sharpen([6 x i8]* %26, [6 x i8]* %27)
  %28 = load i8*, i8** %9, align 8
  %29 = getelementptr inbounds [86400 x [6 x i8]], [86400 x [6 x i8]]* %7, i32 0, i32 0
  %30 = bitcast [6 x i8]* %29 to i8*
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
define void @sharpen([6 x i8]*, [6 x i8]*) #0 {
  %3 = alloca [6 x i8]*, align 8
  %4 = alloca [6 x i8]*, align 8
  %5 = alloca [86400 x [2 x float]], align 16
  %6 = alloca [86400 x [2 x float]], align 16
  %7 = alloca [86400 x [2 x float]], align 16
  %8 = alloca [86400 x [2 x float]], align 16
  %9 = alloca [86400 x [2 x float]], align 16
  %10 = alloca [86400 x [6 x float]], align 16
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  %24 = alloca i32, align 4
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  store [6 x i8]* %0, [6 x i8]** %3, align 8
  store [6 x i8]* %1, [6 x i8]** %4, align 8
  store i32 0, i32* %11, align 4
  br label %27

; <label>:27:                                     ; preds = %87, %2
  %28 = load i32, i32* %11, align 4
  %29 = icmp slt i32 %28, 86400
  br i1 %29, label %30, label %90

; <label>:30:                                     ; preds = %27
  store i32 0, i32* %12, align 4
  br label %31

; <label>:31:                                     ; preds = %83, %30
  %32 = load i32, i32* %12, align 4
  %33 = icmp slt i32 %32, 2
  br i1 %33, label %34, label %86

; <label>:34:                                     ; preds = %31
  %35 = load [6 x i8]*, [6 x i8]** %3, align 8
  %36 = load i32, i32* %11, align 4
  %37 = sext i32 %36 to i64
  %38 = getelementptr inbounds [6 x i8], [6 x i8]* %35, i64 %37
  %39 = load i32, i32* %12, align 4
  %40 = mul nsw i32 3, %39
  %41 = add nsw i32 %40, 0
  %42 = sext i32 %41 to i64
  %43 = getelementptr inbounds [6 x i8], [6 x i8]* %38, i64 0, i64 %42
  %44 = load i8, i8* %43, align 1
  %45 = zext i8 %44 to i32
  %46 = sitofp i32 %45 to double
  %47 = fmul double 1.000000e-01, %46
  %48 = load [6 x i8]*, [6 x i8]** %3, align 8
  %49 = load i32, i32* %11, align 4
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds [6 x i8], [6 x i8]* %48, i64 %50
  %52 = load i32, i32* %12, align 4
  %53 = mul nsw i32 3, %52
  %54 = add nsw i32 %53, 1
  %55 = sext i32 %54 to i64
  %56 = getelementptr inbounds [6 x i8], [6 x i8]* %51, i64 0, i64 %55
  %57 = load i8, i8* %56, align 1
  %58 = zext i8 %57 to i32
  %59 = sitofp i32 %58 to double
  %60 = fmul double 6.000000e-01, %59
  %61 = fadd double %47, %60
  %62 = load [6 x i8]*, [6 x i8]** %3, align 8
  %63 = load i32, i32* %11, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds [6 x i8], [6 x i8]* %62, i64 %64
  %66 = load i32, i32* %12, align 4
  %67 = mul nsw i32 3, %66
  %68 = add nsw i32 %67, 2
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds [6 x i8], [6 x i8]* %65, i64 0, i64 %69
  %71 = load i8, i8* %70, align 1
  %72 = zext i8 %71 to i32
  %73 = sitofp i32 %72 to double
  %74 = fmul double 3.000000e-01, %73
  %75 = fadd double %61, %74
  %76 = fptrunc double %75 to float
  %77 = load i32, i32* %11, align 4
  %78 = sext i32 %77 to i64
  %79 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %78
  %80 = load i32, i32* %12, align 4
  %81 = sext i32 %80 to i64
  %82 = getelementptr inbounds [2 x float], [2 x float]* %79, i64 0, i64 %81
  store float %76, float* %82, align 4
  br label %83

; <label>:83:                                     ; preds = %34
  %84 = load i32, i32* %12, align 4
  %85 = add nsw i32 %84, 1
  store i32 %85, i32* %12, align 4
  br label %31

; <label>:86:                                     ; preds = %31
  br label %87

; <label>:87:                                     ; preds = %86
  %88 = load i32, i32* %11, align 4
  %89 = add nsw i32 %88, 1
  store i32 %89, i32* %11, align 4
  br label %27

; <label>:90:                                     ; preds = %27
  store i32 180, i32* %13, align 4
  br label %91

; <label>:91:                                     ; preds = %135, %90
  %92 = load i32, i32* %13, align 4
  %93 = icmp slt i32 %92, 86220
  br i1 %93, label %94, label %138

; <label>:94:                                     ; preds = %91
  store i32 0, i32* %14, align 4
  br label %95

; <label>:95:                                     ; preds = %131, %94
  %96 = load i32, i32* %14, align 4
  %97 = icmp slt i32 %96, 2
  br i1 %97, label %98, label %134

; <label>:98:                                     ; preds = %95
  %99 = load i32, i32* %13, align 4
  %100 = sub nsw i32 %99, 360
  %101 = sext i32 %100 to i64
  %102 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %101
  %103 = load i32, i32* %14, align 4
  %104 = sext i32 %103 to i64
  %105 = getelementptr inbounds [2 x float], [2 x float]* %102, i64 0, i64 %104
  %106 = load float, float* %105, align 4
  %107 = load i32, i32* %13, align 4
  %108 = sext i32 %107 to i64
  %109 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %108
  %110 = load i32, i32* %14, align 4
  %111 = sext i32 %110 to i64
  %112 = getelementptr inbounds [2 x float], [2 x float]* %109, i64 0, i64 %111
  %113 = load float, float* %112, align 4
  %114 = fadd float %106, %113
  %115 = load i32, i32* %13, align 4
  %116 = add nsw i32 %115, 360
  %117 = sext i32 %116 to i64
  %118 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %117
  %119 = load i32, i32* %14, align 4
  %120 = sext i32 %119 to i64
  %121 = getelementptr inbounds [2 x float], [2 x float]* %118, i64 0, i64 %120
  %122 = load float, float* %121, align 4
  %123 = fadd float %114, %122
  %124 = fdiv float %123, 3.000000e+00
  %125 = load i32, i32* %13, align 4
  %126 = sext i32 %125 to i64
  %127 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %126
  %128 = load i32, i32* %14, align 4
  %129 = sext i32 %128 to i64
  %130 = getelementptr inbounds [2 x float], [2 x float]* %127, i64 0, i64 %129
  store float %124, float* %130, align 4
  br label %131

; <label>:131:                                    ; preds = %98
  %132 = load i32, i32* %14, align 4
  %133 = add nsw i32 %132, 1
  store i32 %133, i32* %14, align 4
  br label %95

; <label>:134:                                    ; preds = %95
  br label %135

; <label>:135:                                    ; preds = %134
  %136 = load i32, i32* %13, align 4
  %137 = add nsw i32 %136, 1
  store i32 %137, i32* %13, align 4
  br label %91

; <label>:138:                                    ; preds = %91
  store i32 180, i32* %15, align 4
  br label %139

; <label>:139:                                    ; preds = %183, %138
  %140 = load i32, i32* %15, align 4
  %141 = icmp slt i32 %140, 86220
  br i1 %141, label %142, label %186

; <label>:142:                                    ; preds = %139
  store i32 0, i32* %16, align 4
  br label %143

; <label>:143:                                    ; preds = %179, %142
  %144 = load i32, i32* %16, align 4
  %145 = icmp slt i32 %144, 2
  br i1 %145, label %146, label %182

; <label>:146:                                    ; preds = %143
  %147 = load i32, i32* %15, align 4
  %148 = sub nsw i32 %147, 1
  %149 = sext i32 %148 to i64
  %150 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %149
  %151 = load i32, i32* %16, align 4
  %152 = sext i32 %151 to i64
  %153 = getelementptr inbounds [2 x float], [2 x float]* %150, i64 0, i64 %152
  %154 = load float, float* %153, align 4
  %155 = load i32, i32* %15, align 4
  %156 = sext i32 %155 to i64
  %157 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %156
  %158 = load i32, i32* %16, align 4
  %159 = sext i32 %158 to i64
  %160 = getelementptr inbounds [2 x float], [2 x float]* %157, i64 0, i64 %159
  %161 = load float, float* %160, align 4
  %162 = fadd float %154, %161
  %163 = load i32, i32* %15, align 4
  %164 = add nsw i32 %163, 1
  %165 = sext i32 %164 to i64
  %166 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %165
  %167 = load i32, i32* %16, align 4
  %168 = sext i32 %167 to i64
  %169 = getelementptr inbounds [2 x float], [2 x float]* %166, i64 0, i64 %168
  %170 = load float, float* %169, align 4
  %171 = fadd float %162, %170
  %172 = fdiv float %171, 3.000000e+00
  %173 = load i32, i32* %15, align 4
  %174 = sext i32 %173 to i64
  %175 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %7, i64 0, i64 %174
  %176 = load i32, i32* %16, align 4
  %177 = sext i32 %176 to i64
  %178 = getelementptr inbounds [2 x float], [2 x float]* %175, i64 0, i64 %177
  store float %172, float* %178, align 4
  br label %179

; <label>:179:                                    ; preds = %146
  %180 = load i32, i32* %16, align 4
  %181 = add nsw i32 %180, 1
  store i32 %181, i32* %16, align 4
  br label %143

; <label>:182:                                    ; preds = %143
  br label %183

; <label>:183:                                    ; preds = %182
  %184 = load i32, i32* %15, align 4
  %185 = add nsw i32 %184, 1
  store i32 %185, i32* %15, align 4
  br label %139

; <label>:186:                                    ; preds = %139
  store i32 0, i32* %17, align 4
  br label %187

; <label>:187:                                    ; preds = %222, %186
  %188 = load i32, i32* %17, align 4
  %189 = icmp slt i32 %188, 86400
  br i1 %189, label %190, label %225

; <label>:190:                                    ; preds = %187
  store i32 0, i32* %18, align 4
  br label %191

; <label>:191:                                    ; preds = %218, %190
  %192 = load i32, i32* %18, align 4
  %193 = icmp slt i32 %192, 2
  br i1 %193, label %194, label %221

; <label>:194:                                    ; preds = %191
  %195 = load i32, i32* %17, align 4
  %196 = sext i32 %195 to i64
  %197 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %196
  %198 = load i32, i32* %18, align 4
  %199 = sext i32 %198 to i64
  %200 = getelementptr inbounds [2 x float], [2 x float]* %197, i64 0, i64 %199
  %201 = load float, float* %200, align 4
  %202 = fmul float 2.000000e+00, %201
  %203 = load i32, i32* %17, align 4
  %204 = sext i32 %203 to i64
  %205 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %7, i64 0, i64 %204
  %206 = load i32, i32* %18, align 4
  %207 = sext i32 %206 to i64
  %208 = getelementptr inbounds [2 x float], [2 x float]* %205, i64 0, i64 %207
  %209 = load float, float* %208, align 4
  %210 = fsub float %202, %209
  %211 = call float @fabs(float %210)
  %212 = load i32, i32* %17, align 4
  %213 = sext i32 %212 to i64
  %214 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %8, i64 0, i64 %213
  %215 = load i32, i32* %18, align 4
  %216 = sext i32 %215 to i64
  %217 = getelementptr inbounds [2 x float], [2 x float]* %214, i64 0, i64 %216
  store float %211, float* %217, align 4
  br label %218

; <label>:218:                                    ; preds = %194
  %219 = load i32, i32* %18, align 4
  %220 = add nsw i32 %219, 1
  store i32 %220, i32* %18, align 4
  br label %191

; <label>:221:                                    ; preds = %191
  br label %222

; <label>:222:                                    ; preds = %221
  %223 = load i32, i32* %17, align 4
  %224 = add nsw i32 %223, 1
  store i32 %224, i32* %17, align 4
  br label %187

; <label>:225:                                    ; preds = %187
  store i32 0, i32* %19, align 4
  br label %226

; <label>:226:                                    ; preds = %260, %225
  %227 = load i32, i32* %19, align 4
  %228 = icmp slt i32 %227, 86400
  br i1 %228, label %229, label %263

; <label>:229:                                    ; preds = %226
  store i32 0, i32* %20, align 4
  br label %230

; <label>:230:                                    ; preds = %256, %229
  %231 = load i32, i32* %20, align 4
  %232 = icmp slt i32 %231, 2
  br i1 %232, label %233, label %259

; <label>:233:                                    ; preds = %230
  %234 = load i32, i32* %19, align 4
  %235 = sext i32 %234 to i64
  %236 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %8, i64 0, i64 %235
  %237 = load i32, i32* %20, align 4
  %238 = sext i32 %237 to i64
  %239 = getelementptr inbounds [2 x float], [2 x float]* %236, i64 0, i64 %238
  %240 = load float, float* %239, align 4
  %241 = load i32, i32* %19, align 4
  %242 = sext i32 %241 to i64
  %243 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %242
  %244 = load i32, i32* %20, align 4
  %245 = sext i32 %244 to i64
  %246 = getelementptr inbounds [2 x float], [2 x float]* %243, i64 0, i64 %245
  %247 = load float, float* %246, align 4
  %248 = fadd float %247, 1.000000e+00
  %249 = fdiv float %240, %248
  %250 = load i32, i32* %19, align 4
  %251 = sext i32 %250 to i64
  %252 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %9, i64 0, i64 %251
  %253 = load i32, i32* %20, align 4
  %254 = sext i32 %253 to i64
  %255 = getelementptr inbounds [2 x float], [2 x float]* %252, i64 0, i64 %254
  store float %249, float* %255, align 4
  br label %256

; <label>:256:                                    ; preds = %233
  %257 = load i32, i32* %20, align 4
  %258 = add nsw i32 %257, 1
  store i32 %258, i32* %20, align 4
  br label %230

; <label>:259:                                    ; preds = %230
  br label %260

; <label>:260:                                    ; preds = %259
  %261 = load i32, i32* %19, align 4
  %262 = add nsw i32 %261, 1
  store i32 %262, i32* %19, align 4
  br label %226

; <label>:263:                                    ; preds = %226
  store i32 0, i32* %21, align 4
  br label %264

; <label>:264:                                    ; preds = %314, %263
  %265 = load i32, i32* %21, align 4
  %266 = icmp slt i32 %265, 86400
  br i1 %266, label %267, label %317

; <label>:267:                                    ; preds = %264
  store i32 0, i32* %22, align 4
  br label %268

; <label>:268:                                    ; preds = %310, %267
  %269 = load i32, i32* %22, align 4
  %270 = icmp slt i32 %269, 3
  br i1 %270, label %271, label %313

; <label>:271:                                    ; preds = %268
  store i32 0, i32* %23, align 4
  br label %272

; <label>:272:                                    ; preds = %306, %271
  %273 = load i32, i32* %23, align 4
  %274 = icmp slt i32 %273, 2
  br i1 %274, label %275, label %309

; <label>:275:                                    ; preds = %272
  %276 = load i32, i32* %21, align 4
  %277 = sext i32 %276 to i64
  %278 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %9, i64 0, i64 %277
  %279 = load i32, i32* %23, align 4
  %280 = sext i32 %279 to i64
  %281 = getelementptr inbounds [2 x float], [2 x float]* %278, i64 0, i64 %280
  %282 = load float, float* %281, align 4
  %283 = load [6 x i8]*, [6 x i8]** %3, align 8
  %284 = load i32, i32* %21, align 4
  %285 = sext i32 %284 to i64
  %286 = getelementptr inbounds [6 x i8], [6 x i8]* %283, i64 %285
  %287 = load i32, i32* %22, align 4
  %288 = load i32, i32* %23, align 4
  %289 = mul nsw i32 3, %288
  %290 = add nsw i32 %287, %289
  %291 = sext i32 %290 to i64
  %292 = getelementptr inbounds [6 x i8], [6 x i8]* %286, i64 0, i64 %291
  %293 = load i8, i8* %292, align 1
  %294 = zext i8 %293 to i32
  %295 = sitofp i32 %294 to float
  %296 = fmul float %282, %295
  %297 = load i32, i32* %21, align 4
  %298 = sext i32 %297 to i64
  %299 = getelementptr inbounds [86400 x [6 x float]], [86400 x [6 x float]]* %10, i64 0, i64 %298
  %300 = load i32, i32* %22, align 4
  %301 = load i32, i32* %23, align 4
  %302 = mul nsw i32 3, %301
  %303 = add nsw i32 %300, %302
  %304 = sext i32 %303 to i64
  %305 = getelementptr inbounds [6 x float], [6 x float]* %299, i64 0, i64 %304
  store float %296, float* %305, align 4
  br label %306

; <label>:306:                                    ; preds = %275
  %307 = load i32, i32* %23, align 4
  %308 = add nsw i32 %307, 1
  store i32 %308, i32* %23, align 4
  br label %272

; <label>:309:                                    ; preds = %272
  br label %310

; <label>:310:                                    ; preds = %309
  %311 = load i32, i32* %22, align 4
  %312 = add nsw i32 %311, 1
  store i32 %312, i32* %22, align 4
  br label %268

; <label>:313:                                    ; preds = %268
  br label %314

; <label>:314:                                    ; preds = %313
  %315 = load i32, i32* %21, align 4
  %316 = add nsw i32 %315, 1
  store i32 %316, i32* %21, align 4
  br label %264

; <label>:317:                                    ; preds = %264
  store i32 0, i32* %24, align 4
  br label %318

; <label>:318:                                    ; preds = %360, %317
  %319 = load i32, i32* %24, align 4
  %320 = icmp slt i32 %319, 86400
  br i1 %320, label %321, label %363

; <label>:321:                                    ; preds = %318
  store i32 0, i32* %25, align 4
  br label %322

; <label>:322:                                    ; preds = %356, %321
  %323 = load i32, i32* %25, align 4
  %324 = icmp slt i32 %323, 3
  br i1 %324, label %325, label %359

; <label>:325:                                    ; preds = %322
  store i32 0, i32* %26, align 4
  br label %326

; <label>:326:                                    ; preds = %352, %325
  %327 = load i32, i32* %26, align 4
  %328 = icmp slt i32 %327, 2
  br i1 %328, label %329, label %355

; <label>:329:                                    ; preds = %326
  %330 = load i32, i32* %24, align 4
  %331 = sext i32 %330 to i64
  %332 = getelementptr inbounds [86400 x [6 x float]], [86400 x [6 x float]]* %10, i64 0, i64 %331
  %333 = load i32, i32* %25, align 4
  %334 = load i32, i32* %26, align 4
  %335 = mul nsw i32 3, %334
  %336 = add nsw i32 %333, %335
  %337 = sext i32 %336 to i64
  %338 = getelementptr inbounds [6 x float], [6 x float]* %332, i64 0, i64 %337
  %339 = load float, float* %338, align 4
  %340 = call float @fmin(float %339, float 2.550000e+02)
  %341 = fptoui float %340 to i8
  %342 = load [6 x i8]*, [6 x i8]** %4, align 8
  %343 = load i32, i32* %24, align 4
  %344 = sext i32 %343 to i64
  %345 = getelementptr inbounds [6 x i8], [6 x i8]* %342, i64 %344
  %346 = load i32, i32* %25, align 4
  %347 = load i32, i32* %26, align 4
  %348 = mul nsw i32 3, %347
  %349 = add nsw i32 %346, %348
  %350 = sext i32 %349 to i64
  %351 = getelementptr inbounds [6 x i8], [6 x i8]* %345, i64 0, i64 %350
  store i8 %341, i8* %351, align 1
  br label %352

; <label>:352:                                    ; preds = %329
  %353 = load i32, i32* %26, align 4
  %354 = add nsw i32 %353, 1
  store i32 %354, i32* %26, align 4
  br label %326

; <label>:355:                                    ; preds = %326
  br label %356

; <label>:356:                                    ; preds = %355
  %357 = load i32, i32* %25, align 4
  %358 = add nsw i32 %357, 1
  store i32 %358, i32* %25, align 4
  br label %322

; <label>:359:                                    ; preds = %322
  br label %360

; <label>:360:                                    ; preds = %359
  %361 = load i32, i32* %24, align 4
  %362 = add nsw i32 %361, 1
  store i32 %362, i32* %24, align 4
  br label %318

; <label>:363:                                    ; preds = %318
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

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #4

declare %struct._IO_FILE* @fopen(i8*, i8*) #2

declare i64 @fwrite(i8*, i64, i64, %struct._IO_FILE*) #2

declare i32 @fclose(%struct._IO_FILE*) #2

declare i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #2

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline nounwind readnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { noreturn nounwind }
attributes #6 = { nounwind readnone }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (tags/RELEASE_400/final)"}
