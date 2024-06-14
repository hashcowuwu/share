CFLAGS=-Wall -g -O2

TEST_TARGETS=main

all:$(TEST_TARGETS)


claen:
	rm -rf $(TEST_TARGETS)


check: $(TEST_TARGETS)
	for target in $^; do \
		./$$target; \
	done

test:
	timeout 5s  ./$(TEST_TARGETS)
