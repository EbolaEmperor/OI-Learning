#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puzzles.h"
#include "loopy.c"

static void emit_square_grid(const game_params *params, const game_state *state) {
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
}

int main(int argc, char **argv) {
    if (argc < 6) {
        fprintf(stderr, "usage: %s <w> <h> <keep_percent> <count> <seed> [nozero]\n", argv[0]);
        return 2;
    }

    game_params params;
    params.w = atoi(argv[1]);
    params.h = atoi(argv[2]);
    params.type = LOOPY_GRID_SQUARE;
    params.diff = DIFF_HARD;
    int keep_percent = atoi(argv[3]);
    int count = atoi(argv[4]);
    bool nozero = argc >= 7 && !strcmp(argv[6], "nozero");

    const char *err = validate_params(&params, true);
    if (err) {
        fprintf(stderr, "%s\n", err);
        return 2;
    }

    random_state *rs = random_new(argv[5], strlen(argv[5]));

    for (int t = 0; t < count; ++t) {
        char *grid_desc = grid_new_desc(grid_types[params.type], params.w, params.h, rs);
        game_state *state = snew(game_state);
        state->game_grid = loopy_generate_grid(&params, grid_desc);
        state->clues = snewn(state->game_grid->num_faces, signed char);
        state->lines = snewn(state->game_grid->num_edges, char);
        state->line_errors = snewn(state->game_grid->num_edges, bool);
        state->exactly_one_loop = false;
        state->grid_type = params.type;
        state->solved = false;
        state->cheated = false;
        memset(state->lines, LINE_UNKNOWN, state->game_grid->num_edges);
        memset(state->line_errors, 0, state->game_grid->num_edges * sizeof(bool));

        add_full_clues(state, rs);
        for (int i = 0; i < state->game_grid->num_faces; ++i) {
            if (nozero && state->clues[i] == 0) {
                state->clues[i] = -1;
            } else if ((int)random_upto(rs, 100) >= keep_percent) {
                state->clues[i] = -1;
            }
        }

        printf("ID keep:%dx%d:%d:%d%s\n", params.w, params.h, keep_percent,
               t + 1, nozero ? ":nozero" : "");
        emit_square_grid(&params, state);
        puts("END");
        fflush(stdout);

        free_game(state);
        if (grid_desc) sfree(grid_desc);
    }

    random_free(rs);
    return 0;
}
