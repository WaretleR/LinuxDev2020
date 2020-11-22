/** @file 
 * Number guessing program. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

/**
 * For localization
 */
#define _(STRING) gettext(STRING)

#define HELP _("Number guessing program.\n\n\
Usage: guess [OPTION]\n\
Numbers can be typed in roman digits by passing -r option.\n\
Program supports english and russian languages.\n\
Variants of answer: yes, no.\n\
--help prints this help\n")

 /**
  *  Strings than contain roman numbers in range 1..100 
  */
const char *roman_letters[100] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
    "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
    "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
    "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
    "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
    "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
    "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
    "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
    "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
    "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

/**
 * Convert roman number to arabic number in range 1..100.
 * @param roman char *roman contains string - source roman number.
 * @returns Returns arabic number if roman number was in range 1..100 or 0 otherwise.
 */
int get_arabic(char *roman) {
    for (int i = 0; i < 100; ++i) {
        if (strcmp(roman_letters[i], roman) == 0) {
            return i + 1;
        }
    }
    return 0;
}

/**
 * Convert arabic number to roman number in range 1..100.
 * @param arabic int arabic contains source number.
 * @returns Returns pointer to roman number in @p roman_letters if arabic number was in range 1..100 or "0" otherwise.
 */
const char *get_roman(int arabic) {
    if (arabic > 0 && arabic <= 100) {
        return roman_letters[arabic - 1];
    }
    return "0";
}

int main(int argc, char **argv) {
    char is_roman = 0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-r") == 0) {
            is_roman = 1;
        }
        if (strcmp(argv[i], "--help") == 0) {
            return !printf("%s",  HELP);
        }
    }

    setlocale(LC_ALL, "");
    bindtextdomain("guess", ".");
    textdomain("guess");

    int chosen;
    int left = 1, right = 100, middle;
    char *answer;
    char *tmp;
    printf(_("Choose a number in range [%d, %d]: "), left, right);
    if (scanf("%ms", &tmp) != 1) {
        printf(_("Wrong number!\n"));
        return 1;
    }
    if (is_roman) {
        chosen = get_arabic(tmp);
    }
    else {
        chosen = atoi(tmp);
    }
    free(tmp);
    if (chosen > right || chosen < left) {
        printf(_("Wrong number!\n"));
        return 1;
    }
    while (right > left) {
        middle = (right - left) / 2 + left;
        if (is_roman) {
            printf(_("Is your number greater than %s?\n"), get_roman(middle));
        }
        else {
            printf(_("Is your number greater than %d?\n"), middle);
        }
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
    if (is_roman) {
        printf(_("Your chosen number = %s!\n"), get_roman(left));
    }
    else {
        printf(_("Your chosen number = %d!\n"), left);
    }   
    return 0;
}