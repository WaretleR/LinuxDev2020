SRC = src/buf.c
TESTS = tests/tests.ts
COVERAGE_ARGS = -fprofile-arcs -ftest-coverage -O0 -g
PARAMS = `pkg-config --libs check`

all: coverage

libbuf_test.so: $(SRC)
	$(CC) -shared -fPIC $< -o $@

libbuf_coverage.so: $(SRC)
	$(CC) -shared -fPIC $(COVERAGE_ARGS) $< -o $@

tests.c: $(TESTS)
	checkmk $< > $@

tests.o: tests.c
	$(CC) -lcheck $^ -c -o $@ -I src

test: tests.o libbuf_test.so
	$(CC) $< -o $@ -lcheck -L. -lbuf_test $(PARAMS)
	./$@

coverage: tests.o libbuf_coverage.so
	$(CC) $< -o $@ -L. -lbuf_coverage $(PARAMS) $(COVERAGE_ARGS)
	./$@
	gcov buf.gcda
	cat buf.c.gcov

clean:
	-rm *.so tests.* *.gcda *.gcno test coverage

distclean: clean
	-rm *.gcov