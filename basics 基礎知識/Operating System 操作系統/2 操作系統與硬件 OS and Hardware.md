
操作系統是介於應用與硬件之間的界面。應用透過操作系統來簡介操作硬件。
An OS is the interface between the user and the architecture. User manages hardware by manipulating the OS.


# 2.1 簡單涉獵操作系統的功能

## 2.1.1 Modern OS Functionality

- Process and Thread Management 進程與線程管理
- Concurrency 並發
	- Doing multiple things simultaneously. 同時做多件事情。
- I/O Devices I/O設備管理
- Memory Management 內存管理
	- Coordinates allocation of memory. 定位內存分配
	- Move data between disk and main memory. 在存儲和主存之間移動數據。
- Files 文件管理
	- Coordinates how disk space is used for files. 規定磁盤空間如何為了存儲文件而分配

## 2.1.2 Architectural Features Motivated by OS Services

操作系統的功能實現離不開硬件的支持；同樣地，操作系統的功能也能夠影響硬件的發展。

| OS Service 操作系統服務                                   | Hardware Support 硬件支持                                                                     |
| --------------------------------------------------- | ----------------------------------------------------------------------------------------- |
| Protection 保護                                       | Kernel/User Mode, Protected Instructions; Base/Limit Registers <br>內核/用戶態，受保護的指令，基址/限製寄存器 |
| Interrupts 中斷                                       | Interrupt Vectors 中斷向量                                                                    |
| System Calls 系統調用                                   | Trap instructions and trap vectors 陷阱指令和向量                                                |
| I/O                                                 | Interrupts and memory mapping 中斷，內存映射                                                     |
| Scheduling, Error Recovery, Accounting <br>調度，錯誤恢復， | Timer 時鐘                                                                                  |
| Synchronization 同步                                  | Atomic instructions. 原字化指令                                                                |


# 2.2 Protection 保護

CPU supports a set of assembly instructions, where some of which are privileged.
CPU支持的眾多指令當中，相當一部分是具有特權的。

```assembly
section .data
	msg db "Hello, World! (User Mode)", 0xA  ; 要打印的字符串

section .text
	global _start

_start:
	; 用戶狀態下進行，調用系統調用打印消息。
	; 使用係統調用

	mov eax, 4    ; 系統調用號 4：sys_write
	mov ebx, 1    ; 文件描述符 1：標準輸出stdout
	mov ecx, msg  ; 要打印的消息
	mov edx, 20   ; 消息長度為20字節
	int 0x80      ; int不是整數，是interrupt中斷的縮寫。這裡切換到內核態執行sys_write

	; 結束程序，調用係統調用1: sys_exit 退出
	mov eax 1     ; 系統調用號 1: sys_exit
	xor ebx, ebx  ; 退出狀態為 0 
	int 0x80      ; 觸發系統調用，切換到內核態執行sys_exit

```

## User Mode vs Kernel Mode 用戶態與內核態

User/Kernel mode is designed to **protect** the system from aberrant users and processors from accessing restricted instructions that could only used by the OS.

用戶態與內核態用於**保護**系統免受異常用戶的侵犯，並防止處理器訪問只能由操作係統使用的受限指令。

A user (in most times are referred as an application) may not:

- Address I/O directly. 
- Use instructions that manipulate the state of memory.
- **Set the mode bits that determine user/kernel mode. **
- Disable or enable interrupt.
- Halt the machine.

But in the kernel mode, the operating system can do all these things above.

The hardware should at least support that:

- A status bit in a protected processor register indicates the mode. 
- Protected instructions can only be executed in kernel mode. 

## System Call 系統調用

System call is an API exposed by the kernel that executes privileged instructions.

System Call，或系統調用，是操作系統暴露給應用程序的一組API。用戶通過調用該API來向操作系統申請執行受保護的程序，並由操作系統代為執行。

<img src="https://data-flair.training/blogs/wp-content/uploads/sites/2/2021/08/Workings-of-a-System-Call.jpg" width="300px">

When a system call is triggered:

1. A **trap** is caused. A **trap vector** jumps to the **trap handler** in the OS kernel.
2. The trap handler uses the parameter to the system call to jump to the required handler from the user.
	1. The architecture must permit the OS to verify the caller's parameters
3. The handler saves the caller's state (Program Counter, mode bit) to restore control to the user process.
	1. The architecture must provide a way to return to user mode when finished.


## Why hardware? 

操作系統的保護功能為什麼必須要靠硬件堅持？