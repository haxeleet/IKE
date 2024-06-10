SRCDIR = src
HDRDIR = include
OBJDIR = .build

PROGRAM = $(OBJDIR)/IKE

SRCS = $(wildcard $(SRCDIR)/*.c)
HDRS = $(wildcard $(SRCDIR)/*.h)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: clean compile run

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
