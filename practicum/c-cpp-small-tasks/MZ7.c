#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }

    int num_symbols = 0, num_words = 0, num_lines = 0;
    int fpr = 1, empty = 1, cc;
    char current_char, previous_char;
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) return 1;
    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) return 1;


    while ((cc = fgetc(input_file)) != EOF) {
        current_char = (char)cc;
        empty = 0;
        num_symbols++;
        if ((current_char == ' ') && (!fpr)) {
            fpr = 1;
            num_words++;
        }
        if (current_char == '\n') {
            if (!fpr) {
                num_words++;
            }
            fpr = 1;
            num_lines++;
        }
        if ((current_char != ' ') && (current_char != '\n')) {
            fpr = 0;
        }
        previous_char = current_char;
    }
    if (previous_char != ' ' && previous_char != '\n' && !empty) {
        num_words++;
    }

    fprintf(output_file, "%d %d %d", num_lines, num_words, num_symbols);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
