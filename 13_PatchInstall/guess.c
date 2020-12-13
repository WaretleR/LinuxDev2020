#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALEDIR);
    textdomain("guess");

    int chosen;
    int left = 1, right = 100, middle;
    char *answer;
    printf(_("Choose a nummber in range [%d, %d]: "), left, right);
    if (scanf("%d", &chosen) != 1 || chosen > right || chosen < left) {
        printf(_("Wrong number!\n"));
        return 1;
    }
    while (right > left) {
        middle = (right - left) / 2 + left;
        printf(_("Is your number greater than %d?\n"), middle);
        int res = scanf("%ms", &answer);
        if (res != 1) {
            printf(_("Wrong answer! Try again.\n"));
            free(answer);
            continue;
        }
        if (strcmp(answer, _("yes")) == 0) {
            left = middle + 1;
        }
        else if (strcmp(answer, _("no")) == 0) {
            right = middle;
        }
        else {
            printf(_("Wrong answer! Try again.\n"));
            free(answer);
            continue;
        }
        free(answer);
    }
    printf(_("Your chosen number = %d!\n"), left);
    return 0;
}