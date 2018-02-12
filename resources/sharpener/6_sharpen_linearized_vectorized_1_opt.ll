; ModuleID = '6_sharpen_linearized_vectorized_1.ll'
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
  %3 = alloca [86400 x [6 x i8]], align 16
  %4 = alloca [86400 x [6 x i8]], align 16
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
  %13 = getelementptr inbounds [86400 x [6 x i8]], [86400 x [6 x i8]]* %3, i32 0, i32 0
  %14 = bitcast [6 x i8]* %13 to i8*
  call void @read_bmp(i8* %10, i8* %14)
  %15 = getelementptr inbounds [86400 x [6 x i8]], [86400 x [6 x i8]]* %3, i32 0, i32 0
  %16 = getelementptr inbounds [86400 x [6 x i8]], [86400 x [6 x i8]]* %4, i32 0, i32 0
  call void @sharpen([6 x i8]* %15, [6 x i8]* %16)
  %17 = getelementptr inbounds [86400 x [6 x i8]], [86400 x [6 x i8]]* %4, i32 0, i32 0
  %18 = bitcast [6 x i8]* %17 to i8*
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
define void @sharpen([6 x i8]*, [6 x i8]*) #0 {
  %3 = alloca [86400 x [2 x float]], align 16
  %4 = alloca [86400 x [2 x float]], align 16
  %5 = alloca [86400 x [2 x float]], align 16
  %6 = alloca [86400 x [2 x float]], align 16
  %7 = alloca [86400 x [2 x float]], align 16
  %8 = alloca [86400 x [6 x float]], align 16
  br label %9

; <label>:9:                                      ; preds = %55, %2
  %.02 = phi i32 [ 0, %2 ], [ %56, %55 ]
  %10 = icmp slt i32 %.02, 86400
  br i1 %10, label %11, label %57

; <label>:11:                                     ; preds = %9
  br label %12

; <label>:12:                                     ; preds = %52, %11
  %.03 = phi i32 [ 0, %11 ], [ %53, %52 ]
  %13 = icmp slt i32 %.03, 2
  br i1 %13, label %14, label %54

; <label>:14:                                     ; preds = %12
  %15 = sext i32 %.02 to i64
  %16 = getelementptr inbounds [6 x i8], [6 x i8]* %0, i64 %15
  %17 = mul nsw i32 3, %.03
  %18 = add nsw i32 %17, 0
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds [6 x i8], [6 x i8]* %16, i64 0, i64 %19
  %21 = load i8, i8* %20, align 1
  %22 = zext i8 %21 to i32
  %23 = sitofp i32 %22 to double
  %24 = fmul double 1.000000e-01, %23
  %25 = sext i32 %.02 to i64
  %26 = getelementptr inbounds [6 x i8], [6 x i8]* %0, i64 %25
  %27 = mul nsw i32 3, %.03
  %28 = add nsw i32 %27, 1
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds [6 x i8], [6 x i8]* %26, i64 0, i64 %29
  %31 = load i8, i8* %30, align 1
  %32 = zext i8 %31 to i32
  %33 = sitofp i32 %32 to double
  %34 = fmul double 6.000000e-01, %33
  %35 = fadd double %24, %34
  %36 = sext i32 %.02 to i64
  %37 = getelementptr inbounds [6 x i8], [6 x i8]* %0, i64 %36
  %38 = mul nsw i32 3, %.03
  %39 = add nsw i32 %38, 2
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds [6 x i8], [6 x i8]* %37, i64 0, i64 %40
  %42 = load i8, i8* %41, align 1
  %43 = zext i8 %42 to i32
  %44 = sitofp i32 %43 to double
  %45 = fmul double 3.000000e-01, %44
  %46 = fadd double %35, %45
  %47 = fptrunc double %46 to float
  %48 = sext i32 %.02 to i64
  %49 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %48
  %50 = sext i32 %.03 to i64
  %51 = getelementptr inbounds [2 x float], [2 x float]* %49, i64 0, i64 %50
  store float %47, float* %51, align 4
  br label %52

; <label>:52:                                     ; preds = %14
  %53 = add nsw i32 %.03, 1
  br label %12

; <label>:54:                                     ; preds = %12
  br label %55

; <label>:55:                                     ; preds = %54
  %56 = add nsw i32 %.02, 1
  br label %9

; <label>:57:                                     ; preds = %9
  br label %58

; <label>:58:                                     ; preds = %91, %57
  %.04 = phi i32 [ 180, %57 ], [ %92, %91 ]
  %59 = icmp slt i32 %.04, 86220
  br i1 %59, label %60, label %93

; <label>:60:                                     ; preds = %58
  br label %61

; <label>:61:                                     ; preds = %88, %60
  %.05 = phi i32 [ 0, %60 ], [ %89, %88 ]
  %62 = icmp slt i32 %.05, 2
  br i1 %62, label %63, label %90

; <label>:63:                                     ; preds = %61
  %64 = sub nsw i32 %.04, 360
  %65 = sext i32 %64 to i64
  %66 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %65
  %67 = sext i32 %.05 to i64
  %68 = getelementptr inbounds [2 x float], [2 x float]* %66, i64 0, i64 %67
  %69 = load float, float* %68, align 4
  %70 = sext i32 %.04 to i64
  %71 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %70
  %72 = sext i32 %.05 to i64
  %73 = getelementptr inbounds [2 x float], [2 x float]* %71, i64 0, i64 %72
  %74 = load float, float* %73, align 4
  %75 = fadd float %69, %74
  %76 = add nsw i32 %.04, 360
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %77
  %79 = sext i32 %.05 to i64
  %80 = getelementptr inbounds [2 x float], [2 x float]* %78, i64 0, i64 %79
  %81 = load float, float* %80, align 4
  %82 = fadd float %75, %81
  %83 = fdiv float %82, 3.000000e+00
  %84 = sext i32 %.04 to i64
  %85 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %84
  %86 = sext i32 %.05 to i64
  %87 = getelementptr inbounds [2 x float], [2 x float]* %85, i64 0, i64 %86
  store float %83, float* %87, align 4
  br label %88

; <label>:88:                                     ; preds = %63
  %89 = add nsw i32 %.05, 1
  br label %61

; <label>:90:                                     ; preds = %61
  br label %91

; <label>:91:                                     ; preds = %90
  %92 = add nsw i32 %.04, 1
  br label %58

; <label>:93:                                     ; preds = %58
  br label %94

; <label>:94:                                     ; preds = %127, %93
  %.06 = phi i32 [ 180, %93 ], [ %128, %127 ]
  %95 = icmp slt i32 %.06, 86220
  br i1 %95, label %96, label %129

; <label>:96:                                     ; preds = %94
  br label %97

; <label>:97:                                     ; preds = %124, %96
  %.07 = phi i32 [ 0, %96 ], [ %125, %124 ]
  %98 = icmp slt i32 %.07, 2
  br i1 %98, label %99, label %126

; <label>:99:                                     ; preds = %97
  %100 = sub nsw i32 %.06, 1
  %101 = sext i32 %100 to i64
  %102 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %101
  %103 = sext i32 %.07 to i64
  %104 = getelementptr inbounds [2 x float], [2 x float]* %102, i64 0, i64 %103
  %105 = load float, float* %104, align 4
  %106 = sext i32 %.06 to i64
  %107 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %106
  %108 = sext i32 %.07 to i64
  %109 = getelementptr inbounds [2 x float], [2 x float]* %107, i64 0, i64 %108
  %110 = load float, float* %109, align 4
  %111 = fadd float %105, %110
  %112 = add nsw i32 %.06, 1
  %113 = sext i32 %112 to i64
  %114 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %4, i64 0, i64 %113
  %115 = sext i32 %.07 to i64
  %116 = getelementptr inbounds [2 x float], [2 x float]* %114, i64 0, i64 %115
  %117 = load float, float* %116, align 4
  %118 = fadd float %111, %117
  %119 = fdiv float %118, 3.000000e+00
  %120 = sext i32 %.06 to i64
  %121 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %120
  %122 = sext i32 %.07 to i64
  %123 = getelementptr inbounds [2 x float], [2 x float]* %121, i64 0, i64 %122
  store float %119, float* %123, align 4
  br label %124

; <label>:124:                                    ; preds = %99
  %125 = add nsw i32 %.07, 1
  br label %97

; <label>:126:                                    ; preds = %97
  br label %127

; <label>:127:                                    ; preds = %126
  %128 = add nsw i32 %.06, 1
  br label %94

; <label>:129:                                    ; preds = %94
  br label %130

; <label>:130:                                    ; preds = %156, %129
  %.08 = phi i32 [ 0, %129 ], [ %157, %156 ]
  %131 = icmp slt i32 %.08, 86400
  br i1 %131, label %132, label %158

; <label>:132:                                    ; preds = %130
  br label %133

; <label>:133:                                    ; preds = %153, %132
  %.09 = phi i32 [ 0, %132 ], [ %154, %153 ]
  %134 = icmp slt i32 %.09, 2
  br i1 %134, label %135, label %155

; <label>:135:                                    ; preds = %133
  %136 = sext i32 %.08 to i64
  %137 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %136
  %138 = sext i32 %.09 to i64
  %139 = getelementptr inbounds [2 x float], [2 x float]* %137, i64 0, i64 %138
  %140 = load float, float* %139, align 4
  %141 = fmul float 2.000000e+00, %140
  %142 = sext i32 %.08 to i64
  %143 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %5, i64 0, i64 %142
  %144 = sext i32 %.09 to i64
  %145 = getelementptr inbounds [2 x float], [2 x float]* %143, i64 0, i64 %144
  %146 = load float, float* %145, align 4
  %147 = fsub float %141, %146
  %148 = call float @fabs(float %147)
  %149 = sext i32 %.08 to i64
  %150 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %149
  %151 = sext i32 %.09 to i64
  %152 = getelementptr inbounds [2 x float], [2 x float]* %150, i64 0, i64 %151
  store float %148, float* %152, align 4
  br label %153

; <label>:153:                                    ; preds = %135
  %154 = add nsw i32 %.09, 1
  br label %133

; <label>:155:                                    ; preds = %133
  br label %156

; <label>:156:                                    ; preds = %155
  %157 = add nsw i32 %.08, 1
  br label %130

; <label>:158:                                    ; preds = %130
  br label %159

; <label>:159:                                    ; preds = %184, %158
  %.010 = phi i32 [ 0, %158 ], [ %185, %184 ]
  %160 = icmp slt i32 %.010, 86400
  br i1 %160, label %161, label %186

; <label>:161:                                    ; preds = %159
  br label %162

; <label>:162:                                    ; preds = %181, %161
  %.011 = phi i32 [ 0, %161 ], [ %182, %181 ]
  %163 = icmp slt i32 %.011, 2
  br i1 %163, label %164, label %183

; <label>:164:                                    ; preds = %162
  %165 = sext i32 %.010 to i64
  %166 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %6, i64 0, i64 %165
  %167 = sext i32 %.011 to i64
  %168 = getelementptr inbounds [2 x float], [2 x float]* %166, i64 0, i64 %167
  %169 = load float, float* %168, align 4
  %170 = sext i32 %.010 to i64
  %171 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %3, i64 0, i64 %170
  %172 = sext i32 %.011 to i64
  %173 = getelementptr inbounds [2 x float], [2 x float]* %171, i64 0, i64 %172
  %174 = load float, float* %173, align 4
  %175 = fadd float %174, 1.000000e+00
  %176 = fdiv float %169, %175
  %177 = sext i32 %.010 to i64
  %178 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %7, i64 0, i64 %177
  %179 = sext i32 %.011 to i64
  %180 = getelementptr inbounds [2 x float], [2 x float]* %178, i64 0, i64 %179
  store float %176, float* %180, align 4
  br label %181

; <label>:181:                                    ; preds = %164
  %182 = add nsw i32 %.011, 1
  br label %162

; <label>:183:                                    ; preds = %162
  br label %184

; <label>:184:                                    ; preds = %183
  %185 = add nsw i32 %.010, 1
  br label %159

; <label>:186:                                    ; preds = %159
  br label %187

; <label>:187:                                    ; preds = %223, %186
  %.012 = phi i32 [ 0, %186 ], [ %224, %223 ]
  %188 = icmp slt i32 %.012, 86400
  br i1 %188, label %189, label %225

; <label>:189:                                    ; preds = %187
  br label %190

; <label>:190:                                    ; preds = %220, %189
  %.013 = phi i32 [ 0, %189 ], [ %221, %220 ]
  %191 = icmp slt i32 %.013, 3
  br i1 %191, label %192, label %222

; <label>:192:                                    ; preds = %190
  br label %193

; <label>:193:                                    ; preds = %217, %192
  %.014 = phi i32 [ 0, %192 ], [ %218, %217 ]
  %194 = icmp slt i32 %.014, 2
  br i1 %194, label %195, label %219

; <label>:195:                                    ; preds = %193
  %196 = sext i32 %.012 to i64
  %197 = getelementptr inbounds [86400 x [2 x float]], [86400 x [2 x float]]* %7, i64 0, i64 %196
  %198 = sext i32 %.014 to i64
  %199 = getelementptr inbounds [2 x float], [2 x float]* %197, i64 0, i64 %198
  %200 = load float, float* %199, align 4
  %201 = sext i32 %.012 to i64
  %202 = getelementptr inbounds [6 x i8], [6 x i8]* %0, i64 %201
  %203 = mul nsw i32 3, %.014
  %204 = add nsw i32 %.013, %203
  %205 = sext i32 %204 to i64
  %206 = getelementptr inbounds [6 x i8], [6 x i8]* %202, i64 0, i64 %205
  %207 = load i8, i8* %206, align 1
  %208 = zext i8 %207 to i32
  %209 = sitofp i32 %208 to float
  %210 = fmul float %200, %209
  %211 = sext i32 %.012 to i64
  %212 = getelementptr inbounds [86400 x [6 x float]], [86400 x [6 x float]]* %8, i64 0, i64 %211
  %213 = mul nsw i32 3, %.014
  %214 = add nsw i32 %.013, %213
  %215 = sext i32 %214 to i64
  %216 = getelementptr inbounds [6 x float], [6 x float]* %212, i64 0, i64 %215
  store float %210, float* %216, align 4
  br label %217

; <label>:217:                                    ; preds = %195
  %218 = add nsw i32 %.014, 1
  br label %193

; <label>:219:                                    ; preds = %193
  br label %220

; <label>:220:                                    ; preds = %219
  %221 = add nsw i32 %.013, 1
  br label %190

; <label>:222:                                    ; preds = %190
  br label %223

; <label>:223:                                    ; preds = %222
  %224 = add nsw i32 %.012, 1
  br label %187

; <label>:225:                                    ; preds = %187
  br label %226

; <label>:226:                                    ; preds = %256, %225
  %.015 = phi i32 [ 0, %225 ], [ %257, %256 ]
  %227 = icmp slt i32 %.015, 86400
  br i1 %227, label %228, label %258

; <label>:228:                                    ; preds = %226
  br label %229

; <label>:229:                                    ; preds = %253, %228
  %.01 = phi i32 [ 0, %228 ], [ %254, %253 ]
  %230 = icmp slt i32 %.01, 3
  br i1 %230, label %231, label %255

; <label>:231:                                    ; preds = %229
  br label %232

; <label>:232:                                    ; preds = %250, %231
  %.0 = phi i32 [ 0, %231 ], [ %251, %250 ]
  %233 = icmp slt i32 %.0, 2
  br i1 %233, label %234, label %252

; <label>:234:                                    ; preds = %232
  %235 = sext i32 %.015 to i64
  %236 = getelementptr inbounds [86400 x [6 x float]], [86400 x [6 x float]]* %8, i64 0, i64 %235
  %237 = mul nsw i32 3, %.0
  %238 = add nsw i32 %.01, %237
  %239 = sext i32 %238 to i64
  %240 = getelementptr inbounds [6 x float], [6 x float]* %236, i64 0, i64 %239
  %241 = load float, float* %240, align 4
  %242 = call float @fmin(float %241, float 2.550000e+02)
  %243 = fptoui float %242 to i8
  %244 = sext i32 %.015 to i64
  %245 = getelementptr inbounds [6 x i8], [6 x i8]* %1, i64 %244
  %246 = mul nsw i32 3, %.0
  %247 = add nsw i32 %.01, %246
  %248 = sext i32 %247 to i64
  %249 = getelementptr inbounds [6 x i8], [6 x i8]* %245, i64 0, i64 %248
  store i8 %243, i8* %249, align 1
  br label %250

; <label>:250:                                    ; preds = %234
  %251 = add nsw i32 %.0, 1
  br label %232

; <label>:252:                                    ; preds = %232
  br label %253

; <label>:253:                                    ; preds = %252
  %254 = add nsw i32 %.01, 1
  br label %229

; <label>:255:                                    ; preds = %229
  br label %256

; <label>:256:                                    ; preds = %255
  %257 = add nsw i32 %.015, 1
  br label %226

; <label>:258:                                    ; preds = %226
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
