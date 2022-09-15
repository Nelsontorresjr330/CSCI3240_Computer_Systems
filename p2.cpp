#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

using namespace std;
int bytes_allocated = 0;

void *mm_alloc(int num_bytes_to_allocate){
    int pgsz, *ip, numpages, maxBytes;
    void *region;
    unsigned char * cp;

    numpages = (int) *getenv("P2_NUM_PAGES");
    pgsz = getpagesize();
    maxBytes = pgsz * numpages;

    if (bytes_allocated + num_bytes_to_allocate > maxBytes){
        return nullptr;
    }

    bytes_allocated += num_bytes_to_allocate;

    region = mmap(NULL, pgsz, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);

    return region + bytes_allocated;

}