#!usr/bin/env
# Run me with 32 bit python !!!
''' lorem ipsum
'''

import ctypes as ct
import os.path as op
import random
import math
from terminal_colors import bcolors

#debugPath = op.abspath(op.join(op.pardir,'Debug'))
debugPath = op.abspath(op.join(op.pardir,'Release'))

# Load DLL into memory
dll = ct.CDLL(debugPath + '\\RunningAllanDLL.dll')

ram = dll.RunningAllanMain
ram.restype = None

ram.argtypes = [ct.c_double, # double input, // Input value
    ct.POINTER(ct.c_int), ct.c_int, # int *lengths, int lengthsN, // Lengths of Allan dev to process
    ct.POINTER(ct.c_int), # int *procL, // Lengths of the currently processing sequence
    ct.POINTER(ct.c_int), # int *procI, // Pointeers to the processed values
    ct.POINTER(ct.c_double), ct.POINTER(ct.c_int), # double *proc, int *procN, // Processed values containers
    ct.POINTER(ct.c_double), ct.POINTER(ct.c_double)] # double *allanDevsWIP, double *allanDevs) // Output arrays

# lengths = [1,2,5,10,20,30,50,100]
lengths = [1,2,3,4]
histN = max(lengths)*50
lengthsN = ct.c_int(len(lengths))
lengths = (ct.c_int * lengthsN.value)(*lengths)
procL = (ct.c_int * lengthsN.value)(0)
procI = (ct.c_int * lengthsN.value)(0)

procN = list(histN/i + 1 for i in lengths)
proc = (ct.c_double * sum(procN))(0)
procN = (ct.c_int * lengthsN.value)(*procN)

allanDevsWIP = (ct.c_double * lengthsN.value)(0)
allanDevs = (ct.c_double * lengthsN.value)(0)

for i in range(3*histN):
    inputValue = ct.c_double(i+1)#ct.c_double(random.random()) #ct.c_double(random.randint(0,10))
    ram(inputValue, lengths, lengthsN, procL, procI, proc, procN, allanDevsWIP, allanDevs)

    if i%2:
        color = bcolors.OKBLUE
        endColor = bcolors.ENDC
    else:
        color = ''
        endColor = ''
    print( color + '==== #{} ===='.format(i+1) + endColor)
    print( color + 'proc''s       : {}'.format(list(p for p in proc)) + endColor)
    print( color + 'procN''s      : {}'.format(list(p for p in procN)) + endColor)
    print( color + 'procI''s      : {}'.format(list(p for p in procI)) + endColor)
    # print( color + 'procL''s: {}'.format(list(i for i in procL)) + endColor)
    print(color + 'allanDevsWIP: {}'.format(list(i for i in allanDevsWIP)) + endColor)
    print(color + 'allanDevs: {}'.format(list(i for i in allanDevs)) + endColor)
    # print('-'*10)

#print(ram(56,2,3,5))
