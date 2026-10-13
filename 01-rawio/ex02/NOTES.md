## MCP ##
mcp copies data from one file to another.
The buffer size can be modified with the option -b "number".

## Data ##
| Buffer size | Number of calls | Total time | Syscall medium time |
|---|---|---|
| 64 | 6553637 | 98.276532 | 12 |
| 4096 | 102438 | 1.618733 | 15 |
| 65536 | 6438 | 0.212155 | 32 |
| 1048576 | 437 | 0.101939 | 233 |

## Errors ##
The errors bellow are from:
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory);

## Interesting fact ##
There is an interesting relation between the buffer size and the number of calls, every try shows that the product is always similar (with a difference of ~1% in the most extreme tests):
419.432.768
419.586.048
421.920.768
458.227.712

### Details ###
## Buffer size: 64 ##
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 50.25   49.388867          15   3276800           write
 49.74   48.887603          14   3276802           read
  0.00    0.000062          15         4           close
  0.00    0.000000           0         2           fstat
  0.00    0.000000           0         8           mmap
  0.00    0.000000           0         3           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         2           pread64
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           arch_prctl
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         4           openat
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         1           prlimit64
  0.00    0.000000           0         1           getrandom
  0.00    0.000000           0         1           rseq
------ ----------- ----------- --------- --------- ----------------
100.00   98.276532          14   6553637         1 total

## Buffer size: 4096 ##
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 50.19    0.812488          15     51200           write
 49.80    0.806056          15     51202           read
  0.01    0.000123          30         4           openat
  0.00    0.000047          11         4           close
  0.00    0.000019           4         4           brk
  0.00    0.000000           0         2           fstat
  0.00    0.000000           0         8           mmap
  0.00    0.000000           0         3           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         2           pread64
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           arch_prctl
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         1           prlimit64
  0.00    0.000000           0         1           getrandom
  0.00    0.000000           0         1           rseq
------ ----------- ----------- --------- --------- ----------------
100.00    1.618733          15    102438         1 total

## Buffer size: 65536 ##
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 50.46    0.107044          33      3202           read
 49.51    0.105032          32      3200           write
  0.02    0.000052          13         4           close
  0.01    0.000027           6         4           brk
  0.00    0.000000           0         2           fstat
  0.00    0.000000           0         8           mmap
  0.00    0.000000           0         3           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         2           pread64
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           arch_prctl
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         4           openat
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         1           prlimit64
  0.00    0.000000           0         1           getrandom
  0.00    0.000000           0         1           rseq
------ ----------- ----------- --------- --------- ----------------
100.00    0.212155          32      6438         1 total

## Buffer size: 1048576 ##
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 50.28    0.051260         256       200           write
 49.27    0.050224         248       202           read
  0.11    0.000115          57         2           munmap
  0.10    0.000097          24         4           close
  0.09    0.000092          23         4           openat
  0.05    0.000053          17         3           mprotect
  0.03    0.000028           3         9           mmap
  0.01    0.000015          15         1           getrandom
  0.01    0.000012          12         1           set_robust_list
  0.01    0.000011          11         1           arch_prctl
  0.01    0.000011          11         1           set_tid_address
  0.01    0.000011          11         1           prlimit64
  0.01    0.000010          10         1           rseq
  0.00    0.000000           0         2           fstat
  0.00    0.000000           0         1           brk
  0.00    0.000000           0         2           pread64
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
------ ----------- ----------- --------- --------- ----------------
100.00    0.101939         233       437         1 total