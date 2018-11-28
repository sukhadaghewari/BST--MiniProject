/*  Data Structures: MINI PROJECT
	Project Statement: Build a data structure that stores the index of a book and display the index alphabetically 
					   with ascending list of page numbers.
	Based On: Binary Search Tree
	Pair No: 54
	
	Project by:
    1.Kirti Bhaskarrao Deshmukh
	Batch: S-1
	PRN No: 2015BCS009
	
	2.Sukhada Vijay Ghewari
	Batch: S-2
	PRN No: 2015BCS016
	
	Guidance:
	Dr. S. H. Bhandari Madam
*/
#include"project_ADT.h"
int main()
{
	char ch, ch1, term[50];
	//m=major terms, p=pages, s=subterms, n=no of pages
	//Initializing all the pointers to 'NULL'
	int n,i, pageno,opt, flag =0;
	MAJOR *mroot = NULL, *mparent = NULL, *msearch = NULL;
	SUB *sparent = NULL, *ssearch = NULL;
	PAGES *pparent = NULL, *psearch = NULL;
	FILE* fp;
	printf("Assumption: A subterm cannot be a major term\n\n");
	printf("Index of the book is created with inputs taken from file\n");
	fp = fopen("HCVerma.txt","a+");
	
	if(!fp)  //If the file can't be opened, it returns 'NULL'
	{
		printf("Unable to open\n");
		exit(0);
    }
    /*In file as well as for dynamic input, we have input in the form
    m major_term/sub_term
    n list_of_pagenos */
    
    fscanf(fp,"%c ",&ch);
    ch = tolower(ch);	//As input can be in both capital & small letters. 
						//For uniformity in the output and in comparison, use of tolower() 
	while(1)
	{
	   while(ch == 'm')
	   {
			fscanf(fp,"%[^\n]s", term);		//To scan major_term_name with spaces
			fscanf(fp,"%d ", &n);
			for(i=0;i<strlen(term);i++)
			{
				term[i]= tolower(term[i]);
			}
			//Returns the address of node with same major_term_name(duplication). If no duplication, returns 'NULL'
			msearch=searchm(mroot, &mparent, term);		
			
			if(msearch==NULL)	//'NULL' indicates that the major_term is occuring first time
			{	
				//If new major_term is encountered. Returns address of the inserted major_term node	
				msearch =insertm(&mroot, &mparent, term);	
			}
			for(i =0; i<n; i++)
			{
				fscanf(fp,"%d ",&pageno);	//To scan each pageno from file
				if(pageno > 0)		//Page nos with negative values are discarded
				{
					//Returns the address of node with same page number(duplication). If no duplication, returns 'NULL'
					psearch = searchp((msearch)->mpages, &pparent, pageno);	
						
					//Avoids duplication of pages
					if(psearch == NULL)		//'NULL' indicates that the pageno is occuring first time
					{ 	
						//If new pageno is encountered. Returns address of the inserted pageno node
						psearch =insertp(&(msearch)->mpages, &pparent, pageno);		
					}
				}
			}
			fscanf(fp,"%c ",&ch);
			ch = tolower(ch);
			while(1)
			{
				while(ch=='s')
			   	{
			    	fscanf(fp,"%[^\n]s",term); //Scans subterm_name with spaces
			    	fscanf(fp,"%d ", &n);
			    	for(i=0;i<strlen(term);i++)
					{
						term[i]= tolower(term[i]);
					}
					//Returns the address of node with same subterm_name(duplication). If no duplication, returns 'NULL'
					ssearch=searchs(msearch->msub, &sparent, term);	
						
		           	if(ssearch==NULL)		//'NULL' indicates that the subterm is occuring first time
			       	{
				       	//If new subterm is encountered. Returns address of the inserted subterm node
						ssearch =inserts(&(msearch->msub), &sparent, term);
					}
				    for(i =0;i<n;i++)
			        {
						fscanf(fp,"%d ",&pageno);	
						if(pageno > 0)		//Discards negative page nos.
						{	
							//Returns the address of node with same page number(duplication). If no duplication, returns 'NULL'
							psearch = searchp(ssearch->spages, &pparent, pageno);		
							//Avoids duplication of pages
					
							if(psearch == NULL)			//'NULL' indicates that the pageno is occuring first time
							{
								//If new pageno is encountered. Returns address of the inserted pageno node
								psearch =insertp(&(ssearch)->spages, &pparent, pageno);
							}
						}
					}
					fscanf(fp,"%c ",&ch);
					ch = tolower(ch);
					if(feof(fp))
						break;
				}
				if(feof(fp))
					break;
				if(ch !='m')	//Invalid input
				{  
			 		printf("\nWrong input for this line:");
					fscanf(fp,"%[^\n]s",term);
			    	fscanf(fp,"%d ", &n);	
			    	//Prints invalid input
					printf(" %c %s %d",ch,term,n);
					for(i=0;i<n;i++)
					{
						fscanf(fp,"%d ", &pageno);
						printf(" %d",pageno);
					}
					fscanf(fp,"%c ",&ch);	
					ch =tolower(ch); 
	    		}
	    		if(ch == 'm')	//Go back to main loop
						break;
			}
			if(feof(fp))
				break;
		}
		if(feof(fp))		//To terminate loop
		{   
			printf("\n\n           *************** INDEX ***************");
			displaym(mroot);
			printf("\n\nDo you want to modify this index (y/n): ");
			scanf("%c",&ch);
			if(ch=='n')
				exit(0);
			printf("Enter the input as the form below:\n(s/m) MAJOR/SUBTERM\nn(no of pages) list_of_pagenos\nEnter 'z' when you are done inserting all the terms\n");
			fflush(stdin);   //dynamic input
			scanf("%c%*c",&ch);
			ch = tolower(ch);
		
			while(1)		//same code as before, only difference is we are taking input dynamically instead of file.
			{				//use of scanf instead of fscanf
	   			while(ch == 'm')
	   			{
	   				fprintf(fp,"\n%c ",ch);
					scanf("%[^\n]s", term);		//To scan major_term_name with spaces
					if(term[strlen(term)-1]==' ')
						term[strlen(term)-1]='\0';
					fprintf(fp,"%s",term);
					for(i =0;i<strlen(term);i++)
					{
						term[i]=tolower(term[i]);
					}
					scanf("%d",&n);
					fprintf(fp,"\n%d",n);
					//Returns the address of node with same major_term_name(duplication). If no duplication, returns 'NULL'
					msearch=searchm(mroot, &mparent, term);
					
					//Avoids duplication
					if(msearch==NULL)		//'NULL' indicates that the major_term is occuring first time
					{  
						//If new major_term is encountered. Returns address of the inserted major_term node	
						msearch =insertm(&mroot, &mparent, term);
					}
					for(i=0; i<n; i++)
				 	{   
						scanf("%d",&pageno);
						fprintf(fp," %d",pageno);
						if(pageno > 0)		//Discards negative pageno
						{
							//Returns the address of node with same page number(duplication). If no duplication, returns 'NULL'
							psearch = searchp(msearch->mpages, &pparent, pageno);
							if(psearch == NULL)		//'NULL' indicates that the pageno is occuring first time
							{
								//If new pageno is encountered. Returns address of the inserted pageno node
								psearch =insertp(&(msearch)->mpages, &pparent, pageno);
							}
						}
					}
					fflush(stdin);
					scanf("%c%*c",&ch);
					ch =tolower(ch);
					while(1)
					{
						while(ch=='s')
						{
							fprintf(fp,"\n%c ",ch);
							scanf("%[^\n]s ",term);
							if(term[strlen(term)-1]==' ')
								term[strlen(term)-1]='\0';
							fprintf(fp,"%s",term);
							for(i =0;i<strlen(term);i++)
							{
								term[i]=tolower(term[i]);
							}		
							scanf("%d",&n);
							fprintf(fp,"\n%d",n);
							//Returns the address of node with same subterm_name(duplication). If no duplication, returns 'NULL'
							ssearch=searchs(msearch->msub, &sparent, term);
		        			if(ssearch==NULL)	//Subterm is occuring first time
			    			{ 
				   				//If new subterm is encountered. Returns address of the inserted subterm node
								ssearch =inserts(&(msearch->msub), &sparent, term);
							}		
				    		for(i =0;i<n;i++)
			        		{
								scanf("%d",&pageno);
								fprintf(fp," %d",pageno);
								if(pageno > 0)		//Discards negative pageno
								{
									//Returns the address of node with same page number(duplication). If no duplication, returns 'NULL'
									psearch = searchp(ssearch->spages, &pparent, pageno);
										
									if(psearch == NULL)		//'NULL' indicates that the pageno is occuring first time
									{
											//If new pageno is encountered. Returns address of the inserted pageno node
											psearch =insertp(&(ssearch)->spages, &pparent, pageno);
									}
								}
							}			
							fflush(stdin);
							scanf("%c%*c",&ch);
							ch = tolower(ch);
						}
						if(ch == 'z')		//To terminate loop
						{
							printf("\n\n           *************** INDEX ***************");
							displaym(mroot);
							exit(0);
						}
						else if( ch !='m')		//Invalid input
						{
							printf("Wrong input\n");
							fflush(stdin);
							scanf("%c%*c",&ch);
							ch =tolower(ch);
						}
						if(ch == 'm')
							break;	
			    	}
				}
				if(ch == 's')	//First time, user MUST give major term
				{
					printf("Please enter the major term first!\n");
					fflush(stdin);
					scanf("%c%*c",&ch);
					ch = tolower(ch);
				}
				else if(ch == 'z')		//To terminate loop
				{
					printf("\n\n           *************** INDEX ***************");
					displaym(mroot);
					exit(0);
				} 
				else if(ch != 'm')		//Invalid input
				{
					printf("Wrong input\n");
					fflush(stdin);
					scanf("%c%*c",&ch);
					ch =tolower(ch);
				}
		    }
		}
		else if(ch == 's')	//For the first time, user MUST give major_term
		{
			printf("\nCan't have subterm without major term:");
			fscanf(fp,"%[^\n]s",term);
        	fscanf(fp,"%d ", &n);
        	//Prints invalid input
			printf("%c %s %d",ch,term, n);
			for(i=0;i<n;i++)
			{
				fscanf(fp,"%d ", &pageno);
				printf(" %d", pageno);
			}
			fscanf(fp,"%c ",&ch);	
			ch =tolower(ch);
		}
		else if(ch != 'm')	//Invalid input
		{
			printf("Wrong input for this line:");
			fscanf(fp,"%[^\n]s",term);
        	fscanf(fp,"%d ", &n);
        	//Prints invalid input
			printf("%c %s %d",ch,term, n);
			for(i=0;i<n;i++)
			{
				fscanf(fp,"%d ", &pageno);
				printf(" %d", pageno);
			}
			fscanf(fp,"%c ",&ch);	
			ch =tolower(ch);
		}
	}
	fclose(fp);	//closing file 
	return 0;
}

