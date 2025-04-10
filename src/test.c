#include <stdio.h>
#include <stdlib.h>

#include "lib/mdb.h"

void test_setkeys(void)
{
  tablist_t *list = readdb("dbs/test.db");
  if (setkeys(&list, -1, "name:john"))
    fprintf(stderr, "test_setkeys: failed\n");
  for (int i = 0; i < list[0].len; ++i) {
    printf("id: %d\n", i);
    int *indexes = getkeys(list, i);
    for (int j = 0; indexes[j]; ++j)
      printf("%s\n", list[i].tab[indexes[j]].key);
    free(indexes);
  }
  delkeys(list, -1, NULL);
  free(list);
}

void test_setkeys_fail(void)
{
  tablist_t *list = readdb("dbs/test.db");
  if (!setkeys(&list, -1, "namejohn"))
    fprintf(stderr, "test_setkeys_fail: failed\n");
  delkeys(list, -1, NULL);
  free(list);
}

void test_setkeys_single(void)
{
  tablist_t *list = readdb("dbs/test.db");
  if (setkeys(&list, 101, "name:alice"))
    fprintf(stderr, "test_setkeys_single: failed\n");
  delkeys(list, -1, NULL);
  free(list);
}

void test_delkeys(void)
{
  tablist_t *list = readdb("dbs/test.db");
  if (delkeys(list, -1, "Row_1"))
    fprintf(stderr, "test_delkeys: failed\n");
  for (int i = 0; i < list[0].len; ++i) {
    printf("id: %d\n", i);
    int *indexes = getkeys(list, i);
    for (int j = 0; indexes[j]; ++j)
      printf("%s\n", list[i].tab[indexes[j]].key);
    free(indexes);
  }
  delkeys(list, -1, NULL);
  free(list);
}

void test_delkeys_all(void)
{
  tablist_t *list = readdb("dbs/test.db");
  if (delkeys(list, -1, NULL))
    fprintf(stderr, "test_delkeys_all: failed\n");
  free(list);
}

void test_delkeys_fail(void)
{
  tablist_t *list = readdb("dbs/test.db");
  if (!delkeys(list, -1, "Row_4"))
    fprintf(stderr, "test_delkeys_fail: failed\n");
  delkeys(list, -1, NULL);
  free(list);
}

void test_delkeys_single(void)
{
  tablist_t *list = readdb("dbs/test.db");
  if (delkeys(list, 0, NULL))
    fprintf(stderr, "test_delkeys_single: failed\n");
  delkeys(list, -1, NULL);
  free(list);
}

int main(void)
{
  test_setkeys();
  test_setkeys_fail();
  test_setkeys_single();

  test_delkeys();
  test_delkeys_all();
  test_delkeys_fail();
  test_delkeys_single();

  exit(0);
}
