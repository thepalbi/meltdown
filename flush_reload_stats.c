#include "libkdump.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *strings[] = {
    "If you can read this, at least the auto configuration is working",
    "Generating witty test message...",
    "Go ahead with the real exploit if you dare",
    "Have a good day.",
    "Welcome to the wonderful world of microarchitectural attacks",
    "Pay no attention to the content of this string",
    "Please wait while we steal your secrets...",
    "Would you like fries with that?",
    "(insert random quote here)",
    "Don't panic...",
    "Wait, do you smell something burning?",
    "How did you get here?"};

#define PAGE_SIZE 4096
#define SAMPLES 10

char string[] = "uggis";

int main(int argc, char *argv[]) {

  // Extract index to cache
  if (argc == 2) {
    int index_to_cache = atoi(argv[1]);
    if (index_to_cache > 255) {
      printf("%s [%s]", argv[0], "NOT REQUIRED: Index to cache in 0 <= index <= 255\n");
      exit(1);
    }
    char char_to_write = (char)(index_to_cache);
    *string = char_to_write;
  }

  char *_probe = NULL, *probe = NULL;
  _probe = malloc(PAGE_SIZE * 300);
  if (!_probe) {
    // Probe array could not be allocated
    exit(1);
  }
  // 0x1000 == 4096
  // This mask the lower 3 bits, and then adds 2 * PAGE_SIZE
  probe = (char *)(((size_t)_probe & ~0xfff) + 0x1000 * 2);

  // address to the first character of the string
  char *value_to_cache = string;


  #ifdef DEBUG
    printf("Writing to %d index\n", *value_to_cache);
  #endif

  for (size_t i = 0; i < SAMPLES; i++) {
    flush_reload_debug_pass(probe, value_to_cache);
  }
}
