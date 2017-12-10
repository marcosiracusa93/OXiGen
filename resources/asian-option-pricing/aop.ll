; ModuleID = 'aop.c'
source_filename = "aop.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.timeval = type { i64, i64 }
%struct.timezone = type { i32, i32 }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@SQRT_2PI = global float 0x40040D9320000000, align 4
@d_A = global [6 x float] [float 0.000000e+00, float 0x400949FB40000000, float 0x405C774E40000000, float 0x407797C380000000, float 0x40A912C160000000, float 0x3FC7C79060000000], align 16
@d_B = global [5 x float] [float 0.000000e+00, float 0x403799EE40000000, float 0x406E80C9E0000000, float 0x40940A7760000000, float 0x40A6387940000000], align 16
@d_C = global [10 x float] [float 0.000000e+00, float 0x3FE20DD500000000, float 0x4021C42C40000000, float 0x405087A0E0000000, float 0x4072AA2980000000, float 0x408B8F9E20000000, float 0x409AC030C0000000, float 0x40A0062820000000, float 0x4093395B80000000, float 0x3E571E7040000000], align 16
@d_D = global [9 x float] [float 0.000000e+00, float 0x402F7D6700000000, float 0x405D6C69C0000000, float 0x4080C972E0000000, float 0x4099558EE0000000, float 0x40A9B59940000000, float 0x40B10A9E80000000, float 0x40AADEBC40000000, float 0x4093395B80000000], align 16
@d_P = global [7 x float] [float 0.000000e+00, float 0x3FD38A78C0000000, float 0x3FD70FE400000000, float 0x3FC0199DA0000000, float 0x3F90784480000000, float 0x3F4595FD00000000, float 0x3F90B4FB20000000], align 16
@d_Q = global [6 x float] [float 0.000000e+00, float 0x40048C5460000000, float 0x3FFDF79D60000000, float 0x3FE0E49940000000, float 0x3FAEFC42A0000000, float 0x3F632147A0000000], align 16
@.str = private unnamed_addr constant [49 x i8] c"missing parameters. Run as: ./program RANGE_FILE\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.2 = private unnamed_addr constant [44 x i8] c"Error during the opening of the input file!\00", align 1
@.str.3 = private unnamed_addr constant [7 x i8] c"Done!\0A\00", align 1
@.str.4 = private unnamed_addr constant [24 x i8] c"Read the input data...\0A\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"%lu\00", align 1
@.str.6 = private unnamed_addr constant [6 x i8] c"%f %f\00", align 1
@.str.7 = private unnamed_addr constant [8 x i8] c"%hd %hd\00", align 1
@.str.8 = private unnamed_addr constant [33 x i8] c"Problem reading files, ave is %d\00", align 1
@.str.9 = private unnamed_addr constant [25 x i8] c"Starting computation...\0A\00", align 1
@.str.10 = private unnamed_addr constant [29 x i8] c"Execution time: %lf seconds\0A\00", align 1
@.str.11 = private unnamed_addr constant [5 x i8] c"End\0A\00", align 1

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
define i64 @getTime() #0 {
  %1 = alloca %struct.timeval, align 8
  %2 = call i32 @gettimeofday(%struct.timeval* %1, %struct.timezone* null) #4
  %3 = getelementptr inbounds %struct.timeval, %struct.timeval* %1, i32 0, i32 0
  %4 = load i64, i64* %3, align 8
  %5 = mul nsw i64 %4, 1000
  %6 = mul nsw i64 %5, 1000
  %7 = getelementptr inbounds %struct.timeval, %struct.timeval* %1, i32 0, i32 1
  %8 = load i64, i64* %7, align 8
  %9 = add nsw i64 %6, %8
  ret i64 %9
}

; Function Attrs: nounwind
declare i32 @gettimeofday(%struct.timeval*, %struct.timezone*) #2

; Function Attrs: noinline nounwind uwtable
define void @Calculation(i32*, float*, float*, float*, float*, i16*, i16*, float*, float*, float*, float*, i64) #0 {
  %13 = alloca i32*, align 8
  %14 = alloca float*, align 8
  %15 = alloca float*, align 8
  %16 = alloca float*, align 8
  %17 = alloca float*, align 8
  %18 = alloca i16*, align 8
  %19 = alloca i16*, align 8
  %20 = alloca float*, align 8
  %21 = alloca float*, align 8
  %22 = alloca float*, align 8
  %23 = alloca float*, align 8
  %24 = alloca i64, align 8
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  %27 = alloca float, align 4
  %28 = alloca float, align 4
  %29 = alloca float, align 4
  %30 = alloca float, align 4
  %31 = alloca float, align 4
  %32 = alloca float, align 4
  %33 = alloca float, align 4
  %34 = alloca float, align 4
  %35 = alloca float, align 4
  %36 = alloca float, align 4
  %37 = alloca float, align 4
  %38 = alloca float, align 4
  %39 = alloca float, align 4
  %40 = alloca float, align 4
  %41 = alloca float, align 4
  %42 = alloca [30 x float], align 16
  %43 = alloca [30 x float], align 16
  %44 = alloca [30 x float], align 16
  %45 = alloca float, align 4
  %46 = alloca [30 x float], align 16
  %47 = alloca float, align 4
  %48 = alloca float, align 4
  %49 = alloca float, align 4
  %50 = alloca float, align 4
  %51 = alloca float, align 4
  %52 = alloca float, align 4
  %53 = alloca float, align 4
  %54 = alloca float, align 4
  %55 = alloca float, align 4
  %56 = alloca float, align 4
  %57 = alloca float, align 4
  %58 = alloca float, align 4
  %59 = alloca float, align 4
  %60 = alloca float, align 4
  %61 = alloca float, align 4
  %62 = alloca float, align 4
  %63 = alloca float, align 4
  %64 = alloca float, align 4
  store i32* %0, i32** %13, align 8
  store float* %1, float** %14, align 8
  store float* %2, float** %15, align 8
  store float* %3, float** %16, align 8
  store float* %4, float** %17, align 8
  store i16* %5, i16** %18, align 8
  store i16* %6, i16** %19, align 8
  store float* %7, float** %20, align 8
  store float* %8, float** %21, align 8
  store float* %9, float** %22, align 8
  store float* %10, float** %23, align 8
  store i64 %11, i64* %24, align 8
  store float 0.000000e+00, float* %33, align 4
  store float 0.000000e+00, float* %34, align 4
  store i32 0, i32* %26, align 4
  br label %65

; <label>:65:                                     ; preds = %479, %12
  %66 = load i32, i32* %26, align 4
  %67 = sext i32 %66 to i64
  %68 = load i64, i64* %24, align 8
  %69 = icmp slt i64 %67, %68
  br i1 %69, label %70, label %482

; <label>:70:                                     ; preds = %65
  store float 0.000000e+00, float* %33, align 4
  store float 0.000000e+00, float* %34, align 4
  %71 = load i16*, i16** %19, align 8
  %72 = load i32, i32* %26, align 4
  %73 = sext i32 %72 to i64
  %74 = getelementptr inbounds i16, i16* %71, i64 %73
  %75 = load i16, i16* %74, align 2
  %76 = sext i16 %75 to i32
  %77 = sitofp i32 %76 to double
  %78 = fsub double %77, 1.000000e+00
  %79 = fptrunc double %78 to float
  store float %79, float* %57, align 4
  %80 = load float*, float** %22, align 8
  %81 = load i32, i32* %26, align 4
  %82 = sext i32 %81 to i64
  %83 = getelementptr inbounds float, float* %80, i64 %82
  %84 = load float, float* %83, align 4
  %85 = load float*, float** %22, align 8
  %86 = load i32, i32* %26, align 4
  %87 = sext i32 %86 to i64
  %88 = getelementptr inbounds float, float* %85, i64 %87
  %89 = load float, float* %88, align 4
  %90 = fmul float %84, %89
  store float %90, float* %63, align 4
  %91 = load float*, float** %21, align 8
  %92 = load i32, i32* %26, align 4
  %93 = sext i32 %92 to i64
  %94 = getelementptr inbounds float, float* %91, i64 %93
  %95 = load float, float* %94, align 4
  %96 = fpext float %95 to double
  %97 = load float, float* %63, align 4
  %98 = fpext float %97 to double
  %99 = fmul double %98, 5.000000e-01
  %100 = fsub double %96, %99
  %101 = fptrunc double %100 to float
  store float %101, float* %59, align 4
  %102 = load float*, float** %17, align 8
  %103 = load i32, i32* %26, align 4
  %104 = sext i32 %103 to i64
  %105 = getelementptr inbounds float, float* %102, i64 %104
  %106 = load float, float* %105, align 4
  %107 = load float*, float** %16, align 8
  %108 = load i32, i32* %26, align 4
  %109 = sext i32 %108 to i64
  %110 = getelementptr inbounds float, float* %107, i64 %109
  %111 = load float, float* %110, align 4
  %112 = fsub float %106, %111
  %113 = load float, float* %57, align 4
  %114 = fdiv float %112, %113
  store float %114, float* %32, align 4
  %115 = load float*, float** %14, align 8
  %116 = load i32, i32* %26, align 4
  %117 = sext i32 %116 to i64
  %118 = getelementptr inbounds float, float* %115, i64 %117
  %119 = load float, float* %118, align 4
  %120 = call float @log(float %119)
  store float %120, float* %27, align 4
  %121 = load i16*, i16** %19, align 8
  %122 = load i32, i32* %26, align 4
  %123 = sext i32 %122 to i64
  %124 = getelementptr inbounds i16, i16* %121, i64 %123
  %125 = load i16, i16* %124, align 2
  %126 = sext i16 %125 to i32
  %127 = sitofp i32 %126 to double
  %128 = fmul double 2.000000e+00, %127
  %129 = fdiv double 1.000000e+00, %128
  %130 = fptrunc double %129 to float
  store float %130, float* %56, align 4
  %131 = load float, float* %27, align 4
  %132 = fpext float %131 to double
  %133 = load float, float* %59, align 4
  %134 = fpext float %133 to double
  %135 = load float*, float** %16, align 8
  %136 = load i32, i32* %26, align 4
  %137 = sext i32 %136 to i64
  %138 = getelementptr inbounds float, float* %135, i64 %137
  %139 = load float, float* %138, align 4
  %140 = fpext float %139 to double
  %141 = load float, float* %57, align 4
  %142 = load float, float* %32, align 4
  %143 = fmul float %141, %142
  %144 = fpext float %143 to double
  %145 = fmul double %144, 5.000000e-01
  %146 = fadd double %140, %145
  %147 = fmul double %134, %146
  %148 = fadd double %132, %147
  %149 = fptrunc double %148 to float
  store float %149, float* %30, align 4
  %150 = load float*, float** %16, align 8
  %151 = load i32, i32* %26, align 4
  %152 = sext i32 %151 to i64
  %153 = getelementptr inbounds float, float* %150, i64 %152
  %154 = load float, float* %153, align 4
  %155 = fpext float %154 to double
  %156 = load float, float* %32, align 4
  %157 = load float, float* %57, align 4
  %158 = fmul float %156, %157
  %159 = fpext float %158 to double
  %160 = load i16*, i16** %19, align 8
  %161 = load i32, i32* %26, align 4
  %162 = sext i32 %161 to i64
  %163 = getelementptr inbounds i16, i16* %160, i64 %162
  %164 = load i16, i16* %163, align 2
  %165 = sext i16 %164 to i32
  %166 = mul nsw i32 2, %165
  %167 = sitofp i32 %166 to double
  %168 = fsub double %167, 1.000000e+00
  %169 = fmul double %159, %168
  %170 = load i16*, i16** %19, align 8
  %171 = load i32, i32* %26, align 4
  %172 = sext i32 %171 to i64
  %173 = getelementptr inbounds i16, i16* %170, i64 %172
  %174 = load i16, i16* %173, align 2
  %175 = sext i16 %174 to i32
  %176 = sitofp i32 %175 to double
  %177 = fmul double 6.000000e+00, %176
  %178 = fdiv double %169, %177
  %179 = fadd double %155, %178
  %180 = fptrunc double %179 to float
  store float %180, float* %58, align 4
  %181 = load float*, float** %22, align 8
  %182 = load i32, i32* %26, align 4
  %183 = sext i32 %182 to i64
  %184 = getelementptr inbounds float, float* %181, i64 %183
  %185 = load float, float* %184, align 4
  %186 = load float, float* %58, align 4
  %187 = call float @sqrt(float %186)
  %188 = fmul float %185, %187
  store float %188, float* %29, align 4
  %189 = load float, float* %29, align 4
  %190 = load float, float* %29, align 4
  %191 = fmul float %189, %190
  %192 = fdiv float 1.000000e+00, %191
  store float %192, float* %60, align 4
  %193 = load float*, float** %15, align 8
  %194 = load i32, i32* %26, align 4
  %195 = sext i32 %194 to i64
  %196 = getelementptr inbounds float, float* %193, i64 %195
  %197 = load float, float* %196, align 4
  %198 = call float @log(float %197)
  store float %198, float* %28, align 4
  %199 = load float, float* %28, align 4
  %200 = load float, float* %30, align 4
  %201 = fsub float %199, %200
  store float %201, float* %61, align 4
  %202 = load float, float* %60, align 4
  %203 = load float, float* %61, align 4
  %204 = fmul float %202, %203
  store float %204, float* %62, align 4
  store i32 0, i32* %25, align 4
  br label %205

; <label>:205:                                    ; preds = %309, %70
  %206 = load i32, i32* %25, align 4
  %207 = icmp slt i32 %206, 30
  br i1 %207, label %208, label %312

; <label>:208:                                    ; preds = %205
  %209 = load float, float* %32, align 4
  %210 = load i32, i32* %25, align 4
  %211 = sitofp i32 %210 to float
  %212 = load i32, i32* %25, align 4
  %213 = add nsw i32 %212, 1
  %214 = load i32, i32* %25, align 4
  %215 = mul nsw i32 %213, %214
  %216 = sitofp i32 %215 to float
  %217 = load float, float* %56, align 4
  %218 = fmul float %216, %217
  %219 = fsub float %211, %218
  %220 = fmul float %209, %219
  store float %220, float* %53, align 4
  %221 = load float*, float** %16, align 8
  %222 = load i32, i32* %26, align 4
  %223 = sext i32 %222 to i64
  %224 = getelementptr inbounds float, float* %221, i64 %223
  %225 = load float, float* %224, align 4
  %226 = load i32, i32* %25, align 4
  %227 = sitofp i32 %226 to float
  %228 = load float, float* %32, align 4
  %229 = fmul float %227, %228
  %230 = fadd float %225, %229
  store float %230, float* %54, align 4
  %231 = load float*, float** %22, align 8
  %232 = load i32, i32* %26, align 4
  %233 = sext i32 %232 to i64
  %234 = getelementptr inbounds float, float* %231, i64 %233
  %235 = load float, float* %234, align 4
  %236 = load float, float* %54, align 4
  %237 = call float @sqrt(float %236)
  %238 = fmul float %235, %237
  store float %238, float* %45, align 4
  %239 = load float, float* %45, align 4
  %240 = load float, float* %45, align 4
  %241 = fmul float %239, %240
  store float %241, float* %55, align 4
  %242 = load float, float* %63, align 4
  %243 = load float*, float** %16, align 8
  %244 = load i32, i32* %26, align 4
  %245 = sext i32 %244 to i64
  %246 = getelementptr inbounds float, float* %243, i64 %245
  %247 = load float, float* %246, align 4
  %248 = load float, float* %53, align 4
  %249 = fadd float %247, %248
  %250 = fmul float %242, %249
  %251 = load i32, i32* %25, align 4
  %252 = sext i32 %251 to i64
  %253 = getelementptr inbounds [30 x float], [30 x float]* %46, i64 0, i64 %252
  store float %250, float* %253, align 4
  %254 = load float, float* %27, align 4
  %255 = load float, float* %59, align 4
  %256 = load float*, float** %16, align 8
  %257 = load i32, i32* %26, align 4
  %258 = sext i32 %257 to i64
  %259 = getelementptr inbounds float, float* %256, i64 %258
  %260 = load float, float* %259, align 4
  %261 = load i32, i32* %25, align 4
  %262 = sitofp i32 %261 to float
  %263 = load float, float* %32, align 4
  %264 = fmul float %262, %263
  %265 = fadd float %260, %264
  %266 = fmul float %255, %265
  %267 = fadd float %254, %266
  store float %267, float* %47, align 4
  %268 = load float, float* %47, align 4
  %269 = fpext float %268 to double
  %270 = load float, float* %55, align 4
  %271 = fpext float %270 to double
  %272 = fmul double %271, 5.000000e-01
  %273 = fadd double %269, %272
  %274 = fptrunc double %273 to float
  %275 = load i32, i32* %25, align 4
  %276 = sext i32 %275 to i64
  %277 = getelementptr inbounds [30 x float], [30 x float]* %44, i64 0, i64 %276
  store float %274, float* %277, align 4
  %278 = load float, float* %47, align 4
  %279 = load i32, i32* %25, align 4
  %280 = sext i32 %279 to i64
  %281 = getelementptr inbounds [30 x float], [30 x float]* %46, i64 0, i64 %280
  %282 = load float, float* %281, align 4
  %283 = load float, float* %62, align 4
  %284 = fmul float %282, %283
  %285 = fadd float %278, %284
  %286 = fpext float %285 to double
  %287 = load float, float* %55, align 4
  %288 = load i32, i32* %25, align 4
  %289 = sext i32 %288 to i64
  %290 = getelementptr inbounds [30 x float], [30 x float]* %46, i64 0, i64 %289
  %291 = load float, float* %290, align 4
  %292 = load i32, i32* %25, align 4
  %293 = sext i32 %292 to i64
  %294 = getelementptr inbounds [30 x float], [30 x float]* %46, i64 0, i64 %293
  %295 = load float, float* %294, align 4
  %296 = fmul float %291, %295
  %297 = load float, float* %60, align 4
  %298 = fmul float %296, %297
  %299 = fsub float %287, %298
  %300 = fpext float %299 to double
  %301 = fmul double %300, 5.000000e-01
  %302 = fadd double %286, %301
  %303 = fptrunc double %302 to float
  store float %303, float* %64, align 4
  %304 = load float, float* %64, align 4
  %305 = call float @exp(float %304)
  %306 = load i32, i32* %25, align 4
  %307 = sext i32 %306 to i64
  %308 = getelementptr inbounds [30 x float], [30 x float]* %42, i64 0, i64 %307
  store float %305, float* %308, align 4
  br label %309

; <label>:309:                                    ; preds = %208
  %310 = load i32, i32* %25, align 4
  %311 = add nsw i32 %310, 1
  store i32 %311, i32* %25, align 4
  br label %205

; <label>:312:                                    ; preds = %205
  store i32 0, i32* %25, align 4
  br label %313

; <label>:313:                                    ; preds = %323, %312
  %314 = load i32, i32* %25, align 4
  %315 = icmp slt i32 %314, 30
  br i1 %315, label %316, label %326

; <label>:316:                                    ; preds = %313
  %317 = load i32, i32* %25, align 4
  %318 = sext i32 %317 to i64
  %319 = getelementptr inbounds [30 x float], [30 x float]* %42, i64 0, i64 %318
  %320 = load float, float* %319, align 4
  %321 = load float, float* %33, align 4
  %322 = fadd float %321, %320
  store float %322, float* %33, align 4
  br label %323

; <label>:323:                                    ; preds = %316
  %324 = load i32, i32* %25, align 4
  %325 = add nsw i32 %324, 1
  store i32 %325, i32* %25, align 4
  br label %313

; <label>:326:                                    ; preds = %313
  %327 = load float*, float** %15, align 8
  %328 = load i32, i32* %26, align 4
  %329 = sext i32 %328 to i64
  %330 = getelementptr inbounds float, float* %327, i64 %329
  %331 = load float, float* %330, align 4
  %332 = fpext float %331 to double
  %333 = fmul double 2.000000e+00, %332
  %334 = load float, float* %33, align 4
  %335 = load i16*, i16** %19, align 8
  %336 = load i32, i32* %26, align 4
  %337 = sext i32 %336 to i64
  %338 = getelementptr inbounds i16, i16* %335, i64 %337
  %339 = load i16, i16* %338, align 2
  %340 = sext i16 %339 to i32
  %341 = sitofp i32 %340 to float
  %342 = fdiv float %334, %341
  %343 = fpext float %342 to double
  %344 = fsub double %333, %343
  %345 = fptrunc double %344 to float
  %346 = call float @log(float %345)
  store float %346, float* %31, align 4
  %347 = load float, float* %29, align 4
  %348 = fdiv float 1.000000e+00, %347
  store float %348, float* %52, align 4
  %349 = load float, float* %30, align 4
  %350 = load float, float* %31, align 4
  %351 = fsub float %349, %350
  %352 = load float, float* %52, align 4
  %353 = fmul float %351, %352
  store float %353, float* %36, align 4
  %354 = load i32*, i32** %13, align 8
  %355 = load i32, i32* %26, align 4
  %356 = sext i32 %355 to i64
  %357 = getelementptr inbounds i32, i32* %354, i64 %356
  %358 = load i32, i32* %357, align 4
  %359 = icmp eq i32 %358, 0
  %360 = select i1 %359, i32 1, i32 -1
  %361 = sitofp i32 %360 to float
  store float %361, float* %41, align 4
  %362 = load float, float* %41, align 4
  %363 = load float, float* %36, align 4
  %364 = fmul float %362, %363
  store float %364, float* %37, align 4
  %365 = load float, float* %41, align 4
  %366 = load float, float* %52, align 4
  %367 = fmul float %365, %366
  store float %367, float* %38, align 4
  store i32 0, i32* %25, align 4
  br label %368

; <label>:368:                                    ; preds = %392, %326
  %369 = load i32, i32* %25, align 4
  %370 = icmp slt i32 %369, 30
  br i1 %370, label %371, label %395

; <label>:371:                                    ; preds = %368
  %372 = load float, float* %37, align 4
  %373 = load float, float* %38, align 4
  %374 = load i32, i32* %25, align 4
  %375 = sext i32 %374 to i64
  %376 = getelementptr inbounds [30 x float], [30 x float]* %46, i64 0, i64 %375
  %377 = load float, float* %376, align 4
  %378 = fmul float %373, %377
  %379 = fadd float %372, %378
  store float %379, float* %35, align 4
  %380 = load float, float* %35, align 4
  %381 = call float @Ncdf(float %380)
  store float %381, float* %39, align 4
  %382 = load i32, i32* %25, align 4
  %383 = sext i32 %382 to i64
  %384 = getelementptr inbounds [30 x float], [30 x float]* %44, i64 0, i64 %383
  %385 = load float, float* %384, align 4
  %386 = call float @exp(float %385)
  %387 = load float, float* %39, align 4
  %388 = fmul float %386, %387
  %389 = load i32, i32* %25, align 4
  %390 = sext i32 %389 to i64
  %391 = getelementptr inbounds [30 x float], [30 x float]* %43, i64 0, i64 %390
  store float %388, float* %391, align 4
  br label %392

; <label>:392:                                    ; preds = %371
  %393 = load i32, i32* %25, align 4
  %394 = add nsw i32 %393, 1
  store i32 %394, i32* %25, align 4
  br label %368

; <label>:395:                                    ; preds = %368
  store i32 0, i32* %25, align 4
  br label %396

; <label>:396:                                    ; preds = %406, %395
  %397 = load i32, i32* %25, align 4
  %398 = icmp slt i32 %397, 30
  br i1 %398, label %399, label %409

; <label>:399:                                    ; preds = %396
  %400 = load i32, i32* %25, align 4
  %401 = sext i32 %400 to i64
  %402 = getelementptr inbounds [30 x float], [30 x float]* %43, i64 0, i64 %401
  %403 = load float, float* %402, align 4
  %404 = load float, float* %34, align 4
  %405 = fadd float %404, %403
  store float %405, float* %34, align 4
  br label %406

; <label>:406:                                    ; preds = %399
  %407 = load i32, i32* %25, align 4
  %408 = add nsw i32 %407, 1
  store i32 %408, i32* %25, align 4
  br label %396

; <label>:409:                                    ; preds = %396
  %410 = load float, float* %41, align 4
  %411 = load float, float* %36, align 4
  %412 = fmul float %410, %411
  store float %412, float* %35, align 4
  %413 = load float, float* %35, align 4
  %414 = call float @Ncdf(float %413)
  store float %414, float* %40, align 4
  %415 = load float*, float** %20, align 8
  %416 = load i32, i32* %26, align 4
  %417 = sext i32 %416 to i64
  %418 = getelementptr inbounds float, float* %415, i64 %417
  %419 = load float, float* %418, align 4
  %420 = load float*, float** %17, align 8
  %421 = load i32, i32* %26, align 4
  %422 = sext i32 %421 to i64
  %423 = getelementptr inbounds float, float* %420, i64 %422
  %424 = load float, float* %423, align 4
  %425 = fmul float %419, %424
  %426 = call float @exp(float %425)
  store float %426, float* %48, align 4
  %427 = load float, float* %48, align 4
  %428 = fdiv float 1.000000e+00, %427
  store float %428, float* %51, align 4
  %429 = load float, float* %34, align 4
  %430 = load i16*, i16** %19, align 8
  %431 = load i32, i32* %26, align 4
  %432 = sext i32 %431 to i64
  %433 = getelementptr inbounds i16, i16* %430, i64 %432
  %434 = load i16, i16* %433, align 2
  %435 = sext i16 %434 to i32
  %436 = sitofp i32 %435 to float
  %437 = fdiv float %429, %436
  %438 = load float*, float** %15, align 8
  %439 = load i32, i32* %26, align 4
  %440 = sext i32 %439 to i64
  %441 = getelementptr inbounds float, float* %438, i64 %440
  %442 = load float, float* %441, align 4
  %443 = load float, float* %40, align 4
  %444 = fmul float %442, %443
  %445 = fsub float %437, %444
  store float %445, float* %49, align 4
  %446 = load float, float* %41, align 4
  %447 = load i16*, i16** %19, align 8
  %448 = load i32, i32* %26, align 4
  %449 = sext i32 %448 to i64
  %450 = getelementptr inbounds i16, i16* %447, i64 %449
  %451 = load i16, i16* %450, align 2
  %452 = sext i16 %451 to i32
  %453 = load i16*, i16** %18, align 8
  %454 = load i32, i32* %26, align 4
  %455 = sext i32 %454 to i64
  %456 = getelementptr inbounds i16, i16* %453, i64 %455
  %457 = load i16, i16* %456, align 2
  %458 = sext i16 %457 to i32
  %459 = sub nsw i32 %452, %458
  %460 = sitofp i32 %459 to float
  %461 = fmul float %446, %460
  %462 = load i16*, i16** %19, align 8
  %463 = load i32, i32* %26, align 4
  %464 = sext i32 %463 to i64
  %465 = getelementptr inbounds i16, i16* %462, i64 %464
  %466 = load i16, i16* %465, align 2
  %467 = sext i16 %466 to i32
  %468 = sitofp i32 %467 to float
  %469 = fdiv float %461, %468
  store float %469, float* %50, align 4
  %470 = load float, float* %49, align 4
  %471 = load float, float* %50, align 4
  %472 = fmul float %470, %471
  %473 = load float, float* %51, align 4
  %474 = fmul float %472, %473
  %475 = load float*, float** %23, align 8
  %476 = load i32, i32* %26, align 4
  %477 = sext i32 %476 to i64
  %478 = getelementptr inbounds float, float* %475, i64 %477
  store float %474, float* %478, align 4
  br label %479

; <label>:479:                                    ; preds = %409
  %480 = load i32, i32* %26, align 4
  %481 = add nsw i32 %480, 1
  store i32 %481, i32* %26, align 4
  br label %65

; <label>:482:                                    ; preds = %65
  ret void
}

; Function Attrs: noinline nounwind uwtable
define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca double, align 8
  %7 = alloca double, align 8
  %8 = alloca double, align 8
  %9 = alloca i32, align 4
  %10 = alloca %struct._IO_FILE*, align 8
  %11 = alloca float, align 4
  %12 = alloca float, align 4
  %13 = alloca i16, align 2
  %14 = alloca i16, align 2
  %15 = alloca i64, align 8
  %16 = alloca i32*, align 8
  %17 = alloca float*, align 8
  %18 = alloca float*, align 8
  %19 = alloca float*, align 8
  %20 = alloca float*, align 8
  %21 = alloca i16*, align 8
  %22 = alloca i16*, align 8
  %23 = alloca float*, align 8
  %24 = alloca float*, align 8
  %25 = alloca float*, align 8
  %26 = alloca float*, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  store i32 0, i32* %9, align 4
  %27 = load i32, i32* %4, align 4
  %28 = icmp slt i32 %27, 2
  br i1 %28, label %29, label %30

; <label>:29:                                     ; preds = %2
  call void @perror(i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str, i32 0, i32 0))
  store i32 1, i32* %3, align 4
  br label %412

; <label>:30:                                     ; preds = %2
  %31 = load i8**, i8*** %5, align 8
  %32 = getelementptr inbounds i8*, i8** %31, i64 1
  %33 = load i8*, i8** %32, align 8
  %34 = call %struct._IO_FILE* @fopen(i8* %33, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0))
  store %struct._IO_FILE* %34, %struct._IO_FILE** %10, align 8
  %35 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %36 = icmp eq %struct._IO_FILE* %35, null
  br i1 %36, label %37, label %38

; <label>:37:                                     ; preds = %30
  call void @perror(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.2, i32 0, i32 0))
  store i32 1, i32* %3, align 4
  br label %412

; <label>:38:                                     ; preds = %30
  %39 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i32 0, i32 0))
  %40 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.4, i32 0, i32 0))
  %41 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %42 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %41, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i64* %15)
  %43 = load i64, i64* %15, align 8
  %44 = mul i64 4, %43
  %45 = call noalias i8* @malloc(i64 %44) #4
  %46 = bitcast i8* %45 to i32*
  store i32* %46, i32** %16, align 8
  %47 = load i64, i64* %15, align 8
  %48 = mul i64 4, %47
  %49 = call noalias i8* @malloc(i64 %48) #4
  %50 = bitcast i8* %49 to float*
  store float* %50, float** %17, align 8
  %51 = load i64, i64* %15, align 8
  %52 = mul i64 4, %51
  %53 = call noalias i8* @malloc(i64 %52) #4
  %54 = bitcast i8* %53 to float*
  store float* %54, float** %18, align 8
  %55 = load i64, i64* %15, align 8
  %56 = mul i64 4, %55
  %57 = call noalias i8* @malloc(i64 %56) #4
  %58 = bitcast i8* %57 to float*
  store float* %58, float** %19, align 8
  %59 = load i64, i64* %15, align 8
  %60 = mul i64 4, %59
  %61 = call noalias i8* @malloc(i64 %60) #4
  %62 = bitcast i8* %61 to float*
  store float* %62, float** %20, align 8
  %63 = load i64, i64* %15, align 8
  %64 = mul i64 2, %63
  %65 = call noalias i8* @malloc(i64 %64) #4
  %66 = bitcast i8* %65 to i16*
  store i16* %66, i16** %21, align 8
  %67 = load i64, i64* %15, align 8
  %68 = mul i64 2, %67
  %69 = call noalias i8* @malloc(i64 %68) #4
  %70 = bitcast i8* %69 to i16*
  store i16* %70, i16** %22, align 8
  %71 = load i64, i64* %15, align 8
  %72 = mul i64 4, %71
  %73 = call noalias i8* @malloc(i64 %72) #4
  %74 = bitcast i8* %73 to float*
  store float* %74, float** %23, align 8
  %75 = load i64, i64* %15, align 8
  %76 = mul i64 4, %75
  %77 = call noalias i8* @malloc(i64 %76) #4
  %78 = bitcast i8* %77 to float*
  store float* %78, float** %24, align 8
  %79 = load i64, i64* %15, align 8
  %80 = mul i64 4, %79
  %81 = call noalias i8* @malloc(i64 %80) #4
  %82 = bitcast i8* %81 to float*
  store float* %82, float** %25, align 8
  %83 = load i64, i64* %15, align 8
  %84 = mul i64 4, %83
  %85 = call noalias i8* @malloc(i64 %84) #4
  %86 = bitcast i8* %85 to float*
  store float* %86, float** %26, align 8
  %87 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %88 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %87, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %11, float* %12)
  store i32 0, i32* %9, align 4
  br label %89

; <label>:89:                                     ; preds = %109, %38
  %90 = load i32, i32* %9, align 4
  %91 = sext i32 %90 to i64
  %92 = load i64, i64* %15, align 8
  %93 = icmp slt i64 %91, %92
  br i1 %93, label %94, label %112

; <label>:94:                                     ; preds = %89
  %95 = call i32 @rand() #4
  %96 = sitofp i32 %95 to float
  %97 = load float, float* %12, align 4
  %98 = load float, float* %11, align 4
  %99 = fsub float %97, %98
  %100 = fmul float %96, %99
  %101 = fdiv float %100, 0x41E0000000000000
  %102 = load float, float* %11, align 4
  %103 = fadd float %101, %102
  %104 = fptosi float %103 to i32
  %105 = load i32*, i32** %16, align 8
  %106 = load i32, i32* %9, align 4
  %107 = sext i32 %106 to i64
  %108 = getelementptr inbounds i32, i32* %105, i64 %107
  store i32 %104, i32* %108, align 4
  br label %109

; <label>:109:                                    ; preds = %94
  %110 = load i32, i32* %9, align 4
  %111 = add nsw i32 %110, 1
  store i32 %111, i32* %9, align 4
  br label %89

; <label>:112:                                    ; preds = %89
  %113 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %114 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %113, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %11, float* %12)
  store i32 0, i32* %9, align 4
  br label %115

; <label>:115:                                    ; preds = %134, %112
  %116 = load i32, i32* %9, align 4
  %117 = sext i32 %116 to i64
  %118 = load i64, i64* %15, align 8
  %119 = icmp slt i64 %117, %118
  br i1 %119, label %120, label %137

; <label>:120:                                    ; preds = %115
  %121 = call i32 @rand() #4
  %122 = sitofp i32 %121 to float
  %123 = load float, float* %12, align 4
  %124 = load float, float* %11, align 4
  %125 = fsub float %123, %124
  %126 = fmul float %122, %125
  %127 = fdiv float %126, 0x41E0000000000000
  %128 = load float, float* %11, align 4
  %129 = fadd float %127, %128
  %130 = load float*, float** %17, align 8
  %131 = load i32, i32* %9, align 4
  %132 = sext i32 %131 to i64
  %133 = getelementptr inbounds float, float* %130, i64 %132
  store float %129, float* %133, align 4
  br label %134

; <label>:134:                                    ; preds = %120
  %135 = load i32, i32* %9, align 4
  %136 = add nsw i32 %135, 1
  store i32 %136, i32* %9, align 4
  br label %115

; <label>:137:                                    ; preds = %115
  %138 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %139 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %138, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %11, float* %12)
  store i32 0, i32* %9, align 4
  br label %140

; <label>:140:                                    ; preds = %159, %137
  %141 = load i32, i32* %9, align 4
  %142 = sext i32 %141 to i64
  %143 = load i64, i64* %15, align 8
  %144 = icmp slt i64 %142, %143
  br i1 %144, label %145, label %162

; <label>:145:                                    ; preds = %140
  %146 = call i32 @rand() #4
  %147 = sitofp i32 %146 to float
  %148 = load float, float* %12, align 4
  %149 = load float, float* %11, align 4
  %150 = fsub float %148, %149
  %151 = fmul float %147, %150
  %152 = fdiv float %151, 0x41E0000000000000
  %153 = load float, float* %11, align 4
  %154 = fadd float %152, %153
  %155 = load float*, float** %18, align 8
  %156 = load i32, i32* %9, align 4
  %157 = sext i32 %156 to i64
  %158 = getelementptr inbounds float, float* %155, i64 %157
  store float %154, float* %158, align 4
  br label %159

; <label>:159:                                    ; preds = %145
  %160 = load i32, i32* %9, align 4
  %161 = add nsw i32 %160, 1
  store i32 %161, i32* %9, align 4
  br label %140

; <label>:162:                                    ; preds = %140
  %163 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %164 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %163, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %11, float* %12)
  store i32 0, i32* %9, align 4
  br label %165

; <label>:165:                                    ; preds = %184, %162
  %166 = load i32, i32* %9, align 4
  %167 = sext i32 %166 to i64
  %168 = load i64, i64* %15, align 8
  %169 = icmp slt i64 %167, %168
  br i1 %169, label %170, label %187

; <label>:170:                                    ; preds = %165
  %171 = call i32 @rand() #4
  %172 = sitofp i32 %171 to float
  %173 = load float, float* %12, align 4
  %174 = load float, float* %11, align 4
  %175 = fsub float %173, %174
  %176 = fmul float %172, %175
  %177 = fdiv float %176, 0x41E0000000000000
  %178 = load float, float* %11, align 4
  %179 = fadd float %177, %178
  %180 = load float*, float** %19, align 8
  %181 = load i32, i32* %9, align 4
  %182 = sext i32 %181 to i64
  %183 = getelementptr inbounds float, float* %180, i64 %182
  store float %179, float* %183, align 4
  br label %184

; <label>:184:                                    ; preds = %170
  %185 = load i32, i32* %9, align 4
  %186 = add nsw i32 %185, 1
  store i32 %186, i32* %9, align 4
  br label %165

; <label>:187:                                    ; preds = %165
  %188 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %189 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %188, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %11, float* %12)
  store i32 0, i32* %9, align 4
  br label %190

; <label>:190:                                    ; preds = %209, %187
  %191 = load i32, i32* %9, align 4
  %192 = sext i32 %191 to i64
  %193 = load i64, i64* %15, align 8
  %194 = icmp slt i64 %192, %193
  br i1 %194, label %195, label %212

; <label>:195:                                    ; preds = %190
  %196 = call i32 @rand() #4
  %197 = sitofp i32 %196 to float
  %198 = load float, float* %12, align 4
  %199 = load float, float* %11, align 4
  %200 = fsub float %198, %199
  %201 = fmul float %197, %200
  %202 = fdiv float %201, 0x41E0000000000000
  %203 = load float, float* %11, align 4
  %204 = fadd float %202, %203
  %205 = load float*, float** %20, align 8
  %206 = load i32, i32* %9, align 4
  %207 = sext i32 %206 to i64
  %208 = getelementptr inbounds float, float* %205, i64 %207
  store float %204, float* %208, align 4
  br label %209

; <label>:209:                                    ; preds = %195
  %210 = load i32, i32* %9, align 4
  %211 = add nsw i32 %210, 1
  store i32 %211, i32* %9, align 4
  br label %190

; <label>:212:                                    ; preds = %190
  %213 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %214 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %213, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %11, float* %12)
  store i32 0, i32* %9, align 4
  br label %215

; <label>:215:                                    ; preds = %234, %212
  %216 = load i32, i32* %9, align 4
  %217 = sext i32 %216 to i64
  %218 = load i64, i64* %15, align 8
  %219 = icmp slt i64 %217, %218
  br i1 %219, label %220, label %237

; <label>:220:                                    ; preds = %215
  %221 = call i32 @rand() #4
  %222 = sitofp i32 %221 to float
  %223 = load float, float* %12, align 4
  %224 = load float, float* %11, align 4
  %225 = fsub float %223, %224
  %226 = fmul float %222, %225
  %227 = fdiv float %226, 0x41E0000000000000
  %228 = load float, float* %11, align 4
  %229 = fadd float %227, %228
  %230 = load float*, float** %23, align 8
  %231 = load i32, i32* %9, align 4
  %232 = sext i32 %231 to i64
  %233 = getelementptr inbounds float, float* %230, i64 %232
  store float %229, float* %233, align 4
  br label %234

; <label>:234:                                    ; preds = %220
  %235 = load i32, i32* %9, align 4
  %236 = add nsw i32 %235, 1
  store i32 %236, i32* %9, align 4
  br label %215

; <label>:237:                                    ; preds = %215
  %238 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %239 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %238, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %11, float* %12)
  store i32 0, i32* %9, align 4
  br label %240

; <label>:240:                                    ; preds = %259, %237
  %241 = load i32, i32* %9, align 4
  %242 = sext i32 %241 to i64
  %243 = load i64, i64* %15, align 8
  %244 = icmp slt i64 %242, %243
  br i1 %244, label %245, label %262

; <label>:245:                                    ; preds = %240
  %246 = call i32 @rand() #4
  %247 = sitofp i32 %246 to float
  %248 = load float, float* %12, align 4
  %249 = load float, float* %11, align 4
  %250 = fsub float %248, %249
  %251 = fmul float %247, %250
  %252 = fdiv float %251, 0x41E0000000000000
  %253 = load float, float* %11, align 4
  %254 = fadd float %252, %253
  %255 = load float*, float** %24, align 8
  %256 = load i32, i32* %9, align 4
  %257 = sext i32 %256 to i64
  %258 = getelementptr inbounds float, float* %255, i64 %257
  store float %254, float* %258, align 4
  br label %259

; <label>:259:                                    ; preds = %245
  %260 = load i32, i32* %9, align 4
  %261 = add nsw i32 %260, 1
  store i32 %261, i32* %9, align 4
  br label %240

; <label>:262:                                    ; preds = %240
  %263 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %264 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %263, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %11, float* %12)
  store i32 0, i32* %9, align 4
  br label %265

; <label>:265:                                    ; preds = %284, %262
  %266 = load i32, i32* %9, align 4
  %267 = sext i32 %266 to i64
  %268 = load i64, i64* %15, align 8
  %269 = icmp slt i64 %267, %268
  br i1 %269, label %270, label %287

; <label>:270:                                    ; preds = %265
  %271 = call i32 @rand() #4
  %272 = sitofp i32 %271 to float
  %273 = load float, float* %12, align 4
  %274 = load float, float* %11, align 4
  %275 = fsub float %273, %274
  %276 = fmul float %272, %275
  %277 = fdiv float %276, 0x41E0000000000000
  %278 = load float, float* %11, align 4
  %279 = fadd float %277, %278
  %280 = load float*, float** %25, align 8
  %281 = load i32, i32* %9, align 4
  %282 = sext i32 %281 to i64
  %283 = getelementptr inbounds float, float* %280, i64 %282
  store float %279, float* %283, align 4
  br label %284

; <label>:284:                                    ; preds = %270
  %285 = load i32, i32* %9, align 4
  %286 = add nsw i32 %285, 1
  store i32 %286, i32* %9, align 4
  br label %265

; <label>:287:                                    ; preds = %265
  %288 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %289 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %288, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.7, i32 0, i32 0), i16* %13, i16* %14)
  store i32 0, i32* %9, align 4
  br label %290

; <label>:290:                                    ; preds = %314, %287
  %291 = load i32, i32* %9, align 4
  %292 = sext i32 %291 to i64
  %293 = load i64, i64* %15, align 8
  %294 = icmp slt i64 %292, %293
  br i1 %294, label %295, label %317

; <label>:295:                                    ; preds = %290
  %296 = call i32 @rand() #4
  %297 = load i16, i16* %14, align 2
  %298 = sext i16 %297 to i32
  %299 = load i16, i16* %13, align 2
  %300 = sext i16 %299 to i32
  %301 = sub nsw i32 %298, %300
  %302 = mul nsw i32 %296, %301
  %303 = sitofp i32 %302 to float
  %304 = fdiv float %303, 0x41E0000000000000
  %305 = load i16, i16* %13, align 2
  %306 = sext i16 %305 to i32
  %307 = sitofp i32 %306 to float
  %308 = fadd float %304, %307
  %309 = fptosi float %308 to i16
  %310 = load i16*, i16** %22, align 8
  %311 = load i32, i32* %9, align 4
  %312 = sext i32 %311 to i64
  %313 = getelementptr inbounds i16, i16* %310, i64 %312
  store i16 %309, i16* %313, align 2
  br label %314

; <label>:314:                                    ; preds = %295
  %315 = load i32, i32* %9, align 4
  %316 = add nsw i32 %315, 1
  store i32 %316, i32* %9, align 4
  br label %290

; <label>:317:                                    ; preds = %290
  %318 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %319 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %318, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.7, i32 0, i32 0), i16* %13, i16* %14)
  store i32 0, i32* %9, align 4
  br label %320

; <label>:320:                                    ; preds = %360, %317
  %321 = load i32, i32* %9, align 4
  %322 = sext i32 %321 to i64
  %323 = load i64, i64* %15, align 8
  %324 = icmp slt i64 %322, %323
  br i1 %324, label %325, label %363

; <label>:325:                                    ; preds = %320
  %326 = call i32 @rand() #4
  %327 = load i16, i16* %14, align 2
  %328 = sext i16 %327 to i32
  %329 = load i16, i16* %13, align 2
  %330 = sext i16 %329 to i32
  %331 = sub nsw i32 %328, %330
  %332 = mul nsw i32 %326, %331
  %333 = trunc i32 %332 to i16
  %334 = sext i16 %333 to i32
  %335 = sdiv i32 %334, 2147483647
  %336 = load i16, i16* %13, align 2
  %337 = sext i16 %336 to i32
  %338 = add nsw i32 %335, %337
  %339 = trunc i32 %338 to i16
  %340 = load i16*, i16** %21, align 8
  %341 = load i32, i32* %9, align 4
  %342 = sext i32 %341 to i64
  %343 = getelementptr inbounds i16, i16* %340, i64 %342
  store i16 %339, i16* %343, align 2
  %344 = load i16*, i16** %21, align 8
  %345 = load i32, i32* %9, align 4
  %346 = sext i32 %345 to i64
  %347 = getelementptr inbounds i16, i16* %344, i64 %346
  %348 = load i16, i16* %347, align 2
  %349 = sext i16 %348 to i32
  %350 = icmp ne i32 %349, 30
  br i1 %350, label %351, label %359

; <label>:351:                                    ; preds = %325
  %352 = load i16*, i16** %21, align 8
  %353 = load i32, i32* %9, align 4
  %354 = sext i32 %353 to i64
  %355 = getelementptr inbounds i16, i16* %352, i64 %354
  %356 = load i16, i16* %355, align 2
  %357 = sext i16 %356 to i32
  %358 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.8, i32 0, i32 0), i32 %357)
  store i32 1, i32* %3, align 4
  br label %412

; <label>:359:                                    ; preds = %325
  br label %360

; <label>:360:                                    ; preds = %359
  %361 = load i32, i32* %9, align 4
  %362 = add nsw i32 %361, 1
  store i32 %362, i32* %9, align 4
  br label %320

; <label>:363:                                    ; preds = %320
  %364 = load %struct._IO_FILE*, %struct._IO_FILE** %10, align 8
  %365 = call i32 @fclose(%struct._IO_FILE* %364)
  %366 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.9, i32 0, i32 0))
  %367 = call i64 @getTime()
  %368 = uitofp i64 %367 to double
  store double %368, double* %6, align 8
  %369 = load i32*, i32** %16, align 8
  %370 = load float*, float** %17, align 8
  %371 = load float*, float** %18, align 8
  %372 = load float*, float** %19, align 8
  %373 = load float*, float** %20, align 8
  %374 = load i16*, i16** %22, align 8
  %375 = load i16*, i16** %21, align 8
  %376 = load float*, float** %23, align 8
  %377 = load float*, float** %24, align 8
  %378 = load float*, float** %25, align 8
  %379 = load float*, float** %26, align 8
  %380 = load i64, i64* %15, align 8
  call void @Calculation(i32* %369, float* %370, float* %371, float* %372, float* %373, i16* %374, i16* %375, float* %376, float* %377, float* %378, float* %379, i64 %380)
  %381 = call i64 @getTime()
  %382 = uitofp i64 %381 to double
  store double %382, double* %7, align 8
  %383 = load double, double* %7, align 8
  %384 = load double, double* %6, align 8
  %385 = fsub double %383, %384
  store double %385, double* %8, align 8
  %386 = load double, double* %8, align 8
  %387 = fdiv double %386, 1.000000e+06
  %388 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.10, i32 0, i32 0), double %387)
  %389 = load i32*, i32** %16, align 8
  %390 = bitcast i32* %389 to i8*
  call void @free(i8* %390) #4
  %391 = load float*, float** %17, align 8
  %392 = bitcast float* %391 to i8*
  call void @free(i8* %392) #4
  %393 = load float*, float** %18, align 8
  %394 = bitcast float* %393 to i8*
  call void @free(i8* %394) #4
  %395 = load float*, float** %19, align 8
  %396 = bitcast float* %395 to i8*
  call void @free(i8* %396) #4
  %397 = load float*, float** %20, align 8
  %398 = bitcast float* %397 to i8*
  call void @free(i8* %398) #4
  %399 = load i16*, i16** %21, align 8
  %400 = bitcast i16* %399 to i8*
  call void @free(i8* %400) #4
  %401 = load i16*, i16** %22, align 8
  %402 = bitcast i16* %401 to i8*
  call void @free(i8* %402) #4
  %403 = load float*, float** %23, align 8
  %404 = bitcast float* %403 to i8*
  call void @free(i8* %404) #4
  %405 = load float*, float** %24, align 8
  %406 = bitcast float* %405 to i8*
  call void @free(i8* %406) #4
  %407 = load float*, float** %25, align 8
  %408 = bitcast float* %407 to i8*
  call void @free(i8* %408) #4
  %409 = load float*, float** %26, align 8
  %410 = bitcast float* %409 to i8*
  call void @free(i8* %410) #4
  %411 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.11, i32 0, i32 0))
  store i32 0, i32* %3, align 4
  br label %412

; <label>:412:                                    ; preds = %363, %351, %37, %29
  %413 = load i32, i32* %3, align 4
  ret i32 %413
}

declare void @perror(i8*) #3

declare %struct._IO_FILE* @fopen(i8*, i8*) #3

declare i32 @printf(i8*, ...) #3

declare i32 @__isoc99_fscanf(%struct._IO_FILE*, i8*, ...) #3

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: nounwind
declare i32 @rand() #2

declare i32 @fclose(%struct._IO_FILE*) #3

; Function Attrs: nounwind
declare void @free(i8*) #2

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline nounwind readnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (tags/RELEASE_400/final)"}
