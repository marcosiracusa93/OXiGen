; ModuleID = 'aop.ll'
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
  %13 = alloca [30 x float], align 16
  %14 = alloca [30 x float], align 16
  %15 = alloca [30 x float], align 16
  %16 = alloca [30 x float], align 16
  br label %17

; <label>:17:                                     ; preds = %289, %12
  %.02 = phi i32 [ 0, %12 ], [ %290, %289 ]
  %18 = sext i32 %.02 to i64
  %19 = icmp slt i64 %18, %11
  br i1 %19, label %20, label %291

; <label>:20:                                     ; preds = %17
  %21 = sext i32 %.02 to i64
  %22 = getelementptr inbounds i16, i16* %6, i64 %21
  %23 = load i16, i16* %22, align 2
  %24 = sext i16 %23 to i32
  %25 = sitofp i32 %24 to double
  %26 = fsub double %25, 1.000000e+00
  %27 = fptrunc double %26 to float
  %28 = sext i32 %.02 to i64
  %29 = getelementptr inbounds float, float* %9, i64 %28
  %30 = load float, float* %29, align 4
  %31 = sext i32 %.02 to i64
  %32 = getelementptr inbounds float, float* %9, i64 %31
  %33 = load float, float* %32, align 4
  %34 = fmul float %30, %33
  %35 = sext i32 %.02 to i64
  %36 = getelementptr inbounds float, float* %8, i64 %35
  %37 = load float, float* %36, align 4
  %38 = fpext float %37 to double
  %39 = fpext float %34 to double
  %40 = fmul double %39, 5.000000e-01
  %41 = fsub double %38, %40
  %42 = fptrunc double %41 to float
  %43 = sext i32 %.02 to i64
  %44 = getelementptr inbounds float, float* %4, i64 %43
  %45 = load float, float* %44, align 4
  %46 = sext i32 %.02 to i64
  %47 = getelementptr inbounds float, float* %3, i64 %46
  %48 = load float, float* %47, align 4
  %49 = fsub float %45, %48
  %50 = fdiv float %49, %27
  %51 = sext i32 %.02 to i64
  %52 = getelementptr inbounds float, float* %1, i64 %51
  %53 = load float, float* %52, align 4
  %54 = call float @log(float %53)
  %55 = sext i32 %.02 to i64
  %56 = getelementptr inbounds i16, i16* %6, i64 %55
  %57 = load i16, i16* %56, align 2
  %58 = sext i16 %57 to i32
  %59 = sitofp i32 %58 to double
  %60 = fmul double 2.000000e+00, %59
  %61 = fdiv double 1.000000e+00, %60
  %62 = fptrunc double %61 to float
  %63 = fpext float %54 to double
  %64 = fpext float %42 to double
  %65 = sext i32 %.02 to i64
  %66 = getelementptr inbounds float, float* %3, i64 %65
  %67 = load float, float* %66, align 4
  %68 = fpext float %67 to double
  %69 = fmul float %27, %50
  %70 = fpext float %69 to double
  %71 = fmul double %70, 5.000000e-01
  %72 = fadd double %68, %71
  %73 = fmul double %64, %72
  %74 = fadd double %63, %73
  %75 = fptrunc double %74 to float
  %76 = sext i32 %.02 to i64
  %77 = getelementptr inbounds float, float* %3, i64 %76
  %78 = load float, float* %77, align 4
  %79 = fpext float %78 to double
  %80 = fmul float %50, %27
  %81 = fpext float %80 to double
  %82 = sext i32 %.02 to i64
  %83 = getelementptr inbounds i16, i16* %6, i64 %82
  %84 = load i16, i16* %83, align 2
  %85 = sext i16 %84 to i32
  %86 = mul nsw i32 2, %85
  %87 = sitofp i32 %86 to double
  %88 = fsub double %87, 1.000000e+00
  %89 = fmul double %81, %88
  %90 = sext i32 %.02 to i64
  %91 = getelementptr inbounds i16, i16* %6, i64 %90
  %92 = load i16, i16* %91, align 2
  %93 = sext i16 %92 to i32
  %94 = sitofp i32 %93 to double
  %95 = fmul double 6.000000e+00, %94
  %96 = fdiv double %89, %95
  %97 = fadd double %79, %96
  %98 = fptrunc double %97 to float
  %99 = sext i32 %.02 to i64
  %100 = getelementptr inbounds float, float* %9, i64 %99
  %101 = load float, float* %100, align 4
  %102 = call float @sqrt(float %98)
  %103 = fmul float %101, %102
  %104 = fmul float %103, %103
  %105 = fdiv float 1.000000e+00, %104
  %106 = sext i32 %.02 to i64
  %107 = getelementptr inbounds float, float* %2, i64 %106
  %108 = load float, float* %107, align 4
  %109 = call float @log(float %108)
  %110 = fsub float %109, %75
  %111 = fmul float %105, %110
  br label %112

; <label>:112:                                    ; preds = %178, %20
  %.03 = phi i32 [ 0, %20 ], [ %179, %178 ]
  %113 = icmp slt i32 %.03, 30
  br i1 %113, label %114, label %180

; <label>:114:                                    ; preds = %112
  %115 = sitofp i32 %.03 to float
  %116 = add nsw i32 %.03, 1
  %117 = mul nsw i32 %116, %.03
  %118 = sitofp i32 %117 to float
  %119 = fmul float %118, %62
  %120 = fsub float %115, %119
  %121 = fmul float %50, %120
  %122 = sext i32 %.02 to i64
  %123 = getelementptr inbounds float, float* %3, i64 %122
  %124 = load float, float* %123, align 4
  %125 = sitofp i32 %.03 to float
  %126 = fmul float %125, %50
  %127 = fadd float %124, %126
  %128 = sext i32 %.02 to i64
  %129 = getelementptr inbounds float, float* %9, i64 %128
  %130 = load float, float* %129, align 4
  %131 = call float @sqrt(float %127)
  %132 = fmul float %130, %131
  %133 = fmul float %132, %132
  %134 = sext i32 %.02 to i64
  %135 = getelementptr inbounds float, float* %3, i64 %134
  %136 = load float, float* %135, align 4
  %137 = fadd float %136, %121
  %138 = fmul float %34, %137
  %139 = sext i32 %.03 to i64
  %140 = getelementptr inbounds [30 x float], [30 x float]* %16, i64 0, i64 %139
  store float %138, float* %140, align 4
  %141 = sext i32 %.02 to i64
  %142 = getelementptr inbounds float, float* %3, i64 %141
  %143 = load float, float* %142, align 4
  %144 = sitofp i32 %.03 to float
  %145 = fmul float %144, %50
  %146 = fadd float %143, %145
  %147 = fmul float %42, %146
  %148 = fadd float %54, %147
  %149 = fpext float %148 to double
  %150 = fpext float %133 to double
  %151 = fmul double %150, 5.000000e-01
  %152 = fadd double %149, %151
  %153 = fptrunc double %152 to float
  %154 = sext i32 %.03 to i64
  %155 = getelementptr inbounds [30 x float], [30 x float]* %15, i64 0, i64 %154
  store float %153, float* %155, align 4
  %156 = sext i32 %.03 to i64
  %157 = getelementptr inbounds [30 x float], [30 x float]* %16, i64 0, i64 %156
  %158 = load float, float* %157, align 4
  %159 = fmul float %158, %111
  %160 = fadd float %148, %159
  %161 = fpext float %160 to double
  %162 = sext i32 %.03 to i64
  %163 = getelementptr inbounds [30 x float], [30 x float]* %16, i64 0, i64 %162
  %164 = load float, float* %163, align 4
  %165 = sext i32 %.03 to i64
  %166 = getelementptr inbounds [30 x float], [30 x float]* %16, i64 0, i64 %165
  %167 = load float, float* %166, align 4
  %168 = fmul float %164, %167
  %169 = fmul float %168, %105
  %170 = fsub float %133, %169
  %171 = fpext float %170 to double
  %172 = fmul double %171, 5.000000e-01
  %173 = fadd double %161, %172
  %174 = fptrunc double %173 to float
  %175 = call float @exp(float %174)
  %176 = sext i32 %.03 to i64
  %177 = getelementptr inbounds [30 x float], [30 x float]* %13, i64 0, i64 %176
  store float %175, float* %177, align 4
  br label %178

; <label>:178:                                    ; preds = %114
  %179 = add nsw i32 %.03, 1
  br label %112

; <label>:180:                                    ; preds = %112
  br label %181

; <label>:181:                                    ; preds = %188, %180
  %.1 = phi i32 [ 0, %180 ], [ %189, %188 ]
  %.01 = phi float [ 0.000000e+00, %180 ], [ %187, %188 ]
  %182 = icmp slt i32 %.1, 30
  br i1 %182, label %183, label %190

; <label>:183:                                    ; preds = %181
  %184 = sext i32 %.1 to i64
  %185 = getelementptr inbounds [30 x float], [30 x float]* %13, i64 0, i64 %184
  %186 = load float, float* %185, align 4
  %187 = fadd float %.01, %186
  br label %188

; <label>:188:                                    ; preds = %183
  %189 = add nsw i32 %.1, 1
  br label %181

; <label>:190:                                    ; preds = %181
  %191 = sext i32 %.02 to i64
  %192 = getelementptr inbounds float, float* %2, i64 %191
  %193 = load float, float* %192, align 4
  %194 = fpext float %193 to double
  %195 = fmul double 2.000000e+00, %194
  %196 = sext i32 %.02 to i64
  %197 = getelementptr inbounds i16, i16* %6, i64 %196
  %198 = load i16, i16* %197, align 2
  %199 = sext i16 %198 to i32
  %200 = sitofp i32 %199 to float
  %201 = fdiv float %.01, %200
  %202 = fpext float %201 to double
  %203 = fsub double %195, %202
  %204 = fptrunc double %203 to float
  %205 = call float @log(float %204)
  %206 = fdiv float 1.000000e+00, %103
  %207 = fsub float %75, %205
  %208 = fmul float %207, %206
  %209 = sext i32 %.02 to i64
  %210 = getelementptr inbounds i32, i32* %0, i64 %209
  %211 = load i32, i32* %210, align 4
  %212 = icmp eq i32 %211, 0
  %213 = select i1 %212, i32 1, i32 -1
  %214 = sitofp i32 %213 to float
  %215 = fmul float %214, %208
  %216 = fmul float %214, %206
  br label %217

; <label>:217:                                    ; preds = %233, %190
  %.2 = phi i32 [ 0, %190 ], [ %234, %233 ]
  %218 = icmp slt i32 %.2, 30
  br i1 %218, label %219, label %235

; <label>:219:                                    ; preds = %217
  %220 = sext i32 %.2 to i64
  %221 = getelementptr inbounds [30 x float], [30 x float]* %16, i64 0, i64 %220
  %222 = load float, float* %221, align 4
  %223 = fmul float %216, %222
  %224 = fadd float %215, %223
  %225 = call float @Ncdf(float %224)
  %226 = sext i32 %.2 to i64
  %227 = getelementptr inbounds [30 x float], [30 x float]* %15, i64 0, i64 %226
  %228 = load float, float* %227, align 4
  %229 = call float @exp(float %228)
  %230 = fmul float %229, %225
  %231 = sext i32 %.2 to i64
  %232 = getelementptr inbounds [30 x float], [30 x float]* %14, i64 0, i64 %231
  store float %230, float* %232, align 4
  br label %233

; <label>:233:                                    ; preds = %219
  %234 = add nsw i32 %.2, 1
  br label %217

; <label>:235:                                    ; preds = %217
  br label %236

; <label>:236:                                    ; preds = %243, %235
  %.3 = phi i32 [ 0, %235 ], [ %244, %243 ]
  %.0 = phi float [ 0.000000e+00, %235 ], [ %242, %243 ]
  %237 = icmp slt i32 %.3, 30
  br i1 %237, label %238, label %245

; <label>:238:                                    ; preds = %236
  %239 = sext i32 %.3 to i64
  %240 = getelementptr inbounds [30 x float], [30 x float]* %14, i64 0, i64 %239
  %241 = load float, float* %240, align 4
  %242 = fadd float %.0, %241
  br label %243

; <label>:243:                                    ; preds = %238
  %244 = add nsw i32 %.3, 1
  br label %236

; <label>:245:                                    ; preds = %236
  %246 = fmul float %214, %208
  %247 = call float @Ncdf(float %246)
  %248 = sext i32 %.02 to i64
  %249 = getelementptr inbounds float, float* %7, i64 %248
  %250 = load float, float* %249, align 4
  %251 = sext i32 %.02 to i64
  %252 = getelementptr inbounds float, float* %4, i64 %251
  %253 = load float, float* %252, align 4
  %254 = fmul float %250, %253
  %255 = call float @exp(float %254)
  %256 = fdiv float 1.000000e+00, %255
  %257 = sext i32 %.02 to i64
  %258 = getelementptr inbounds i16, i16* %6, i64 %257
  %259 = load i16, i16* %258, align 2
  %260 = sext i16 %259 to i32
  %261 = sitofp i32 %260 to float
  %262 = fdiv float %.0, %261
  %263 = sext i32 %.02 to i64
  %264 = getelementptr inbounds float, float* %2, i64 %263
  %265 = load float, float* %264, align 4
  %266 = fmul float %265, %247
  %267 = fsub float %262, %266
  %268 = sext i32 %.02 to i64
  %269 = getelementptr inbounds i16, i16* %6, i64 %268
  %270 = load i16, i16* %269, align 2
  %271 = sext i16 %270 to i32
  %272 = sext i32 %.02 to i64
  %273 = getelementptr inbounds i16, i16* %5, i64 %272
  %274 = load i16, i16* %273, align 2
  %275 = sext i16 %274 to i32
  %276 = sub nsw i32 %271, %275
  %277 = sitofp i32 %276 to float
  %278 = fmul float %214, %277
  %279 = sext i32 %.02 to i64
  %280 = getelementptr inbounds i16, i16* %6, i64 %279
  %281 = load i16, i16* %280, align 2
  %282 = sext i16 %281 to i32
  %283 = sitofp i32 %282 to float
  %284 = fdiv float %278, %283
  %285 = fmul float %267, %284
  %286 = fmul float %285, %256
  %287 = sext i32 %.02 to i64
  %288 = getelementptr inbounds float, float* %10, i64 %287
  store float %286, float* %288, align 4
  br label %289

; <label>:289:                                    ; preds = %245
  %290 = add nsw i32 %.02, 1
  br label %17

; <label>:291:                                    ; preds = %17
  ret void
}

; Function Attrs: noinline nounwind uwtable
define i32 @main(i32, i8**) #0 {
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  %5 = alloca i16, align 2
  %6 = alloca i16, align 2
  %7 = alloca i64, align 8
  %8 = icmp slt i32 %0, 2
  br i1 %8, label %9, label %10

; <label>:9:                                      ; preds = %2
  call void @perror(i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str, i32 0, i32 0))
  br label %309

; <label>:10:                                     ; preds = %2
  %11 = getelementptr inbounds i8*, i8** %1, i64 1
  %12 = load i8*, i8** %11, align 8
  %13 = call %struct._IO_FILE* @fopen(i8* %12, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0))
  %14 = icmp eq %struct._IO_FILE* %13, null
  br i1 %14, label %15, label %16

; <label>:15:                                     ; preds = %10
  call void @perror(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.2, i32 0, i32 0))
  br label %309

; <label>:16:                                     ; preds = %10
  %17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i32 0, i32 0))
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.4, i32 0, i32 0))
  %19 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i64* %7)
  %20 = load i64, i64* %7, align 8
  %21 = mul i64 4, %20
  %22 = call noalias i8* @malloc(i64 %21) #4
  %23 = bitcast i8* %22 to i32*
  %24 = load i64, i64* %7, align 8
  %25 = mul i64 4, %24
  %26 = call noalias i8* @malloc(i64 %25) #4
  %27 = bitcast i8* %26 to float*
  %28 = load i64, i64* %7, align 8
  %29 = mul i64 4, %28
  %30 = call noalias i8* @malloc(i64 %29) #4
  %31 = bitcast i8* %30 to float*
  %32 = load i64, i64* %7, align 8
  %33 = mul i64 4, %32
  %34 = call noalias i8* @malloc(i64 %33) #4
  %35 = bitcast i8* %34 to float*
  %36 = load i64, i64* %7, align 8
  %37 = mul i64 4, %36
  %38 = call noalias i8* @malloc(i64 %37) #4
  %39 = bitcast i8* %38 to float*
  %40 = load i64, i64* %7, align 8
  %41 = mul i64 2, %40
  %42 = call noalias i8* @malloc(i64 %41) #4
  %43 = bitcast i8* %42 to i16*
  %44 = load i64, i64* %7, align 8
  %45 = mul i64 2, %44
  %46 = call noalias i8* @malloc(i64 %45) #4
  %47 = bitcast i8* %46 to i16*
  %48 = load i64, i64* %7, align 8
  %49 = mul i64 4, %48
  %50 = call noalias i8* @malloc(i64 %49) #4
  %51 = bitcast i8* %50 to float*
  %52 = load i64, i64* %7, align 8
  %53 = mul i64 4, %52
  %54 = call noalias i8* @malloc(i64 %53) #4
  %55 = bitcast i8* %54 to float*
  %56 = load i64, i64* %7, align 8
  %57 = mul i64 4, %56
  %58 = call noalias i8* @malloc(i64 %57) #4
  %59 = bitcast i8* %58 to float*
  %60 = load i64, i64* %7, align 8
  %61 = mul i64 4, %60
  %62 = call noalias i8* @malloc(i64 %61) #4
  %63 = bitcast i8* %62 to float*
  %64 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %3, float* %4)
  br label %65

; <label>:65:                                     ; preds = %82, %16
  %.01 = phi i32 [ 0, %16 ], [ %83, %82 ]
  %66 = sext i32 %.01 to i64
  %67 = load i64, i64* %7, align 8
  %68 = icmp slt i64 %66, %67
  br i1 %68, label %69, label %84

; <label>:69:                                     ; preds = %65
  %70 = call i32 @rand() #4
  %71 = sitofp i32 %70 to float
  %72 = load float, float* %4, align 4
  %73 = load float, float* %3, align 4
  %74 = fsub float %72, %73
  %75 = fmul float %71, %74
  %76 = fdiv float %75, 0x41E0000000000000
  %77 = load float, float* %3, align 4
  %78 = fadd float %76, %77
  %79 = fptosi float %78 to i32
  %80 = sext i32 %.01 to i64
  %81 = getelementptr inbounds i32, i32* %23, i64 %80
  store i32 %79, i32* %81, align 4
  br label %82

; <label>:82:                                     ; preds = %69
  %83 = add nsw i32 %.01, 1
  br label %65

; <label>:84:                                     ; preds = %65
  %85 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %3, float* %4)
  br label %86

; <label>:86:                                     ; preds = %102, %84
  %.1 = phi i32 [ 0, %84 ], [ %103, %102 ]
  %87 = sext i32 %.1 to i64
  %88 = load i64, i64* %7, align 8
  %89 = icmp slt i64 %87, %88
  br i1 %89, label %90, label %104

; <label>:90:                                     ; preds = %86
  %91 = call i32 @rand() #4
  %92 = sitofp i32 %91 to float
  %93 = load float, float* %4, align 4
  %94 = load float, float* %3, align 4
  %95 = fsub float %93, %94
  %96 = fmul float %92, %95
  %97 = fdiv float %96, 0x41E0000000000000
  %98 = load float, float* %3, align 4
  %99 = fadd float %97, %98
  %100 = sext i32 %.1 to i64
  %101 = getelementptr inbounds float, float* %27, i64 %100
  store float %99, float* %101, align 4
  br label %102

; <label>:102:                                    ; preds = %90
  %103 = add nsw i32 %.1, 1
  br label %86

; <label>:104:                                    ; preds = %86
  %105 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %3, float* %4)
  br label %106

; <label>:106:                                    ; preds = %122, %104
  %.2 = phi i32 [ 0, %104 ], [ %123, %122 ]
  %107 = sext i32 %.2 to i64
  %108 = load i64, i64* %7, align 8
  %109 = icmp slt i64 %107, %108
  br i1 %109, label %110, label %124

; <label>:110:                                    ; preds = %106
  %111 = call i32 @rand() #4
  %112 = sitofp i32 %111 to float
  %113 = load float, float* %4, align 4
  %114 = load float, float* %3, align 4
  %115 = fsub float %113, %114
  %116 = fmul float %112, %115
  %117 = fdiv float %116, 0x41E0000000000000
  %118 = load float, float* %3, align 4
  %119 = fadd float %117, %118
  %120 = sext i32 %.2 to i64
  %121 = getelementptr inbounds float, float* %31, i64 %120
  store float %119, float* %121, align 4
  br label %122

; <label>:122:                                    ; preds = %110
  %123 = add nsw i32 %.2, 1
  br label %106

; <label>:124:                                    ; preds = %106
  %125 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %3, float* %4)
  br label %126

; <label>:126:                                    ; preds = %142, %124
  %.3 = phi i32 [ 0, %124 ], [ %143, %142 ]
  %127 = sext i32 %.3 to i64
  %128 = load i64, i64* %7, align 8
  %129 = icmp slt i64 %127, %128
  br i1 %129, label %130, label %144

; <label>:130:                                    ; preds = %126
  %131 = call i32 @rand() #4
  %132 = sitofp i32 %131 to float
  %133 = load float, float* %4, align 4
  %134 = load float, float* %3, align 4
  %135 = fsub float %133, %134
  %136 = fmul float %132, %135
  %137 = fdiv float %136, 0x41E0000000000000
  %138 = load float, float* %3, align 4
  %139 = fadd float %137, %138
  %140 = sext i32 %.3 to i64
  %141 = getelementptr inbounds float, float* %35, i64 %140
  store float %139, float* %141, align 4
  br label %142

; <label>:142:                                    ; preds = %130
  %143 = add nsw i32 %.3, 1
  br label %126

; <label>:144:                                    ; preds = %126
  %145 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %3, float* %4)
  br label %146

; <label>:146:                                    ; preds = %162, %144
  %.4 = phi i32 [ 0, %144 ], [ %163, %162 ]
  %147 = sext i32 %.4 to i64
  %148 = load i64, i64* %7, align 8
  %149 = icmp slt i64 %147, %148
  br i1 %149, label %150, label %164

; <label>:150:                                    ; preds = %146
  %151 = call i32 @rand() #4
  %152 = sitofp i32 %151 to float
  %153 = load float, float* %4, align 4
  %154 = load float, float* %3, align 4
  %155 = fsub float %153, %154
  %156 = fmul float %152, %155
  %157 = fdiv float %156, 0x41E0000000000000
  %158 = load float, float* %3, align 4
  %159 = fadd float %157, %158
  %160 = sext i32 %.4 to i64
  %161 = getelementptr inbounds float, float* %39, i64 %160
  store float %159, float* %161, align 4
  br label %162

; <label>:162:                                    ; preds = %150
  %163 = add nsw i32 %.4, 1
  br label %146

; <label>:164:                                    ; preds = %146
  %165 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %3, float* %4)
  br label %166

; <label>:166:                                    ; preds = %182, %164
  %.5 = phi i32 [ 0, %164 ], [ %183, %182 ]
  %167 = sext i32 %.5 to i64
  %168 = load i64, i64* %7, align 8
  %169 = icmp slt i64 %167, %168
  br i1 %169, label %170, label %184

; <label>:170:                                    ; preds = %166
  %171 = call i32 @rand() #4
  %172 = sitofp i32 %171 to float
  %173 = load float, float* %4, align 4
  %174 = load float, float* %3, align 4
  %175 = fsub float %173, %174
  %176 = fmul float %172, %175
  %177 = fdiv float %176, 0x41E0000000000000
  %178 = load float, float* %3, align 4
  %179 = fadd float %177, %178
  %180 = sext i32 %.5 to i64
  %181 = getelementptr inbounds float, float* %51, i64 %180
  store float %179, float* %181, align 4
  br label %182

; <label>:182:                                    ; preds = %170
  %183 = add nsw i32 %.5, 1
  br label %166

; <label>:184:                                    ; preds = %166
  %185 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %3, float* %4)
  br label %186

; <label>:186:                                    ; preds = %202, %184
  %.6 = phi i32 [ 0, %184 ], [ %203, %202 ]
  %187 = sext i32 %.6 to i64
  %188 = load i64, i64* %7, align 8
  %189 = icmp slt i64 %187, %188
  br i1 %189, label %190, label %204

; <label>:190:                                    ; preds = %186
  %191 = call i32 @rand() #4
  %192 = sitofp i32 %191 to float
  %193 = load float, float* %4, align 4
  %194 = load float, float* %3, align 4
  %195 = fsub float %193, %194
  %196 = fmul float %192, %195
  %197 = fdiv float %196, 0x41E0000000000000
  %198 = load float, float* %3, align 4
  %199 = fadd float %197, %198
  %200 = sext i32 %.6 to i64
  %201 = getelementptr inbounds float, float* %55, i64 %200
  store float %199, float* %201, align 4
  br label %202

; <label>:202:                                    ; preds = %190
  %203 = add nsw i32 %.6, 1
  br label %186

; <label>:204:                                    ; preds = %186
  %205 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), float* %3, float* %4)
  br label %206

; <label>:206:                                    ; preds = %222, %204
  %.7 = phi i32 [ 0, %204 ], [ %223, %222 ]
  %207 = sext i32 %.7 to i64
  %208 = load i64, i64* %7, align 8
  %209 = icmp slt i64 %207, %208
  br i1 %209, label %210, label %224

; <label>:210:                                    ; preds = %206
  %211 = call i32 @rand() #4
  %212 = sitofp i32 %211 to float
  %213 = load float, float* %4, align 4
  %214 = load float, float* %3, align 4
  %215 = fsub float %213, %214
  %216 = fmul float %212, %215
  %217 = fdiv float %216, 0x41E0000000000000
  %218 = load float, float* %3, align 4
  %219 = fadd float %217, %218
  %220 = sext i32 %.7 to i64
  %221 = getelementptr inbounds float, float* %59, i64 %220
  store float %219, float* %221, align 4
  br label %222

; <label>:222:                                    ; preds = %210
  %223 = add nsw i32 %.7, 1
  br label %206

; <label>:224:                                    ; preds = %206
  %225 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.7, i32 0, i32 0), i16* %5, i16* %6)
  br label %226

; <label>:226:                                    ; preds = %247, %224
  %.8 = phi i32 [ 0, %224 ], [ %248, %247 ]
  %227 = sext i32 %.8 to i64
  %228 = load i64, i64* %7, align 8
  %229 = icmp slt i64 %227, %228
  br i1 %229, label %230, label %249

; <label>:230:                                    ; preds = %226
  %231 = call i32 @rand() #4
  %232 = load i16, i16* %6, align 2
  %233 = sext i16 %232 to i32
  %234 = load i16, i16* %5, align 2
  %235 = sext i16 %234 to i32
  %236 = sub nsw i32 %233, %235
  %237 = mul nsw i32 %231, %236
  %238 = sitofp i32 %237 to float
  %239 = fdiv float %238, 0x41E0000000000000
  %240 = load i16, i16* %5, align 2
  %241 = sext i16 %240 to i32
  %242 = sitofp i32 %241 to float
  %243 = fadd float %239, %242
  %244 = fptosi float %243 to i16
  %245 = sext i32 %.8 to i64
  %246 = getelementptr inbounds i16, i16* %47, i64 %245
  store i16 %244, i16* %246, align 2
  br label %247

; <label>:247:                                    ; preds = %230
  %248 = add nsw i32 %.8, 1
  br label %226

; <label>:249:                                    ; preds = %226
  %250 = call i32 (%struct._IO_FILE*, i8*, ...) @__isoc99_fscanf(%struct._IO_FILE* %13, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.7, i32 0, i32 0), i16* %5, i16* %6)
  br label %251

; <label>:251:                                    ; preds = %284, %249
  %.9 = phi i32 [ 0, %249 ], [ %285, %284 ]
  %252 = sext i32 %.9 to i64
  %253 = load i64, i64* %7, align 8
  %254 = icmp slt i64 %252, %253
  br i1 %254, label %255, label %286

; <label>:255:                                    ; preds = %251
  %256 = call i32 @rand() #4
  %257 = load i16, i16* %6, align 2
  %258 = sext i16 %257 to i32
  %259 = load i16, i16* %5, align 2
  %260 = sext i16 %259 to i32
  %261 = sub nsw i32 %258, %260
  %262 = mul nsw i32 %256, %261
  %263 = trunc i32 %262 to i16
  %264 = sext i16 %263 to i32
  %265 = sdiv i32 %264, 2147483647
  %266 = load i16, i16* %5, align 2
  %267 = sext i16 %266 to i32
  %268 = add nsw i32 %265, %267
  %269 = trunc i32 %268 to i16
  %270 = sext i32 %.9 to i64
  %271 = getelementptr inbounds i16, i16* %43, i64 %270
  store i16 %269, i16* %271, align 2
  %272 = sext i32 %.9 to i64
  %273 = getelementptr inbounds i16, i16* %43, i64 %272
  %274 = load i16, i16* %273, align 2
  %275 = sext i16 %274 to i32
  %276 = icmp ne i32 %275, 30
  br i1 %276, label %277, label %283

; <label>:277:                                    ; preds = %255
  %278 = sext i32 %.9 to i64
  %279 = getelementptr inbounds i16, i16* %43, i64 %278
  %280 = load i16, i16* %279, align 2
  %281 = sext i16 %280 to i32
  %282 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.8, i32 0, i32 0), i32 %281)
  br label %309

; <label>:283:                                    ; preds = %255
  br label %284

; <label>:284:                                    ; preds = %283
  %285 = add nsw i32 %.9, 1
  br label %251

; <label>:286:                                    ; preds = %251
  %287 = call i32 @fclose(%struct._IO_FILE* %13)
  %288 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.9, i32 0, i32 0))
  %289 = call i64 @getTime()
  %290 = uitofp i64 %289 to double
  %291 = load i64, i64* %7, align 8
  call void @Calculation(i32* %23, float* %27, float* %31, float* %35, float* %39, i16* %47, i16* %43, float* %51, float* %55, float* %59, float* %63, i64 %291)
  %292 = call i64 @getTime()
  %293 = uitofp i64 %292 to double
  %294 = fsub double %293, %290
  %295 = fdiv double %294, 1.000000e+06
  %296 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.10, i32 0, i32 0), double %295)
  %297 = bitcast i32* %23 to i8*
  call void @free(i8* %297) #4
  %298 = bitcast float* %27 to i8*
  call void @free(i8* %298) #4
  %299 = bitcast float* %31 to i8*
  call void @free(i8* %299) #4
  %300 = bitcast float* %35 to i8*
  call void @free(i8* %300) #4
  %301 = bitcast float* %39 to i8*
  call void @free(i8* %301) #4
  %302 = bitcast i16* %43 to i8*
  call void @free(i8* %302) #4
  %303 = bitcast i16* %47 to i8*
  call void @free(i8* %303) #4
  %304 = bitcast float* %51 to i8*
  call void @free(i8* %304) #4
  %305 = bitcast float* %55 to i8*
  call void @free(i8* %305) #4
  %306 = bitcast float* %59 to i8*
  call void @free(i8* %306) #4
  %307 = bitcast float* %63 to i8*
  call void @free(i8* %307) #4
  %308 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.11, i32 0, i32 0))
  br label %309

; <label>:309:                                    ; preds = %286, %277, %15, %9
  %.0 = phi i32 [ 1, %9 ], [ 1, %15 ], [ 1, %277 ], [ 0, %286 ]
  ret i32 %.0
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
