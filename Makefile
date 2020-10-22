release:
	gcc main.c funcs_pub.c funcs_prv.c -o stack.out
debug:
	gcc main.c stack.c assertion.c -o stack_d.out