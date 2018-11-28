/* BST ADT for MAJOR TERM, SUBTERM, PAGES */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define TRUE 1
#define FALSE 0

//set of pages structure
typedef struct node
{
	int pageno;		//page number
	struct node* left;		//pointer to its own type pointing to left child
	struct node* right;		//pointer to its own type pointing to right child
}
PAGES;

//subterms BST structure
typedef struct subterm
{
	char term[50];		//subterm_name
	struct subterm* left;	//pointer to its own type pointing to left child
	struct subterm* right;	//pointer to its own type pointing to right child
	PAGES* spages;		//pointer pointing to pages BST

}
SUB;

//Major terms BST structure
typedef struct major
{
	char term[50];		//major_term_name
	struct major* left;		//pointer to its own type pointing to left child
	struct major* right;	//pointer to its own type pointing to right child
	SUB* msub;			//pointer pointing to subterms BST
	PAGES* mpages;		//pointer pointing to pages BST
}
MAJOR;


/*Searches for major term. Returns NULL if not found or if root is NULL
Otherwisr returns the address of node having same major_term_name (duplication) */
MAJOR* searchm(MAJOR* root, MAJOR** parent, char* m)
{  
	/* root is pointer to the root of major terms BST
	parent is a reference variable. It points to the parent of the node to be searched and is updated accordingly
	m is the string to be searched */
	MAJOR *search = NULL, *looker = root;	// search will contain the node having major_term_name m if found.
	*parent = NULL;
	if(root == NULL)	//Empty MAJOR BST
	{
		return search;
	}
	while(looker != NULL)
	{
		if(strcmp(m, looker->term) == 0)		//Match found
		{
			search = looker;		//Search is set to the node having same major_term_name and is returned
			break;
		}
		else if(strcmp(m, looker->term) < 0)		//Term to be searched comes alphabetically before the looker node
		{
			*parent = looker;
			looker = looker->left;	//Hence looker node is set to its left child
		}
		else			//Term to be searched comes alphabetically after the looker node
		{
			*parent = looker;	
			looker = looker->right;		//Hence looker node is set to its right child
		}
	}
	return search;	//If match not found, NULL is returned
}


/*Searches for subterm. Returns NULL if not found or if root is NULL.
Otherwise returns the address of node having same subterm_name (duplication) */

SUB* searchs(SUB* root, SUB** parent, char* s)
{
	/* root is pointer to the root of pages BST (pointer is part of node of major term)
	parent is a reference variable. It points to the parent of the node to be searched and is updated accordingly
	s is the string to be searched */
	SUB *search = NULL, *looker = root;	// search will contain the node having subterm_name s if found.
	*parent = NULL;
	if(root == NULL)	//Empty SUB BST
	{
		return search;
	}
	while(looker != NULL)
	{
		if(strcmp(s, looker->term) == 0)		//Match found
		{   
			search = looker;		//Search is set to the node having same subterm_name and is returned
			break;
		}
		else if(strcmp(s, looker->term) < 0)		//Term to be searched comes alphabetically before the looker node
		{
			*parent = looker;
			looker = looker->left;		//Hence looker node is set to its left child
		}
		else		//Term to be searched comes alphabetically after the looker node
		{
			*parent = looker;
			looker = looker->right;	//Hence looker node is set to its right child
		}
	}
	return search;		//If match not found, NULL is returned
}


/*Searches for page number. Returns NULL if not found or if root is NULL.
Otherwise returns the address of node having same page number (duplication)*/

PAGES* searchp(PAGES* root, PAGES** parent, int d)
{
	/* root is pointer to the root of PAGES BST (pointer can be part of node of major term or subterm)
	parent is a reference variable. It points to the parent of the node to be searched and is updated accordingly
	d is the pageno to be searched */
	PAGES *search = NULL, *looker = root; // search will contain the node having page number d if found. 
	*parent = NULL;
	if(root == NULL)	//Empty PAGES BST
	{
		return search;
	}
	while(looker != NULL)
	{
		if(looker->pageno == d)		//Match found
		{
			search = looker;			//Search is set to the node having same page number and is returned
			break;
		}
		else if(d < looker->pageno)	//Page number to be searched is less than that of the looker node
		{
			*parent = looker;
			looker = looker->left;		//Hence looker node is set to its left child
		}
		else		//Page number to be searched is greater than that of the looker node
		{
			*parent = looker;
			 looker = looker->right;		//Hence looker node is set to its right child
		}
	}
	return search;		//If match not found, NULL is returned
}


/*Inserts pages node in the pages BST.
This function is called only if node returned by searchp is NULL i.e. page number is not duplicated */ 

PAGES* insertp(PAGES** root, PAGES** parent, int d)
{
	/* root is pointer to the root of pages BST
	parent is a reference variable. It points to the parent of the node to be inserted. It is provided by searchp function 
	d is the page number to be inserted */
	PAGES *node = (PAGES*)malloc(sizeof(PAGES));	//Creating new node of type PAGES and assigning d as pageno
	node->pageno =d;
	node->left = NULL;
	node->right = NULL;

	if(*root == NULL)	//Empty PAGES BST
	{
		*root = node;
	}
	else
	{
		if(d < (*parent)->pageno )		//d is less than the page number of parent
		{
			(*parent)->left = node;		//Hence newly created node having d as pageno is inserted as left child of parent
		}
		else				//d is greater than the page number of parent
		{
			(*parent)->right = node;	//Hence newly created node having d as pageno is inserted as right child of parent
		}
	}
	return node;
}


/*Inserts subterm node in the subterm BST.
This function is called only if node returned by searchs is NULL i.e. subterm is not duplicated */

SUB* inserts(SUB** root, SUB** parent, char* s)
{
	/* root is pointer to the root of pages BST (pointer is part of node of major term)
	parent is a reference variable. It points to the parent of the node to be inserted and is provided by searchs function
	s is the string to be inserted*/
	SUB* snode = (SUB*)malloc(sizeof(SUB));		//Creating new node of type SUB and assigning s as its term
	strcpy(snode->term , s);
	snode->left = NULL;
	snode->right = NULL;
	snode->spages = NULL;

	if(*root == NULL)	//Empty SUB BST
	{
		*root = snode;
	}
	else
	{
		if(strcmp(s, (*parent)->term) < 0 )		//s comes alphabetically before the term of parent
		{
			(*parent)->left = snode;		//Hence newly created node having s as subterm_name is inserted as left child of parent
		}
		else		//s comes alphabetically after the term of parent
		{
			(*parent)->right = snode;		//Hence newly created node having s as subterm_name is inserted as right child of parent
		}
	}
	return snode;
}


/*Inserts major_term node in the major_term BST.
This function is called only if node returned by searchm is NULL i.e. major term is not duplicated */

MAJOR* insertm(MAJOR** root, MAJOR** parent, char* m)
{
	/* root is pointer to the root of major terms BST
	parent is a reference variable. It points to the parent of node to be inserted and is provided by searchm function
	m is the string to be inserted */
	MAJOR* mnode = (MAJOR*)malloc(sizeof(MAJOR));	//Creating new node of type MAJOR and assigning s as its term
	strcpy(mnode->term , m);
	mnode->left = NULL;
	mnode->right = NULL;
	mnode->msub = NULL;
	mnode->mpages = NULL;

	if(*root == NULL)		//Empty MAJOR BST
	{
		*root = mnode;
	}
	else
	{
		if(strcmp(m, (*parent)->term) < 0 )		//m comes alphabetically before the term of parent
		{
			(*parent)->left = mnode;		//Hence newly created node having m as major_term_name is inserted as left child of parent
		}
		else		//m comes alphabetically after the term of parent
		{
			(*parent)->right = mnode;		//Hence newly created node having m as major_term_name is inserted as right child of parent
		}
	}
	return mnode;
}


/* Displays page numbers for specific node
 Recursive function
 Not directly used in main. Used in displaym in the ADT */
 
void displayp(PAGES* root)
{
	if(root!= NULL)
	{
		displayp(root->left );
		printf("  %d", root->pageno);
		displayp(root->right );
	}
}


/*Displays subterms in a major term node and page numbers of subterms
Recursive function
Not directly used in main. Used in displaym in the ADT */

void displays(SUB* root)
{  
	if(root != NULL)
	{
		displays(root->left);
		printf("\n     %-40s", root->term);
		displayp(root->spages);
		displays(root->right);
	}
}


/*Displays the major terms along with subterms and page numbers and page numbers of subterm
Displays whole index. Recursive function */

void displaym( MAJOR* root)
{	
	int i;
    if(root != NULL)
	{
		displaym(root->left);
		printf("\n\n%-45s", root->term);
		displayp(root->mpages);
		displays(root->msub);
		displaym(root->right);
	}
}
