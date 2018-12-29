//Kishan Patel (NetID: kp661) & Niharika Mishra (NetID: nm729)
//January 30, 2018
//Assignment 0: String Sorting

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node { //BST structure
	char* pword;
	int occ; //Occurrence counter for duplicates
	struct Node* right;
	struct Node* left;
}Node;

Node* root; //Top node or root of BST (global variable)

void insert(Node* n); //Inserts new nodes containing tockenized words in BST
int compare(char* s0, char* s1); //Compares 2 strings and returns the one with higher precedence
int iscap(char c); //Checks to see if char is capital alphabetic
void print(Node* root); //Prints BST to console in reverse inorder: right -> middle -> left
void freemem(Node* root); //Frees up memory used for BST in reverse postorder -> right -> left -> middle

int main(int argc, char* argv[])
{
	if (argc > 2) { //Checks for invalid inputs, that is anything more than a single string
		printf("Error! Too many parameters.\n");
		return 0;
	}
	else if(argc == 1){ //Prints nothing when there's no input
		printf("No input read!\n");
		return 0;
	}
	
	int len = strlen(argv[1]); //Length of input string
	int wordlen = 0; //Initial word length
	char* pstr = argv[1]; //Pointer to input string
	int i;

	for (i = 0; i < len; i++) { //Loops through length of input string
		if (isalpha(pstr[i])) {
			wordlen++; //Word length is incremented for every alphabetic char
		}
		if (!isalpha(pstr[i]) || i == len - 1) { //Tokenizes word when separator is reached; that is any non-alpha char
			if (wordlen > 0) {
				if(i == len - 1){ //i is incremented for the last word
					i++;
				}
				char* pword = (char*)malloc(wordlen+1);
				memcpy(pword, &pstr[i - wordlen], wordlen); //Word is copied from input string into pword
				pword[wordlen] = '\0'; //Adds "end" to end of word
				Node* n = (Node*)malloc(sizeof(Node)); //Memory is allocated for the Node to be inserted into BST
				n->pword = pword;
				n->occ = 1; //Default value of occurences is set to 1
				n->left = NULL;
				n->right = NULL;
				insert(n); //Adds Node to correct position in BST
			}
			wordlen = 0;
		}
	}

	Node* temp = root;

	printf("\nSorted list in descending order:\n");
	print(temp); //BST is printed in desired order

	if(temp != NULL){
		freemem(root); //Memory allocated for BST is freed
	}

	return 0;
}

void insert(Node* n) {
	if (root == NULL) { //Inserts root of BST
		root = n;
		return;
	}
	Node* temp = root;
	int c;
	while (1) { //Traverses BST until Node is inserted; All inserted Nodes are children
		c = compare(temp->pword, n->pword);
		if (c == 0) { //If compare returns 0, go left
			if (temp->left != NULL) {
				temp = temp->left;
			}
			else {
				temp->left = n;
				return;
			}
		}
		else if (c == 1) { //If compare returns 1, go right
			if (temp->right != NULL) {
				temp = temp->right;
			}
			else {
				temp->right = n;
				return;
			}
		}
		else if (c == 2) { //If compare returns 2, word is a duplicate; increment occurrence
			(temp->occ)++;
			return;
		}
	}
}

int compare(char* s0, char* s1) { //Return 0 if string0 is greater, 1 if string1 is greater, 2 if same
	int l = 0;
	int s0len = (int)strlen(s0);
	int s1len = (int)strlen(s1);
	if (s0len >= s1len) {
		l = s0len;
	}
	else {
		l = s1len;
	}
	int i;
	for (i = 0; i < l; i++) { //Loops through the longest string length amount of times
		if (s0len > i && s1len > i) { //Current index is < longest string length
			if (iscap(s0[i]) && iscap(s1[i])) { //String containing capital letter with greater ascii value precedes and is returned
				if (s0[i] > s1[i]) {
					return 0;
				}
				else if (s0[i] < s1[i]) {
					return 1;
				}
			}
			else if (!iscap(s0[i]) && iscap(s1[i])) { //Capital letters precede over lower case
				return 1;
			}
			else if (iscap(s0[i]) && !iscap(s1[i])) {
				return 0;
			}
			else { //String containing lower case letter with lower ascii value precedes and is returned
				if (s0[i] < s1[i]) {
					return 0;
				}
				else if (s0[i] > s1[i]) {
					return 1;
				}
			}
		}
		else if (s0len <= i && s1len > i) { //Shorter string is prefix of larger string, therefore the shorter string is returned
			return 0;
		}
		else if (s0len > i && s1len <= i) {
			return 1;
		}
	}
	return 2; //Identical strings
}

int iscap(char c) {
	if (c >= 65 && c <= 90) { //Returns true or 1 if char c is a capital letter
		return 1;
	}
	else { //Returns false or 0 if char c is not a capital letter
		return 0;
	}
}

void print(Node* root) {
	if (root == NULL) { //Base case
		return;
	}
	print(root->right); //Recursively builds a queue stack calling the function print
	int i;
	for (i = 0; i < root->occ; i++) { //Prints the word contained in the current node based on the number of occurrences
		printf("%s\n", root->pword);
	}
	print(root->left);
}

void freemem(Node* root) {
	if (root == NULL) { //Base case
		return;
	}
	freemem(root->right); //Recursively builds a queue stack calling the function freemem
	freemem(root->left);
	free(root->pword); //Frees the memory of the string for the current node
	free(root); //Frees the memory of the current node
}
