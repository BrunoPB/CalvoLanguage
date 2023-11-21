; ModuleID = 'CalvoModule'
source_filename = "CalvoModule"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare void @printf(i8*, i32, ...)

declare i32 @scanf(i8*, i32*, ...)

define i32 @main() {
entry:
  %0 = alloca i32, align 4
  store i32 -5, i32* %0, align 4
  %var = load i32, i32* %0, align 4
  call void (i8*, i32, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), i32 %var)
  ret i32 0
}
