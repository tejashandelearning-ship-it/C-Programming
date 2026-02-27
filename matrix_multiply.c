#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

/* Read a matrix and auto-detect dimensions */
int read_matrix(FILE *fp, double matrix[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
    int i = 0;
    int first_row_cols = -1;
    char line[4096];
    int reading = 0;  /* Track if we've started reading matrix data */

    /* Read lines until we find a valid matrix (skip comments and blanks) */
    while (fgets(line, sizeof(line), fp) != NULL) {
        /* Skip comment lines */
        if (line[0] == '#') continue;
        
        /* If we're already reading and hit blank line, we're done with this matrix */
        if (reading && (line[0] == '\n' || line[0] == '\r')) {
            break;
        }

        /* Skip blank lines before matrix starts */
        if (line[0] == '\n' || line[0] == '\r') continue;

        int j = 0;
        double val;
        char *ptr = line;

        /* Parse all numbers in this line */
        while (sscanf(ptr, "%lf", &val) == 1) {
            if (i >= MAX_ROWS || j >= MAX_COLS) {
                printf("Error: Matrix exceeds maximum size (%dx%d).\n", MAX_ROWS, MAX_COLS);
                return 0;
            }
            matrix[i][j] = val;
            j++;
            reading = 1;

            /* Skip past this number to find next one */
            while (*ptr && !isspace(*ptr)) ptr++;
            while (*ptr && isspace(*ptr) && *ptr != '\n') ptr++;
        }

        /* If we parsed values, validate column count */
        if (j > 0) {
            if (first_row_cols == -1) {
                first_row_cols = j;
            } else if (j != first_row_cols) {
                printf("Error: Row %d has %d values, expected %d.\n", i + 1, j, first_row_cols);
                return 0;
            }
            i++;
        }
    }

    *rows = i;
    *cols = first_row_cols;

    if (i == 0 || first_row_cols <= 0) {
        printf("Error: No valid matrix data found.\n");
        return 0;
    }

    return 1;
}

int main(void) {
    FILE *fp;
    int rows1, cols1, rows2, cols2;
    double matrix1[MAX_ROWS][MAX_COLS], matrix2[MAX_ROWS][MAX_COLS];
    double result[MAX_ROWS][MAX_COLS];
    int i, j, k;

    printf("Reading matrices from matrices.txt...\n");
    fp = fopen("matrices.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open matrices.txt.\n");
        return 1;
    }

    if (!read_matrix(fp, matrix1, &rows1, &cols1)) {
        fclose(fp);
        return 1;
    }
    printf("✓ Matrix 1 (%dx%d) read successfully.\n", rows1, cols1);

    /* Read second matrix */
    if (!read_matrix(fp, matrix2, &rows2, &cols2)) {
        fclose(fp);
        return 1;
    }
    printf("✓ Matrix 2 (%dx%d) read successfully.\n", rows2, cols2);
    fclose(fp);

    /* Check if multiplication is possible */
    if (cols1 != rows2) {
        printf("\nError: Cannot multiply!\n");
        printf("  Matrix 1 columns (%d) must equal Matrix 2 rows (%d).\n", cols1, rows2);
        printf("  Matrix 1: %dx%d | Matrix 2: %dx%d\n", rows1, cols1, rows2, cols2);
        return 1;
    }

    /* Perform matrix multiplication */
    printf("\nMultiplying matrices...\n");
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols2; j++) {
            result[i][j] = 0.0;
            for (k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    printf("✓ Result matrix (%dx%d) computed.\n", rows1, cols2);

    /* Write result back to file */
    fp = fopen("matrices.txt", "w");
    if (fp == NULL) {
        printf("Error: Could not open matrices.txt for writing.\n");
        return 1;
    }

    fprintf(fp, "# Matrix 1 (original %dx%d)\n", rows1, cols1);
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols1; j++) {
            fprintf(fp, "%lf ", matrix1[i][j]);
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "\n# Matrix 2 (original %dx%d)\n", rows2, cols2);
    for (i = 0; i < rows2; i++) {
        for (j = 0; j < cols2; j++) {
            fprintf(fp, "%lf ", matrix2[i][j]);
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "\n# Product Matrix (result %dx%d)\n", rows1, cols2);
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols2; j++) {
            fprintf(fp, "%lf ", result[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("\n✓ Result written to matrices.txt.\n");

    return 0;
}
