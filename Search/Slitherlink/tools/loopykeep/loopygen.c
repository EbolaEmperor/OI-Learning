#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puzzles.h"
#include "loopy.c"

static void emit_square_grid(const game_params *params, const char *desc) {
    game_state *state = new_game(NULL, params, desc);
    grid *g = state->game_grid;
    grid_face *f = g->faces[0];
    int cell_size = abs(f->dots[0]->x - f->dots[2]->x);
    char *cells = snewn(params->w * params->h, char);

    for (int i = 0; i < params->w * params->h; ++i)
        cells[i] = '.';

    for (int i = 0; i < g->num_faces; ++i) {
        int x1, x2, y1, y2, x, y, col, row;
        f = g->faces[i];
        x1 = (f->dots[0]->x - g->lowest_x) / cell_size;
        x2 = (f->dots[2]->x - g->lowest_x) / cell_size;
        y1 = (f->dots[0]->y - g->lowest_y) / cell_size;
        y2 = (f->dots[2]->y - g->lowest_y) / cell_size;
        x = x1 + x2;
        y = y1 + y2;
        col = (x - 1) / 2;
        row = (y - 1) / 2;
        if (row >= 0 && row < params->h && col >= 0 && col < params->w)
            cells[row * params->w + col] =
                state->clues[i] < 0 ? '.' : CLUE2CHAR(state->clues[i]);
    }

    for (int r = 0; r < params->h; ++r) {
        fwrite(cells + r * params->w, 1, params->w, stdout);
        putchar('\n');
    }

    sfree(cells);
    free_game(state);
}

int main(int argc, char **argv) {
    if (argc < 6) {
        fprintf(stderr, "usage: %s <w> <h> <e|n|t|h> <count> <seed>\n", argv[0]);
        return 2;
    }

    game_params params;
    params.w = atoi(argv[1]);
    params.h = atoi(argv[2]);
    params.type = LOOPY_GRID_SQUARE;
    params.diff = DIFF_HARD;
    for (int i = 0; i < DIFF_MAX; ++i) {
        if (argv[3][0] == diffchars[i]) {
            params.diff = i;
            break;
        }
    }

    const char *err = validate_params(&params, true);
    if (err) {
        fprintf(stderr, "%s\n", err);
        return 2;
    }

    int count = atoi(argv[4]);
    random_state *rs = random_new(argv[5], strlen(argv[5]));
    char *params_text = encode_params(&params, true);

    for (int t = 0; t < count; ++t) {
        char *aux = NULL;
        char *desc = new_game_desc(&params, rs, &aux, false);
        printf("ID %s:%s\n", params_text, desc);
        emit_square_grid(&params, desc);
        puts("END");
        if (aux) sfree(aux);
        sfree(desc);
        fflush(stdout);
    }

    sfree(params_text);
    random_free(rs);
    return 0;
}
