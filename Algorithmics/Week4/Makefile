CC     = g++
CFLAGS = -std=c++14 -Wall -Wextra -ggdb

SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
BINS = qsort-3waysplit

all: $(BINS)

qsort-3waysplit: sorting-jmesser.o
	@$(CC) $^ -o $@
	@echo "$(CC) $^ -o $@"

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $^
	@echo "$(CC) $(CFLAGS) -c $^"

.PHONY: clean
clean:
	@$(RM) -f $(OBJS) 
	@$(RM) -f $(BINS)
