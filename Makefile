build:
	clang loader.c -o loader

test:
	make build
	clang aslr_test.c -o aslr_test
	./loader ./aslr_test