#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *f1, *f2, *f3, *f4;
char label[100], code[100], operand[100], du_label[100], du_code[100], du_operand[100], ala2[100], ala1[100];
int mdtc = 1, mntc = 1, mdi = 0, mdlc = 0, mdtp = 0, flag = 0;

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
	
	f1 = fopen ("input5.txt","r");
	f2 = fopen ("mnt_table.txt","w+");
	f3 = fopen ("mdt_table.txt","w+");
	f4 = fopen ("output_file.txt","w+");
	
	do
	{
		READ();
		flag = 0;
		SEARCH_IN_MNT();
		if ( flag == 1 )
		{
			mdi = 1;
			PREPARE_ALA2();
			fseek(f3, 0, SEEK_SET);
			READ();
		}
		else if ( strcmp (code,"MACRO") == 0 )
		{
			mdlc ++;
			READ ();
			fseek(f2, 0, SEEK_END); 
			fseek(f3, 0, SEEK_END); 
			fprintf (f2,"%d\t%s\t%s\t%s\t%d\n",mntc,label,code,operand,mdtc);
			fprintf (f3,"%d\t%s\t%s\t%s\n",mdtc,label,code,operand);
			mdtc ++;
			mntc ++;
			len_ala1 = PREPARE_ALA1();
		//	printf ("\nala1 : %s",ala1);
			flag = 0;
			do
			{
				READ ();
				SUBSTITUTE_ALA1(len_ala1);
				
				if (flag == 1)
					flag = 0;
				fseek(f3, 0, SEEK_END);
				fprintf (f3,"%d\t%s\t%s\t%s\n",mdtc,label,code,operand);
			//	printf ("%d\t%s\t%s\t%s\tala1 : %s\n",mdtc,label,code,operand,ala1);
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
		else if ( mdi == 0 && strcmp (code,"MEND") != 0 )
			fprintf (f4,"%s\t%s\t%s\n",label,code,operand);
	}while (strcmp (code,"END") != 0 );
}

void READ ()
{
	int i, mdtc;
	if ( mdi == 0)
	{
		fscanf (f1,"%s%s%s",label,code,operand);
		return;
	}
	else
	{
			mdtp ++;
			fseek(f3, 0, SEEK_SET);
			for (i = 1; i <= mdtp; i ++)
				fscanf (f3,"%d%s%s%s",&mdtc,label,code,operand); 
			printf ("\n%d\t%s\t%s\t%s\tala2 : %s",mdtc,label,code,operand,ala2);
			SUBSTIUTE_ALA2();
		//	printf ("\n%d\t%s\t%s\t%s\tmdlc : %d",mdtc,label,code,operand,mdlc);
			if ( strcmp (code,"MEND") == 0 )
			{
				if ( mdlc == 0 )
					{
						mdi = 0;
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
	while ( operand[i] != '\0' )
	{ 
		if ( operand[i] == '#' )
		{
			k = ((int) operand[i + 1]) - 48;
			j = 0;
			while (k != 0)
			{
				if (ala2[j] == ' ')
				k = k - 1;
				j = j + 1;
			}
			while (ala2[j] != ' ')
				operand[i ++] = ala2[j ++];
			operand[i] = '\0';
		}
		else
			i ++;				
	}
	i = 0;
	while ( code[i] != '\0' )
	{ 
		if ( code[i] == '#' )
		{
			k = ((int) code[i + 1]) - 48;
			j = 0;
			while (k != 0)
			{
				if (ala2[j] == ' ')
				k = k - 1;
				j = j + 1;
			}
			while (ala2[j] != ' ')
				code[i ++] = ala2[j ++];
			code[i] = '\0';
		}
		else
			i ++;				
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
			mdtp = mdtc;
			break;
		}
	}
}

void PREPARE_ALA2 ()
{
	int i, j;
	i = j = 0;
	while ( operand[i] != '\0' )
	{ 
		ala2[j ++] = operand[i ++];
		if (operand[i] == ',')
		{
			i ++;
			ala2[j ++] = ' ';
		}
	}
	ala2[j] = ' ';
}

int PREPARE_ALA1 ()
{
	int i, j;
	i = j = 0;
	while ( operand[i] != '\0' )
	{
		if ( operand[i ++] == '&' )
			while (operand[i] != ',' && operand[i] != '\0')
				ala1[j ++] = operand[i ++];
		ala1[j ++] = ' ';
		if ( operand[i] != '\0' )
			i ++;
	}
	return j;
}

void SUBSTITUTE_ALA1 (int len_ala1)
{
	int i, k, m, counter, check;
	i = counter = k = m = 0;
	
	if (flag == 0)
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
