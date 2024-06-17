SRCDIR = src
HDRDIR = include
OBJDIR = .build

PROGRAM = $(OBJDIR)/IKE

SRCS = $(wildcard $(SRCDIR)/*.c)
HDRS = $(wildcard $(SRCDIR)/*.h)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

ifeq ($(shell id -u), 0)
all: clean run
else
all: clean compile run
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc -c $< -I$(HDRDIR) -o $@

$(PROGRAM): $(OBJS)
	gcc $^ -o $@

run: $(PROGRAM)
	$(PROGRAM)

compile:
	compiledb -n make $(PROGRAM)

clean:
	rm -rf $(OBJDIR)/*
