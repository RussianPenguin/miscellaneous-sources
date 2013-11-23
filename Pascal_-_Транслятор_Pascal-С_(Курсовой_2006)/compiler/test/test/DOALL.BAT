rem translate all sample programs to c
set tptc=-l -wj: -sc:\inc -i
for %%f in (tptcsys minicrt acker dia dial fmap puzzle qsort sieve test test2 unsq) do tptc %%f
for %%f in (varrec timedat4 smallrec subrange sets pointers point4 linklist findchrs) do tptc %%f
tptc mtplus -m
