gcc -c .\headers\message.c .\headers\compress.c .\headers\basic_structures.c .\headers\archive.c .\main.c
move .\message.o .\objects\message.o
move .\main.o .\objects\main.o
move compress.o .\objects\compress.o
move .\basic_structures.o .\objects\basic_structures.o
move .\archive.o .\objects\archive.o
gcc .\objects\main.o .\objects\message.o .\objects\basic_structures.o .\objects\compress.o .\objects\archive.o -o dt_cmp

