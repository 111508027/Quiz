#include <gtk/gtk.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsexmlfile.c"

#define SINGLE 1
#define TRUEFALSE 1
#define MULTIPLE 2
#define SHORTANSWER 3
#define MATCH 4
#define NUMERICAL 5

static int sel = 0, d = 0;
static int final;
static int final_index_num[100];
static int howmany;
static int outof;

int no_of_attempt[100];
int option_multiple_selected[10][100];
int count_ans_single = 0;
float count_ans_multiple = 0;
float count_ans_numerical = 0;
char *text[100];

GdkColor yellow = {0, 0xffff, 0xffff, 0x0000};
GdkColor red = {0, 0xffff, 0x0000, 0x0000};
GdkColor green = {0, 0x0000, 0xffff, 0x0000};
GdkColor blue = {0, 0x0000, 0x0000, 0xffff};
GdkColor purple = {0, 0xffff, 0x0000, 0xffff};
GdkColor orange = {0, 0xffff, 0x9999, 0x0000};
GdkColor cyan = {0, 0x0000, 0xffff, 0xffff};
GdkColor black = {0, 0x0000, 0x0000, 0x0000};
GdkColor white = {0, 0xffff, 0xffff, 0xffff};
  	

static void enter_callback(GtkWidget *widget, gpointer data);
static void check_func(GtkWidget *widget, gpointer data);
static void radio_func(GtkWidget *widget, gpointer data);
static void create_clicked(GtkWidget *widget, gpointer data);
static void help_clicked(GtkWidget *widget, gpointer data);
static void add_que_clicked(GtkWidget *widget, gpointer data);
static void attempt_clicked(GtkWidget *widget, gpointer data);
static void select_que(GtkWidget *widget, gpointer data);
static void quiz_clicked(GtkWidget *widget, gpointer data);
static void finish_clicked(GtkWidget *widget, gpointer data);

int quechecker(int n, int s);
float single_ans_checker();
float multiple_ans_checker();
float numerical_ans_checker();
int quetypechecker(int n);

void radio_func(GtkWidget *widget, gpointer data) {
	
	int count = 0, i = 0, sum = 0;
	if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) {
		while(i <= 100) {
			sum = sum + no_of_opt[i];
			if(sum > GPOINTER_TO_INT(data))
				break;
			else
				i++;
		}	
		option_single_selected[i] = GPOINTER_TO_INT(data);
		no_of_attempt[i] = ++count; 			
	}
	else {
		while(i <= 100) {
			sum = sum + no_of_opt[i];
			if(sum > GPOINTER_TO_INT(data))
				break;
			else
				i++;
		}
		
	}
			
}

static void submit_clicked(GtkWidget *widget, gpointer data) {
	
	GtkWidget *window, *vbox, *label1, *label2;
	
	window = gtk_dialog_new ();
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 1080, 720);
  	gtk_window_set_title(GTK_WINDOW(window), "QUESTION BANK");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 0);
	
	vbox = gtk_vbox_new(0, 0);
	
	GtkWidget *scrolled_window;
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 0);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(window)->vbox), scrolled_window,TRUE, TRUE, 0);
	
	float marks1 = single_ans_checker();
	float marks2 = multiple_ans_checker();
	float marks3 = numerical_ans_checker();
	float total = marks1 + marks2 + marks3;
	
	char marks[100], tmp1[100];
	if( total >= (float)outof * 0.5 ) {
		strcpy(tmp1, " CONGRATS !!!! YOU HAVE FINISHED YOUR QUIZ AND YOU GOT ");
	}
	else {
		strcpy(tmp1, " OHH!!! SO POOR !!!! YOU HAVE FINISHED YOUR QUIZ AND YOU GOT ");
	}
	char tmp2[10];
	
	snprintf(marks, 10, "%f", total);
	strcat(marks, " MARKS OUT OF  ");
	snprintf(tmp2, 10, "%d", outof);
	
	strcat(tmp1, marks);
	strcat(tmp1, tmp2);
		
	label1 = gtk_label_new(tmp1);
	gtk_container_add(GTK_CONTAINER(vbox), label1);
	
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), vbox);		
	
	gtk_widget_show_all(window);
  	
}

static void check_func(GtkWidget *widget, gpointer data) {

	static int j = 0;
	int i = 0, sum = 0, k = 0, l = 0;
	if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) {
		while( i <= 100 ) {
			sum = sum + no_of_opt[i];
			if(sum > GPOINTER_TO_INT(data))
				break;
			i++;
			//j = 0;
		}	
		option_multiple_selected[j][i] = GPOINTER_TO_INT(data);
		no_of_attempt[i] = ++j;
	}	
	
	else {
		while( i <= 100 ) {
			sum = sum + no_of_opt[i];
			if(sum > GPOINTER_TO_INT(data))
				break;
			i++;
		}	
			
		for(k = 0; k <= j - 1; k++) {
			if( GPOINTER_TO_INT(data) == option_multiple_selected[k][i] ) {
			 		for(l = k; l <= j - 1; l++)
			 			option_multiple_selected[l][i] = option_multiple_selected[l + 1][i];	
			}	
		}
		no_of_attempt[i] = --j;
	}
}

float single_ans_checker() {

	int i;
	for(i = 0; i < 100; i++) {
		int tmp = option_single_selected[i];
		if(tmp != -1) {
			if( !( strncmp(ans[0][i], opt[tmp], strlen(opt[tmp])) ) ) {
				++count_ans_single;
				//i++;
			}	
		}
	}	
	return count_ans_single;
}			


float multiple_ans_checker() {
	
	int i, k = 0, j = 0;	
	for(i = 0; i < 100;) {
		if(option_multiple_selected[k][i] == -1)
			i++;
			
		else {
			for(k = 0; k < no_of_attempt[i]; k++) {
				for(j = 0; j < no_of_ans[i]; j++) {
					if(!(strncmp(ans[j][i], opt[option_multiple_selected[k][i]], strlen(ans[j][i])))) {
						count_ans_multiple = count_ans_multiple + ((float)1/(float)no_of_ans[i]);
						break;
					}
				}
			}
			i++;				
		}
	}
	return count_ans_multiple; 				
}


float numerical_ans_checker() {
	
	int i = 0, j = 0;
	for(i = 0; i < 100; i++) {
		int tmp = nos_of_numerical_que[i];
		if(text[tmp] != NULL) {
			for(j = 0; j < no_of_ans[tmp]; j++) {
				if(!(strncmp(ans[j][tmp], text[tmp], strlen(text[tmp])))) {
					++count_ans_numerical;
					break;
				}
			}	
		}			
	}
	return count_ans_numerical;				
}		
	
static void enter_callback(GtkWidget *widget, gpointer data) {
	int tmp2 = GPOINTER_TO_INT(data); 
	text[tmp2] = gtk_entry_get_text(widget);
	if(widget == NULL)
		gtk_editable_insert_text (GTK_EDITABLE (widget), text, -1, 0);
}
				
int quechecker(int n, int quizno) {
	int a, b = 0;
	for(a = 0; a < quizno; a++) {
		b = b + que_quiz[a];
	}
	int initial = b;
	int final = b + que_quiz[a];
	
	int x = initial;
	while(x < final) {
		if(n == que_selected[x])
			return 1;	
		x++;
	}
	return 0;
}				

int quetypechecker(int n) {
	int x = 0;
	while(x < 100) {
		if(n == nos_of_single_que[x])
			return SINGLE;
		
		else if(n == nos_of_multiple_que[x])
			return MULTIPLE;
		
		else if(n == nos_of_truefalse_que[x])
			return TRUEFALSE;
		
		else if(n == nos_of_shortanswer_que[x])
			return SHORTANSWER;
		
		else if(n == nos_of_match_que[x])
			return MATCH;
		
		else if(n == nos_of_numerical_que[x])
			return NUMERICAL;
		else	
			x++;
	}
	if(x == 100)
		return 0; 
}				

static void select_que(GtkWidget *widget, gpointer data) {
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		
		int tmp = (GPOINTER_TO_INT(data)); 
		for(int i = 0; i < 100; i++) {
			if((tmp >= start_que_no_of_quiz[i]) && (tmp < start_que_no_of_quiz[i + 1])) {				
				que_quiz[i] = ++sel;		
				que_selected[--sel] = tmp;
				sel++;			
			}
		}	
	}	
	
	else {
		int tmp2 = GPOINTER_TO_INT(data);
		int i = 0, k = 0;
		
		for(i = 0; i < sel; i++) {
			if(que_selected[i] == tmp2) {
				for(int j = i; j < sel; j++)
					que_selected[j] = que_selected[j + 1];

			}
		}
		
		sel--;
		
		for(int i = 0; i < 100; i++) {
			if((tmp2 >= start_que_no_of_quiz[i]) && (tmp2 < start_que_no_of_quiz[i + 1])) 
				que_quiz[i] = sel;		
		}					
	}	
}

static void next_clicked(GtkWidget *widget, gpointer data) {
	
	GtkWidget *window, *vbox, *next, *label, *hbox, *halign, *valign, *submit, *radio, *radio2, *check, *check2;
	
    	window = gtk_dialog_new ();
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window),1080, 720);
  	gtk_window_set_title(GTK_WINDOW(window), "MY QUIZ");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 0);
			
	vbox = gtk_vbox_new(0, 0);
	
	GtkWidget *scrolled_window;
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 0);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(window)->vbox), scrolled_window,TRUE, TRUE, 0);
	
	
	int a = 0, b = 0, p, q, sum, min, max, i, r, temp, n;
		
	int tmp1 = GPOINTER_TO_INT(data);
	int tmp2 = que_selected[final_index_num[tmp1]];
	sum = 0;
				
    	int z = quetypechecker(tmp2);
    	
    	if(z == SINGLE && z == TRUEFALSE) {

		label = gtk_label_new( que[tmp2] );
					
		p = 0, q = 0;
		sum = 0;
		while(q < tmp2) {
			sum = sum + no_of_opt[q];
			q++;
		}	
			
		min = sum;
		max = sum + no_of_opt[tmp2] - 1;
		int len = max - min + 1;
		int optnum[len];
		
		for( temp = 0, i = min; temp < len; i++, temp++ )
        		optnum[temp] = i;
	
    		srand( time(NULL) );  
      		
      		for( i = len - 1; i > 0; i-- ){
        		r = rand() % i;   
        		temp = optnum[i];
       			optnum[i] = optnum[r];
        		optnum[r] = temp;
        				
    		}
    			
		gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
		radio = gtk_radio_button_new_with_label(NULL, opt[optnum[p]]);
		gtk_box_pack_start(GTK_BOX(vbox), radio, 0, 0, 0);
		g_signal_connect(radio, "toggled", G_CALLBACK(radio_func), (gpointer)optnum[p]);  
		p++;
		
		while(p < no_of_opt[tmp2]) {
			radio2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio)), opt[optnum[p]]);		
			gtk_box_pack_start(GTK_BOX(vbox), radio2, 0, 0, 0);
			g_signal_connect(radio2, "toggled", G_CALLBACK(radio_func), (gpointer)optnum[p]);  
			p++;
					
		}
		
		if(--howmany) { 
			valign = gtk_alignment_new(5, 2, 0, 0);
  			gtk_container_add(GTK_CONTAINER(vbox), valign);
  		
  			hbox = gtk_hbox_new(TRUE, 3);

  			next = gtk_button_new_with_label("NEXT");
  			gtk_widget_set_size_request(next, 70, 30);
  			gtk_container_add(GTK_CONTAINER(hbox), next);
  		
  			halign = gtk_alignment_new(0, 0, 5, 0);
  			gtk_container_add(GTK_CONTAINER(halign), hbox);

  			gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);			
			gtk_widget_modify_bg(next, GTK_STATE_PRELIGHT, &cyan);
  			g_signal_connect(next, "clicked", G_CALLBACK(next_clicked), (gpointer)(++tmp1));  
		}
		
		else {
			valign = gtk_alignment_new(5, 2, 0, 0);
  			gtk_container_add(GTK_CONTAINER(vbox), valign);
  		
  			hbox = gtk_hbox_new(TRUE, 3);

  			submit = gtk_button_new_with_label("SUBMIT THE QUIZ ");
  			gtk_widget_set_size_request(submit, 70, 30);
  			gtk_container_add(GTK_CONTAINER(hbox), submit);
  		
  			halign = gtk_alignment_new(0, 0, 5, 0);
  			gtk_container_add(GTK_CONTAINER(halign), hbox);

  			gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);			
			gtk_widget_modify_bg(submit, GTK_STATE_PRELIGHT, &cyan);
  			g_signal_connect(submit, "clicked", G_CALLBACK(submit_clicked), NULL);  
		}
	}	
			
	if(z == MULTIPLE) {
				 
		label = gtk_label_new(que[tmp2]);
				
		p = 0, q = 0;
		sum = 0;
		while(q < tmp2) {
			sum = sum + no_of_opt[q];
			q++;
		}	
			
		min = sum;
		max = sum + no_of_opt[tmp2] - 1;
		int len = max - min + 1;
		int optnum[len];
			
       		for(temp = 0, i = min; temp < len; i++, temp++)
        		optnum[temp] = i;
	
    		srand( time(NULL) );  
      		
      		for(i = len-1; i > 0; i--) {
        		r = rand() % i;   
        		temp = optnum[i];
       			optnum[i] = optnum[r];
        		optnum[r] = temp;
    		}
				
		gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);		
		check = gtk_check_button_new_with_label(opt[optnum[p]]);	
		gtk_box_pack_start(GTK_BOX(vbox), check, 0, 0, 0);
		g_signal_connect(check, "toggled", G_CALLBACK(check_func), (gpointer)optnum[p]);  
		p++;
		
		while(p < no_of_opt[tmp2]) {
			check2 = gtk_check_button_new_with_label(opt[optnum[p]]);
			gtk_box_pack_start(GTK_BOX(vbox), check2, 0, 0, 0);
			g_signal_connect(check2, "toggled", G_CALLBACK(check_func), (gpointer)optnum[p]);  
			p++;
		}
		
		if(--howmany) { 
			valign = gtk_alignment_new(5, 2, 0, 0);
  			gtk_container_add(GTK_CONTAINER(vbox), valign);
  		
  			hbox = gtk_hbox_new(TRUE, 3);

  			next = gtk_button_new_with_label("NEXT");
  			gtk_widget_set_size_request(next, 70, 30);
  			gtk_container_add(GTK_CONTAINER(hbox), next);
  		
  			halign = gtk_alignment_new(0, 0, 5, 0);
  			gtk_container_add(GTK_CONTAINER(halign), hbox);

  			gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);			
			gtk_widget_modify_bg(next, GTK_STATE_PRELIGHT, &cyan);
  			g_signal_connect(next, "clicked", G_CALLBACK(next_clicked), (gpointer)(++tmp1));  
		
		}
		
		else {
			valign = gtk_alignment_new(5, 2, 0, 0);
  			gtk_container_add(GTK_CONTAINER(vbox), valign);
  		
  			hbox = gtk_hbox_new(TRUE, 3);

  			submit = gtk_button_new_with_label("SUBMIT THE QUIZ ");
  			gtk_widget_set_size_request(submit, 70, 30 );
  			gtk_container_add(GTK_CONTAINER(hbox), submit);
  		
  			halign = gtk_alignment_new(0, 0, 5, 0);
  			gtk_container_add(GTK_CONTAINER(halign), hbox);

  			gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);			
			gtk_widget_modify_bg(submit, GTK_STATE_PRELIGHT, &cyan);
  			g_signal_connect(submit, "clicked", G_CALLBACK(submit_clicked), NULL);  
		}		
	}
			
	if(z == SHORTANSWER) {
				
	}

	if(z == MATCH) {
				
	}

	if(z == NUMERICAL) {
					
		GtkWidget *entry, *table; 
		
		label = gtk_label_new(que[tmp2]);
		table = gtk_table_new(2, 1, FALSE);
		
		gtk_container_add(GTK_CONTAINER(vbox), table);
		gtk_table_attach(GTK_TABLE(table), label, 0, 1, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
		
		entry = gtk_entry_new();
		gtk_table_attach(GTK_TABLE(table), entry, 1, 2, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
		g_signal_connect (entry, "activate", G_CALLBACK (enter_callback), (gpointer)tmp2);
				
		if(--howmany) { 
			valign = gtk_alignment_new(5, 2, 0, 0);
  			gtk_container_add(GTK_CONTAINER(vbox), valign);
  		
  			hbox = gtk_hbox_new(TRUE, 3);

  			next = gtk_button_new_with_label("NEXT");
  			gtk_widget_set_size_request(next, 70, 30);
  			gtk_container_add(GTK_CONTAINER(hbox), next);
  		
  			halign = gtk_alignment_new(0, 0, 5, 0);
  			gtk_container_add(GTK_CONTAINER(halign), hbox);

  			gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);			
			gtk_widget_modify_bg(next, GTK_STATE_PRELIGHT, &cyan);
  			g_signal_connect(next, "clicked", G_CALLBACK(next_clicked), (gpointer)(++tmp1));  
		}
		
		else {
			valign = gtk_alignment_new(5, 2, 0, 0);
  			gtk_container_add(GTK_CONTAINER(vbox), valign);
  		
  			hbox = gtk_hbox_new(TRUE, 3);

  			submit = gtk_button_new_with_label("SUBMIT");
  			gtk_widget_set_size_request(submit, 70, 30);
  			gtk_container_add(GTK_CONTAINER(hbox), submit);
  		
  			halign = gtk_alignment_new(0, 0, 5, 0);
  			gtk_container_add(GTK_CONTAINER(halign), hbox);

  			gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);			
			gtk_widget_modify_bg(submit, GTK_STATE_PRELIGHT, &cyan);
  			g_signal_connect(submit, "clicked", G_CALLBACK(submit_clicked), NULL);  
		}	
	}
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), vbox);		
	
	gtk_widget_show_all(window);		
}

static void quiz_clicked(GtkWidget *widget, gpointer data) {
	
	GtkWidget *window, *label, *vbox, *next, *hbox, *halign, *valign, *submit;
	
	window = gtk_dialog_new ();
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 1080, 720);
  	gtk_window_set_title(GTK_WINDOW(window), "MY QUIZ");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 0);
	
	
	vbox = gtk_vbox_new(0, 0);
	
	GtkWidget *scrolled_window;
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 0);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(window)->vbox), scrolled_window,TRUE, TRUE, 0);
	
	gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &orange);
	
	int quizno = GPOINTER_TO_INT(data);
	int a = 0, b = 0, p, q, sum, min, max, i, r, temp, n;
	
	for(int i = 100; i > 0; i--)
		que_quiz[i] = que_quiz[i] - que_quiz[i - 1];
	
	howmany = que_quiz[quizno];
	outof = howmany;
		
	for(a = 0; a < quizno; a++) {
		b = b + que_quiz[a];
	}
	
	int initial = b;
	final = b + que_quiz[quizno] - 1;
	
	int t;
	min = initial;
	max = final;
	
	int len = max - min + 1;
	int indexnum[len];
	for(temp = 0, i = min; temp < len; i++, temp++)
        	indexnum[temp] = i;
 
    	srand( time(NULL) );  
      	
      	for(i = len-1; i > 0; i--){
        	r = rand() % i;   
        	temp = indexnum[i];
       		indexnum[i] = indexnum[r];
        	indexnum[r] = temp;
        	
    	}
    	
    	for(i = 0; i < len; i++)
    		final_index_num[i] = indexnum[i];
    		
    	valign = gtk_alignment_new(5, 2, 0, 0);
  	gtk_container_add(GTK_CONTAINER(vbox), valign);
  		
  	hbox = gtk_hbox_new(TRUE, 3);

  	next = gtk_button_new_with_label("NEXT");
  	gtk_widget_set_size_request(next, 70, 30);
  	gtk_container_add(GTK_CONTAINER(hbox), next);
  		
  	halign = gtk_alignment_new(0, 0, 5, 0);
  	gtk_container_add(GTK_CONTAINER(halign), hbox);

  	gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);			
	gtk_widget_modify_bg(next, GTK_STATE_PRELIGHT, &cyan);
  	g_signal_connect(next, "clicked", G_CALLBACK(next_clicked), (gpointer)(0));  
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), vbox);		
	
	gtk_widget_show_all(window);

}	
    	

static void add_que_clicked(GtkWidget *widget, gpointer data) {

}

static void help_clicked(GtkWidget *widget, gpointer data) {
	
	GtkWidget *window;
	GtkWidget *label;
	GtkWidget *event_box;
		
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_title(GTK_WINDOW(window), "HOW TO PLAY");
  	gtk_window_set_default_size(GTK_WINDOW(window),1080, 720);

	event_box = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(window), event_box);
	gtk_widget_show(event_box);
  	
  	label = gtk_label_new("1)It is the moodle type quiz\n\n2)It has Graphical Interface of type  GTK ( G-NOME TOOLKIT )\n\n3)It supports to the XML type file ...All you have to run the program with a xml file which contains question bank.When xml file is given, it is parsed and corresponding questions in xml file will be displayed using GTK graphical interface...\n\n4)When user will run the program along with xml file ,he will get new window having 3 MENUS\n\n\n(i) CREATE THE QUIZ\n\n\n(ii) HELP\n\n\n(iii) EXIT\n\n5)When User will click on 'CREATE THE QUIZ' he will get new window,in it he will be shown questions in xml file. Questions are of the more than or equal to 3 types(depends on xml file) i.e.\n\n\n(i)SINGLE CORRECT - where user can select only one option as answer...\n\n\n(ii)MULTIPLE CORRECT - where user can select more than one as answer...\n\n\n(iii)TRUE FALSE type questions - where user can state whether true or false...\n\n\n(iv) NUMERICAL type questions - where user can give answer in the form of numbers...\n\n\n(i),(ii) will have more than or equal to 4 options as stated(depends on xml file)...\n\n6)User will select the questions to make quiz and add them to corresponding quiz . Then CLICK on NEXT QUIZ , user will get another question bank if and only if he attached another xml file and so on...\n\n7) After making all quizes user wll get ' FINISH MAKING QUIZes' Then On clicking it user will get ' ATTEMPT THE QUIZes ' on clicking it User will get list of QUIZes he made . Then whichever quiz user wants to play ,he can choose and play and after that user will get corresponding\n question along with choices if given and user can attempt questions.So everytime when user go on clicking 'NEXT', he will \nget next question..It has same properties like a original moodle quiz has.. In the quiz every time user will get new question along\n with shuffled options.. that is ,it has shuffling property...\n\n8) At the end one option is given i.e. SUBMIT . When user will click on that option , quiz will automatically be stopped and all the answers that user puts on will be stored in LIST in the form of data structure . Then automatically those answers will be compared with the right answers and user will be given corresponding marks for each right answers in that corresponding 	quiz .....marks are based on the defaulgrade set in xml file for each of the question...\n\n9) When User will click on 'HELP' button , he will get information about the quiz and how to play it...and there certain rules set for quiz...\n\n11) On clicking 'EXIT' user will be thrown out of the QUIZ game..\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tPRESS QUIT");
		
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_FILL);
  	gtk_container_add(GTK_CONTAINER(event_box), label);
	gtk_widget_show(label);
	gtk_widget_set_events(event_box, GDK_BUTTON_PRESS_MASK);
	gtk_signal_connect(GTK_OBJECT(event_box), "button_press_event", GTK_SIGNAL_FUNC(gtk_main_quit), window);
	gtk_widget_realize(event_box);
	gdk_window_set_cursor(event_box->window, gdk_cursor_new(GDK_HAND1));	
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  	gtk_widget_show_all(window);
		
}

static void attempt_clicked(GtkWidget *widget, gpointer data) {
	
	int tmp = GPOINTER_TO_INT(data);
	GtkWidget *window, *vbox, *quiz[tmp];
	char *label[10] = { "QUIZ 1", "QUIZ 2", "QUIZ 3", "QUIZ 4", "QUIZ 5", "QUIZ 6", "QUIZ 7", "QUIZ 8", "QUIZ 9", "QUIZ 10" };
	
	window = gtk_dialog_new ();
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window),1080, 720);
  	gtk_window_set_title(GTK_WINDOW(window), "ATTEMPT THE QUIZES ");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 0);
	
	
	vbox = gtk_vbox_new(0, 0);		
	
	GtkWidget *scrolled_window;
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 0);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(window)->vbox), scrolled_window,TRUE, TRUE, 0);
	
	
	int g = 0;
	while(g < tmp) {
		quiz[g] = gtk_button_new_with_label(label[g]);
		gtk_box_pack_start(GTK_BOX(vbox), quiz[g], 0, 0, 0);
		gtk_widget_modify_bg(quiz[g], GTK_STATE_PRELIGHT, &cyan);
  		g_signal_connect(G_OBJECT(quiz[g]), "clicked", G_CALLBACK(quiz_clicked), (gpointer)(g));
  		g++;	
	}
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), vbox);		
	
  	gtk_widget_show_all(window);
}

static void finish_clicked(GtkWidget *widget, gpointer data) {
	
	int tmp = GPOINTER_TO_INT(data);
	
	GtkWidget *window, *vbox, *attempt;
	
	window = gtk_dialog_new ();
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 1080, 720);
  	gtk_window_set_title(GTK_WINDOW(window), "QUESTION BANK");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 0);
	
	vbox = gtk_vbox_new(0, 0);		
	
	GtkWidget *scrolled_window;
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 0);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(window)->vbox), scrolled_window,TRUE, TRUE, 0);
	
	attempt = gtk_button_new_with_label("ATTEMPT THE QUIZes");
	gtk_widget_modify_bg(attempt, GTK_STATE_PRELIGHT, &cyan);
  	gtk_box_pack_start(GTK_BOX(vbox), attempt, TRUE, TRUE, 500);
	g_signal_connect(G_OBJECT(attempt), "clicked", G_CALLBACK(attempt_clicked), (gpointer)tmp);
  	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), vbox);		
	
  	gtk_widget_show_all(window);
  			
}

static void create_clicked(GtkWidget *widget, gpointer data) {
	
	GtkWidget *window, *vbox, *check[100], *add, *attempt, *next, *label, *finish, *hbox, *halign, *valign;
	
	window = gtk_dialog_new ();
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 1080, 720);
  	gtk_window_set_title(GTK_WINDOW(window), "QUESTION BANK");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 0);
	
	vbox = gtk_vbox_new(0, 0);
	
	GtkWidget *scrolled_window;
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 0);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(window)->vbox), scrolled_window,TRUE, TRUE, 0);
	
	
        int w; 
	int tmp = GPOINTER_TO_INT(data);
	int tmp2; 	
	w = start_que_no_of_quiz[tmp];
	tmp2 = start_que_no_of_quiz[tmp + 1]; 
	int size = tmp2 - w;
	
	if(w != -1 && tmp2 != -1) {
		while(w < tmp2) {
			label = gtk_label_new(type[w]);		
			gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
			gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0); 
        		check[w] = gtk_check_button_new_with_label(que[w]);
			gtk_box_pack_start(GTK_BOX(vbox), check[w], 0, 0, 0);
			g_signal_connect(check[w], "toggled", G_CALLBACK(select_que), (gpointer)w);  
			w++;
		}			
		tmp++;
		
  		valign = gtk_alignment_new(5, 2, 0, 0);
  		gtk_container_add(GTK_CONTAINER(vbox), valign);
  		
  		hbox = gtk_hbox_new(TRUE, 3);

  		add = gtk_button_new_with_label("ADD QUESTONs TO QUIZ");
  		gtk_widget_set_size_request(add, 70, 30);
  		gtk_container_add(GTK_CONTAINER(hbox), add);
  		next = gtk_button_new_with_label("NEXT QUIZ ");
  		gtk_container_add(GTK_CONTAINER(hbox), next);

  		halign = gtk_alignment_new(0, 0, 5, 0);
  		gtk_container_add(GTK_CONTAINER(halign), hbox);
		
  		gtk_box_pack_start(GTK_BOX(vbox), halign, FALSE, FALSE, 0);
  		
  		gtk_widget_modify_bg(add, GTK_STATE_PRELIGHT, &cyan);
  		gtk_widget_modify_bg(next, GTK_STATE_PRELIGHT, &cyan);
  		g_signal_connect(G_OBJECT(add), "clicked", G_CALLBACK(add_que_clicked), NULL);
  		g_signal_connect(G_OBJECT(next), "clicked", G_CALLBACK(create_clicked), (gpointer)tmp);
			
	}
	
	else {		
		finish = gtk_button_new_with_label("FINISH MAKING QUIZ");
		gtk_widget_modify_bg(finish, GTK_STATE_PRELIGHT, &cyan);
  		gtk_box_pack_start(GTK_BOX(vbox), finish, TRUE, TRUE, 500);		
		g_signal_connect(G_OBJECT(finish), "clicked", G_CALLBACK(finish_clicked), (gpointer)(tmp));
  	}
  	
  	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), vbox);		
	gtk_widget_show_all(window);
}  	
	
int main(int argc, char *argv[]) {
	
	int k = 0, j = 0;
	while(k<100) {
		que_selected[k] = -1;
		k++;
	}		
	
	k = 0;
	while(k < 100) {
		option_single_selected[k] = -1;	
		while(j < 10) {
			option_multiple_selected[j][k] = -1;
			j++;			
		}
		j = 0;
			
		no_of_opt[k] = 0;
		no_of_ans[k] = 0;							
		no_of_attempt[k] = 0;		
		nos_of_single_que[k] = -1;
		nos_of_multiple_que[k] = -1;
		nos_of_shortanswer_que[k] = -1;
		nos_of_match_que[k] = -1;
		que_quiz[k] = -1;
		nos_of_numerical_que[k] = -1;
		text[k] = NULL;
		k++;		
	}
	k = 0;
	start_que_no_of_quiz[k++] = 0;
	while(k < 100) {
		start_que_no_of_quiz[k] = -1;
		k++;
	}
		
	char *docname;
	if (argc <= 1) {
		printf(" put your xml file names to parse i.e question bank in xml format after './project'\n ");;
		printf("Usage: %s xmlfilenames\n", argv[0]);
		printf(" for e.g. : ./project questionbank.xml ...\n ");
		return 0;
	}
	
	if(!strncmp(argv[1], "-h", 2)) {
		printf(" put your xml file name to parse i.e question bank in xml format after './project'\n ");;
		printf("Usage: %s xmlfilenames\n", argv[0]);
		printf(" for e.g. : ./project questionbank.xml ...\n ");
		return 0;
	}
	k = 1;
	static int start = 0;
	
	while(k < argc) {
	
		docname = argv[k];
		xmlDocPtr doc;
		xmlNodePtr cur;
		doc = xmlParseFile(docname);
		if (doc == NULL ) {
			fprintf(stderr, "Document not parsed successfully. \n");
			return 0;
		}
			
		cur = xmlDocGetRootElement(doc);
		if (cur == NULL) {
			fprintf(stderr, "empty document\n");
			xmlFreeDoc(doc);
			return 0;
		}

		if ((xmlStrcmp(cur->name, (const xmlChar *) "quiz"))) {
			fprintf(stderr, "document of the wrong type, root node != quiz");
			xmlFreeDoc(doc);
			return 0;
		}
		 
		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"question"))) {
				parsechild (doc, cur);
			}
			cur = cur->next;
		}
		start_que_no_of_quiz[++start] = i;
		k++;
	}
	k = 0;	
	
	GtkWidget *window;
  	GtkWidget *vbox;
	GtkWidget *create;
 	GtkWidget *help;
 	GtkWidget *exit;
  
  	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 1080, 720);
  	gtk_window_set_title(GTK_WINDOW(window), "MY QUIZ");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 300);
	
  	vbox = gtk_vbox_new(0, 0);
  	gtk_container_add(GTK_CONTAINER(window), vbox);
	
      	create = gtk_button_new_with_label("CREATE A QUIZ");
  	help = gtk_button_new_with_label("HELP");
  	exit = gtk_button_new_with_label("EXIT");

  	gtk_box_pack_start(GTK_BOX(vbox), create, TRUE, TRUE, 20);
  	gtk_box_pack_start(GTK_BOX(vbox), help, TRUE, TRUE, 20);
  	gtk_box_pack_start(GTK_BOX(vbox), exit, TRUE, TRUE, 20);
	
	gtk_widget_modify_bg(create, GTK_STATE_PRELIGHT, &cyan);
	gtk_widget_modify_bg(help, GTK_STATE_PRELIGHT, &cyan);
  	gtk_widget_modify_bg(exit, GTK_STATE_PRELIGHT, &cyan);
	
  	g_signal_connect(G_OBJECT(create), "clicked", G_CALLBACK(create_clicked), (gpointer)k);
  	g_signal_connect(G_OBJECT(help), "clicked", G_CALLBACK(help_clicked), NULL);
  	g_signal_connect(G_OBJECT(exit), "clicked", G_CALLBACK(gtk_main_quit), G_OBJECT(window));
  	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  	gtk_widget_show_all(window);
  	gtk_main();
  	
  	return 0;
}

