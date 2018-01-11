; ModuleID = '1_sharpener_oxygen_friendly.ll'
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
define i32 @main(i32, i8**) #0 {
  %3 = alloca [172800 x [3 x i8]], align 16
  %4 = alloca [172800 x [3 x i8]], align 16
  %5 = alloca [172800 x i8], align 16
  %6 = alloca [172800 x i8], align 16
  %7 = alloca [172800 x i8], align 16
  %8 = alloca [172800 x i8], align 16
  %9 = alloca [172800 x i8], align 16
  %10 = alloca [172800 x i8], align 16
  %11 = icmp slt i32 %0, 3
  br i1 %11, label %12, label %14

; <label>:12:                                     ; preds = %2
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str, i32 0, i32 0))
  call void @exit(i32 1) #5
  unreachable

; <label>:14:                                     ; preds = %2
  %15 = getelementptr inbounds i8*, i8** %1, i64 1
  %16 = load i8*, i8** %15, align 8
  %17 = getelementptr inbounds i8*, i8** %1, i64 2
  %18 = load i8*, i8** %17, align 8
  %19 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %3, i32 0, i32 0
  %20 = bitcast [3 x i8]* %19 to i8*
  call void @read_bmp(i8* %16, i8* %20)
  %21 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %3, i32 0, i32 0
  %22 = getelementptr inbounds [172800 x i8], [172800 x i8]* %5, i32 0, i32 0
  %23 = getelementptr inbounds [172800 x i8], [172800 x i8]* %6, i32 0, i32 0
  %24 = getelementptr inbounds [172800 x i8], [172800 x i8]* %7, i32 0, i32 0
  call void @deinterleave([3 x i8]* %21, i8* %22, i8* %23, i8* %24)
  %25 = getelementptr inbounds [172800 x i8], [172800 x i8]* %5, i32 0, i32 0
  %26 = getelementptr inbounds [172800 x i8], [172800 x i8]* %6, i32 0, i32 0
  %27 = getelementptr inbounds [172800 x i8], [172800 x i8]* %7, i32 0, i32 0
  %28 = getelementptr inbounds [172800 x i8], [172800 x i8]* %8, i32 0, i32 0
  %29 = getelementptr inbounds [172800 x i8], [172800 x i8]* %9, i32 0, i32 0
  %30 = getelementptr inbounds [172800 x i8], [172800 x i8]* %10, i32 0, i32 0
  call void @sharpen(i8* %25, i8* %26, i8* %27, i8* %28, i8* %29, i8* %30)
  %31 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %4, i32 0, i32 0
  %32 = getelementptr inbounds [172800 x i8], [172800 x i8]* %8, i32 0, i32 0
  %33 = getelementptr inbounds [172800 x i8], [172800 x i8]* %9, i32 0, i32 0
  %34 = getelementptr inbounds [172800 x i8], [172800 x i8]* %10, i32 0, i32 0
  call void @interleave([3 x i8]* %31, i8* %32, i8* %33, i8* %34)
  %35 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %4, i32 0, i32 0
  %36 = bitcast [3 x i8]* %35 to i8*
  call void @write_bmp(i8* %18, i8* %36)
  %37 = icmp sge i32 %0, 4
  br i1 %37, label %38, label %45

; <label>:38:                                     ; preds = %14
  %39 = getelementptr inbounds i8*, i8** %1, i64 3
  %40 = load i8*, i8** %39, align 8
  %41 = call i32 @validate_result(i8* %40, i8* %18, i32 1)
  %42 = icmp ne i32 %41, 0
  br i1 %42, label %44, label %43

; <label>:43:                                     ; preds = %38
  br label %46

; <label>:44:                                     ; preds = %38
  br label %45

; <label>:45:                                     ; preds = %44, %14
  br label %46

; <label>:46:                                     ; preds = %45, %43
  %.0 = phi i32 [ 0, %45 ], [ 1, %43 ]
  ret i32 %.0
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: noreturn nounwind
declare void @exit(i32) #3

; Function Attrs: noinline nounwind uwtable
define void @read_bmp(i8*, i8*) #0 {
  %3 = alloca [54 x i8], align 16
  %4 = call %struct._IO_FILE* @fopen(i8* %0, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0))
  %5 = icmp ne %struct._IO_FILE* %4, null
  br i1 %5, label %8, label %6

; <label>:6:                                      ; preds = %2
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.4, i32 0, i32 0), i8* %0)
  call void @exit(i32 1) #5
  unreachable

; <label>:8:                                      ; preds = %2
  %9 = getelementptr inbounds [54 x i8], [54 x i8]* %3, i32 0, i32 0
  %10 = call i64 @fread(i8* %9, i64 1, i64 54, %struct._IO_FILE* %4)
  %11 = getelementptr inbounds [54 x i8], [54 x i8]* %3, i64 0, i64 18
  %12 = bitcast i8* %11 to i32*
  %13 = load i32, i32* %12, align 2
  %14 = getelementptr inbounds [54 x i8], [54 x i8]* %3, i64 0, i64 22
  %15 = bitcast i8* %14 to i32*
  %16 = load i32, i32* %15, align 2
  %17 = icmp ne i32 %13, 360
  br i1 %17, label %20, label %18

; <label>:18:                                     ; preds = %8
  %19 = icmp ne i32 %16, 480
  br i1 %19, label %20, label %24

; <label>:20:                                     ; preds = %18, %8
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.5, i32 0, i32 0))
  %22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.6, i32 0, i32 0), i32 %13, i32 %16)
  %23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.7, i32 0, i32 0), i32 360, i32 480)
  call void @exit(i32 1) #5
  unreachable

; <label>:24:                                     ; preds = %18
  %25 = mul nsw i32 3, %13
  %26 = mul nsw i32 %25, %16
  %27 = sext i32 %26 to i64
  %28 = call i64 @fread(i8* %1, i64 1, i64 %27, %struct._IO_FILE* %4)
  %29 = call i32 @fclose(%struct._IO_FILE* %4)
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @deinterleave([3 x i8]*, i8*, i8*, i8*) #0 {
  br label %5

; <label>:5:                                      ; preds = %26, %4
  %.0 = phi i32 [ 0, %4 ], [ %27, %26 ]
  %6 = icmp slt i32 %.0, 172800
  br i1 %6, label %7, label %28

; <label>:7:                                      ; preds = %5
  %8 = sext i32 %.0 to i64
  %9 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %8
  %10 = getelementptr inbounds [3 x i8], [3 x i8]* %9, i64 0, i64 0
  %11 = load i8, i8* %10, align 1
  %12 = sext i32 %.0 to i64
  %13 = getelementptr inbounds i8, i8* %1, i64 %12
  store i8 %11, i8* %13, align 1
  %14 = sext i32 %.0 to i64
  %15 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %14
  %16 = getelementptr inbounds [3 x i8], [3 x i8]* %15, i64 0, i64 1
  %17 = load i8, i8* %16, align 1
  %18 = sext i32 %.0 to i64
  %19 = getelementptr inbounds i8, i8* %2, i64 %18
  store i8 %17, i8* %19, align 1
  %20 = sext i32 %.0 to i64
  %21 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %20
  %22 = getelementptr inbounds [3 x i8], [3 x i8]* %21, i64 0, i64 2
  %23 = load i8, i8* %22, align 1
  %24 = sext i32 %.0 to i64
  %25 = getelementptr inbounds i8, i8* %3, i64 %24
  store i8 %23, i8* %25, align 1
  br label %26

; <label>:26:                                     ; preds = %7
  %27 = add nsw i32 %.0, 1
  br label %5

; <label>:28:                                     ; preds = %5
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @sharpen(i8*, i8*, i8*, i8*, i8*, i8*) #0 {
  %7 = alloca [172800 x float], align 16
  %8 = alloca [172800 x float], align 16
  %9 = alloca [172800 x float], align 16
  %10 = alloca [172800 x float], align 16
  %11 = alloca [172800 x float], align 16
  br label %12

; <label>:12:                                     ; preds = %38, %6
  %.05 = phi i32 [ 0, %6 ], [ %39, %38 ]
  %13 = icmp slt i32 %.05, 172800
  br i1 %13, label %14, label %40

; <label>:14:                                     ; preds = %12
  %15 = sext i32 %.05 to i64
  %16 = getelementptr inbounds i8, i8* %0, i64 %15
  %17 = load i8, i8* %16, align 1
  %18 = zext i8 %17 to i32
  %19 = sitofp i32 %18 to double
  %20 = fmul double 1.000000e-01, %19
  %21 = sext i32 %.05 to i64
  %22 = getelementptr inbounds i8, i8* %1, i64 %21
  %23 = load i8, i8* %22, align 1
  %24 = zext i8 %23 to i32
  %25 = sitofp i32 %24 to double
  %26 = fmul double 6.000000e-01, %25
  %27 = fadd double %20, %26
  %28 = sext i32 %.05 to i64
  %29 = getelementptr inbounds i8, i8* %2, i64 %28
  %30 = load i8, i8* %29, align 1
  %31 = zext i8 %30 to i32
  %32 = sitofp i32 %31 to double
  %33 = fmul double 3.000000e-01, %32
  %34 = fadd double %27, %33
  %35 = fptrunc double %34 to float
  %36 = sext i32 %.05 to i64
  %37 = getelementptr inbounds [172800 x float], [172800 x float]* %7, i64 0, i64 %36
  store float %35, float* %37, align 4
  br label %38

; <label>:38:                                     ; preds = %14
  %39 = add nsw i32 %.05, 1
  br label %12

; <label>:40:                                     ; preds = %12
  br label %41

; <label>:41:                                     ; preds = %60, %40
  %.04 = phi i32 [ 360, %40 ], [ %61, %60 ]
  %42 = icmp slt i32 %.04, 172440
  br i1 %42, label %43, label %62

; <label>:43:                                     ; preds = %41
  %44 = sub nsw i32 %.04, 360
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds [172800 x float], [172800 x float]* %7, i64 0, i64 %45
  %47 = load float, float* %46, align 4
  %48 = sext i32 %.04 to i64
  %49 = getelementptr inbounds [172800 x float], [172800 x float]* %7, i64 0, i64 %48
  %50 = load float, float* %49, align 4
  %51 = fadd float %47, %50
  %52 = add nsw i32 %.04, 360
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds [172800 x float], [172800 x float]* %7, i64 0, i64 %53
  %55 = load float, float* %54, align 4
  %56 = fadd float %51, %55
  %57 = fdiv float %56, 3.000000e+00
  %58 = sext i32 %.04 to i64
  %59 = getelementptr inbounds [172800 x float], [172800 x float]* %8, i64 0, i64 %58
  store float %57, float* %59, align 4
  br label %60

; <label>:60:                                     ; preds = %43
  %61 = add nsw i32 %.04, 1
  br label %41

; <label>:62:                                     ; preds = %41
  br label %63

; <label>:63:                                     ; preds = %82, %62
  %.03 = phi i32 [ 360, %62 ], [ %83, %82 ]
  %64 = icmp slt i32 %.03, 172440
  br i1 %64, label %65, label %84

; <label>:65:                                     ; preds = %63
  %66 = sub nsw i32 %.03, 1
  %67 = sext i32 %66 to i64
  %68 = getelementptr inbounds [172800 x float], [172800 x float]* %8, i64 0, i64 %67
  %69 = load float, float* %68, align 4
  %70 = sext i32 %.03 to i64
  %71 = getelementptr inbounds [172800 x float], [172800 x float]* %8, i64 0, i64 %70
  %72 = load float, float* %71, align 4
  %73 = fadd float %69, %72
  %74 = add nsw i32 %.03, 1
  %75 = sext i32 %74 to i64
  %76 = getelementptr inbounds [172800 x float], [172800 x float]* %8, i64 0, i64 %75
  %77 = load float, float* %76, align 4
  %78 = fadd float %73, %77
  %79 = fdiv float %78, 3.000000e+00
  %80 = sext i32 %.03 to i64
  %81 = getelementptr inbounds [172800 x float], [172800 x float]* %9, i64 0, i64 %80
  store float %79, float* %81, align 4
  br label %82

; <label>:82:                                     ; preds = %65
  %83 = add nsw i32 %.03, 1
  br label %63

; <label>:84:                                     ; preds = %63
  br label %85

; <label>:85:                                     ; preds = %99, %84
  %.02 = phi i32 [ 360, %84 ], [ %100, %99 ]
  %86 = icmp slt i32 %.02, 172440
  br i1 %86, label %87, label %101

; <label>:87:                                     ; preds = %85
  %88 = sext i32 %.02 to i64
  %89 = getelementptr inbounds [172800 x float], [172800 x float]* %7, i64 0, i64 %88
  %90 = load float, float* %89, align 4
  %91 = fmul float 2.000000e+00, %90
  %92 = sext i32 %.02 to i64
  %93 = getelementptr inbounds [172800 x float], [172800 x float]* %9, i64 0, i64 %92
  %94 = load float, float* %93, align 4
  %95 = fsub float %91, %94
  %96 = call float @fabs(float %95)
  %97 = sext i32 %.02 to i64
  %98 = getelementptr inbounds [172800 x float], [172800 x float]* %10, i64 0, i64 %97
  store float %96, float* %98, align 4
  br label %99

; <label>:99:                                     ; preds = %87
  %100 = add nsw i32 %.02, 1
  br label %85

; <label>:101:                                    ; preds = %85
  br label %102

; <label>:102:                                    ; preds = %115, %101
  %.01 = phi i32 [ 360, %101 ], [ %116, %115 ]
  %103 = icmp slt i32 %.01, 172440
  br i1 %103, label %104, label %117

; <label>:104:                                    ; preds = %102
  %105 = sext i32 %.01 to i64
  %106 = getelementptr inbounds [172800 x float], [172800 x float]* %10, i64 0, i64 %105
  %107 = load float, float* %106, align 4
  %108 = sext i32 %.01 to i64
  %109 = getelementptr inbounds [172800 x float], [172800 x float]* %7, i64 0, i64 %108
  %110 = load float, float* %109, align 4
  %111 = fadd float %110, 1.000000e+00
  %112 = fdiv float %107, %111
  %113 = sext i32 %.01 to i64
  %114 = getelementptr inbounds [172800 x float], [172800 x float]* %11, i64 0, i64 %113
  store float %112, float* %114, align 4
  br label %115

; <label>:115:                                    ; preds = %104
  %116 = add nsw i32 %.01, 1
  br label %102

; <label>:117:                                    ; preds = %102
  br label %118

; <label>:118:                                    ; preds = %160, %117
  %.0 = phi i32 [ 360, %117 ], [ %161, %160 ]
  %119 = icmp slt i32 %.0, 172440
  br i1 %119, label %120, label %162

; <label>:120:                                    ; preds = %118
  %121 = sext i32 %.0 to i64
  %122 = getelementptr inbounds [172800 x float], [172800 x float]* %11, i64 0, i64 %121
  %123 = load float, float* %122, align 4
  %124 = sext i32 %.0 to i64
  %125 = getelementptr inbounds i8, i8* %0, i64 %124
  %126 = load i8, i8* %125, align 1
  %127 = zext i8 %126 to i32
  %128 = sitofp i32 %127 to float
  %129 = fmul float %123, %128
  %130 = call float @fmin(float %129, float 2.550000e+02)
  %131 = fptoui float %130 to i8
  %132 = sext i32 %.0 to i64
  %133 = getelementptr inbounds i8, i8* %3, i64 %132
  store i8 %131, i8* %133, align 1
  %134 = sext i32 %.0 to i64
  %135 = getelementptr inbounds [172800 x float], [172800 x float]* %11, i64 0, i64 %134
  %136 = load float, float* %135, align 4
  %137 = sext i32 %.0 to i64
  %138 = getelementptr inbounds i8, i8* %1, i64 %137
  %139 = load i8, i8* %138, align 1
  %140 = zext i8 %139 to i32
  %141 = sitofp i32 %140 to float
  %142 = fmul float %136, %141
  %143 = call float @fmin(float %142, float 2.550000e+02)
  %144 = fptoui float %143 to i8
  %145 = sext i32 %.0 to i64
  %146 = getelementptr inbounds i8, i8* %4, i64 %145
  store i8 %144, i8* %146, align 1
  %147 = sext i32 %.0 to i64
  %148 = getelementptr inbounds [172800 x float], [172800 x float]* %11, i64 0, i64 %147
  %149 = load float, float* %148, align 4
  %150 = sext i32 %.0 to i64
  %151 = getelementptr inbounds i8, i8* %2, i64 %150
  %152 = load i8, i8* %151, align 1
  %153 = zext i8 %152 to i32
  %154 = sitofp i32 %153 to float
  %155 = fmul float %149, %154
  %156 = call float @fmin(float %155, float 2.550000e+02)
  %157 = fptoui float %156 to i8
  %158 = sext i32 %.0 to i64
  %159 = getelementptr inbounds i8, i8* %5, i64 %158
  store i8 %157, i8* %159, align 1
  br label %160

; <label>:160:                                    ; preds = %120
  %161 = add nsw i32 %.0, 1
  br label %118

; <label>:162:                                    ; preds = %118
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @interleave([3 x i8]*, i8*, i8*, i8*) #0 {
  br label %5

; <label>:5:                                      ; preds = %26, %4
  %.0 = phi i32 [ 0, %4 ], [ %27, %26 ]
  %6 = icmp slt i32 %.0, 172800
  br i1 %6, label %7, label %28

; <label>:7:                                      ; preds = %5
  %8 = sext i32 %.0 to i64
  %9 = getelementptr inbounds i8, i8* %1, i64 %8
  %10 = load i8, i8* %9, align 1
  %11 = sext i32 %.0 to i64
  %12 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %11
  %13 = getelementptr inbounds [3 x i8], [3 x i8]* %12, i64 0, i64 0
  store i8 %10, i8* %13, align 1
  %14 = sext i32 %.0 to i64
  %15 = getelementptr inbounds i8, i8* %2, i64 %14
  %16 = load i8, i8* %15, align 1
  %17 = sext i32 %.0 to i64
  %18 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %17
  %19 = getelementptr inbounds [3 x i8], [3 x i8]* %18, i64 0, i64 1
  store i8 %16, i8* %19, align 1
  %20 = sext i32 %.0 to i64
  %21 = getelementptr inbounds i8, i8* %3, i64 %20
  %22 = load i8, i8* %21, align 1
  %23 = sext i32 %.0 to i64
  %24 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %23
  %25 = getelementptr inbounds [3 x i8], [3 x i8]* %24, i64 0, i64 2
  store i8 %22, i8* %25, align 1
  br label %26

; <label>:26:                                     ; preds = %7
  %27 = add nsw i32 %.0, 1
  br label %5

; <label>:28:                                     ; preds = %5
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @write_bmp(i8*, i8*) #0 {
  %3 = alloca [54 x i8], align 16
  %4 = bitcast [54 x i8]* %3 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %4, i8* getelementptr inbounds ([54 x i8], [54 x i8]* @write_bmp.header, i32 0, i32 0), i64 54, i32 16, i1 false)
  %5 = getelementptr inbounds [54 x i8], [54 x i8]* %3, i64 0, i64 18
  %6 = bitcast i8* %5 to i32*
  store i32 360, i32* %6, align 2
  %7 = getelementptr inbounds [54 x i8], [54 x i8]* %3, i64 0, i64 22
  %8 = bitcast i8* %7 to i32*
  store i32 480, i32* %8, align 2
  %9 = call %struct._IO_FILE* @fopen(i8* %0, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0))
  %10 = icmp ne %struct._IO_FILE* %9, null
  br i1 %10, label %13, label %11

; <label>:11:                                     ; preds = %2
  %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.2, i32 0, i32 0), i8* %0)
  call void @exit(i32 1) #5
  unreachable

; <label>:13:                                     ; preds = %2
  %14 = getelementptr inbounds [54 x i8], [54 x i8]* %3, i32 0, i32 0
  %15 = call i64 @fwrite(i8* %14, i64 1, i64 54, %struct._IO_FILE* %9)
  %16 = sext i32 518400 to i64
  %17 = call i64 @fwrite(i8* %1, i64 1, i64 %16, %struct._IO_FILE* %9)
  %18 = call i32 @fclose(%struct._IO_FILE* %9)
  ret void
}

; Function Attrs: noinline nounwind uwtable
define i32 @validate_result(i8*, i8*, i32) #0 {
  %4 = alloca [518400 x i8], align 16
  %5 = alloca [518400 x i8], align 16
  %6 = getelementptr inbounds [518400 x i8], [518400 x i8]* %4, i32 0, i32 0
  call void @read_bmp(i8* %1, i8* %6)
  %7 = getelementptr inbounds [518400 x i8], [518400 x i8]* %5, i32 0, i32 0
  call void @read_bmp(i8* %0, i8* %7)
  br label %8

; <label>:8:                                      ; preds = %45, %3
  %.03 = phi i32 [ 0, %3 ], [ %.3, %45 ]
  %.02 = phi i32 [ 0, %3 ], [ %.2, %45 ]
  %.01 = phi i32 [ 0, %3 ], [ %46, %45 ]
  %9 = icmp slt i32 %.01, 518400
  br i1 %9, label %10, label %47

; <label>:10:                                     ; preds = %8
  %11 = sdiv i32 %.01, 3
  %12 = srem i32 %11, 360
  %13 = sdiv i32 %.01, 3
  %14 = sdiv i32 %13, 360
  %15 = icmp ne i32 %2, 0
  br i1 %15, label %16, label %25

; <label>:16:                                     ; preds = %10
  %17 = icmp eq i32 %12, 0
  br i1 %17, label %24, label %18

; <label>:18:                                     ; preds = %16
  %19 = icmp eq i32 %14, 0
  br i1 %19, label %24, label %20

; <label>:20:                                     ; preds = %18
  %21 = icmp eq i32 %12, 359
  br i1 %21, label %24, label %22

; <label>:22:                                     ; preds = %20
  %23 = icmp eq i32 %14, 479
  br i1 %23, label %24, label %25

; <label>:24:                                     ; preds = %22, %20, %18, %16
  br label %45

; <label>:25:                                     ; preds = %22, %10
  %26 = getelementptr inbounds [518400 x i8], [518400 x i8]* %4, i32 0, i32 0
  %27 = sext i32 %.01 to i64
  %28 = getelementptr inbounds i8, i8* %26, i64 %27
  %29 = load i8, i8* %28, align 1
  %30 = zext i8 %29 to i32
  %31 = getelementptr inbounds [518400 x i8], [518400 x i8]* %5, i32 0, i32 0
  %32 = sext i32 %.01 to i64
  %33 = getelementptr inbounds i8, i8* %31, i64 %32
  %34 = load i8, i8* %33, align 1
  %35 = zext i8 %34 to i32
  %36 = sub nsw i32 %30, %35
  %37 = call i32 @abs(i32 %36) #6
  %38 = icmp sgt i32 %37, 1
  br i1 %38, label %39, label %44

; <label>:39:                                     ; preds = %25
  %40 = add nsw i32 %.02, 1
  %41 = icmp sgt i32 %37, %.03
  br i1 %41, label %42, label %43

; <label>:42:                                     ; preds = %39
  br label %43

; <label>:43:                                     ; preds = %42, %39
  %.14 = phi i32 [ %37, %42 ], [ %.03, %39 ]
  br label %44

; <label>:44:                                     ; preds = %43, %25
  %.25 = phi i32 [ %.14, %43 ], [ %.03, %25 ]
  %.1 = phi i32 [ %40, %43 ], [ %.02, %25 ]
  br label %45

; <label>:45:                                     ; preds = %44, %24
  %.3 = phi i32 [ %.03, %24 ], [ %.25, %44 ]
  %.2 = phi i32 [ %.02, %24 ], [ %.1, %44 ]
  %46 = add nsw i32 %.01, 1
  br label %8

; <label>:47:                                     ; preds = %8
  %48 = icmp sgt i32 %.02, 0
  br i1 %48, label %49, label %51

; <label>:49:                                     ; preds = %47
  %50 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.8, i32 0, i32 0), i32 %.02, i32 %.03)
  br label %53

; <label>:51:                                     ; preds = %47
  %52 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.9, i32 0, i32 0))
  br label %53

; <label>:53:                                     ; preds = %51, %49
  %.0 = phi i32 [ 0, %49 ], [ 1, %51 ]
  ret i32 %.0
}

declare float @fmin(float, float) #2

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
