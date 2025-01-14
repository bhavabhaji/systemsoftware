#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *f1, *f2, *f3, *f4;
char label[100], code[100], operand[100], du_label[100], du_code[100], du_operand[100], ala2[100], ala1[100], temp[100];
int mdtc = 1, mntc = 1, mdlc = 0, mdtp = 0, flag = 0, n = 0, t;

typedef struct stack 
{
	char data[100];
	int sp;
}stack;

stack s;



void READ ();
void SUBSTIUTE_ALA2 ();
void SEARCH_IN_MNT ();
void PREPARE_ALA2 ();
int PREPARE_ALA1 ();
void SUBSTITUTE_ALA1 (int len_ala1);

void main()
{
	int len_ala1 = 0;
	//mntc = mdtc = 1;
	//mdi = mdlc = 0;
	s.sp = -1;
	f1 = fopen ("input7.txt","r");
	f2 = fopen ("mnt_table.txt","w+");
	f3 = fopen ("mdt_table.txt","w+");
	f4 = fopen ("output_file.txt","w+");
	
	do
	{
		label1: READ();
		flag = 0;
		SEARCH_IN_MNT();
		printf ("\nOut from search MNT with flag = %d",flag);
		if ( flag == 1 )
		{
			printf ("\nflag = 1");
			s.data[s.sp + n + 2] = s.sp;
			s.sp = s.sp + n + 2;
			s.data[s.sp + 1] = mdtp;
			PREPARE_ALA2();
			fseek(f3, 0, SEEK_SET);
			READ();
			
			
			
		}
		else if ( strcmp (code,"MACRO") == 0 )
		{
			printf ("\nIt is Macro");
			mdlc ++;
			READ ();
			flag = 0;
			SEARCH_IN_MNT();
			if (flag == 1)
			{
				printf ("\nIt is MNT 2");
				while ( strcmp (code,"MEND") != 0 )
					READ ();
				printf ("\nouter code = %s",code);
				mdlc --;
				printf ("\nmdlc = %d",mdlc);
				if (mdlc == 0)
				{
					n = s.sp - 2 - s.data[s.sp];
					s.sp = s.data[s.sp];
					
					
				}
				goto label1;
			}
			printf ("\nOuter MNT Search LOOP");
			fseek(f2, 0, SEEK_END); 
			fseek(f3, 0, SEEK_END);
			fprintf (f2,"%d\t%s\t%s\t%s\t%d\n",mntc,label,code,operand,mdtc);
			fprintf (f3,"%d\t%s\t%s\t%s\n",mdtc,label,code,operand);
			mdtc ++;
			mntc ++;
			len_ala1 = PREPARE_ALA1();
			printf ("\nlen_ala1 = %d",len_ala1);
			flag = 0;
			do
			{
				READ ();
				SUBSTITUTE_ALA1(len_ala1);
				
				if (flag == 1)
					flag = 0;
				fseek(f3, 0, SEEK_END);
				fprintf (f3,"%d\t%s\t%s\t%s\n",mdtc,label,code,operand);
				mdtc ++;
				if ( strcmp (code,"MACRO") == 0 )
				{
					mdlc ++;
					flag = 1;
				}
				else if ( strcmp (code,"MEND") == 0 )
					mdlc --;
			}while ( strcmp (code,"MACRO") == 0 || mdlc != 0 );
		}
		else if ( s.sp == -1 && strcmp (code,"MEND") != 0 )
		{
			printf ("%s\t%s\t%s\n",label,code,operand);
			fprintf (f4,"Hi\n");
			fprintf (f4,"%s\t%s\t%s\n",label,code,operand);
			printf("\nelse");
		}
		printf ("\nLoop one end");
	}while (strcmp (code,"END") != 0 );
}

void READ ()
{
	int i, mdtc;
	if ( s.sp == -1 )
	{
		fscanf (f1,"%s%s%s",label,code,operand);
		return;
	}
	else
	{
		    t = s.data[s.sp + 1] + 1;
			s.data[s.sp + 1] = t;
			
			
			fseek(f3, 0, SEEK_SET);
			for (i = 1; i <= t; i ++)
				fscanf (f3,"%d%s%s%s",&mdtc,label,code,operand); 
			SUBSTIUTE_ALA2();
			if ( strcmp (code,"MEND") == 0 )
			{
				if ( mdlc == 0 )
					{
						t = s.data[s.sp];
						n = s.sp - 2 - t;
						s.sp = t;
						
						return;
					}
				else
					return;
			}
			if ( strcmp (code,"MACRO") != 0  && mdlc == 0 )
				fprintf (f4,"%s\t%s\t%s\n",label,code,operand); 
	}
}

void SUBSTIUTE_ALA2 ()
{
	int i, j, k;
	i = 0; 
	if ( mdlc == 0 )
	{
		while ( operand[i] != '\0' )
		{ 
			if ( operand[i] == '#' )
			{
				k = ((int) operand[i + 1]) - 48;
				k = k + 1;
				operand[i ++] = s.data[s.sp + k + 1];
				operand[i] = '\0';
				
				
			}
			else
				i ++;				
		}
	}
	else
	{
		i = 0;
		while ( code[i] != '\0' )
		{ 
			if ( code[i] == '#' )
			{
				k = ((int) code[i + 1]) - 48;
				k = k + 1;
				code[i ++] = s.data[s.sp + k + 1];
				code[i] = '\0';
			}
			else
				i ++;				
		}
	}
}

void SEARCH_IN_MNT ()
{
	int mntc, mdtc, i;
	fseek(f2, 0, SEEK_SET);
	while (fscanf (f2,"%d%s%s%s%d",&mntc,du_label,du_code,du_operand,&mdtc) != EOF) 
	{
		
		if ( strcmp (code,du_code) == 0)
		{
			flag = 1;
			if (s.sp == -1)
				mdtp = mdtc;
			break;
		}
	}
}

void PREPARE_ALA2 ()
{
	int i;
	i = 0;
	n = n + 1;
	while ( operand[i] != '\0' )
	{ 
		s.data[s.sp + n + 1] = operand[i ++];
		n ++;
		
		if (operand[i] == ',')
			i ++;
	}
}

int PREPARE_ALA1 ()
{
	int i, j, k;
	i = j = k = 0;
	printf("\n%s",operand);
	while ( operand[i] != '\0' )
	{
		if ( operand[i ++] == '&' )
		{
			while (operand[i] != ',' && operand[i] != '\0')
				ala1[j ++] = operand[i ++];
			k ++;
		}
		
		if ( operand[i] != '\0' )
			i ++;
		printf("\nPrepare ALA1");
	}
	printf("\nj = %d",j);
	for (i = 0; i < j; i ++)
		printf("\nHi\t%s",operand[i]);
	return j;
}

void SUBSTITUTE_ALA1 (int len_ala1)
{
	int i, k, m, counter, check;
	i = counter = k = m = 0;
	
	if ( flag == 0 && mdlc == 1 )
	{
		while ( operand[i] != '\0' ) 			// substitue index notation from ala
		{
			if ( operand[i] == '&' )
			{
				counter = 0;
				m = i;
				check = 0;
				++ i;
				for (k = 0; k < len_ala1; k ++)
				{
					if (ala1[k] == operand[i])
					{
						check = 1;
						i ++;
					}
					if (check == 0)
							if (ala1[k] == ' ')
									counter ++;
				}
				if (check == 1)
				{
					operand[m] = '#';
					operand[++ m] = ( (char) counter ) + 48;
					operand[++ m] ='\0';
					i = m;
				}
			}
			else
				i ++;
		}
	}
	else
	{
		while ( code[i] != '\0' ) 			// substitue index notation from ala
		{
			if ( code[i] == '&' )
			{
				counter = 0;
				m = i;
				check = 0;
				++ i;
				for (k = 0; k < len_ala1; k ++)
				{
					if (ala1[k] == code[i])
					{
						check = 1;
						i ++;
					}
					if (check == 0)
							if (ala1[k] == ' ')
									counter ++;
				}
				if (check == 1)
				{
					code[m] = '#';
					code[++ m] = ( (char) counter ) + 48;
					code[++ m] ='\0';
					i = m;
				}
			}
			else
				i ++;
		}
	}
}
