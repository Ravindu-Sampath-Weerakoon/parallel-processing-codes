#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if the user provided a filename
    if (argc < 2) {
        printf("Usage: %s <filename.c>\n", argv[0]);
        return 1;
    }

    char *source_file = argv[1];
    char output_file[256];

    // Find the '.c' extension to extract the base name for the output file
    char *dot = strrchr(source_file, '.');
    if (dot && strcmp(dot, ".c") == 0) {
        // Copy the name up to the '.' and add '.out'
        size_t len = dot - source_file;
        strncpy(output_file, source_file, len);
        output_file[len] = '\0';
        strcat(output_file, ".out");
    } else {
        // If they didn't provide a .c extension, just append .out to whatever they typed
        snprintf(output_file, sizeof(output_file), "%s.out", source_file);
    }

    // 1. Construct the compilation command
    char compile_cmd[512];
    snprintf(compile_cmd, sizeof(compile_cmd), "gcc %s -fopenmp -o %s", source_file, output_file);

    printf("[AUTOMATION] Compiling: %s\n", compile_cmd);
    
    // Run the compilation command
    int compile_status = system(compile_cmd);

    // If compilation fails, stop right here
    if (compile_status != 0) {
        printf("[AUTOMATION] Compilation failed!\n");
        return compile_status;
    }

    // 2. Construct the execution command
    char run_cmd[512];
    snprintf(run_cmd, sizeof(run_cmd), "./%s", output_file);

    printf("[AUTOMATION] Running: %s\n", run_cmd);
    printf("-----------------------------------------\n");

    // Run the executable
    int run_status = system(run_cmd);
    
    return run_status;
}