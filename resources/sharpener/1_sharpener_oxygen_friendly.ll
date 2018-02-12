; ModuleID = '1_sharpener_oxygen_friendly.c'
source_filename = "1_sharpener_oxygen_friendly.c"
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
  %8 = alloca [2073600 x i8], align 16
  %9 = alloca [2073600 x i8], align 16
  %10 = alloca [2073600 x i8], align 16
  %11 = alloca [2073600 x i8], align 16
  %12 = alloca [2073600 x i8], align 16
  %13 = alloca [2073600 x i8], align 16
  %14 = alloca i8*, align 8
  %15 = alloca i8*, align 8
  %16 = alloca i8*, align 8
  %17 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  %18 = load i32, i32* %4, align 4
  %19 = icmp slt i32 %18, 3
  br i1 %19, label %20, label %22

; <label>:20:                                     ; preds = %2
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str, i32 0, i32 0))
  call void @exit(i32 1) #5
  unreachable

; <label>:22:                                     ; preds = %2
  %23 = load i8**, i8*** %5, align 8
  %24 = getelementptr inbounds i8*, i8** %23, i64 1
  %25 = load i8*, i8** %24, align 8
  store i8* %25, i8** %14, align 8
  %26 = load i8**, i8*** %5, align 8
  %27 = getelementptr inbounds i8*, i8** %26, i64 2
  %28 = load i8*, i8** %27, align 8
  store i8* %28, i8** %15, align 8
  %29 = load i8*, i8** %14, align 8
  %30 = getelementptr inbounds [2073600 x [3 x i8]], [2073600 x [3 x i8]]* %6, i32 0, i32 0
  %31 = bitcast [3 x i8]* %30 to i8*
  call void @read_bmp(i8* %29, i8* %31)
  %32 = getelementptr inbounds [2073600 x [3 x i8]], [2073600 x [3 x i8]]* %6, i32 0, i32 0
  %33 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %8, i32 0, i32 0
  %34 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %9, i32 0, i32 0
  %35 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %10, i32 0, i32 0
  call void @deinterleave([3 x i8]* %32, i8* %33, i8* %34, i8* %35)
  %36 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %8, i32 0, i32 0
  %37 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %9, i32 0, i32 0
  %38 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %10, i32 0, i32 0
  %39 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %11, i32 0, i32 0
  %40 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %12, i32 0, i32 0
  %41 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %13, i32 0, i32 0
  call void @sharpen_3ch(i8* %36, i8* %37, i8* %38, i8* %39, i8* %40, i8* %41)
  %42 = getelementptr inbounds [2073600 x [3 x i8]], [2073600 x [3 x i8]]* %7, i32 0, i32 0
  %43 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %11, i32 0, i32 0
  %44 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %12, i32 0, i32 0
  %45 = getelementptr inbounds [2073600 x i8], [2073600 x i8]* %13, i32 0, i32 0
  call void @interleave([3 x i8]* %42, i8* %43, i8* %44, i8* %45)
  %46 = load i8*, i8** %15, align 8
  %47 = getelementptr inbounds [2073600 x [3 x i8]], [2073600 x [3 x i8]]* %7, i32 0, i32 0
  %48 = bitcast [3 x i8]* %47 to i8*
  call void @write_bmp(i8* %46, i8* %48)
  %49 = load i32, i32* %4, align 4
  %50 = icmp sge i32 %49, 4
  br i1 %50, label %51, label %62

; <label>:51:                                     ; preds = %22
  %52 = load i8**, i8*** %5, align 8
  %53 = getelementptr inbounds i8*, i8** %52, i64 3
  %54 = load i8*, i8** %53, align 8
  store i8* %54, i8** %16, align 8
  %55 = load i8*, i8** %16, align 8
  %56 = load i8*, i8** %15, align 8
  %57 = call i32 @validate_result(i8* %55, i8* %56, i32 1)
  store i32 %57, i32* %17, align 4
  %58 = load i32, i32* %17, align 4
  %59 = icmp ne i32 %58, 0
  br i1 %59, label %61, label %60

; <label>:60:                                     ; preds = %51
  store i32 1, i32* %3, align 4
  br label %63

; <label>:61:                                     ; preds = %51
  br label %62

; <label>:62:                                     ; preds = %61, %22
  store i32 0, i32* %3, align 4
  br label %63

; <label>:63:                                     ; preds = %62, %60
  %64 = load i32, i32* %3, align 4
  ret i32 %64
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
define void @deinterleave([3 x i8]*, i8*, i8*, i8*) #0 {
  %5 = alloca [3 x i8]*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i32, align 4
  store [3 x i8]* %0, [3 x i8]** %5, align 8
  store i8* %1, i8** %6, align 8
  store i8* %2, i8** %7, align 8
  store i8* %3, i8** %8, align 8
  store i32 0, i32* %9, align 4
  br label %10

; <label>:10:                                     ; preds = %44, %4
  %11 = load i32, i32* %9, align 4
  %12 = icmp slt i32 %11, 2073600
  br i1 %12, label %13, label %47

; <label>:13:                                     ; preds = %10
  %14 = load [3 x i8]*, [3 x i8]** %5, align 8
  %15 = load i32, i32* %9, align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds [3 x i8], [3 x i8]* %14, i64 %16
  %18 = getelementptr inbounds [3 x i8], [3 x i8]* %17, i64 0, i64 0
  %19 = load i8, i8* %18, align 1
  %20 = load i8*, i8** %6, align 8
  %21 = load i32, i32* %9, align 4
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds i8, i8* %20, i64 %22
  store i8 %19, i8* %23, align 1
  %24 = load [3 x i8]*, [3 x i8]** %5, align 8
  %25 = load i32, i32* %9, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds [3 x i8], [3 x i8]* %24, i64 %26
  %28 = getelementptr inbounds [3 x i8], [3 x i8]* %27, i64 0, i64 1
  %29 = load i8, i8* %28, align 1
  %30 = load i8*, i8** %7, align 8
  %31 = load i32, i32* %9, align 4
  %32 = sext i32 %31 to i64
  %33 = getelementptr inbounds i8, i8* %30, i64 %32
  store i8 %29, i8* %33, align 1
  %34 = load [3 x i8]*, [3 x i8]** %5, align 8
  %35 = load i32, i32* %9, align 4
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds [3 x i8], [3 x i8]* %34, i64 %36
  %38 = getelementptr inbounds [3 x i8], [3 x i8]* %37, i64 0, i64 2
  %39 = load i8, i8* %38, align 1
  %40 = load i8*, i8** %8, align 8
  %41 = load i32, i32* %9, align 4
  %42 = sext i32 %41 to i64
  %43 = getelementptr inbounds i8, i8* %40, i64 %42
  store i8 %39, i8* %43, align 1
  br label %44

; <label>:44:                                     ; preds = %13
  %45 = load i32, i32* %9, align 4
  %46 = add nsw i32 %45, 1
  store i32 %46, i32* %9, align 4
  br label %10

; <label>:47:                                     ; preds = %10
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @sharpen_3ch(i8*, i8*, i8*, i8*, i8*, i8*) #0 {
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i8*, align 8
  %11 = alloca i8*, align 8
  %12 = alloca i8*, align 8
  %13 = alloca [2073600 x float], align 16
  %14 = alloca [2073600 x float], align 16
  %15 = alloca [2073600 x float], align 16
  %16 = alloca [2073600 x float], align 16
  %17 = alloca [2073600 x float], align 16
  %18 = alloca i32, align 4
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  store i8* %0, i8** %7, align 8
  store i8* %1, i8** %8, align 8
  store i8* %2, i8** %9, align 8
  store i8* %3, i8** %10, align 8
  store i8* %4, i8** %11, align 8
  store i8* %5, i8** %12, align 8
  store i32 0, i32* %18, align 4
  br label %24

; <label>:24:                                     ; preds = %58, %6
  %25 = load i32, i32* %18, align 4
  %26 = icmp slt i32 %25, 2073600
  br i1 %26, label %27, label %61

; <label>:27:                                     ; preds = %24
  %28 = load i8*, i8** %7, align 8
  %29 = load i32, i32* %18, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds i8, i8* %28, i64 %30
  %32 = load i8, i8* %31, align 1
  %33 = zext i8 %32 to i32
  %34 = sitofp i32 %33 to double
  %35 = fmul double 1.000000e-01, %34
  %36 = load i8*, i8** %8, align 8
  %37 = load i32, i32* %18, align 4
  %38 = sext i32 %37 to i64
  %39 = getelementptr inbounds i8, i8* %36, i64 %38
  %40 = load i8, i8* %39, align 1
  %41 = zext i8 %40 to i32
  %42 = sitofp i32 %41 to double
  %43 = fmul double 6.000000e-01, %42
  %44 = fadd double %35, %43
  %45 = load i8*, i8** %9, align 8
  %46 = load i32, i32* %18, align 4
  %47 = sext i32 %46 to i64
  %48 = getelementptr inbounds i8, i8* %45, i64 %47
  %49 = load i8, i8* %48, align 1
  %50 = zext i8 %49 to i32
  %51 = sitofp i32 %50 to double
  %52 = fmul double 3.000000e-01, %51
  %53 = fadd double %44, %52
  %54 = fptrunc double %53 to float
  %55 = load i32, i32* %18, align 4
  %56 = sext i32 %55 to i64
  %57 = getelementptr inbounds [2073600 x float], [2073600 x float]* %13, i64 0, i64 %56
  store float %54, float* %57, align 4
  br label %58

; <label>:58:                                     ; preds = %27
  %59 = load i32, i32* %18, align 4
  %60 = add nsw i32 %59, 1
  store i32 %60, i32* %18, align 4
  br label %24

; <label>:61:                                     ; preds = %24
  store i32 1920, i32* %19, align 4
  br label %62

; <label>:62:                                     ; preds = %86, %61
  %63 = load i32, i32* %19, align 4
  %64 = icmp slt i32 %63, 2071680
  br i1 %64, label %65, label %89

; <label>:65:                                     ; preds = %62
  %66 = load i32, i32* %19, align 4
  %67 = sub nsw i32 %66, 1920
  %68 = sext i32 %67 to i64
  %69 = getelementptr inbounds [2073600 x float], [2073600 x float]* %13, i64 0, i64 %68
  %70 = load float, float* %69, align 4
  %71 = load i32, i32* %19, align 4
  %72 = sext i32 %71 to i64
  %73 = getelementptr inbounds [2073600 x float], [2073600 x float]* %13, i64 0, i64 %72
  %74 = load float, float* %73, align 4
  %75 = fadd float %70, %74
  %76 = load i32, i32* %19, align 4
  %77 = add nsw i32 %76, 1920
  %78 = sext i32 %77 to i64
  %79 = getelementptr inbounds [2073600 x float], [2073600 x float]* %13, i64 0, i64 %78
  %80 = load float, float* %79, align 4
  %81 = fadd float %75, %80
  %82 = fdiv float %81, 3.000000e+00
  %83 = load i32, i32* %19, align 4
  %84 = sext i32 %83 to i64
  %85 = getelementptr inbounds [2073600 x float], [2073600 x float]* %14, i64 0, i64 %84
  store float %82, float* %85, align 4
  br label %86

; <label>:86:                                     ; preds = %65
  %87 = load i32, i32* %19, align 4
  %88 = add nsw i32 %87, 1
  store i32 %88, i32* %19, align 4
  br label %62

; <label>:89:                                     ; preds = %62
  store i32 1920, i32* %20, align 4
  br label %90

; <label>:90:                                     ; preds = %114, %89
  %91 = load i32, i32* %20, align 4
  %92 = icmp slt i32 %91, 2071680
  br i1 %92, label %93, label %117

; <label>:93:                                     ; preds = %90
  %94 = load i32, i32* %20, align 4
  %95 = sub nsw i32 %94, 1
  %96 = sext i32 %95 to i64
  %97 = getelementptr inbounds [2073600 x float], [2073600 x float]* %14, i64 0, i64 %96
  %98 = load float, float* %97, align 4
  %99 = load i32, i32* %20, align 4
  %100 = sext i32 %99 to i64
  %101 = getelementptr inbounds [2073600 x float], [2073600 x float]* %14, i64 0, i64 %100
  %102 = load float, float* %101, align 4
  %103 = fadd float %98, %102
  %104 = load i32, i32* %20, align 4
  %105 = add nsw i32 %104, 1
  %106 = sext i32 %105 to i64
  %107 = getelementptr inbounds [2073600 x float], [2073600 x float]* %14, i64 0, i64 %106
  %108 = load float, float* %107, align 4
  %109 = fadd float %103, %108
  %110 = fdiv float %109, 3.000000e+00
  %111 = load i32, i32* %20, align 4
  %112 = sext i32 %111 to i64
  %113 = getelementptr inbounds [2073600 x float], [2073600 x float]* %15, i64 0, i64 %112
  store float %110, float* %113, align 4
  br label %114

; <label>:114:                                    ; preds = %93
  %115 = load i32, i32* %20, align 4
  %116 = add nsw i32 %115, 1
  store i32 %116, i32* %20, align 4
  br label %90

; <label>:117:                                    ; preds = %90
  store i32 1920, i32* %21, align 4
  br label %118

; <label>:118:                                    ; preds = %136, %117
  %119 = load i32, i32* %21, align 4
  %120 = icmp slt i32 %119, 2071680
  br i1 %120, label %121, label %139

; <label>:121:                                    ; preds = %118
  %122 = load i32, i32* %21, align 4
  %123 = sext i32 %122 to i64
  %124 = getelementptr inbounds [2073600 x float], [2073600 x float]* %13, i64 0, i64 %123
  %125 = load float, float* %124, align 4
  %126 = fmul float 2.000000e+00, %125
  %127 = load i32, i32* %21, align 4
  %128 = sext i32 %127 to i64
  %129 = getelementptr inbounds [2073600 x float], [2073600 x float]* %15, i64 0, i64 %128
  %130 = load float, float* %129, align 4
  %131 = fsub float %126, %130
  %132 = call float @fabs(float %131)
  %133 = load i32, i32* %21, align 4
  %134 = sext i32 %133 to i64
  %135 = getelementptr inbounds [2073600 x float], [2073600 x float]* %16, i64 0, i64 %134
  store float %132, float* %135, align 4
  br label %136

; <label>:136:                                    ; preds = %121
  %137 = load i32, i32* %21, align 4
  %138 = add nsw i32 %137, 1
  store i32 %138, i32* %21, align 4
  br label %118

; <label>:139:                                    ; preds = %118
  store i32 1920, i32* %22, align 4
  br label %140

; <label>:140:                                    ; preds = %157, %139
  %141 = load i32, i32* %22, align 4
  %142 = icmp slt i32 %141, 2071680
  br i1 %142, label %143, label %160

; <label>:143:                                    ; preds = %140
  %144 = load i32, i32* %22, align 4
  %145 = sext i32 %144 to i64
  %146 = getelementptr inbounds [2073600 x float], [2073600 x float]* %16, i64 0, i64 %145
  %147 = load float, float* %146, align 4
  %148 = load i32, i32* %22, align 4
  %149 = sext i32 %148 to i64
  %150 = getelementptr inbounds [2073600 x float], [2073600 x float]* %13, i64 0, i64 %149
  %151 = load float, float* %150, align 4
  %152 = fadd float %151, 1.000000e+00
  %153 = fdiv float %147, %152
  %154 = load i32, i32* %22, align 4
  %155 = sext i32 %154 to i64
  %156 = getelementptr inbounds [2073600 x float], [2073600 x float]* %17, i64 0, i64 %155
  store float %153, float* %156, align 4
  br label %157

; <label>:157:                                    ; preds = %143
  %158 = load i32, i32* %22, align 4
  %159 = add nsw i32 %158, 1
  store i32 %159, i32* %22, align 4
  br label %140

; <label>:160:                                    ; preds = %140
  store i32 1920, i32* %23, align 4
  br label %161

; <label>:161:                                    ; preds = %219, %160
  %162 = load i32, i32* %23, align 4
  %163 = icmp slt i32 %162, 2071680
  br i1 %163, label %164, label %222

; <label>:164:                                    ; preds = %161
  %165 = load i32, i32* %23, align 4
  %166 = sext i32 %165 to i64
  %167 = getelementptr inbounds [2073600 x float], [2073600 x float]* %17, i64 0, i64 %166
  %168 = load float, float* %167, align 4
  %169 = load i8*, i8** %7, align 8
  %170 = load i32, i32* %23, align 4
  %171 = sext i32 %170 to i64
  %172 = getelementptr inbounds i8, i8* %169, i64 %171
  %173 = load i8, i8* %172, align 1
  %174 = zext i8 %173 to i32
  %175 = sitofp i32 %174 to float
  %176 = fmul float %168, %175
  %177 = call float @fmin(float %176, float 2.550000e+02)
  %178 = fptoui float %177 to i8
  %179 = load i8*, i8** %10, align 8
  %180 = load i32, i32* %23, align 4
  %181 = sext i32 %180 to i64
  %182 = getelementptr inbounds i8, i8* %179, i64 %181
  store i8 %178, i8* %182, align 1
  %183 = load i32, i32* %23, align 4
  %184 = sext i32 %183 to i64
  %185 = getelementptr inbounds [2073600 x float], [2073600 x float]* %17, i64 0, i64 %184
  %186 = load float, float* %185, align 4
  %187 = load i8*, i8** %8, align 8
  %188 = load i32, i32* %23, align 4
  %189 = sext i32 %188 to i64
  %190 = getelementptr inbounds i8, i8* %187, i64 %189
  %191 = load i8, i8* %190, align 1
  %192 = zext i8 %191 to i32
  %193 = sitofp i32 %192 to float
  %194 = fmul float %186, %193
  %195 = call float @fmin(float %194, float 2.550000e+02)
  %196 = fptoui float %195 to i8
  %197 = load i8*, i8** %11, align 8
  %198 = load i32, i32* %23, align 4
  %199 = sext i32 %198 to i64
  %200 = getelementptr inbounds i8, i8* %197, i64 %199
  store i8 %196, i8* %200, align 1
  %201 = load i32, i32* %23, align 4
  %202 = sext i32 %201 to i64
  %203 = getelementptr inbounds [2073600 x float], [2073600 x float]* %17, i64 0, i64 %202
  %204 = load float, float* %203, align 4
  %205 = load i8*, i8** %9, align 8
  %206 = load i32, i32* %23, align 4
  %207 = sext i32 %206 to i64
  %208 = getelementptr inbounds i8, i8* %205, i64 %207
  %209 = load i8, i8* %208, align 1
  %210 = zext i8 %209 to i32
  %211 = sitofp i32 %210 to float
  %212 = fmul float %204, %211
  %213 = call float @fmin(float %212, float 2.550000e+02)
  %214 = fptoui float %213 to i8
  %215 = load i8*, i8** %12, align 8
  %216 = load i32, i32* %23, align 4
  %217 = sext i32 %216 to i64
  %218 = getelementptr inbounds i8, i8* %215, i64 %217
  store i8 %214, i8* %218, align 1
  br label %219

; <label>:219:                                    ; preds = %164
  %220 = load i32, i32* %23, align 4
  %221 = add nsw i32 %220, 1
  store i32 %221, i32* %23, align 4
  br label %161

; <label>:222:                                    ; preds = %161
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @interleave([3 x i8]*, i8*, i8*, i8*) #0 {
  %5 = alloca [3 x i8]*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i32, align 4
  store [3 x i8]* %0, [3 x i8]** %5, align 8
  store i8* %1, i8** %6, align 8
  store i8* %2, i8** %7, align 8
  store i8* %3, i8** %8, align 8
  store i32 0, i32* %9, align 4
  br label %10

; <label>:10:                                     ; preds = %44, %4
  %11 = load i32, i32* %9, align 4
  %12 = icmp slt i32 %11, 2073600
  br i1 %12, label %13, label %47

; <label>:13:                                     ; preds = %10
  %14 = load i8*, i8** %6, align 8
  %15 = load i32, i32* %9, align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds i8, i8* %14, i64 %16
  %18 = load i8, i8* %17, align 1
  %19 = load [3 x i8]*, [3 x i8]** %5, align 8
  %20 = load i32, i32* %9, align 4
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds [3 x i8], [3 x i8]* %19, i64 %21
  %23 = getelementptr inbounds [3 x i8], [3 x i8]* %22, i64 0, i64 0
  store i8 %18, i8* %23, align 1
  %24 = load i8*, i8** %7, align 8
  %25 = load i32, i32* %9, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds i8, i8* %24, i64 %26
  %28 = load i8, i8* %27, align 1
  %29 = load [3 x i8]*, [3 x i8]** %5, align 8
  %30 = load i32, i32* %9, align 4
  %31 = sext i32 %30 to i64
  %32 = getelementptr inbounds [3 x i8], [3 x i8]* %29, i64 %31
  %33 = getelementptr inbounds [3 x i8], [3 x i8]* %32, i64 0, i64 1
  store i8 %28, i8* %33, align 1
  %34 = load i8*, i8** %8, align 8
  %35 = load i32, i32* %9, align 4
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds i8, i8* %34, i64 %36
  %38 = load i8, i8* %37, align 1
  %39 = load [3 x i8]*, [3 x i8]** %5, align 8
  %40 = load i32, i32* %9, align 4
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds [3 x i8], [3 x i8]* %39, i64 %41
  %43 = getelementptr inbounds [3 x i8], [3 x i8]* %42, i64 0, i64 2
  store i8 %38, i8* %43, align 1
  br label %44

; <label>:44:                                     ; preds = %13
  %45 = load i32, i32* %9, align 4
  %46 = add nsw i32 %45, 1
  store i32 %46, i32* %9, align 4
  br label %10

; <label>:47:                                     ; preds = %10
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
  %61 = icmp sgt i32 %60, 1
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
