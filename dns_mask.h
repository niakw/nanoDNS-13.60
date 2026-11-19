/* nanoDNS wildcard matcher (GPL-3.0; original project: drakmor/nanoDNS).
 * Iterative backtracking avoids recursive stack growth on hostile masks.
 * Supports *, ?, bracket sets/ranges/negation and backslash escapes.
 */
#ifndef NANODNS_DNS_MASK_H
#define NANODNS_DNS_MASK_H

#include <stdbool.h>

/* Match one non-* token. On an unterminated bracket treat '[' literally. */
static bool
dns_mask_match_token(const char *pattern, unsigned char ch,
                     const char **next) {
  if(*pattern == '?') {
    *next = pattern + 1;
    return true;
  }

  if(*pattern == '[') {
    bool negate = false;
    bool matched = false;
    const char *p = pattern + 1;
    if(*p == '!' || *p == '^') {
      negate = true;
      ++p;
    }
    if(*p == ']') {
      matched = ch == ']';
      ++p;
    }
    while(*p != '\0' && *p != ']') {
      unsigned char start, end;
      if(*p == '\\' && p[1] != '\0') {
        start = (unsigned char)p[1];
        p += 2;
      } else {
        start = (unsigned char)*p++;
      }
      end = start;
      if(*p == '-' && p[1] != '\0' && p[1] != ']') {
        ++p;
        if(*p == '\\' && p[1] != '\0') {
          end = (unsigned char)p[1];
          p += 2;
        } else {
          end = (unsigned char)*p++;
        }
      }
      if(ch >= start && ch <= end) matched = true;
    }
    if(*p == ']') {
      *next = p + 1;
      return negate ? !matched : matched;
    }
    /* Unclosed bracket: treat it as the literal '['. */
  }

  if(*pattern == '\\' && pattern[1] != '\0') {
    ++pattern;
  }
  *next = pattern + 1;
  return (unsigned char)*pattern == ch;
}

/* Case normalization is applied to DNS names and masks at parse time. */
static int
domain_mask_match(const char *mask, const char *domain) {
  const char *pattern = mask;
  const char *current = domain;
  const char *last_star = NULL;
  const char *star_input = NULL;

  while(*current != '\0') {
    if(*pattern == '*') {
      do {
        ++pattern;
      } while(*pattern == '*');
      last_star = pattern;
      star_input = current;
      continue;
    }

    if(*pattern != '\0') {
      const char *next;
      if(dns_mask_match_token(pattern, (unsigned char)*current, &next)) {
        pattern = next;
        ++current;
        continue;
      }
    }

    if(last_star != NULL) {
      pattern = last_star;
      current = ++star_input;
      continue;
    }
    return 0;
  }

  while(*pattern == '*') ++pattern;
  return *pattern == '\0';
}

#endif /* NANODNS_DNS_MASK_H */
