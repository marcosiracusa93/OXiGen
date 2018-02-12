; ModuleID = '7_sharpen_linearized_vectorized_2.ll'
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
  %3 = fmul float %0, %0
  %4 = fadd float %3, %0
  ret float %4
}

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
  %3 = alloca [172800 x [2 x [3 x i8]]], align 16
  %4 = alloca [172800 x [2 x [3 x i8]]], align 16
  %5 = icmp slt i32 %0, 3
  br i1 %5, label %6, label %8

; <label>:6:                                      ; preds = %2
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str, i32 0, i32 0))
  call void @exit(i32 1) #5
  unreachable

; <label>:8:                                      ; preds = %2
  %9 = getelementptr inbounds i8*, i8** %1, i64 1
  %10 = load i8*, i8** %9, align 8
  %11 = getelementptr inbounds i8*, i8** %1, i64 2
  %12 = load i8*, i8** %11, align 8
  %13 = getelementptr inbounds [172800 x [2 x [3 x i8]]], [172800 x [2 x [3 x i8]]]* %3, i32 0, i32 0
  %14 = bitcast [2 x [3 x i8]]* %13 to i8*
  call void @read_bmp(i8* %10, i8* %14)
  %15 = getelementptr inbounds [172800 x [2 x [3 x i8]]], [172800 x [2 x [3 x i8]]]* %3, i32 0, i32 0
  %16 = getelementptr inbounds [172800 x [2 x [3 x i8]]], [172800 x [2 x [3 x i8]]]* %4, i32 0, i32 0
  call void @sharpen([2 x [3 x i8]]* %15, [2 x [3 x i8]]* %16)
  %17 = getelementptr inbounds [172800 x [2 x [3 x i8]]], [172800 x [2 x [3 x i8]]]* %4, i32 0, i32 0
  %18 = bitcast [2 x [3 x i8]]* %17 to i8*
  call void @write_bmp(i8* %12, i8* %18)
  %19 = icmp sge i32 %0, 4
  br i1 %19, label %20, label %27

; <label>:20:                                     ; preds = %8
  %21 = getelementptr inbounds i8*, i8** %1, i64 3
  %22 = load i8*, i8** %21, align 8
  %23 = call i32 @validate_result(i8* %22, i8* %12, i32 1)
  %24 = icmp ne i32 %23, 0
  br i1 %24, label %26, label %25

; <label>:25:                                     ; preds = %20
  br label %28

; <label>:26:                                     ; preds = %20
  br label %27

; <label>:27:                                     ; preds = %26, %8
  br label %28

; <label>:28:                                     ; preds = %27, %25
  %.0 = phi i32 [ 0, %27 ], [ 1, %25 ]
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
define void @sharpen([2 x [3 x i8]]*, [2 x [3 x i8]]*) #0 {
  %3 = alloca [86400 x [2 x float]], align 16
  %4 = alloca [86400 x [2 x float]], align 16
  %5 = alloca [86400 x [2 x float]], align 16
  %6 = alloca [86400 x [2 x float]], align 16
  %7 = alloca [86400 x [2 x float]], align 16
  %8 = alloca [86400 x [2 x [3 x float]]], align 16
  br label %9

; <label>:9:                                      ; preds = %52, %2
  %.02 = phi i32 [ 0, %2 ], [ %53, %52 ]
  %10 = icmp slt i32 %.02, 86400
  br i1 %10, label %11, label %54

; <label>:11:                                     ; preds = %9
  br label %12

; <label>:12:                                     ; preds = %49, %11
  %.03 = phi i32 [ 0, %11 ], [ %50, %49 ]
  %13 = icmp slt i32 %.03, 2
  br i1 %13, label %14, label %51

; <label>:14:                                     ; preds = %12
  %15 = sext i32 %.02 to i64
  %16 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %15
  %17 = sext i32 %.03 to i64
  %18 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %16, i64 0, i64 %17
  %19 = getelementptr inbounds [3 x i8], [3 x i8]* %18, i64 0, i64 0
  %20 = load i8, i8* %19, align 1
  %21 = zext i8 %20 to i32
  %22 = sitofp i32 %21 to double
  %23 = fmul double 1.000000e-01, %22
  %24 = sext i32 %.02 to i64
  %25 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %24
  %26 = sext i32 %.03 to i64
  %27 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %25, i64 0, i64 %26
  %28 = getelementptr inbounds [3 x i8], [3 x i8]* %27, i64 0, i64 1
  %29 = load i8, i8* %28, align 1
  %30 = zext i8 %29 to i32
  %31 = sitofp i32 %30 to double
  %32 = fmul double 6.000000e-01, %31
  %33 = fadd double %23, %32
  %34 = sext i32 %.02 to i64
  %35 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %34
  %36 = sext i32 %.03 to i64
  %37 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %35, i64 0, i64 %36
  %38 = getelementptr inbounds [3 x i8], [3 x i8]* %37, i64 0, i64 2
  %39 = load i8, i8* %38, align 1
  %40 = zext i8 %39 to i32
  %41 = sitofp i32 %40 to double
  %42 = fmul double 3.000000e-01, %41
  %43 = fadd double %33, %42
  %44 = fptrunc double %43 to float
  %45 = sext i32 %.02 to i64
  %46 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %45
  %47 = sext i32 %.03 to i64
  %48 = getelementptr inbounds [2 x float], [2 x float]* %46, i64 0, i64 %47
  store float %44, float* %48, align 4
  br label %49

; <label>:49:                                     ; preds = %14
  %50 = add nsw i32 %.03, 1
  br label %12

; <label>:51:                                     ; preds = %12
  br label %52

; <label>:52:                                     ; preds = %51
  %53 = add nsw i32 %.02, 1
  br label %9

; <label>:54:                                     ; preds = %9
  br label %55

; <label>:55:                                     ; preds = %88, %54
  %.04 = phi i32 [ 180, %54 ], [ %89, %88 ]
  %56 = icmp slt i32 %.04, 86220
  br i1 %56, label %57, label %90

; <label>:57:                                     ; preds = %55
  br label %58

; <label>:58:                                     ; preds = %85, %57
  %.05 = phi i32 [ 0, %57 ], [ %86, %85 ]
  %59 = icmp slt i32 %.05, 2
  br i1 %59, label %60, label %87

; <label>:60:                                     ; preds = %58
  %61 = sub nsw i32 %.04, 180
  %62 = sext i32 %61 to i64
  %63 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %62
  %64 = sext i32 %.05 to i64
  %65 = getelementptr inbounds [2 x float], [2 x float]* %63, i64 0, i64 %64
  %66 = load float, float* %65, align 4
  %67 = sext i32 %.04 to i64
  %68 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %67
  %69 = sext i32 %.05 to i64
  %70 = getelementptr inbounds [2 x float], [2 x float]* %68, i64 0, i64 %69
  %71 = load float, float* %70, align 4
  %72 = fadd float %66, %71
  %73 = add nsw i32 %.04, 180
  %74 = sext i32 %73 to i64
  %75 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %74
  %76 = sext i32 %.05 to i64
  %77 = getelementptr inbounds [2 x float], [2 x float]* %75, i64 0, i64 %76
  %78 = load float, float* %77, align 4
  %79 = fadd float %72, %78
  %80 = fdiv float %79, 3.000000e+00
  %81 = sext i32 %.04 to i64
  %82 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %81
  %83 = sext i32 %.05 to i64
  %84 = getelementptr inbounds [2 x float], [2 x float]* %82, i64 0, i64 %83
  store float %80, float* %84, align 4
  br label %85

; <label>:85:                                     ; preds = %60
  %86 = add nsw i32 %.05, 1
  br label %58

; <label>:87:                                     ; preds = %58
  br label %88

; <label>:88:                                     ; preds = %87
  %89 = add nsw i32 %.04, 1
  br label %55

; <label>:90:                                     ; preds = %55
  br label %91

; <label>:91:                                     ; preds = %124, %90
  %.06 = phi i32 [ 180, %90 ], [ %125, %124 ]
  %92 = icmp slt i32 %.06, 86220
  br i1 %92, label %93, label %126

; <label>:93:                                     ; preds = %91
  br label %94

; <label>:94:                                     ; preds = %121, %93
  %.07 = phi i32 [ 0, %93 ], [ %122, %121 ]
  %95 = icmp slt i32 %.07, 2
  br i1 %95, label %96, label %123

; <label>:96:                                     ; preds = %94
  %97 = sub nsw i32 %.06, 1
  %98 = sext i32 %97 to i64
  %99 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %98
  %100 = sext i32 %.07 to i64
  %101 = getelementptr inbounds [2 x float], [2 x float]* %99, i64 0, i64 %100
  %102 = load float, float* %101, align 4
  %103 = sext i32 %.06 to i64
  %104 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %103
  %105 = sext i32 %.07 to i64
  %106 = getelementptr inbounds [2 x float], [2 x float]* %104, i64 0, i64 %105
  %107 = load float, float* %106, align 4
  %108 = fadd float %102, %107
  %109 = add nsw i32 %.06, 1
  %110 = sext i32 %109 to i64
  %111 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %110
  %112 = sext i32 %.07 to i64
  %113 = getelementptr inbounds [2 x float], [2 x float]* %111, i64 0, i64 %112
  %114 = load float, float* %113, align 4
  %115 = fadd float %108, %114
  %116 = fdiv float %115, 3.000000e+00
  %117 = sext i32 %.06 to i64
  %118 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %117
  %119 = sext i32 %.07 to i64
  %120 = getelementptr inbounds [2 x float], [2 x float]* %118, i64 0, i64 %119
  store float %116, float* %120, align 4
  br label %121

; <label>:121:                                    ; preds = %96
  %122 = add nsw i32 %.07, 1
  br label %94

; <label>:123:                                    ; preds = %94
  br label %124

; <label>:124:                                    ; preds = %123
  %125 = add nsw i32 %.06, 1
  br label %91

; <label>:126:                                    ; preds = %91
  br label %127

; <label>:127:                                    ; preds = %153, %126
  %.08 = phi i32 [ 0, %126 ], [ %154, %153 ]
  %128 = icmp slt i32 %.08, 86400
  br i1 %128, label %129, label %155

; <label>:129:                                    ; preds = %127
  br label %130

; <label>:130:                                    ; preds = %150, %129
  %.09 = phi i32 [ 0, %129 ], [ %151, %150 ]
  %131 = icmp slt i32 %.09, 2
  br i1 %131, label %132, label %152

; <label>:132:                                    ; preds = %130
  %133 = sext i32 %.08 to i64
  %134 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %133
  %135 = sext i32 %.09 to i64
  %136 = getelementptr inbounds [2 x float], [2 x float]* %134, i64 0, i64 %135
  %137 = load float, float* %136, align 4
  %138 = fmul float 2.000000e+00, %137
  %139 = sext i32 %.08 to i64
  %140 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %139
  %141 = sext i32 %.09 to i64
  %142 = getelementptr inbounds [2 x float], [2 x float]* %140, i64 0, i64 %141
  %143 = load float, float* %142, align 4
  %144 = fsub float %138, %143
  %145 = call float @fabs(float %144)
  %146 = sext i32 %.08 to i64
  %147 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %146
  %148 = sext i32 %.09 to i64
  %149 = getelementptr inbounds [2 x float], [2 x float]* %147, i64 0, i64 %148
  store float %145, float* %149, align 4
  br label %150

; <label>:150:                                    ; preds = %132
  %151 = add nsw i32 %.09, 1
  br label %130

; <label>:152:                                    ; preds = %130
  br label %153

; <label>:153:                                    ; preds = %152
  %154 = add nsw i32 %.08, 1
  br label %127

; <label>:155:                                    ; preds = %127
  br label %156

; <label>:156:                                    ; preds = %181, %155
  %.010 = phi i32 [ 0, %155 ], [ %182, %181 ]
  %157 = icmp slt i32 %.010, 86400
  br i1 %157, label %158, label %183

; <label>:158:                                    ; preds = %156
  br label %159

; <label>:159:                                    ; preds = %178, %158
  %.011 = phi i32 [ 0, %158 ], [ %179, %178 ]
  %160 = icmp slt i32 %.011, 2
  br i1 %160, label %161, label %180

; <label>:161:                                    ; preds = %159
  %162 = sext i32 %.010 to i64
  %163 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %162
  %164 = sext i32 %.011 to i64
  %165 = getelementptr inbounds [2 x float], [2 x float]* %163, i64 0, i64 %164
  %166 = load float, float* %165, align 4
  %167 = sext i32 %.010 to i64
  %168 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %167
  %169 = sext i32 %.011 to i64
  %170 = getelementptr inbounds [2 x float], [2 x float]* %168, i64 0, i64 %169
  %171 = load float, float* %170, align 4
  %172 = fadd float %171, 1.000000e+00
  %173 = fdiv float %166, %172
  %174 = sext i32 %.010 to i64
  %175 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %7, i64 0, i64 %174
  %176 = sext i32 %.011 to i64
  %177 = getelementptr inbounds [2 x float], [2 x float]* %175, i64 0, i64 %176
  store float %173, float* %177, align 4
  br label %178

; <label>:178:                                    ; preds = %161
  %179 = add nsw i32 %.011, 1
  br label %159

; <label>:180:                                    ; preds = %159
  br label %181

; <label>:181:                                    ; preds = %180
  %182 = add nsw i32 %.010, 1
  br label %156

; <label>:183:                                    ; preds = %156
  br label %184

; <label>:184:                                    ; preds = %220, %183
  %.012 = phi i32 [ 0, %183 ], [ %221, %220 ]
  %185 = icmp slt i32 %.012, 86400
  br i1 %185, label %186, label %222

; <label>:186:                                    ; preds = %184
  br label %187

; <label>:187:                                    ; preds = %217, %186
  %.013 = phi i32 [ 0, %186 ], [ %218, %217 ]
  %188 = icmp slt i32 %.013, 2
  br i1 %188, label %189, label %219

; <label>:189:                                    ; preds = %187
  br label %190

; <label>:190:                                    ; preds = %214, %189
  %.014 = phi i32 [ 0, %189 ], [ %215, %214 ]
  %191 = icmp slt i32 %.014, 3
  br i1 %191, label %192, label %216

; <label>:192:                                    ; preds = %190
  %193 = sext i32 %.012 to i64
  %194 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %7, i64 0, i64 %193
  %195 = sext i32 %.013 to i64
  %196 = getelementptr inbounds [2 x float], [2 x float]* %194, i64 0, i64 %195
  %197 = load float, float* %196, align 4
  %198 = sext i32 %.012 to i64
  %199 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %0, i64 %198
  %200 = sext i32 %.013 to i64
  %201 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %199, i64 0, i64 %200
  %202 = sext i32 %.014 to i64
  %203 = getelementptr inbounds [3 x i8], [3 x i8]* %201, i64 0, i64 %202
  %204 = load i8, i8* %203, align 1
  %205 = zext i8 %204 to i32
  %206 = sitofp i32 %205 to float
  %207 = fmul float %197, %206
  %208 = sext i32 %.012 to i64
  %209 = getelementptr inbounds [86400 x [2 x [3 x float]]], [86400 x [2 x [3 x float]]]* %8, i64 0, i64 %208
  %210 = sext i32 %.013 to i64
  %211 = getelementptr inbounds [2 x [3 x float]], [2 x [3 x float]]* %209, i64 0, i64 %210
  %212 = sext i32 %.014 to i64
  %213 = getelementptr inbounds [3 x float], [3 x float]* %211, i64 0, i64 %212
  store float %207, float* %213, align 4
  br label %214

; <label>:214:                                    ; preds = %192
  %215 = add nsw i32 %.014, 1
  br label %190

; <label>:216:                                    ; preds = %190
  br label %217

; <label>:217:                                    ; preds = %216
  %218 = add nsw i32 %.013, 1
  br label %187

; <label>:219:                                    ; preds = %187
  br label %220

; <label>:220:                                    ; preds = %219
  %221 = add nsw i32 %.012, 1
  br label %184

; <label>:222:                                    ; preds = %184
  br label %223

; <label>:223:                                    ; preds = %253, %222
  %.015 = phi i32 [ 0, %222 ], [ %254, %253 ]
  %224 = icmp slt i32 %.015, 86400
  br i1 %224, label %225, label %255

; <label>:225:                                    ; preds = %223
  br label %226

; <label>:226:                                    ; preds = %250, %225
  %.01 = phi i32 [ 0, %225 ], [ %251, %250 ]
  %227 = icmp slt i32 %.01, 2
  br i1 %227, label %228, label %252

; <label>:228:                                    ; preds = %226
  br label %229

; <label>:229:                                    ; preds = %247, %228
  %.0 = phi i32 [ 0, %228 ], [ %248, %247 ]
  %230 = icmp slt i32 %.0, 3
  br i1 %230, label %231, label %249

; <label>:231:                                    ; preds = %229
  %232 = sext i32 %.015 to i64
  %233 = getelementptr inbounds [86400 x [2 x [3 x float]]], [86400 x [2 x [3 x float]]]* %8, i64 0, i64 %232
  %234 = sext i32 %.01 to i64
  %235 = getelementptr inbounds [2 x [3 x float]], [2 x [3 x float]]* %233, i64 0, i64 %234
  %236 = sext i32 %.0 to i64
  %237 = getelementptr inbounds [3 x float], [3 x float]* %235, i64 0, i64 %236
  %238 = load float, float* %237, align 4
  %239 = call float @fmin(float %238, float 2.550000e+02)
  %240 = fptoui float %239 to i8
  %241 = sext i32 %.015 to i64
  %242 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %1, i64 %241
  %243 = sext i32 %.01 to i64
  %244 = getelementptr inbounds [2 x [3 x i8]], [2 x [3 x i8]]* %242, i64 0, i64 %243
  %245 = sext i32 %.0 to i64
  %246 = getelementptr inbounds [3 x i8], [3 x i8]* %244, i64 0, i64 %245
  store i8 %240, i8* %246, align 1
  br label %247

; <label>:247:                                    ; preds = %231
  %248 = add nsw i32 %.0, 1
  br label %229

; <label>:249:                                    ; preds = %229
  br label %250

; <label>:250:                                    ; preds = %249
  %251 = add nsw i32 %.01, 1
  br label %226

; <label>:252:                                    ; preds = %226
  br label %253

; <label>:253:                                    ; preds = %252
  %254 = add nsw i32 %.015, 1
  br label %223

; <label>:255:                                    ; preds = %223
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
  %38 = icmp sgt i32 %37, 0
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
