clang++ compiler.cpp -o cc.out `llvm-config --cxxflags --ldflags --system-libs --libs core`

./cc.out a.calvo ir.ll

lli ir.ll
