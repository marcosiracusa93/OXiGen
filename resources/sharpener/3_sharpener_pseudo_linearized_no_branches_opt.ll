; ModuleID = '3_sharpener_pseudo_linearized_no_branches.ll'
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
  %13 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %3, i32 0, i32 0
  %14 = bitcast [3 x i8]* %13 to i8*
  call void @read_bmp(i8* %10, i8* %14)
  %15 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %3, i32 0, i32 0
  %16 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %4, i32 0, i32 0
  call void @sharpen([3 x i8]* %15, [3 x i8]* %16)
  %17 = getelementptr inbounds [172800 x [3 x i8]], [172800 x [3 x i8]]* %4, i32 0, i32 0
  %18 = bitcast [3 x i8]* %17 to i8*
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
  %13 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %12
  %14 = getelementptr inbounds [3 x i8], [3 x i8]* %13, i64 0, i64 0
  %15 = load i8, i8* %14, align 1
  %16 = zext i8 %15 to i32
  %17 = sitofp i32 %16 to double
  %18 = fmul double 1.000000e-01, %17
  %19 = sext i32 %.02 to i64
  %20 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %19
  %21 = getelementptr inbounds [3 x i8], [3 x i8]* %20, i64 0, i64 1
  %22 = load i8, i8* %21, align 1
  %23 = zext i8 %22 to i32
  %24 = sitofp i32 %23 to double
  %25 = fmul double 6.000000e-01, %24
  %26 = fadd double %18, %25
  %27 = sext i32 %.02 to i64
  %28 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %27
  %29 = getelementptr inbounds [3 x i8], [3 x i8]* %28, i64 0, i64 2
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
  %128 = getelementptr inbounds [3 x i8], [3 x i8]* %0, i64 %127
  %129 = sext i32 %.08 to i64
  %130 = getelementptr inbounds [3 x i8], [3 x i8]* %128, i64 0, i64 %129
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
  %159 = getelementptr inbounds [3 x i8], [3 x i8]* %1, i64 %158
  %160 = sext i32 %.0 to i64
  %161 = getelementptr inbounds [3 x i8], [3 x i8]* %159, i64 0, i64 %160
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
