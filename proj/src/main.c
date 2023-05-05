#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>  

int main(int argc, char *argv[]){
    lcf_set_language("EN-US");

    lcf_trace_calls("home/lcom/labs/g4/proj/src/output/trace.txt");

    lcf_log_output("/home/lcom/labs/g4/proj/src/output/output.txt");

    if (lcf_start(argc, argv)) return 1;

    lcf_cleanup();

    return 0;
}