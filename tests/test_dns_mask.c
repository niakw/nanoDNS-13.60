#include "../dns_mask.h"
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXPECTED_RULES 124

static const struct {
  const char *mask;
  const char *domain;
  int expected;
} cases[] = {
  {"*sony*", "ps5.sony.com", 1},
  {"*sony*", "github.com", 0},
  {"*nintendo*", "nintendo.net", 1},
  {"*.playstation.net", "ps5.np.playstation.net", 1},
  {"*.playstation.net", "playstation.net", 0},
  {"foo??.com", "foo12.com", 1},
  {"foo??.com", "foo1.com", 0},
  {"foo[ab].com", "foob.com", 1},
  {"foo[ab].com", "fooc.com", 0},
  {"foo[a-c].com", "foob.com", 1},
  {"foo[!0-9].com", "foox.com", 1},
  {"foo[!0-9].com", "foo8.com", 0},
  {"api\\?.test", "api?.test", 1},
  {"api\\?.test", "apia.test", 0},
  {"abc[", "abc[", 1},
  {"***a***b***", "XaZbY", 1},
  {"*a*a*a*a*a*Z", "aaaaaaaaaaaaaaaaaaaaaaa", 0},
  {"*a*a*a*a*a*Z", "aaaaaaaaaaaaaaaaaaaaaaZ", 1},
};

static int
load_masks(char masks[EXPECTED_RULES][256]) {
  FILE *fp = fopen("nanodns.ini", "r");
  char line[1024];
  int count = 0;
  int section_overrides = 0;
  if(!fp) return -1;
  while(fgets(line, sizeof(line), fp)) {
    char *start = line;
    char *equal, *end;
    while(*start == ' ' || *start == '\t') ++start;
    if(*start == '#' || *start == ';' || *start == '\n' || *start == '\0')
      continue;
    if(*start == '[') {
      section_overrides = strncmp(start, "[overrides]", 11) == 0;
      continue;
    }
    if(!section_overrides) continue;
    equal = strchr(start, '=');
    if(!equal || count >= EXPECTED_RULES) {
      fclose(fp);
      return -1;
    }
    end = equal;
    while(end > start && (end[-1] == ' ' || end[-1] == '\t')) --end;
    if((size_t)(end - start) >= sizeof(masks[0])) {
      fclose(fp);
      return -1;
    }
    memcpy(masks[count], start, (size_t)(end - start));
    masks[count][end - start] = '\0';
    ++count;
  }
  fclose(fp);
  return count;
}

static int
compare_match(const char *mask, const char *domain) {
  int expected = fnmatch(mask, domain, 0) == 0;
  int actual = domain_mask_match(mask, domain);
  if(expected != actual) {
    fprintf(stderr, "Mismatch: mask=%s domain=%s fnmatch=%d native=%d\n",
            mask, domain, expected, actual);
    return -1;
  }
  return 0;
}

int main(void) {
  static char masks[EXPECTED_RULES][256];
  const char alphabet[] = "abcdefghijklmnopqrstuvwxyz0123456789.-";
  unsigned int seed = 0x1360u;
  int count = load_masks(masks);
  if(count != EXPECTED_RULES) {
    fprintf(stderr, "Expected 124 policy rules, read %d\n", count);
    return 1;
  }
  for(size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
    if(domain_mask_match(cases[i].mask, cases[i].domain) != cases[i].expected) {
      fprintf(stderr, "Failed specific mask case %zu (%s, %s)\n",
              i, cases[i].mask, cases[i].domain);
      return 1;
    }
  }
  for(int i = 0; i < EXPECTED_RULES; ++i) {
    /* A positive witness for every wildcard in the shipped denylist. */
    char positive[512] = {0};
    size_t out = 0;
    for(const char *p = masks[i]; *p; ++p) {
      const char *replacement = *p == '*' ? "test" : NULL;
      if(replacement) {
        size_t n = strlen(replacement);
        memcpy(positive + out, replacement, n);
        out += n;
      } else {
        positive[out++] = *p;
      }
    }
    positive[out] = '\0';
    if(!domain_mask_match(masks[i], positive) ||
       compare_match(masks[i], positive)) {
      fprintf(stderr, "Positive witness failed for rule %s\n", masks[i]);
      return 1;
    }
  }
  for(int trial = 0; trial < 500; ++trial) {
    char domain[64];
    size_t len;
    seed = seed * 1664525u + 1013904223u;
    len = 1 + (seed % 48u);
    for(size_t j = 0; j < len; ++j) {
      seed = seed * 1664525u + 1013904223u;
      domain[j] = alphabet[seed % (sizeof(alphabet) - 1)];
    }
    domain[len] = '\0';
    for(int i = 0; i < EXPECTED_RULES; ++i) {
      if(compare_match(masks[i], domain)) return 1;
    }
  }
  puts("native DNS matcher OK: 124 rules, positive witnesses, 62,000 differential cases");
  return 0;
}
