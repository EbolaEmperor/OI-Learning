CC ?= cc
CFLAGS ?= -O3

VENDOR := vendor
BUILD := build

COMMON_SRCS := \
	$(VENDOR)/nullfe.c \
	$(VENDOR)/combi.c \
	$(VENDOR)/divvy.c \
	$(VENDOR)/draw-poly.c \
	$(VENDOR)/dsf.c \
	$(VENDOR)/findloop.c \
	$(VENDOR)/grid.c \
	$(VENDOR)/latin.c \
	$(VENDOR)/laydomino.c \
	$(VENDOR)/loopgen.c \
	$(VENDOR)/malloc.c \
	$(VENDOR)/matching.c \
	$(VENDOR)/midend.c \
	$(VENDOR)/misc.c \
	$(VENDOR)/penrose.c \
	$(VENDOR)/penrose-legacy.c \
	$(VENDOR)/random.c \
	$(VENDOR)/sort.c \
	$(VENDOR)/tdq.c \
	$(VENDOR)/tree234.c \
	$(VENDOR)/version.c \
	$(VENDOR)/hat.c \
	$(VENDOR)/spectre.c

.PHONY: all clean

all: $(BUILD)/loopykeep $(BUILD)/loopygen $(BUILD)/loopysolver

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/loopykeep: loopykeep.c $(COMMON_SRCS) $(VENDOR)/loopy.c | $(BUILD)
	$(CC) $(CFLAGS) -I$(VENDOR) loopykeep.c $(COMMON_SRCS) -lm -o $@

$(BUILD)/loopygen: loopygen.c $(COMMON_SRCS) $(VENDOR)/loopy.c | $(BUILD)
	$(CC) $(CFLAGS) -I$(VENDOR) loopygen.c $(COMMON_SRCS) -lm -o $@

$(BUILD)/loopysolver: $(VENDOR)/loopy.c $(COMMON_SRCS) | $(BUILD)
	$(CC) $(CFLAGS) -DSTANDALONE_SOLVER -I$(VENDOR) $(VENDOR)/loopy.c $(COMMON_SRCS) -lm -o $@

clean:
	rm -rf $(BUILD)
