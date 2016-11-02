#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/tree.h>

static int i = 0, j = 0, k = 0, m = 0, n = 0, s = 0, single = 0, mult = 0, tf = 0, num = 0, shortans = 0, match = 0, countopt = 0, countans = 0, a = 0, b = 0;

static int que_selected[100];
static int option_single_selected[100];
static int nos_of_single_que[100];
static int nos_of_multiple_que[100];
static int nos_of_truefalse_que[100];
static int nos_of_shortanswer_que[100];
static int nos_of_match_que[100];
static int nos_of_numerical_que[100];
static int no_of_opt[100];
static int no_of_ans[100];
static int start_que_no_of_quiz[100];
static int que_quiz[100];

xmlChar *fraction;
xmlChar *defaultgrade[100];
xmlChar *penalty[100];
xmlChar *hidden[100];
xmlChar *cfeed[100];
xmlChar *pcfeed[100];
xmlChar *icfeed[100];
xmlChar *type[100];
xmlChar *que[100];
xmlChar *opt[500];  
xmlChar *ans[10][100];
xmlChar *gfeed[100];
xmlChar *name[100];
xmlChar *match_que[100];
xmlChar *match_ans[100];

void parsesubchild_multichoice (xmlDocPtr doc, xmlNodePtr cur) {
			
	if ((!xmlStrncmp(cur->name, (const xmlChar *)"name", 4))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				else {
					name[i] = tmp;
				}
			}	
			cur = cur->next;
		}	
	}					
			
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"questiontext", 8))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				else {
					que[i] = tmp;
					i++;
					countopt = 0;
					countans = 0;
					a = 0;
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"generalfeedback", 15))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				else {
					gfeed[i - 1] = tmp;
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"defaultgrade", 12))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
		else {
			defaultgrade[i - 1] = tmp;
		}		
	}			

	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"penalty", 8))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);		
		else {
			penalty[i - 1] = tmp;	
		}		
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"hidden", 6))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);		
		else {
			hidden[i - 1] = tmp;	
		}		
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"single", 5))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
		else {
			if ((!xmlStrncmp(tmp, (const xmlChar *)"true", 4))) {
				nos_of_single_que[single] = i - 1;
				single++;
			}
		
			else if ((!xmlStrncmp(tmp, (const xmlChar *)"false", 5))) {
				nos_of_multiple_que[mult] = i - 1;
				mult++;
			}
				
		}			
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"shuffleanswer", 13))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
		else
			printf("%d\t%s\n", i - 1, tmp);
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"answernumbering", 12))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else
			printf("%d\t%s\n", i - 1, tmp);
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"correctfeedback", 15))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				else {
					cfeed[i - 1] = tmp;	
				}		
			}			
			cur = cur->next;
		}
	}
				
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"partiallycorrectfeedback", 24))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					pcfeed[i - 1] = tmp;	
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"incorrectfeedback", 24))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					icfeed[i - 1] = tmp;
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"answer", 15))) {
		fraction = xmlGetProp(cur, "fraction");
		
		if((!xmlStrncmp(fraction, (const xmlChar *)"0", 1))) {
			cur = cur->xmlChildrenNode;
			while(cur != NULL) {	
				if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
					xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					if(tmp == NULL);
					else {
						opt[k] = tmp;
						k++;
						countopt++;
						no_of_opt[i - 1] = countopt;
					}		
				}					
				cur = cur->next;
			}	
		}	
	
		else {	
			cur = cur->xmlChildrenNode;
			while(cur != NULL) {	
				if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
					xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					if(tmp == NULL);
					else {
						opt[k] = tmp;
						k++;
						countopt++;
						ans[a][i - 1] = tmp;
						a++;
						countans++;					
						no_of_opt[i - 1] = countopt;
						no_of_ans[i - 1] = countans;	
					}		
				}					
				cur = cur->next;
			}	
		}	
	}		
}

void parsesubchild_truefalse (xmlDocPtr doc, xmlNodePtr cur) {
	
	if ((!xmlStrncmp(cur->name, (const xmlChar *)"name", 4))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				else {
					name[i] = tmp;	
				}
			}	
			cur = cur->next;
		}	
	}					
			
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"question", 8))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					que[i] = tmp;
					i++;
					nos_of_truefalse_que[tf] = i - 1;
					tf++;
					countopt = 0;
					countans = 0;
					a = 0;
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"generalfeedback", 15))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				else {
					gfeed[i - 1] = tmp;	
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"defaultgrade", 12))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			defaultgrade[i - 1] = tmp;	
		}		
	}			

	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"penalty", 8))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			penalty[i - 1] = tmp;	
		}		
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"hidden", 6))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			hidden[i-1] = tmp;	
		}		
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"answer", 15))) {
		fraction = xmlGetProp(cur, "fraction");
		
		if((!xmlStrncmp(fraction, (const xmlChar *)"0", 1))) {
			cur = cur->xmlChildrenNode;
			while(cur != NULL) {	
				if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
					xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					if(tmp == NULL);
					else {
						opt[k] = tmp;
						k++;
						countopt++;
						no_of_opt[i - 1] = countopt;
					}		
				}					
				cur = cur->next;
			}	
		}	
	
		else {	
			cur = cur->xmlChildrenNode;
			while(cur != NULL) {	
				if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
					xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					if(tmp == NULL);
					else {
						opt[k] = tmp;
						k++;
						countopt++;
						ans[a][i - 1] = tmp;
						a++;
						countans++;					
						no_of_opt[i - 1] = countopt;
						no_of_ans[i - 1] = countans;	
					}		
				}					
				cur = cur->next;
			}	
		}	
	}		
}

void parsesubchild_matching (xmlDocPtr doc, xmlNodePtr cur) {
	
	if ((!xmlStrncmp(cur->name, (const xmlChar *)"name", 4))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				else {
					name[i] = tmp;	
				}
			}	
			cur = cur->next;
		}	
	}					
			
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"questiontext", 8))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					que[i] = tmp;
					i++;
					nos_of_match_que[match] = i - 1;
					match++;
					countopt = 0;
					countans = 0;
					a = 0;
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"generalfeedback", 15))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					gfeed[i - 1] = tmp;	
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"defaultgrade", 12))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			defaultgrade[i - 1] = tmp;	
		}		
	}			

	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"penalty", 8))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			penalty[i - 1] = tmp;	
		}		
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"hidden", 6))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			hidden[i - 1] = tmp;	
		}		
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"correctfeedback", 15))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					cfeed[i - 1] = tmp;	
				}		
			}			
			cur = cur->next;
		}
	}
				
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"partiallycorrectfeedback", 24))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					pcfeed[i - 1] = tmp;	
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"incorrectfeedback", 24))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					icfeed[i - 1] = tmp;	
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"subquestion", 11))) {
		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				else {	
					match_que[m - 1] = tmp;
					m++;
				}
			}
					
			else if ((!xmlStrncmp(cur->name, (const xmlChar *)"answer", 6))) {
				cur = cur->xmlChildrenNode;
				while(cur != NULL) {	
					if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
						xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
						if(tmp == NULL);
						else {
							match_ans[m - 2] = tmp;
						}		
					}			
					cur = cur->next;
				}			
			}
			cur=cur->next;
		}		
	}
	
}



void parsesubchild_numerical (xmlDocPtr doc, xmlNodePtr cur) {
	
	if ((!xmlStrncmp(cur->name, (const xmlChar *)"name", 4))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				else {
					name[i] = tmp;	
				}
			}	
			cur = cur->next;
		}	
	}					
			
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"question", 8))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					que[i] = tmp;
					i++;
					nos_of_numerical_que[num] = i - 1;
					num++;
					countopt = 0;
					countans = 0;
					a = 0;
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"generalfeedback", 15))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					gfeed[i - 1] = tmp;	
				}		
			}			
			cur = cur->next;
		
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"defaultgrade", 12))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			defaultgrade[i - 1] = tmp;	
		}		
	}			

	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"penalty", 8))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			penalty[i - 1] = tmp;	
		}		
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"hidden", 6))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			hidden[i-1] = tmp;	
		}		
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"answer", 15))) {
		fraction = xmlGetProp(cur, "fraction");
		if((!xmlStrncmp(fraction, (const xmlChar *)"0", 1))) {
			cur = cur->xmlChildrenNode;
			while(cur != NULL) {	
				if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
					xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					if(tmp == NULL);
					else {
						opt[k] = tmp;
						k++;
						countopt++;
						no_of_opt[i - 1] = countopt;
					}		
				}					
				cur = cur->next;
			}	
		}	
	
		else {	
			cur = cur->xmlChildrenNode;
			while(cur != NULL) {	
				if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
					xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					if(tmp == NULL);
					else {
						opt[k] = tmp;
						k++;
						countopt++;
						ans[a][i-1] = tmp;
						a++;
						countans++;					
						no_of_opt[i - 1] = countopt;
						no_of_ans[i - 1] = countans;	
					}		
				}					
				cur = cur->next;
			}	
		}	
		
	}
	
}

void parsesubchild_shortanswer (xmlDocPtr doc, xmlNodePtr cur) {
	
	if ((!xmlStrncmp(cur->name, (const xmlChar *)"name", 4))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				else {
					name[i] = tmp;	
				}
			}	
			cur = cur->next;
		}	
	}					
			
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"question", 8))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					que[i] = tmp;
					i++;
					nos_of_shortanswer_que[shortans] = i - 1;
					shortans++;
					countopt = 0;
					countans = 0;
					a = 0;
				}		
			}			
			cur = cur->next;
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"generalfeedback", 15))) {
		cur = cur->xmlChildrenNode;
		while(cur != NULL) {	
			if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
				xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				if(tmp == NULL);
				
				else {
					gfeed[i - 1] = tmp;	
				}		
			}			
			cur = cur->next;
		
		}
	}
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"defaultgrade", 12))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			defaultgrade[i - 1] = tmp;	
		}		
	}			

	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"penalty", 8))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			penalty[i - 1] = tmp;	
		}		
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"hidden", 6))) {
		xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		if(tmp == NULL);
				
		else {
			hidden[i - 1] = tmp;	
		}		
	}			
	
	else if ((!xmlStrncmp(cur->name, (const xmlChar *)"answer", 15))) {
		fraction = xmlGetProp(cur, "fraction");
		if((!xmlStrncmp(fraction, (const xmlChar *)"100", 3))) {
			cur = cur->xmlChildrenNode;
			while(cur != NULL) {	
				if ((!xmlStrncmp(cur->name, (const xmlChar *)"text", 4))) {
					xmlChar *tmp = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					if(tmp == NULL);
					else {
						ans[a][i - 1] = tmp;
						a++;
						countans++;					
						no_of_ans[i - 1] = countans;	
					}		
				}					
				cur = cur->next;
			}	
		}	
	}
}

void parsechild (xmlDocPtr doc, xmlNodePtr cur) {
	 type[i] = xmlGetProp(cur, "type");
	if((!xmlStrncmp(type[i], (const xmlChar *)"multichoice", 11))) {
		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			parsesubchild_multichoice (doc, cur);
			cur = cur->next;
		}		
	}	
	
	else if((!xmlStrncmp(type[i], (const xmlChar *)"truefalse", 11))) {
		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			parsesubchild_truefalse (doc, cur);
			cur = cur->next;
		}		
	}	
	
	else if((!xmlStrncmp(type[i], (const xmlChar *)"matching", 11))) {
		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			parsesubchild_matching (doc, cur);
			cur = cur->next;
		}		
	}	
		
	else if((!xmlStrncmp(type[i], (const xmlChar *)"numerical", 11))) {
		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			parsesubchild_numerical (doc, cur);
			cur = cur->next;
		}		
	}	
	
	else if((!xmlStrncmp(type[i], (const xmlChar *)"shortanswer", 11))) {
		cur = cur->xmlChildrenNode;
		while (cur != NULL) {
			parsesubchild_shortanswer (doc, cur);
			cur = cur->next;
		}		
	}

}

