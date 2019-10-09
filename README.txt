this is a small c++ project which displays 1 dimensional cellular automata

the file "automata" is the linux executable
it can be used like:
automata rule_number [num_gens] [t0] [img_fname]

rule_number: 
    a decimal number specifying the rule

num_gens: 
    a decimal number specifying how many generations to compute.
    defaults to 20

t0: 
    a string of 1's and 0's specifying the first generation.
    defaults to "1"

img_fname:
    the name of the output image file. 
    Image file is a .pbm and should end with that extension.
    if this argument is not given, the program will display to the console.
