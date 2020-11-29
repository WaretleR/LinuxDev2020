#include <stdio.h>
#include <glib.h>

#define MAX_STRLEN 81

gint compare_count(gconstpointer first, gconstpointer second, gpointer hash) {
    gint first_value = GPOINTER_TO_INT(g_hash_table_lookup(hash, (gchar *)first));
    gint second_value = GPOINTER_TO_INT(g_hash_table_lookup(hash, (gchar *)second));
    return first_value < second_value;
}

void convert_to_list(gpointer key, gpointer value, gpointer ptr) {
    GSList **list = ptr;
    *list = g_slist_prepend(*list, key);
}

int main(int argc, char *argv[]) {
    GHashTable *hash = g_hash_table_new_full(g_str_hash, g_str_equal, (GDestroyNotify)g_free, NULL);
    gchar str[MAX_STRLEN];
    while (fgets(str, MAX_STRLEN, stdin)) {
        gchar **words = g_strsplit_set(str, " \n,.!?\t:;()", 0);
        for (gint i = 0; words[i]; ++i) {
            if (!g_strcmp0(words[i], "")) {
                continue;
            }
            gpointer count = g_hash_table_lookup(hash, words[i]);
            if (count) {
                g_hash_table_insert(hash, g_strdup(words[i]), count + 1);
            }
            else {
                g_hash_table_insert(hash, g_strdup(words[i]), GINT_TO_POINTER(1));
            }
        }
        g_strfreev(words);
    }

    GSList *keyval_list = NULL;
    g_hash_table_foreach(hash, (GHFunc)convert_to_list, &keyval_list);
    keyval_list = g_slist_sort_with_data(keyval_list, (GCompareDataFunc) compare_count, hash);
    for (GSList *iterator = keyval_list; iterator; iterator = iterator->next) {
        printf("%s : %d\n", (gchar *)iterator->data, GPOINTER_TO_INT(g_hash_table_lookup(hash, iterator->data)));
    }
    g_slist_free(keyval_list);
    g_hash_table_destroy(hash);

    return 0;
}