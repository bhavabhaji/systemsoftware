# input file
input_file = 'input2.txt'

# open and read input file
fp = open(input_file, 'r')
data = fp.readline()

line_no = 1  # counter for line in input file
mntc = 1
mdtc = 1

# open/create other files
fp_mn = open('mnt_table.txt', 'w')
fp_md = open('mdt_table.txt', 'w')
fp_out = open('output_file1.txt', 'w')

while data != '':  # Check for end of file
    elements = data.split()
    if elements[1] == 'MACRO':
        data = fp.readline()
        line_no += 1

        # store macro arguments (for use in numbering)
        macro_arguments = data[data.find('&'):].rstrip().split(',')

        fp_mn.write('%d\t%s\t%d\n' %(mntc, data[data.find('-'):].rstrip(), mdtc))
        fp_md.write('%d\t%s\t\n' %(mdtc, data[data.find('-'):].rstrip()))
        mntc += 1; mdtc += 1
#        counter_mn = 0

        # read next line from input before executing while loop
        data = fp.readline()
        line_no += 1
        while elements[1] != 'MEND':  # while it is inside MACRO block
            # prepare string to be written
            start = data.find('-')
            end = data.find(',')
            string_to_write = '%d\t%s' %(mdtc, data[start:end+1].rstrip())

            if '&' in data[end:]:
                string_to_write += '#%d\n' %(macro_arguments.index(data[end+1:].rstrip()))
#                counter_mn += 1
            else:
                string_to_write += data[end+1:].split('&')[-1]

            fp_md.write(string_to_write)
            mdtc += 1

            # read next line in input
            data = fp.readline()
            line_no += 1
            elements = data.split()

        if 'MEND' in data:  # Macro END detected, write this line and read next line
            fp_md.write('%d\t%s' %(mdtc, data))
            mdtc += 1
            # read next line in input
            data = fp.readline()
            line_no += 1
    else:  # write to output file
        fp_out.write(data)
        data = fp.readline()
        line_no += 1

# close files
fp.close()
fp_mn.close()
fp_md.close()
fp_out.close()
