#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
	FILE *f1, *f2, *f3, *f4;
	char label[100], code[100], operand[100];
	int mntc = 1, mdtc = 1, ala[100], i = 0, j = 0, k = 0, m = 0, counter = 0, flag = 0;
	
	f1 = fopen ("input.txt","r");
	f2 = fopen ("mnt_table.txt","w");
	f3 = fopen ("mdt_table.txt","w");
	f4 = fopen ("output_file1.txt","w");
	
	while (fscanf (f1,"%s%s%s",label,code,operand) != EOF)
	{
		if ( strcmp (code, "MACRO") == 0 )
		{	
			fscanf (f1,"%s%s%s",label,code,operand);
			fprintf (f2,"%d\t%s\t%s\t%s\t%d\n",mntc,label,code,operand,mdtc);
			fprintf (f3,"%d\t%s\t%s\t%s\n",mdtc,label,code,operand);
			mntc ++;
			mdtc ++;
			i = 0;
			j = 0;
			counter = 0;
			while ( operand[i] != '\0' )
			{
				if ( operand[i ++] == '&' )
					while (operand[i] != ',' && operand[i] != '\0')
						ala[j ++] = operand[i ++];
					ala[j ++] = ' ';
				i ++;
			}
			while ( !( strcmp (code, "MEND") == 0) )
			{
				i = 0;
				fscanf (f1,"%s%s%s",label,code,operand);
				while ( operand[i] != '\0' ) // substitue index notation from ala
				{
					if ( operand[i] == '&' )
					{
						counter = 0;
						m = i;
						flag = 0;
						++ i;
						for (k = 0; k < j; k ++)
						{
							if (ala[k] == operand[i])
							{
								flag = 1;
								i ++;
							}
							if (flag == 0)
								if (ala[k] == ' ')
									counter ++;
						}
							if (flag == 1)
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
				fprintf (f3,"%d\t%s\t%s\t%s\n",mdtc,label,code,operand);
				mdtc ++;
			}
				
		}
		else			
			fprintf (f4,"%s\t%s\t%s\n",label,code,operand);
	}
	
	fclose (f1);
	fclose (f2);
	fclose (f3);
	fclose (f4);
}
