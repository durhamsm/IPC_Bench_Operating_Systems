program_NAME := ipc_bench
program_SRCS := $(wildcard *.c)
program_OBJS := ${program_SRCS:.c=.o}

CPPFLAGS+= 

.PHONY: all clean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)
	@- $(RM) *~
