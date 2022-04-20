# Lock comparison

## Build and Run

```bash
mkdir build
cd build
cmake ..
./lock_comparison 4 10000 # 10000 times counter increment by 4 threads
```

## Lock types

* TAS lock: Test-and-Set lock using inline assembly (x86)
* TAS Sample lock: Test-and-Set lock using `std::atomic_flag`
* TATAS lock: Test-and-Set lock using inline assembly (x86)
* TATAS Sample lock: Test-and-Set lock using `std::atomic_flag`