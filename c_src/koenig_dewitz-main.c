#include <stdio.h>
#include <stdlib.h>
//#include <inttypes.h>


/* fw-decl */
int pop();

/* Print debug-messages with -D DEBUG (or make DEBUG=1 when using the Makefile) */
#ifdef DEBUG
#define dprint(S, ...) printf(" (I) "S, __VA_ARGS__)
#define delim "====="
#else
#define dprint(S, ...)
#endif



/* benoetigte Struktur zum Erzeugen der Stack-Eintraege */
typedef struct item {
	int elem;
	struct item *next;
} item;

int myerrno;

/* Zeiger auf oberstes Element */
item *head = NULL;

/* Freigabe eines Elements */
void trash(item *garbage)
{
	myerrno = 0;
	dprint("garbage has address %p\n", (void *)garbage);

	if (garbage == head) {
		pop();
		return;
	}
	item *temp = head;
	while (temp != NULL && temp->next != NULL) {
		dprint("current temp has address: %p\n", (void *)temp);
		// alternative version with inttypes:
		//dprint("current temp is: %" PRIxPTR "\n", (long unsigned int)temp);

		if (temp->next == garbage) {
			item *temp2;
			temp2 = temp->next;
			temp->next = temp->next->next;
			free(temp2);
			return;
		}
		temp = temp->next;
	}
	fprintf(stderr, " (E) Error, element to trash not in list!%c", '\n');
	myerrno = 1;
}

/* Ein neues Element anlegen */
item *new_item(int value)
{
	item *temp;
	temp = (item *)malloc(sizeof(item));
	temp->elem = value;
	temp->next = NULL;
	return temp;
}

/* is_empty testet , ob die Liste leer ist
   und liefert entsprechend 1 fuer leer, 0 fuer nicht leer */
int is_empty()
{
	return (head == NULL);
}

/* das neue Element wird auf den Stack abgelegt */
void push(item *elem)
{
	dprint("pushing elem %p\n", (void *)elem);
	elem->next = head;
	head = elem;
}

/* entfernt das oberste Element vom Stack und gibt es zurück */
/* edited to return int */
int pop()
{
	/*  trash(head); */
	if (head == NULL) {
		fprintf(stderr, " (E) Head is NULL%c", '\n');
		myerrno = 1;
		return 0;
	}
	item *temp = head;
	head = head->next;
	int temp2 = temp->elem;
	free(temp);
	return temp2;
}

/* Teil b :
    nimmt zwei Operanden vom Stack, multipliziert diese und
    legt das Ergebnis auf dem Stack ab.
*/
int multiplication()
{
	int op1, op2;
	myerrno = 0;
	if (!is_empty()) {
		op1 = pop();
		if (!is_empty()) {
			op2 = pop();
		}
	} else {
		myerrno = 1;
	}

	if (myerrno) {
		fprintf(stderr, " (E) Could not get first 2 elements%c",  '\n');
		myerrno = 1;
		return 0;
	}
	op2 *= op1;
	item *temp = new_item(op2);
	push(temp);
	return op2;
}

int debug_run()
{
	while (!is_empty()) {
		pop();
	}
	int temp;
	printf("Test 1: Push 0..9, pop all\n");
	for (int i=0; i<=2; i++) {
		myerrno = 0;
		for (int i=0; i<10; i++) {
			push(new_item(i));
		}
		for (int i=10; i>0; i--) {
			temp = pop();
			dprint("%d\n", temp);
		}
		if (myerrno) {
			fprintf(stderr, "Failed test!\n");
			return 1;
		}
		printf("Should error now:\n");
		pop();
		if (!myerrno) {
			fprintf(stderr, "Failed test!\n");
			return 1;
		}
		printf("Test 1, run %d complete!\n", i);
	}


	printf("Test 2: push 0..9, trash 5th elem (5), pop remaining\n");
	myerrno = 0;
	item *temp2;
	for (int i=0; i<10; i++) {
		item *temp = new_item(i);
		if (i == 5) {
			temp2 = temp;
			dprint("set temp2 to %p\n", (void *)temp2);
			dprint("temp is %p\n", (void *)temp);
		}
		push(temp);
	}
	trash(temp2);
	for (int i=9; i>0; i--) {
		temp = pop();
		dprint("%d\n", temp);
	}
	if (myerrno) {
		fprintf(stderr, "Failed test!\n");
		return 1;
	}
	printf("Should error now:\n");
	pop();
	if (!myerrno) {
		fprintf(stderr, "Failed test!\n");
		return 1;
	}


	printf("Test 3: push 0..9, multiply (pop 2x, push 1), pop remaining\n");
	for (int i=0; i<10; i++) {
		item *temp = new_item(i);
		push(temp);
	}
	int temp3 = multiplication();
	temp = pop();
	if (myerrno || temp3 != temp) {
		fprintf(stderr, "Failed test!\n");
		return 1;
	}

	for (int i=8; i>0; i--) {
		printf("%d\n", pop());
	}
	printf("Should error now:\n");
	pop();
	if (!myerrno) {
		fprintf(stderr, "Failed test!\n");
		return 1;
	}

	while (!is_empty()) {
		pop();
	}
	return 0;
}

void show_help()
{
	printf(" HELP\n"
	       "[-d] to run selftest\n"
	       "[-a] to add element to stack\n"
	       "[-r] to remove element from stack\n"
	       "[-e] to check if empty\n" );

}

int wait_command()
{
	printf(" === Launching the probably most annoying prompt === \n");
	char temp;

	while (1) {
		fscanf(stdin, " %c2", &temp);

		int itemp;
		switch (temp) {
		case 'd':
			return debug_run();
			break;
		case 'a':
			fscanf(stdin, " %d2", &itemp);
			push(new_item(itemp));
			printf("Pushed %d\n", itemp);
			break;
		case 'r':
			myerrno = 0;
			itemp = pop();
			if (myerrno) {
				return 1;
			}
			printf("Popped %d from stack\n", itemp);
			break;
		case 'e':
			itemp = is_empty();
			if (itemp) {
				printf("Stack is empty\n");
			} else {
				printf("Stack is not empty\n");
			}
			break;
		case 'm':
			myerrno = 0;
			itemp = multiplication();
			if (myerrno) {
				return 1;
			}
			printf("Top 2 elements multiplied were: %d\n"
			       "pushed result to stack.\n", itemp);
			break;
		default:
			show_help();
			while (!is_empty()) {
				pop();
			}
			return 0;
			break;
		}
	}
}

int main(int argc, char *argv[])
{
#ifdef DEBUG
	if (debug_run()) {
		printf("SELFTEST FAILED!\n"
		       "to skip selftest, compile without DEBUG set\n");
		return 1;
	}
#endif

	return wait_command();
}
