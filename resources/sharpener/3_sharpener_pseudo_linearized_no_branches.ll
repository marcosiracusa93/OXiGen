; ModuleID = '3_sharpener_pseudo_linearized_no_branches.c'
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
  %6 = alloca [2073600 x [3 x i8]], align 16
  %7 = alloca [2073600 x [3 x i8]], align 16
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
  %24 = getelementptr inbounds [2073600 x [3 x i8]], [2073600 x [3 x i8]]* %6, i32 0, i32 0
  %25 = bitcast [3 x i8]* %24 to i8*
  call void @read_bmp(i8* %23, i8* %25)
  %26 = getelementptr inbounds [2073600 x [3 x i8]], [2073600 x [3 x i8]]* %6, i32 0, i32 0
  %27 = getelementptr inbounds [2073600 x [3 x i8]], [2073600 x [3 x i8]]* %7, i32 0, i32 0
  call void @sharpen([3 x i8]* %26, [3 x i8]* %27)
  %28 = load i8*, i8** %9, align 8
  %29 = getelementptr inbounds [2073600 x [3 x i8]], [2073600 x [3 x i8]]* %7, i32 0, i32 0
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
  %28 = icmp ne i32 %27, 1920
  br i1 %28, label %32, label %29

; <label>:29:                                     ; preds = %17
  %30 = load i32, i32* %8, align 4
  %31 = icmp ne i32 %30, 1080
  br i1 %31, label %32, label %38

; <label>:32:                                     ; preds = %29, %17
  %33 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.5, i32 0, i32 0))
  %34 = load i32, i32* %7, align 4
  %35 = load i32, i32* %8, align 4
  %36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.6, i32 0, i32 0), i32 %34, i32 %35)
  %37 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.7, i32 0, i32 0), i32 1920, i32 1080)
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
  %3 = alloca [3 x i8]*, align 8
  %4 = alloca [3 x i8]*, align 8
  %5 = alloca [2073600 x float], align 16
  %6 = alloca [2073600 x float], align 16
  %7 = alloca [2073600 x float], align 16
  %8 = alloca [2073600 x float], align 16
  %9 = alloca [2073600 x float], align 16
  %10 = alloca [2073600 x [3 x float]], align 16
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %19 = alloca i32, align 4
  store [3 x i8]* %0, [3 x i8]** %3, align 8
  store [3 x i8]* %1, [3 x i8]** %4, align 8
  store i32 0, i32* %11, align 4
  br label %20

; <label>:20:                                     ; preds = %57, %2
  %21 = load i32, i32* %11, align 4
  %22 = icmp slt i32 %21, 2073600
  br i1 %22, label %23, label %60

; <label>:23:                                     ; preds = %20
  %24 = load [3 x i8]*, [3 x i8]** %3, align 8
  %25 = load i32, i32* %11, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds [3 x i8], [3 x i8]* %24, i64 %26
  %28 = getelementptr inbounds [3 x i8], [3 x i8]* %27, i64 0, i64 0
  %29 = load i8, i8* %28, align 1
  %30 = zext i8 %29 to i32
  %31 = sitofp i32 %30 to double
  %32 = fmul double 1.000000e-01, %31
  %33 = load [3 x i8]*, [3 x i8]** %3, align 8
  %34 = load i32, i32* %11, align 4
  %35 = sext i32 %34 to i64
  %36 = getelementptr inbounds [3 x i8], [3 x i8]* %33, i64 %35
  %37 = getelementptr inbounds [3 x i8], [3 x i8]* %36, i64 0, i64 1
  %38 = load i8, i8* %37, align 1
  %39 = zext i8 %38 to i32
  %40 = sitofp i32 %39 to double
  %41 = fmul double 6.000000e-01, %40
  %42 = fadd double %32, %41
  %43 = load [3 x i8]*, [3 x i8]** %3, align 8
  %44 = load i32, i32* %11, align 4
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds [3 x i8], [3 x i8]* %43, i64 %45
  %47 = getelementptr inbounds [3 x i8], [3 x i8]* %46, i64 0, i64 2
  %48 = load i8, i8* %47, align 1
  %49 = zext i8 %48 to i32
  %50 = sitofp i32 %49 to double
  %51 = fmul double 3.000000e-01, %50
  %52 = fadd double %42, %51
  %53 = fptrunc double %52 to float
  %54 = load i32, i32* %11, align 4
  %55 = sext i32 %54 to i64
  %56 = getelementptr inbounds [2073600 x float], [2073600 x float]* %5, i64 0, i64 %55
  store float %53, float* %56, align 4
  br label %57

; <label>:57:                                     ; preds = %23
  %58 = load i32, i32* %11, align 4
  %59 = add nsw i32 %58, 1
  store i32 %59, i32* %11, align 4
  br label %20

; <label>:60:                                     ; preds = %20
  store i32 1920, i32* %12, align 4
  br label %61

; <label>:61:                                     ; preds = %85, %60
  %62 = load i32, i32* %12, align 4
  %63 = icmp slt i32 %62, 2071680
  br i1 %63, label %64, label %88

; <label>:64:                                     ; preds = %61
  %65 = load i32, i32* %12, align 4
  %66 = sub nsw i32 %65, 1920
  %67 = sext i32 %66 to i64
  %68 = getelementptr inbounds [2073600 x float], [2073600 x float]* %5, i64 0, i64 %67
  %69 = load float, float* %68, align 4
  %70 = load i32, i32* %12, align 4
  %71 = sext i32 %70 to i64
  %72 = getelementptr inbounds [2073600 x float], [2073600 x float]* %5, i64 0, i64 %71
  %73 = load float, float* %72, align 4
  %74 = fadd float %69, %73
  %75 = load i32, i32* %12, align 4
  %76 = add nsw i32 %75, 1920
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds [2073600 x float], [2073600 x float]* %5, i64 0, i64 %77
  %79 = load float, float* %78, align 4
  %80 = fadd float %74, %79
  %81 = fdiv float %80, 3.000000e+00
  %82 = load i32, i32* %12, align 4
  %83 = sext i32 %82 to i64
  %84 = getelementptr inbounds [2073600 x float], [2073600 x float]* %6, i64 0, i64 %83
  store float %81, float* %84, align 4
  br label %85

; <label>:85:                                     ; preds = %64
  %86 = load i32, i32* %12, align 4
  %87 = add nsw i32 %86, 1
  store i32 %87, i32* %12, align 4
  br label %61

; <label>:88:                                     ; preds = %61
  store i32 1920, i32* %13, align 4
  br label %89

; <label>:89:                                     ; preds = %113, %88
  %90 = load i32, i32* %13, align 4
  %91 = icmp slt i32 %90, 2071680
  br i1 %91, label %92, label %116

; <label>:92:                                     ; preds = %89
  %93 = load i32, i32* %13, align 4
  %94 = sub nsw i32 %93, 1
  %95 = sext i32 %94 to i64
  %96 = getelementptr inbounds [2073600 x float], [2073600 x float]* %6, i64 0, i64 %95
  %97 = load float, float* %96, align 4
  %98 = load i32, i32* %13, align 4
  %99 = sext i32 %98 to i64
  %100 = getelementptr inbounds [2073600 x float], [2073600 x float]* %6, i64 0, i64 %99
  %101 = load float, float* %100, align 4
  %102 = fadd float %97, %101
  %103 = load i32, i32* %13, align 4
  %104 = add nsw i32 %103, 1
  %105 = sext i32 %104 to i64
  %106 = getelementptr inbounds [2073600 x float], [2073600 x float]* %6, i64 0, i64 %105
  %107 = load float, float* %106, align 4
  %108 = fadd float %102, %107
  %109 = fdiv float %108, 3.000000e+00
  %110 = load i32, i32* %13, align 4
  %111 = sext i32 %110 to i64
  %112 = getelementptr inbounds [2073600 x float], [2073600 x float]* %7, i64 0, i64 %111
  store float %109, float* %112, align 4
  br label %113

; <label>:113:                                    ; preds = %92
  %114 = load i32, i32* %13, align 4
  %115 = add nsw i32 %114, 1
  store i32 %115, i32* %13, align 4
  br label %89

; <label>:116:                                    ; preds = %89
  store i32 0, i32* %14, align 4
  br label %117

; <label>:117:                                    ; preds = %135, %116
  %118 = load i32, i32* %14, align 4
  %119 = icmp slt i32 %118, 2073600
  br i1 %119, label %120, label %138

; <label>:120:                                    ; preds = %117
  %121 = load i32, i32* %14, align 4
  %122 = sext i32 %121 to i64
  %123 = getelementptr inbounds [2073600 x float], [2073600 x float]* %5, i64 0, i64 %122
  %124 = load float, float* %123, align 4
  %125 = fmul float 2.000000e+00, %124
  %126 = load i32, i32* %14, align 4
  %127 = sext i32 %126 to i64
  %128 = getelementptr inbounds [2073600 x float], [2073600 x float]* %7, i64 0, i64 %127
  %129 = load float, float* %128, align 4
  %130 = fsub float %125, %129
  %131 = call float @fabs(float %130)
  %132 = load i32, i32* %14, align 4
  %133 = sext i32 %132 to i64
  %134 = getelementptr inbounds [2073600 x float], [2073600 x float]* %8, i64 0, i64 %133
  store float %131, float* %134, align 4
  br label %135

; <label>:135:                                    ; preds = %120
  %136 = load i32, i32* %14, align 4
  %137 = add nsw i32 %136, 1
  store i32 %137, i32* %14, align 4
  br label %117

; <label>:138:                                    ; preds = %117
  store i32 0, i32* %15, align 4
  br label %139

; <label>:139:                                    ; preds = %156, %138
  %140 = load i32, i32* %15, align 4
  %141 = icmp slt i32 %140, 2073600
  br i1 %141, label %142, label %159

; <label>:142:                                    ; preds = %139
  %143 = load i32, i32* %15, align 4
  %144 = sext i32 %143 to i64
  %145 = getelementptr inbounds [2073600 x float], [2073600 x float]* %8, i64 0, i64 %144
  %146 = load float, float* %145, align 4
  %147 = load i32, i32* %15, align 4
  %148 = sext i32 %147 to i64
  %149 = getelementptr inbounds [2073600 x float], [2073600 x float]* %5, i64 0, i64 %148
  %150 = load float, float* %149, align 4
  %151 = fadd float %150, 1.000000e+00
  %152 = fdiv float %146, %151
  %153 = load i32, i32* %15, align 4
  %154 = sext i32 %153 to i64
  %155 = getelementptr inbounds [2073600 x float], [2073600 x float]* %9, i64 0, i64 %154
  store float %152, float* %155, align 4
  br label %156

; <label>:156:                                    ; preds = %142
  %157 = load i32, i32* %15, align 4
  %158 = add nsw i32 %157, 1
  store i32 %158, i32* %15, align 4
  br label %139

; <label>:159:                                    ; preds = %139
  store i32 0, i32* %16, align 4
  br label %160

; <label>:160:                                    ; preds = %193, %159
  %161 = load i32, i32* %16, align 4
  %162 = icmp slt i32 %161, 2073600
  br i1 %162, label %163, label %196

; <label>:163:                                    ; preds = %160
  store i32 0, i32* %17, align 4
  br label %164

; <label>:164:                                    ; preds = %189, %163
  %165 = load i32, i32* %17, align 4
  %166 = icmp slt i32 %165, 3
  br i1 %166, label %167, label %192

; <label>:167:                                    ; preds = %164
  %168 = load i32, i32* %16, align 4
  %169 = sext i32 %168 to i64
  %170 = getelementptr inbounds [2073600 x float], [2073600 x float]* %9, i64 0, i64 %169
  %171 = load float, float* %170, align 4
  %172 = load [3 x i8]*, [3 x i8]** %3, align 8
  %173 = load i32, i32* %16, align 4
  %174 = sext i32 %173 to i64
  %175 = getelementptr inbounds [3 x i8], [3 x i8]* %172, i64 %174
  %176 = load i32, i32* %17, align 4
  %177 = sext i32 %176 to i64
  %178 = getelementptr inbounds [3 x i8], [3 x i8]* %175, i64 0, i64 %177
  %179 = load i8, i8* %178, align 1
  %180 = zext i8 %179 to i32
  %181 = sitofp i32 %180 to float
  %182 = fmul float %171, %181
  %183 = load i32, i32* %16, align 4
  %184 = sext i32 %183 to i64
  %185 = getelementptr inbounds [2073600 x [3 x float]], [2073600 x [3 x float]]* %10, i64 0, i64 %184
  %186 = load i32, i32* %17, align 4
  %187 = sext i32 %186 to i64
  %188 = getelementptr inbounds [3 x float], [3 x float]* %185, i64 0, i64 %187
  store float %182, float* %188, align 4
  br label %189

; <label>:189:                                    ; preds = %167
  %190 = load i32, i32* %17, align 4
  %191 = add nsw i32 %190, 1
  store i32 %191, i32* %17, align 4
  br label %164

; <label>:192:                                    ; preds = %164
  br label %193

; <label>:193:                                    ; preds = %192
  %194 = load i32, i32* %16, align 4
  %195 = add nsw i32 %194, 1
  store i32 %195, i32* %16, align 4
  br label %160

; <label>:196:                                    ; preds = %160
  store i32 0, i32* %18, align 4
  br label %197

; <label>:197:                                    ; preds = %225, %196
  %198 = load i32, i32* %18, align 4
  %199 = icmp slt i32 %198, 2073600
  br i1 %199, label %200, label %228

; <label>:200:                                    ; preds = %197
  store i32 0, i32* %19, align 4
  br label %201

; <label>:201:                                    ; preds = %221, %200
  %202 = load i32, i32* %19, align 4
  %203 = icmp slt i32 %202, 3
  br i1 %203, label %204, label %224

; <label>:204:                                    ; preds = %201
  %205 = load i32, i32* %18, align 4
  %206 = sext i32 %205 to i64
  %207 = getelementptr inbounds [2073600 x [3 x float]], [2073600 x [3 x float]]* %10, i64 0, i64 %206
  %208 = load i32, i32* %19, align 4
  %209 = sext i32 %208 to i64
  %210 = getelementptr inbounds [3 x float], [3 x float]* %207, i64 0, i64 %209
  %211 = load float, float* %210, align 4
  %212 = call float @fmin(float %211, float 2.550000e+02)
  %213 = fptoui float %212 to i8
  %214 = load [3 x i8]*, [3 x i8]** %4, align 8
  %215 = load i32, i32* %18, align 4
  %216 = sext i32 %215 to i64
  %217 = getelementptr inbounds [3 x i8], [3 x i8]* %214, i64 %216
  %218 = load i32, i32* %19, align 4
  %219 = sext i32 %218 to i64
  %220 = getelementptr inbounds [3 x i8], [3 x i8]* %217, i64 0, i64 %219
  store i8 %213, i8* %220, align 1
  br label %221

; <label>:221:                                    ; preds = %204
  %222 = load i32, i32* %19, align 4
  %223 = add nsw i32 %222, 1
  store i32 %223, i32* %19, align 4
  br label %201

; <label>:224:                                    ; preds = %201
  br label %225

; <label>:225:                                    ; preds = %224
  %226 = load i32, i32* %18, align 4
  %227 = add nsw i32 %226, 1
  store i32 %227, i32* %18, align 4
  br label %197

; <label>:228:                                    ; preds = %197
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
  store i32 1920, i32* %10, align 2
  %11 = getelementptr inbounds [54 x i8], [54 x i8]* %5, i64 0, i64 22
  %12 = bitcast i8* %11 to i32*
  store i32 1080, i32* %12, align 2
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
  store i32 6220800, i32* %7, align 4
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
  %8 = alloca [6220800 x i8], align 16
  %9 = alloca [6220800 x i8], align 16
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
  %17 = getelementptr inbounds [6220800 x i8], [6220800 x i8]* %8, i32 0, i32 0
  call void @read_bmp(i8* %16, i8* %17)
  %18 = load i8*, i8** %5, align 8
  %19 = getelementptr inbounds [6220800 x i8], [6220800 x i8]* %9, i32 0, i32 0
  call void @read_bmp(i8* %18, i8* %19)
  store i32 0, i32* %10, align 4
  store i32 0, i32* %11, align 4
  store i32 0, i32* %12, align 4
  br label %20

; <label>:20:                                     ; preds = %72, %3
  %21 = load i32, i32* %12, align 4
  %22 = icmp slt i32 %21, 6220800
  br i1 %22, label %23, label %75

; <label>:23:                                     ; preds = %20
  %24 = load i32, i32* %12, align 4
  %25 = sdiv i32 %24, 3
  %26 = srem i32 %25, 1920
  store i32 %26, i32* %13, align 4
  %27 = load i32, i32* %12, align 4
  %28 = sdiv i32 %27, 3
  %29 = sdiv i32 %28, 1920
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
  %40 = icmp eq i32 %39, 1919
  br i1 %40, label %44, label %41

; <label>:41:                                     ; preds = %38
  %42 = load i32, i32* %14, align 4
  %43 = icmp eq i32 %42, 1079
  br i1 %43, label %44, label %45

; <label>:44:                                     ; preds = %41, %38, %35, %32
  br label %72

; <label>:45:                                     ; preds = %41, %23
  %46 = getelementptr inbounds [6220800 x i8], [6220800 x i8]* %8, i32 0, i32 0
  %47 = load i32, i32* %12, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds i8, i8* %46, i64 %48
  %50 = load i8, i8* %49, align 1
  %51 = zext i8 %50 to i32
  %52 = getelementptr inbounds [6220800 x i8], [6220800 x i8]* %9, i32 0, i32 0
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
