#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void READ();

	FILE *f1, *f2, *f3, *f4;
	char label[100], code[100], operand[100], du_label[100], du_code[100], du_operand[100], ala2[100];
	int mdtc = 1, mntc = 1, mdi = 0, mdlc = 0, flag = 0, i = 0, j = 0, ala1[100], mdtp = 0, k = 0, m = 0, counter = 0;

void main()
{
	f1 = fopen ("input.txt","r");
	f2 = fopen ("mnt_table.txt","w");
	f3 = fopen ("mdt_table.txt","w");
	f4 = fopen ("output_file1.txt","w");
	
	while ( fscanf (f1,"%s%s%s",label,code,operand) != EOF )
	{
		label2: READ();
		while (fscanf (f2,"%d%s%s%s%d",&mntc,du_label,du_code,du_operand,&mdtc) != EOF) // searching in mnt_table for match
			if ( strcmp (code,du_code) == 0)
			{
				flag = 1; // it's a match !
				mdtp = mdtc;
				break;
			}
			if (flag == 0)
			{
				if ( strcmp (code,"MACRO") == 0 )
				{
					READ();
					fprintf (f2,"%d\t%s\t%s\t%s\t%d\n",mntc,label,code,operand,mdtc);
					fprintf (f3,"%d\t%s\t%s\t%s\n",mdtc,label,code,operand);
					mdtc ++;
					mntc ++;
					i = 0;
					j = 0;
					while ( operand[i] != '\0' )
					{
						if ( operand[i ++] == '&' )
							while (operand[i] != ',' && operand[i] != '\0')
								ala1[j ++] = operand[i ++];
						ala1[j ++] = ' ';
						i ++;
					}
					mdlc ++;
				label1:	READ();
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
									if (ala1[k] == operand[i])
									{
										flag = 1;
										i ++;
									}
									if (flag == 0)
										if (ala1[k] == ' ')
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
						if ( strcmp (code,"MACRO") == 0 ) // MACRO PSEUDO OP-CODE
						{
							mdlc ++;
							goto label1;
						}
						else if ( strcmp (code,"MEND") == 0 )
						{
							mdlc --;
							if ( mdlc == 0)
								goto label2;
							else
								goto label1;
						}
						else
							goto label1;
				}
				else
				{
					fprintf (f4,"%s\t%s\t%s\n",label,code,operand);
				}
			}
			else
			{ 
				mdi = 1;
				i = 0;
				j = 0;
				while ( operand[i] != '\0' )
				{ // setup ala
					ala2[j ++] = operand[i ++];
					if (operand[i] == ',')
					{
						i ++;
						ala2[j ++] = ' ';
					}
				}
				ala2[j] = ' ';
				goto label2;
			}
	}
}

void READ()
{
	if ( mdi == 0)
	{
		fscanf (f1,"%s%s%s",label,code,operand);
		return;
	}
	else
	{
		mdtp ++;
		for (i = 0; i <= mdtp; i ++)
			fscanf (f3,"%d%s%s%s",mdtc,label,code,operand);
		i = 0;
		while ( du_operand[i] != '\0' )
		{ // substitute arguments 
			if ( du_operand[i] == '#' )
			{
				k = ((int) du_operand[i + 1]) - 48;
				j = 0;
				while (k != 0)
				{
					if (ala2[j] == ' ')
					k = k - 1;
					j = j + 1;
				}
				while (ala2[j] != ' ')
					du_operand[i ++] = ala2[j ++];
				du_operand[i] = '\0';
			}
			else
				i ++;				
		}
		if ( strcmp (code,"MEND") == 0 )
		{
			if (mdlc == 0)
			{
				mdi = 0;
				fscanf (f1,"%s%s%s",label,code,operand);
				return;
			}
			else
				return;
		}
		else	
			return;
	}
}
