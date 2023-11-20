; ModuleID = 'CalvoModule'
source_filename = "CalvoModule"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare void @printf(i8*, i32, ...)

define i32 @main() {
entry:
  %i = alloca i32, i32 0, align 4
  store i32 0, i32* %i, align 4
  br label %condition

condition:                                        ; preds = %while, %entry
  %i1 = load i32, i32* %i, align 4
  %0 = icmp ne i32 %i1, 7
  br i1 %0, label %while, label %endWhile

while:                                            ; preds = %condition
  %i2 = load i32, i32* %i, align 4
  %1 = add i32 %i2, 1
  store i32 %1, i32* %i, align 4
  %i3 = load i32, i32* %i, align 4
  call void (i8*, i32, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), i32 %i3)
  br label %condition

endWhile:                                         ; preds = %condition
  ret i32 0
}
