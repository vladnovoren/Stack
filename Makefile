release:
	gcc main.c funcs_pub.c funcs_prv.c -o stack.out
debug:
	gcc main.c funcs_pub.c funcs_prv.c assertion.c -o stack_d.out -DDEBUG