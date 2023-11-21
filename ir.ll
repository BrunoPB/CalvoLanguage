; ModuleID = 'CalvoModule'
source_filename = "CalvoModule"

@0 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare void @printf(i8*, i32, ...)

declare i32 @scanf(i8*, i32*, ...)

define i32 @main() {
entry:
  %input = alloca i32, i32 0, align 4
  store i32 0, i32* %input, align 4
  %input1 = load i32, i32* %input, align 4
  %0 = call i32 (i8*, i32*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* %input)
  %input2 = load i32, i32* %input, align 4
  %1 = icmp sgt i32 %input2, 0
  br i1 %1, label %then, label %else

then:                                             ; preds = %entry
  call void (i8*, i32, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @1, i32 0, i32 0), i32 1)
  br label %ifEnd

ifEnd:                                            ; preds = %else, %then
  ret i32 0

else:                                             ; preds = %entry
  call void (i8*, i32, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @1, i32 0, i32 0), i32 25)
  br label %ifEnd
}
