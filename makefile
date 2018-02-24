SRCDIR := "./src"
OBJDIR := "./obj"

SRCS := $(shell find $(SRCDIR) -name "*.c")
OBJ_FILES := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LD_FLAGS := -lSDL2 -lSDL2_mixer -lm
CC_FLAGS := -Wall -O3

#AQFFOS.exe: $(OBJ_FILES)
#	 i686-w64-mingw32-gcc $(CC_FLAGS) -o $@ $^ res.o $(LD_FLAGS)

AQFFOS: $(OBJ_FILES)
	 gcc $(CC_FLAGS) -o $@ $^ $(LD_FLAGS)
