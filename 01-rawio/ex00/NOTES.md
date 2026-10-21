## 1. First syscall: execve(const char *pathname, char *const argv[], char *const envp[]) ##
This syscall executes the program reffered by path.
The program that was running gets substituted by the new program and its data (heap, stack, initialized and uninitialized variables).

The path can be either:
- A binary executable
- A script that starts with: "#!interpreter"

ARGV is an array of pointers (the 'v' stands for vector) to the strings passed to the new program.
There is another parameter "envp", which I need to furthermore investigate, seems to be similar to hashmaps. However it is not POSIX1 compliant, see environ(7).

It says that execve() does not return in success, but it seems to return 0 (tried with strace).
The text, uninitialized data (bss -> like mi name), and stack are overwritten;

## 2 BRK, MMAP, MPROTECT ##
### 2.1 BRK ###
brk adjust the position of the last byte of memory owned by the program. So incresing the break gives more memory 'allocates -> malloc', and decreasing it deallocates memory.
The system decides whether or not the program will get the memory it asked for, it depends on how much free memory the system has, and also, on setrlimit(). With strace prlimit64() is what I can see to be used by commands like ls.
Return values differ deppending from where it was called, kernel or c programs.
On failure the syscall will return the current break, but on c programs it will return -1.

### 2.2 MMAP ###
Mmap tryes to put X bytes from a file descriptor to memory.
The protection of that data can be:
- prot_exec -> it can be executed
- prot_red -> it can be read
- prot_write -> it can be changed/written
- prot_none -> it cant be accesed
Here I found some examples of how language barrier can make learning sometimes difficult.
In: https://manpages.ubuntu.com/manpages/bionic/es/man2/mmap.2.html
The description of protection said: "debe ser ejecutado/leido/escrito", that means "Must be executed/readed/written".
Those are small details, but I have noticed more in the past.

#### BASIC FLAGS: #####
- map_shared -> content is shared with other processes that map the same area.
- map_shared_validate -> similar to shared, but the kernel verifies all the flags and fails if one of then is unrecognized.
- map_private -> creates a private copy-on-write of the map, other processes and the file are not aware of this changes.

There are many more flags, some for size, others for locking or unlocking the map. It is all specified in the man.


These syscalls ensure that the program will have the necesary space and memory protection to run.

### 2.3 MPROTECT ###
mprotect changes the protection OF THE CALLING PROCCESS memory pages.
Addr (from where protection start) must be aligned with a page boundary, in my system, page_size is 4096.
The protection levels are like MMAP (thats because MMAP calls MPROTECT):
- prot_exec, prot_red, prot_write and prot_none.
New:
- pront_sem -> Memory can be used for atomic operations, futex() is important.
- prot_sao -> Memory has strong access ordering (compiler and processor cannot change the order of the instrucctions).
- prot_growsup -> It is made specifically for growing upwards stack architectures (ARM can be like that but is rare).
- prot_growdown -> It is made specifically for growing downward stack architectures.

Example with strace ls:
"mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_STACK, -1, 0) = 0x73b913587000"
The call is made to mmap, with all the flags set, and the next call is:
"mprotect(0x73b913587000, 4096, PROT_NONE) = 0"


## OPEN VS OPENAT ##

Open works from the current directory if the path is relative, but if it is absolute /, starts from the system root.
Open is not safe in multi-threaded programs or safe systems.

Openat has one more parameter:
- dir_fd

If dir_fd is set to AT_FDCWD, it will behave like open(). But when it is set to other value, the starting point for a relative path is dir_fd.
However, if the path is absolute '/', it will ignore the dir_fd.

It is safer when more than one thread is safe, because the program can traverse differnt folders without changing the relative paths.


## PRINTF > terminal VS PRINTF > file ##

The main difference is between these two lines:
1. fstat(1, {st_mode=S_IFREG|0777, st_size=0, ...}) = 0 -> S_IFREG = is regular file.
2. fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0 -> S_IFCHR = is character device.
The fstat function gets the terminal output or the file output depending on >.



## MOST CALLED SYSCALL ##

The most called is mmap, that is because it is used for more than malloc:
1. Loading libraries and space for the stack.
2. Cache reading like this example:
``
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=49915, ...}) = 0
mmap(NULL, 49915, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7cd41b44b000
``
3. Heap allocation.

## WRITING THIS NOTES ##

This notes were almost completly written after ex01 and ex02 where done.
These exercises have made me grasp what is working underneath every program in linux systems, but I have also realised how complex it is.
I am thankful to 42 foundation and UNIR for giving me the basis of C programming, but the type of programming and thinking required here is different. While doing this exercises I found that error handling and defensive codding are by far more difficult and detailed than what I needed in 42 or the Uni, but I am really happy to have the opportunity to learn and improve troughout this roadmap, the code will get better in the future.