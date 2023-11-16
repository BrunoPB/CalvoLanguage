; ModuleID = 'CalvoModule'
source_filename = "CalvoModule"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare void @printf(i8*, i32, ...)

define i32 @main() {
entry:
  call void (i8*, i32, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), i32 2)
  ret i32 0
}
