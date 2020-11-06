CC = cc
TO_DELETE = file_test.txt
NOT_TO_DELETE = file_FIX_test.txt

all: unlinkat_wrapper.so

unlinkat_wrapper.so: unlinkat_wrapper.c
	$(CC) -shared -fPIC $^ -ldl -o $@

test: unlinkat_wrapper.so
	echo "This file should be deleted" > $(TO_DELETE)
	echo "This file should NOT be deleted" > $(NOT_TO_DELETE)
	-rm $(TO_DELETE)
	-rm $(NOT_TO_DELETE)
	if test -f $(TO_DELETE) || test -f $(NOT_TO_DELETE); then \
		echo ERROR! rm did not delete one or more files!; \
	else \
		echo rm passed the test.; \
	fi

	echo "This file should be deleted" > $(TO_DELETE)
	echo "This file should NOT be deleted" > $(NOT_TO_DELETE)
	-LD_PRELOAD=$^ rm $(TO_DELETE)
	-LD_PRELOAD=$^ rm $(NOT_TO_DELETE)
	if test -f $(TO_DELETE); then \
		echo ERROR! File is not deleted!; \
	else \
	if test -f $(NOT_TO_DELETE); then \
		echo wrapper passed the test.; \
	else \
		echo ERROR! FIX file is deleted!; \
	fi \
	fi

clean:
	-rm *.txt

distclean: clean
	-rm *.so