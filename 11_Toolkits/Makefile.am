bin_PROGRAMS = wordcount
CFLAGS += $(GLIB_CFLAGS) -Wall
LIBS += $(GLIB_LIBS)
GENERATES = *.o
TEST_FILE = test.txt

test: $(TEST_FILE) $(bin_PROGRAMS)
	./$(bin_PROGRAMS) < $(TEST_FILE)

clean:
	-rm $(GENERATES)
