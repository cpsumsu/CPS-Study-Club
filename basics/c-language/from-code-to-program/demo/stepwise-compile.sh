# 1. 预处理 (Preprocess): C语言代码 -> C语言代码
gcc -E ./stage-0_source-code/addition.c \
    -o ./stage-1_preprocessed-code/addition.i
gcc -E ./stage-0_source-code/main.c \
    -o ./stage-1_preprocessed-code/main.i

# 2. 编译 (Compile): C语言代码 -> 汇编代码
gcc -S ./stage-1_preprocessed-code/addition.i \
    -masm="intel" \
    -fno-asynchronous-unwind-tables \
    -o ./stage-2_assembly-code/addition.s
gcc -S ./stage-1_preprocessed-code/main.i \
    -masm="intel" \
    -fno-asynchronous-unwind-tables \
    -o ./stage-2_assembly-code/main.s

# 3. 汇编 (Assembly): 汇编代码 -> 目标代码
gcc -c ./stage-2_assembly-code/addition.s \
    -o ./stage-3_object-code/addition.o
gcc -c ./stage-2_assembly-code/main.s \
    -o ./stage-3_object-code/main.o

# 4. 链接 (Link): 目标代码 -> 可执行文件
gcc ./stage-3_object-code/addition.o \
    ./stage-3_object-code/main.o \
    -o ./stage-4_executable/main