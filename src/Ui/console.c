/*
* console.c
*
*  Created on: 5 mar. 2016
*      Author: marius
*/

#include "console.h"

Console* console_init(Controller* ctr) {
	/*
	* @input  : ctr - pointer to object of type Controller
	* @output : returns a pointer to a newly created Console object
	*/
	Console* cons = (Console*)malloc(sizeof(Console));
	cons->ctr = ctr;
	return cons;
}

void console_destroy(Console* this) {
	/*
	* @input  : this - pointer to object of type Console
	* @output : frees the memory occupied by the Console object this
	*/
	free(this);
}

char* console_read_main_menu_cmd() {
	/*
	* @input  : true
	* @output : returns a pointer string read from stdin
	*/
	printf("Meniu:\n");
	printf("	0 - Iesire\n");
	printf("	1 - Adaugare cheltuiala\n");
	printf("	2 - Modificare cheltuiala\n");
	printf("	3 - Stergere cheltuiala\n");
	printf("	4 - Filtrare\n");
	printf("	5 - Vizualizare cheltuieli ordonat\n");
	printf("	6 - Afiseaza toate cheltuielile\n");
	//printf("	7 - Undo\n");
	printf("Introduceti optiunea: ");
	fflush(stdout);
	char* cmd = (char*)malloc(255 * sizeof(char));
	scanf("%s", cmd);
	return cmd;
}

char* console_read_nr_ap() {
	/*
	* @input  : true
	* @output : returns a pointer string read from stdin, allocated on the heap
	*/
	char* temp = (char*)malloc(255 * sizeof(char));;
	printf("Introduceti numarul apartamentului: ");
	fflush(stdout);
	scanf("%s", temp);
	return temp;
}

char* console_read_suma() {
	/*
	* @input  : true
	* @output : returns a pointer string read from stdin
	*/
	char* temp = (char*)malloc(255 * sizeof(char));;
	printf("Introduceti suma: ");
	fflush(stdout);
	scanf("%s", temp);
	return temp;
}

char* console_read_tip() {
	/*
	* @input  : true
	* @output : returns a pointer string read from stdin
	*/
	char* temp = (char*)malloc(255 * sizeof(char));;
	printf("Introduceti tipul cheltuielii(apa/ canal/ incalzire/ gaz): ");
	fflush(stdout);
	scanf("%s", temp);
	return temp;
}

void console_add_cheltuiala(Console* this) {
	/*
	* @input  : this - pointer to object of type Console
	* @output : reads the attributes of an pointer to object of type Cheltuiala,
	*			and adds it to repository, signalling eventual errors
	*/
	Cheltuiala* ch = console_read_cheltuiala(this);
	if (ch != NULL) {
		if (controller_find_item(this->ctr, ch) == 0) {
			controller_add_item(this->ctr, ch);
			printf("Cheltuiala a fost adaugata cu succes!\n");
		}
		else {
			printf("Aceasta cheltuiala a fost deja adaugata!\nDoriti sa o actualizati? (y/n) : ");
			fflush(stdout);
			char chr[255];
			scanf("%s", chr);
			if (strlen(chr) == 1 && (chr[0] == 'y' || chr[0] == 'Y'))
				console_modify_menu(this, ch);
			cheltuiala_destroy(ch);
		}
	}
	else
		printf("Datele introduse sunt incorecte!\n");
}

void console_print_spaces(int number_spaces) {
	/*
	 *	@input  : number_of_spaces - integer
	 *	@output : printf on the screen "space" character, number_spaces times
	 */
	for (; number_spaces; number_spaces--)
		printf(" ");
}

void console_print_cheltuieli(Console* this, Vector* items, int spaces) {
	/*
	* @input  : this  - pointer to object of type Console
	*			items - pointer to a dynamic array
	*			spaces- integer representing the indent of the output
	* @output : prints the items on the screen using an
	*			iterator (see Utils/Vector)
	*/
	Iterator* it = iterator_init(items);
	int cnt = 0;
	if (iterator_valid(it)) {
		console_print_spaces(spaces);
		printf("_________________________________________\n");
		console_print_spaces(spaces);
		printf("|Nr.Crt | Nr. Ap.|   Suma    |   Tip    |\n");
		console_print_spaces(spaces);
		printf("_________________________________________\n");
	}
	for (; iterator_valid(it); iterator_next(it)) {
		Cheltuiala* ch_ptr = iterator_element(it);
		cnt++;
		int nr_ap = cheltuiala_get_numar_apartament(ch_ptr);
		double suma = cheltuiala_get_sum(ch_ptr);
		char* tip = cheltuiala_get_tip(ch_ptr);
		char buff[255], suma_str[12];
		snprintf(suma_str, 11, "%5.3lf", suma);
		snprintf(buff, 50, "|%7d|%8d|%11s|%10s|", cnt, nr_ap, suma_str, tip);
		console_print_spaces(spaces);
		printf("%s\n", buff);
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
	}
	iterator_destroy(it);
}

void console_print_all(Console* this, int spaces) {
	/*
	* @input  : this - pointer to object of type Console
	* @output : all the objects from repository on stdout
	*/
	Vector* alls = controller_get_all(this->ctr);
	if (vector_size(alls) == 0)
		printf("Nu este nicio cheltuiala de afisat!\n");
	else {
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
		console_print_spaces(spaces);
		printf("Cheltuielile curente sunt:\n");
		console_print_cheltuieli(this, alls, spaces);
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
	}
}

char* console_read_modify_menu_cmd(Cheltuiala* ch_ptr) {
	/*
	* @input  : this - pointer to object of type Console
	* @output : reads a command from stdin an retuns a pointer to a string
	*/
	printf("Meniu modificare cheltuiala:\n");
	printf("  		[ Cheltuiala curenta este: %d %lf %s ]\n", cheltuiala_get_numar_apartament(ch_ptr), cheltuiala_get_sum(ch_ptr), cheltuiala_get_tip(ch_ptr));
	printf("	0 - Inapoi\n");
	printf("	1 - Modificare suma\n");
	printf("	2 - Modificare tip\n");
	printf("Introduceti optiunea: ");
	fflush(stdout);
	char* cmd = (char*)malloc(255 * sizeof(char));
	scanf("%s", cmd);
	return cmd;
}

void console_modify_suma(Console* this, Cheltuiala* ch, int* nr_op) {
	/*
	* @input  : this - pointer to object of type Console
	*			ch	 - pointer to object of type Cheltuiala
	* @output : realizes the user's interface in the modify sum option
	*/
	char* suma_str = console_read_suma();
	if (controller_validate_suma(this->ctr, suma_str)) {
		double suma = controller_str_to_double(this->ctr, suma_str);
		controller_modify_item_sum(this->ctr, ch, suma);
		cheltuiala_set_suma(ch, suma);
		(*nr_op)++;
		printf("Suma a fost modificata cu succes!\n");
	}
	else
		printf("Ati introdus o suma gresita\n");
	free(suma_str);
}

void console_modify_tip(Console* this, Cheltuiala* ch, int* nr_op) {
	/*
	* @input  : this - pointer to object of type Console
	*			ch	 - pointer to object of type Cheltuiala
	* @output : realizes the user's interface in the modify tip option
	*/
	char* tip = console_read_tip();
	if (controller_validate_tip(this->ctr, tip)) {
		controller_modify_item_tip(this->ctr, ch, tip);
		cheltuiala_set_tip(ch, tip);
		(*nr_op)++;
		printf("Tipul a fost modificat cu succes!\n");
	}
	else
		printf("Tipul introdus este gresit!\n");
	free(tip);
}

void console_modify_menu(Console* this, Cheltuiala* ch) {
	/*
	* @input  : this - pointer to object of type Console
	*			ch	 - pointer to object of type Cheltuiala
	* @output : realizes the user's interface in the modify option
	*/
	int valid, cmd, number_of_operations = 0;
	for (; 1; ) {
		char* cmd_str = NULL;
		cmd_str = console_read_modify_menu_cmd(ch);
		valid = controller_validate_cmd(this->ctr, cmd_str);
		if (!valid)
			printf("Optiunea introdusa este incorecta!\n");
		else {
			cmd = controller_str_to_int(this->ctr, cmd_str);
			if (cmd == 0) {
				free(cmd_str);
				break;
			}
			else
				if (cmd == 1)
					console_modify_suma(this, ch, &number_of_operations);
				else
					if (cmd == 2)
						console_modify_tip(this, ch, &number_of_operations);
					else
						if (cmd == 3) {
							Vector* alls = controller_get_all(this->ctr);
							int pos = vector_element_index(alls, ch, &cheltuiala_equal);
							if (number_of_operations <= 0)
								printf("Ati ajuns deja la atributele intiale pentru aceasta cheltuiala!\n");
							else {
								if (controller_restore_cheltuiala(this->ctr) == 0)
									printf("Nu se mai poate face undo!\n");
								else {
									number_of_operations--;
									Cheltuiala* ch_in_repo = vector_element_at(alls, pos);
									cheltuiala_set_tip(ch, cheltuiala_get_tip(ch_in_repo));
									cheltuiala_set_suma(ch, cheltuiala_get_sum(ch_in_repo));
								}
							}
						}
						else
							printf("Optiunea introdusa este incorecta!\n");
		}
		fflush(stdout);
		free(cmd_str);
	}
}

void console_modify_cheltuiala(Console* this) {
	/*
	* @input  : this - pointer to object of type Console
	*			ch	 - pointer to object of type Cheltuiala
	* @output : realizes the user's interface in the modify sum option
	*/
	Cheltuiala* ch = console_read_cheltuiala(this);
	if (ch != NULL) {
		if (controller_find_item(this->ctr, ch) == 1) {
			console_modify_menu(this, ch);
		}
		else
			printf("Cheltuiala introdusa nu a putut fi gasita!\n");
		cheltuiala_destroy(ch);
	}
	else {
		printf("Datele introduse sunt incorecte!\n");
	}
}

Cheltuiala* console_read_cheltuiala(Console* this) {
	/*
	* @input  : this - pointer to object of type Console
	* @output : reads the attributes of an object of type Cheltuiala
	*			returns NULL if the introduced dates are invalid
	*			returns the pointer to newly created object, otherwise
	*/
	Cheltuiala* ch = NULL;
	char* numar_ap_str = console_read_nr_ap();
	char* suma_str = console_read_suma();
	char* tip = console_read_tip();
	if (controller_validate_cheltuiala(this->ctr, numar_ap_str, suma_str, tip)) {
		int numar_ap = controller_str_to_int(this->ctr, numar_ap_str);
		double suma = controller_str_to_double(this->ctr, suma_str);
		ch = cheltuiala_init(numar_ap, suma, tip);
	}
	free(numar_ap_str);
	free(suma_str);
	free(tip);
	return ch;
}

void console_delete_cheltuiala(Console* this) {
	/*
	* @input  : this - pointer to object of type Console
	* @output : realizes the user's interface in the del option
	*/
	Cheltuiala* ch = console_read_cheltuiala(this);
	if (ch != NULL) {
		if (controller_find_item(this->ctr, ch) == 1) {
			controller_delete_item(this->ctr, ch);
			printf("Cheltuiala a fost stearsa!\n");
			//cheltuiala_destroy(ch);
		}
		else {
			cheltuiala_destroy(ch);
			printf("Cheltuiala introdusa nu a putut fi gasita!\n");
		}
	}
	else
		printf("Datele introduse sunt incorecte!\n");
}

char* console_read_filter_menu_cmd() {
	/*
	* @input  : true
	* @output : returns a pointer string read from stdin
	*/
	printf("Meniu filtrare:\n");
	printf("	0 - Inapoi\n");
	printf("	1 - Filtrare dupa numar apartament\n");
	printf("	2 - Filtrare mai mici decat o suma data\n");
	printf("	3 - Filtrare dupa tip\n");
	printf("Introduceti optiunea: ");
	fflush(stdout);
	char* cmd = (char*)malloc(255 * sizeof(char));
	scanf("%s", cmd);
	return cmd;
}

void console_filter_by_nr_ap(Console* this, int spaces) {
	/*
	* @input  : this  - Console object
	*			spaces- int
	* @output : realises user interface when filtering by number of apartment
	*/
	char* nr_ap_str = console_read_nr_ap();
	int valid = controller_validate_nr_ap(this->ctr, nr_ap_str), nr_ap;
	Vector* partials = NULL;
	if (valid) {
		nr_ap = controller_str_to_int(this->ctr, nr_ap_str);
		partials = controller_get_filtered_by_nr_ap(this->ctr, nr_ap);
	}
	else {
		printf("Datele introduse sunt incorecte!\n");
		free(nr_ap_str);
		return;
	}
	if (vector_size(partials) > 0) {
		console_print_spaces(spaces);
		printf("Cheltuielile cu numarul apartamentului %d sunt: \n", nr_ap);
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
		console_print_cheltuieli(this, partials, spaces);
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
	}
	else
		printf("Nu este nicio cheltuiala de afisat!\n");
	vector_destroy(partials);
	free(nr_ap_str);
}

void console_filter_by_sum(Console* this, int spaces) {
	/*
	* @input  : this  - Console object
	*			spaces- int
	* @output : realises user interface when filtering by sum
	*/
	char* suma_str = console_read_suma();
	int valid = controller_validate_suma(this->ctr, suma_str);
	double suma;
	Vector* partials = NULL;
	if (valid) {
		suma = controller_str_to_double(this->ctr, suma_str);
		partials = controller_get_filtered_by_sum(this->ctr, suma);
	}
	else {
		printf("Datele introduse sunt incorecte!\n");
		free(suma_str);
		return;
	}
	if (vector_size(partials) > 0) {
		console_print_spaces(spaces);
		printf("Cheltuielile cu suma mai mica sau egala cu %.3lf sunt: \n", suma);
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
		console_print_cheltuieli(this, partials, spaces);
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
	}
	else
		printf("Nu este nicio cheltuiala de afisat!\n");
	if (partials != NULL)
		vector_destroy(partials);
	free(suma_str);
}

void console_filter_by_tip(Console* this, int spaces) {
	/*
	* @input  : this  - Console object
	*			spaces- int
	* @output : realises user interface when filtering by tip
	*/
	char* tip = console_read_tip();
	int valid = controller_validate_tip(this->ctr, tip);
	Vector* partials = NULL;
	if (valid)
		partials = controller_get_filtered_by_tip(this->ctr, tip);
	else {
		printf("Datele introduse sunt incorecte!\n");
		free(tip);
		return;
	}
	if (vector_size(partials) > 0) {
		console_print_spaces(spaces);
		printf("Cheltuielile de tipul %s sunt: \n", tip);
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
		console_print_cheltuieli(this, partials, spaces);
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
	}
	else
		printf("Nu este nicio cheltuiala de afisat!\n");
	if (partials != NULL)
		vector_destroy(partials);
	free(tip);
}

void console_filter_menu(Console* this, int spaces) {
	/*
	* @input  : this  - Console object
	*			spaces- int
	* @output : realises user interface in the filter menu
	*/
	int valid, cmd;
	for (; 1; ) {
		char* cmd_str = NULL;
		cmd_str = console_read_filter_menu_cmd();
		valid = controller_validate_cmd(this->ctr, cmd_str);
		if (valid == 0)
			printf("Ati introdus o optiune incorecta!\n");
		else {
			cmd = controller_str_to_int(this->ctr, cmd_str);
			if (cmd == 0) {
				free(cmd_str);
				break;
			}
			else
				if (cmd == 1)
					console_filter_by_nr_ap(this, spaces);
				else
					if (cmd == 2)
						console_filter_by_sum(this, spaces);
					else
						if (cmd == 3)
							console_filter_by_tip(this, spaces);
						else
							printf("Ati introdus o optiune incorecta!\n");
		}
		fflush(stdout);
		free(cmd_str);
	}
}

char* console_read_ordered_menu_cmd() {
	/*
	* @input  : true
	* @output : returns a pointer string read from stdin
	*/
	printf("Meniu vizualizare cheltuieli sortat:\n");
	printf("	0 - Inapoi\n");
	printf("	1 - Afisare cheltuieli sortat dupa suma\n");
	printf("	2 - Afisare cheltuieli sortat dupa tip\n");
	printf("Introduceti optiunea: ");
	fflush(stdout);
	char* cmd = (char*)malloc(255 * sizeof(char));
	scanf("%s", cmd);
	return cmd;
}

char* console_read_sort_menu_cmd() {
	/*
	* @input  : true
	* @output : returns a pointer string read from stdin
	*/
	printf("Cum doriti sa se faca sortarea ?\n");
	printf("	0 - Inapoi\n");
	printf("	1 - Ascendent\n");
	printf("	2 - Descendent\n");
	printf("Introduceti optiunea: ");
	fflush(stdout);
	char* cmd = (char*)malloc(255 * sizeof(char));
	scanf("%s", cmd);
	return cmd;
}

void console_order_by_sum(Console* this, int spaces) {
	/*
	* @input  : this  - Console object
	*			spaces- int
	* @output : realises user interface when ordering by sum
	*/
	int valid = 0;
	int reversed;
	for (; 1; ) {
		char* cmd_str = console_read_sort_menu_cmd();
		valid = controller_validate_cmd(this->ctr, cmd_str);
		if (valid) {
			int cmd = controller_str_to_int(this->ctr, cmd_str);
			if (cmd == 0) {
				free(cmd_str);
				return;
			}
			else
				if (cmd == 1 || cmd == 2) {
					reversed = cmd - 1;
					free(cmd_str);
					break;
				}
		}
		printf("Ati introdus o optiune incorecta!\n");
		free(cmd_str);
	}
	Vector* vec = controller_get_sorted_by_sum(this->ctr, reversed);
	if (vector_size(vec) == 0)
		printf("Nu exista nicio cheltuiala de afisat!\n");
	else {
		if (reversed) {
			console_print_spaces(spaces);
			printf("Cheltuielile ordonate descendent dupa suma sunt: \n");
		}
		else {
			console_print_spaces(spaces);
			printf("Cheltuielile ordonate ascendent dupa suma sunt: \n");
		}
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
		console_print_cheltuieli(this, vec, spaces);
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
	}
	vector_destroy(vec);
}

void console_order_by_tip(Console* this, int spaces) {
	/*
	* @input  : this  - Console object
	*			spaces- int
	* @output : realises user interface when ordering by tip
	*/
	int valid = 0;
	int reversed;
	for (; 1; ) {
		char* cmd_str = console_read_sort_menu_cmd();
		valid = controller_validate_cmd(this->ctr, cmd_str);
		if (valid) {
			int cmd = controller_str_to_int(this->ctr, cmd_str);
			if (cmd == 0) {
				free(cmd_str);
				return;
			}
			else
				if (cmd == 1 || cmd == 2) {
					reversed = cmd - 1;
					free(cmd_str);
					break;
				}
		}
		printf("Ati introdus o optiune incorecta!\n");
		free(cmd_str);
	}
	Vector* vec = controller_get_sorted_by_tip(this->ctr, reversed);
	if (vector_size(vec) == 0)
		printf("Nu exista nicio cheltuiala de afisat!\n");
	else {
		if (reversed) {
			console_print_spaces(spaces);
			printf("Cheltuielile ordonate descendent dupa tip sunt: \n");
		}
		else {
			console_print_spaces(spaces);
			printf("Cheltuielile ordonate ascendent dupa tip sunt: \n");
		}
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
		console_print_cheltuieli(this, vec, spaces);
		console_print_spaces(spaces);
		printf("-----------------------------------------\n");
	}
	vector_destroy(vec);
}

void console_order_menu(Console* this, int spaces) {
	/*
	* @input  : this  - Console object
	*			spaces- int
	* @output : realises user interface on the order menu
	*/
	int valid, cmd;
	for (; 1; ) {
		char* cmd_str = NULL;
		cmd_str = console_read_ordered_menu_cmd();
		valid = controller_validate_cmd(this->ctr, cmd_str);
		if (valid == 0)
			printf("Ati introdus o optiune incorecta!\n");
		else {
			cmd = controller_str_to_int(this->ctr, cmd_str);
			if (cmd == 0) {
				free(cmd_str);
				break;
			}
			else
			if (cmd == 1) console_order_by_sum(this, spaces);
			else
			if (cmd == 2) console_order_by_tip(this, spaces);
			else
				printf("Ati introdus o optiune incorecta!\n");
		}
		fflush(stdout);
		free(cmd_str);
	}
}

void console_run(Console* this) {
	/*
	* @input  : this - pointer to object of type Console
	* @output : realizes the user's interface in the main menu
	*/
	int valid, cmd, spaces = 40;
	for (; 1;) {
		char* cmd_str = NULL;
		cmd_str = console_read_main_menu_cmd();
		valid = controller_validate_cmd(this->ctr, cmd_str);
		if (valid == 0)
			printf("Ati introdus o optiune incorecta!\n");
		else {
			cmd = controller_str_to_int(this->ctr, cmd_str);
			if (cmd == 0) {
				printf("Iesire...\n");
				free(cmd_str);
				break;
			}
			else
			if (cmd == 1) console_add_cheltuiala(this);
			else
			if (cmd == 2) console_modify_cheltuiala(this);
			else
			if (cmd == 3) console_delete_cheltuiala(this);
			else
			if (cmd == 4) console_filter_menu(this, spaces);
			else
			if (cmd == 5) console_order_menu(this, spaces);
			else
			if (cmd == 6) console_print_all(this, spaces);
			else
			if (cmd == 7) {
			if (controller_restore_cheltuiala(this->ctr) == 0)
				printf("Nu se mai poate face undo!\n");
			}
			else
				printf("Ati introdus o optiune incorecta!\n");
		}
		fflush(stdout);
		if (cmd_str != NULL)
			free(cmd_str);
	}
}
