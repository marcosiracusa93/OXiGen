; ModuleID = '7_sharpen_linearized_vectorized_2.c'
source_filename = "7_sharpen_linearized_vectorized_2.c"
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
  %6 = alloca [172800 x [2 x [3 x i8]]], align 16
  %7 = alloca [172800 x [2 x [3 x i8]]], align 16
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
  %24 = getelementptr inbounds [172800 x [2 x [3 x i8]]], [172800 x [2 x [3 x i8]]]* %6, i32 0, i32 0
  %25 = bitcast [2 x [3 x i8]]* %24 to i8*
  call void @read_bmp(i8* %23, i8* %25)
  %26 = getelementptr inbounds [172800 x [2 x [3 x i8]]], [172800 x [2 x [3 x i8]]]* %6, i32 0, i32 0
  %27 = getelementptr inbounds [172800 x [2 x [3 x i8]]], [172800 x [2 x [3 x i8]]]* %7, i32 0, i32 0
  call void @sharpen([2 x [3 x i8]]* %26, [2 x [3 x i8]]* %27)
  %28 = load i8*, i8** %9, align 8
  %29 = getelementptr inbounds [172800 x [2 x [3 x i8]]], [172800 x [2 x [3 x i8]]]* %7, i32 0, i32 0
  %30 = bitcast [2 x [3 x i8]]* %29 to i8*
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
define void @sharpen([2 x [3 x i8]]*, [2 x [3 x i8]]*) #0 {
  %3 = alloca [2 x [3 x i8]]*, align 8
  %4 = alloca [2 x [3 x i8]]*, align 8
  %5 = alloca [86400 x [2 x float]], align 16
  %6 = alloca [86400 x [2 x float]], align 16
  %7 = alloca [86400 x [2 x float]], align 16
  %8 = alloca [86400 x [2 x float]], align 16
  %9 = alloca [86400 x [2 x float]], align 16
  %10 = alloca [86400 x [2 x [3 x float]]], align 16
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
  store [2 x [3 x i8]]* %0, [2 x [3 x i8]]** %3, align 8
  store [2 x [3 x i8]]* %1, [2 x [3 x i8]]** %4, align 8
  store i32 0, i32* %11, align 4
  br label %27

; <label>:27:                                     ; preds = %84, %2
  %28 = load i32, i32* %11, align 4
  %29 = icmp slt i32 %28, 86400
  br i1 %29, label %30, label %87

; <label>:30:                                     ; preds = %27
  store i32 0, i32* %12, align 4
  br label %31

; <label>:31:                                     ; preds = %80, %30
  %32 = load i32, i32* %12, align 4
  %33 = icmp slt i32 %32, 2
  br i1 %33, label %34, label %83

; <label>:34:                                     ; preds = %31
  %35 = load [2 x [3 x i8]]*, [2 x [3 x i8]]** %3, align 8
  %36 = load i32, i32* %11, align 4
  %37 = sext i32 %36 to i64
  %38 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %35, i64 %37
  %39 = load i32, i32* %12, align 4
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %38, i64 0, i64 %40
  %42 = getelementptr inbounds [3 x i8], [3 x i8]* %41, i64 0, i64 0
  %43 = load i8, i8* %42, align 1
  %44 = zext i8 %43 to i32
  %45 = sitofp i32 %44 to double
  %46 = fmul double 1.000000e-01, %45
  %47 = load [2 x [3 x i8]]*, [2 x [3 x i8]]** %3, align 8
  %48 = load i32, i32* %11, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %47, i64 %49
  %51 = load i32, i32* %12, align 4
  %52 = sext i32 %51 to i64
  %53 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %50, i64 0, i64 %52
  %54 = getelementptr inbounds [3 x i8], [3 x i8]* %53, i64 0, i64 1
  %55 = load i8, i8* %54, align 1
  %56 = zext i8 %55 to i32
  %57 = sitofp i32 %56 to double
  %58 = fmul double 6.000000e-01, %57
  %59 = fadd double %46, %58
  %60 = load [2 x [3 x i8]]*, [2 x [3 x i8]]** %3, align 8
  %61 = load i32, i32* %11, align 4
  %62 = sext i32 %61 to i64
  %63 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %60, i64 %62
  %64 = load i32, i32* %12, align 4
  %65 = sext i32 %64 to i64
  %66 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %63, i64 0, i64 %65
  %67 = getelementptr inbounds [3 x i8], [3 x i8]* %66, i64 0, i64 2
  %68 = load i8, i8* %67, align 1
  %69 = zext i8 %68 to i32
  %70 = sitofp i32 %69 to double
  %71 = fmul double 3.000000e-01, %70
  %72 = fadd double %59, %71
  %73 = fptrunc double %72 to float
  %74 = load i32, i32* %11, align 4
  %75 = sext i32 %74 to i64
  %76 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %75
  %77 = load i32, i32* %12, align 4
  %78 = sext i32 %77 to i64
  %79 = getelementptr inbounds [2 x float], [2 x float]* %76, i64 0, i64 %78
  store float %73, float* %79, align 4
  br label %80

; <label>:80:                                     ; preds = %34
  %81 = load i32, i32* %12, align 4
  %82 = add nsw i32 %81, 1
  store i32 %82, i32* %12, align 4
  br label %31

; <label>:83:                                     ; preds = %31
  br label %84

; <label>:84:                                     ; preds = %83
  %85 = load i32, i32* %11, align 4
  %86 = add nsw i32 %85, 1
  store i32 %86, i32* %11, align 4
  br label %27

; <label>:87:                                     ; preds = %27
  store i32 180, i32* %13, align 4
  br label %88

; <label>:88:                                     ; preds = %132, %87
  %89 = load i32, i32* %13, align 4
  %90 = icmp slt i32 %89, 86220
  br i1 %90, label %91, label %135

; <label>:91:                                     ; preds = %88
  store i32 0, i32* %14, align 4
  br label %92

; <label>:92:                                     ; preds = %128, %91
  %93 = load i32, i32* %14, align 4
  %94 = icmp slt i32 %93, 2
  br i1 %94, label %95, label %131

; <label>:95:                                     ; preds = %92
  %96 = load i32, i32* %13, align 4
  %97 = sub nsw i32 %96, 180
  %98 = sext i32 %97 to i64
  %99 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %98
  %100 = load i32, i32* %14, align 4
  %101 = sext i32 %100 to i64
  %102 = getelementptr inbounds [2 x float], [2 x float]* %99, i64 0, i64 %101
  %103 = load float, float* %102, align 4
  %104 = load i32, i32* %13, align 4
  %105 = sext i32 %104 to i64
  %106 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %105
  %107 = load i32, i32* %14, align 4
  %108 = sext i32 %107 to i64
  %109 = getelementptr inbounds [2 x float], [2 x float]* %106, i64 0, i64 %108
  %110 = load float, float* %109, align 4
  %111 = fadd float %103, %110
  %112 = load i32, i32* %13, align 4
  %113 = add nsw i32 %112, 180
  %114 = sext i32 %113 to i64
  %115 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %114
  %116 = load i32, i32* %14, align 4
  %117 = sext i32 %116 to i64
  %118 = getelementptr inbounds [2 x float], [2 x float]* %115, i64 0, i64 %117
  %119 = load float, float* %118, align 4
  %120 = fadd float %111, %119
  %121 = fdiv float %120, 3.000000e+00
  %122 = load i32, i32* %13, align 4
  %123 = sext i32 %122 to i64
  %124 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %123
  %125 = load i32, i32* %14, align 4
  %126 = sext i32 %125 to i64
  %127 = getelementptr inbounds [2 x float], [2 x float]* %124, i64 0, i64 %126
  store float %121, float* %127, align 4
  br label %128

; <label>:128:                                    ; preds = %95
  %129 = load i32, i32* %14, align 4
  %130 = add nsw i32 %129, 1
  store i32 %130, i32* %14, align 4
  br label %92

; <label>:131:                                    ; preds = %92
  br label %132

; <label>:132:                                    ; preds = %131
  %133 = load i32, i32* %13, align 4
  %134 = add nsw i32 %133, 1
  store i32 %134, i32* %13, align 4
  br label %88

; <label>:135:                                    ; preds = %88
  store i32 180, i32* %15, align 4
  br label %136

; <label>:136:                                    ; preds = %180, %135
  %137 = load i32, i32* %15, align 4
  %138 = icmp slt i32 %137, 86220
  br i1 %138, label %139, label %183

; <label>:139:                                    ; preds = %136
  store i32 0, i32* %16, align 4
  br label %140

; <label>:140:                                    ; preds = %176, %139
  %141 = load i32, i32* %16, align 4
  %142 = icmp slt i32 %141, 2
  br i1 %142, label %143, label %179

; <label>:143:                                    ; preds = %140
  %144 = load i32, i32* %15, align 4
  %145 = sub nsw i32 %144, 1
  %146 = sext i32 %145 to i64
  %147 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %146
  %148 = load i32, i32* %16, align 4
  %149 = sext i32 %148 to i64
  %150 = getelementptr inbounds [2 x float], [2 x float]* %147, i64 0, i64 %149
  %151 = load float, float* %150, align 4
  %152 = load i32, i32* %15, align 4
  %153 = sext i32 %152 to i64
  %154 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %153
  %155 = load i32, i32* %16, align 4
  %156 = sext i32 %155 to i64
  %157 = getelementptr inbounds [2 x float], [2 x float]* %154, i64 0, i64 %156
  %158 = load float, float* %157, align 4
  %159 = fadd float %151, %158
  %160 = load i32, i32* %15, align 4
  %161 = add nsw i32 %160, 1
  %162 = sext i32 %161 to i64
  %163 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %162
  %164 = load i32, i32* %16, align 4
  %165 = sext i32 %164 to i64
  %166 = getelementptr inbounds [2 x float], [2 x float]* %163, i64 0, i64 %165
  %167 = load float, float* %166, align 4
  %168 = fadd float %159, %167
  %169 = fdiv float %168, 3.000000e+00
  %170 = load i32, i32* %15, align 4
  %171 = sext i32 %170 to i64
  %172 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %7, i64 0, i64 %171
  %173 = load i32, i32* %16, align 4
  %174 = sext i32 %173 to i64
  %175 = getelementptr inbounds [2 x float], [2 x float]* %172, i64 0, i64 %174
  store float %169, float* %175, align 4
  br label %176

; <label>:176:                                    ; preds = %143
  %177 = load i32, i32* %16, align 4
  %178 = add nsw i32 %177, 1
  store i32 %178, i32* %16, align 4
  br label %140

; <label>:179:                                    ; preds = %140
  br label %180

; <label>:180:                                    ; preds = %179
  %181 = load i32, i32* %15, align 4
  %182 = add nsw i32 %181, 1
  store i32 %182, i32* %15, align 4
  br label %136

; <label>:183:                                    ; preds = %136
  store i32 0, i32* %17, align 4
  br label %184

; <label>:184:                                    ; preds = %219, %183
  %185 = load i32, i32* %17, align 4
  %186 = icmp slt i32 %185, 86400
  br i1 %186, label %187, label %222

; <label>:187:                                    ; preds = %184
  store i32 0, i32* %18, align 4
  br label %188

; <label>:188:                                    ; preds = %215, %187
  %189 = load i32, i32* %18, align 4
  %190 = icmp slt i32 %189, 2
  br i1 %190, label %191, label %218

; <label>:191:                                    ; preds = %188
  %192 = load i32, i32* %17, align 4
  %193 = sext i32 %192 to i64
  %194 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %193
  %195 = load i32, i32* %18, align 4
  %196 = sext i32 %195 to i64
  %197 = getelementptr inbounds [2 x float], [2 x float]* %194, i64 0, i64 %196
  %198 = load float, float* %197, align 4
  %199 = fmul float 2.000000e+00, %198
  %200 = load i32, i32* %17, align 4
  %201 = sext i32 %200 to i64
  %202 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %7, i64 0, i64 %201
  %203 = load i32, i32* %18, align 4
  %204 = sext i32 %203 to i64
  %205 = getelementptr inbounds [2 x float], [2 x float]* %202, i64 0, i64 %204
  %206 = load float, float* %205, align 4
  %207 = fsub float %199, %206
  %208 = call float @fabs(float %207)
  %209 = load i32, i32* %17, align 4
  %210 = sext i32 %209 to i64
  %211 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %8, i64 0, i64 %210
  %212 = load i32, i32* %18, align 4
  %213 = sext i32 %212 to i64
  %214 = getelementptr inbounds [2 x float], [2 x float]* %211, i64 0, i64 %213
  store float %208, float* %214, align 4
  br label %215

; <label>:215:                                    ; preds = %191
  %216 = load i32, i32* %18, align 4
  %217 = add nsw i32 %216, 1
  store i32 %217, i32* %18, align 4
  br label %188

; <label>:218:                                    ; preds = %188
  br label %219

; <label>:219:                                    ; preds = %218
  %220 = load i32, i32* %17, align 4
  %221 = add nsw i32 %220, 1
  store i32 %221, i32* %17, align 4
  br label %184

; <label>:222:                                    ; preds = %184
  store i32 0, i32* %19, align 4
  br label %223

; <label>:223:                                    ; preds = %257, %222
  %224 = load i32, i32* %19, align 4
  %225 = icmp slt i32 %224, 86400
  br i1 %225, label %226, label %260

; <label>:226:                                    ; preds = %223
  store i32 0, i32* %20, align 4
  br label %227

; <label>:227:                                    ; preds = %253, %226
  %228 = load i32, i32* %20, align 4
  %229 = icmp slt i32 %228, 2
  br i1 %229, label %230, label %256

; <label>:230:                                    ; preds = %227
  %231 = load i32, i32* %19, align 4
  %232 = sext i32 %231 to i64
  %233 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %8, i64 0, i64 %232
  %234 = load i32, i32* %20, align 4
  %235 = sext i32 %234 to i64
  %236 = getelementptr inbounds [2 x float], [2 x float]* %233, i64 0, i64 %235
  %237 = load float, float* %236, align 4
  %238 = load i32, i32* %19, align 4
  %239 = sext i32 %238 to i64
  %240 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %239
  %241 = load i32, i32* %20, align 4
  %242 = sext i32 %241 to i64
  %243 = getelementptr inbounds [2 x float], [2 x float]* %240, i64 0, i64 %242
  %244 = load float, float* %243, align 4
  %245 = fadd float %244, 1.000000e+00
  %246 = fdiv float %237, %245
  %247 = load i32, i32* %19, align 4
  %248 = sext i32 %247 to i64
  %249 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %9, i64 0, i64 %248
  %250 = load i32, i32* %20, align 4
  %251 = sext i32 %250 to i64
  %252 = getelementptr inbounds [2 x float], [2 x float]* %249, i64 0, i64 %251
  store float %246, float* %252, align 4
  br label %253

; <label>:253:                                    ; preds = %230
  %254 = load i32, i32* %20, align 4
  %255 = add nsw i32 %254, 1
  store i32 %255, i32* %20, align 4
  br label %227

; <label>:256:                                    ; preds = %227
  br label %257

; <label>:257:                                    ; preds = %256
  %258 = load i32, i32* %19, align 4
  %259 = add nsw i32 %258, 1
  store i32 %259, i32* %19, align 4
  br label %223

; <label>:260:                                    ; preds = %223
  store i32 0, i32* %21, align 4
  br label %261

; <label>:261:                                    ; preds = %311, %260
  %262 = load i32, i32* %21, align 4
  %263 = icmp slt i32 %262, 86400
  br i1 %263, label %264, label %314

; <label>:264:                                    ; preds = %261
  store i32 0, i32* %22, align 4
  br label %265

; <label>:265:                                    ; preds = %307, %264
  %266 = load i32, i32* %22, align 4
  %267 = icmp slt i32 %266, 2
  br i1 %267, label %268, label %310

; <label>:268:                                    ; preds = %265
  store i32 0, i32* %23, align 4
  br label %269

; <label>:269:                                    ; preds = %303, %268
  %270 = load i32, i32* %23, align 4
  %271 = icmp slt i32 %270, 3
  br i1 %271, label %272, label %306

; <label>:272:                                    ; preds = %269
  %273 = load i32, i32* %21, align 4
  %274 = sext i32 %273 to i64
  %275 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %9, i64 0, i64 %274
  %276 = load i32, i32* %22, align 4
  %277 = sext i32 %276 to i64
  %278 = getelementptr inbounds [2 x float], [2 x float]* %275, i64 0, i64 %277
  %279 = load float, float* %278, align 4
  %280 = load [2 x [3 x i8]]*, [2 x [3 x i8]]** %3, align 8
  %281 = load i32, i32* %21, align 4
  %282 = sext i32 %281 to i64
  %283 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %280, i64 %282
  %284 = load i32, i32* %22, align 4
  %285 = sext i32 %284 to i64
  %286 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %283, i64 0, i64 %285
  %287 = load i32, i32* %23, align 4
  %288 = sext i32 %287 to i64
  %289 = getelementptr inbounds [3 x i8], [3 x i8]* %286, i64 0, i64 %288
  %290 = load i8, i8* %289, align 1
  %291 = zext i8 %290 to i32
  %292 = sitofp i32 %291 to float
  %293 = fmul float %279, %292
  %294 = load i32, i32* %21, align 4
  %295 = sext i32 %294 to i64
  %296 = getelementptr inbounds [86400 x [2 x [3 x float]]], [86400 x [2 x [3 x float]]]* %10, i64 0, i64 %295
  %297 = load i32, i32* %22, align 4
  %298 = sext i32 %297 to i64
  %299 = getelementptr inbounds [2 x [3 x float]], [2 x [3 x float]]* %296, i64 0, i64 %298
  %300 = load i32, i32* %23, align 4
  %301 = sext i32 %300 to i64
  %302 = getelementptr inbounds [3 x float], [3 x float]* %299, i64 0, i64 %301
  store float %293, float* %302, align 4
  br label %303

; <label>:303:                                    ; preds = %272
  %304 = load i32, i32* %23, align 4
  %305 = add nsw i32 %304, 1
  store i32 %305, i32* %23, align 4
  br label %269

; <label>:306:                                    ; preds = %269
  br label %307

; <label>:307:                                    ; preds = %306
  %308 = load i32, i32* %22, align 4
  %309 = add nsw i32 %308, 1
  store i32 %309, i32* %22, align 4
  br label %265

; <label>:310:                                    ; preds = %265
  br label %311

; <label>:311:                                    ; preds = %310
  %312 = load i32, i32* %21, align 4
  %313 = add nsw i32 %312, 1
  store i32 %313, i32* %21, align 4
  br label %261

; <label>:314:                                    ; preds = %261
  store i32 0, i32* %24, align 4
  br label %315

; <label>:315:                                    ; preds = %357, %314
  %316 = load i32, i32* %24, align 4
  %317 = icmp slt i32 %316, 86400
  br i1 %317, label %318, label %360

; <label>:318:                                    ; preds = %315
  store i32 0, i32* %25, align 4
  br label %319

; <label>:319:                                    ; preds = %353, %318
  %320 = load i32, i32* %25, align 4
  %321 = icmp slt i32 %320, 2
  br i1 %321, label %322, label %356

; <label>:322:                                    ; preds = %319
  store i32 0, i32* %26, align 4
  br label %323

; <label>:323:                                    ; preds = %349, %322
  %324 = load i32, i32* %26, align 4
  %325 = icmp slt i32 %324, 3
  br i1 %325, label %326, label %352

; <label>:326:                                    ; preds = %323
  %327 = load i32, i32* %24, align 4
  %328 = sext i32 %327 to i64
  %329 = getelementptr inbounds [86400 x [2 x [3 x float]]], [86400 x [2 x [3 x float]]]* %10, i64 0, i64 %328
  %330 = load i32, i32* %25, align 4
  %331 = sext i32 %330 to i64
  %332 = getelementptr inbounds [2 x [3 x float]], [2 x [3 x float]]* %329, i64 0, i64 %331
  %333 = load i32, i32* %26, align 4
  %334 = sext i32 %333 to i64
  %335 = getelementptr inbounds [3 x float], [3 x float]* %332, i64 0, i64 %334
  %336 = load float, float* %335, align 4
  %337 = call float @fmin(float %336, float 2.550000e+02)
  %338 = fptoui float %337 to i8
  %339 = load [2 x [3 x i8]]*, [2 x [3 x i8]]** %4, align 8
  %340 = load i32, i32* %24, align 4
  %341 = sext i32 %340 to i64
  %342 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %339, i64 %341
  %343 = load i32, i32* %25, align 4
  %344 = sext i32 %343 to i64
  %345 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %342, i64 0, i64 %344
  %346 = load i32, i32* %26, align 4
  %347 = sext i32 %346 to i64
  %348 = getelementptr inbounds [3 x i8], [3 x i8]* %345, i64 0, i64 %347
  store i8 %338, i8* %348, align 1
  br label %349

; <label>:349:                                    ; preds = %326
  %350 = load i32, i32* %26, align 4
  %351 = add nsw i32 %350, 1
  store i32 %351, i32* %26, align 4
  br label %323

; <label>:352:                                    ; preds = %323
  br label %353

; <label>:353:                                    ; preds = %352
  %354 = load i32, i32* %25, align 4
  %355 = add nsw i32 %354, 1
  store i32 %355, i32* %25, align 4
  br label %319

; <label>:356:                                    ; preds = %319
  br label %357

; <label>:357:                                    ; preds = %356
  %358 = load i32, i32* %24, align 4
  %359 = add nsw i32 %358, 1
  store i32 %359, i32* %24, align 4
  br label %315

; <label>:360:                                    ; preds = %315
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
