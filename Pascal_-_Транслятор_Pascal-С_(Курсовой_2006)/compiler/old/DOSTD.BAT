rem translate standard unit specifications
set tptc=-l -wj: -sc:\inc -i
tptc tptcsys
tptc \tp\system.doc system 
tptc \tp\dos.doc dos 
tptc \tp\crt.doc crt 
tptc \tp\printer.doc printer 
rem - note: you must edit graph.doc to properly comment the documentation
rem -       blocks that were added
tptc \tp\graph.doc graph 
