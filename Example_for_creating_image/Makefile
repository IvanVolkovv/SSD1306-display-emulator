
TARGET = a.exe
CC := gcc
FLAGS := -c -Wall

OBJ = main.o Fonts_SSD1306.o

.PHONY: clean a

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
	
main.o : main.c
	$(CC) main.c $(FLAGS)
	
Fonts_SSD1306.o : Fonts_SSD1306.c
	$(CC) Fonts_SSD1306.c $(FLAGS)
	
clean: 
	del *.o 

