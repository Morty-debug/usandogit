#include <stdio.h>



void printbin(int number){
    int i;
    for(i = 128; i > 0; i >>= 1){
    	if((number & i) == i){
        	printf("1");	
        }
        else{
        	printf("0");	
        }
    }
}



int main(){
	int contador;
	char puntero[(1048576*5)];
	int bytes;
	int bytesmaximo;
	
	int pesolectura;
	FILE * archivolectura;
	char * nombrearchivolectura;
	
	int pesoescritura;
	FILE * archivoescritura;
	char * nombrearchivoescritura;


	
	bytes = 1;
	bytesmaximo = (1048576*5);
	nombrearchivolectura = "imagen original.jpg";
	printf("\nLECTURA DE '%s' ",nombrearchivolectura);
	archivolectura = fopen(nombrearchivolectura,"rb");
	if(archivolectura == NULL){ 
		printf("\nNo se logro abrir el archivo para leer\n");
		return -1; 
	}
	
	fseek(archivolectura, 0, SEEK_END);
	pesolectura = ftell(archivolectura);
	if(pesolectura>(1048576*5)){
		printf("\nEL archivo debe ser de 5 MByte o menos\n");
		return -1;
	}
	fclose (archivolectura);	

	archivolectura = fopen(nombrearchivolectura,"rb");
	if(archivolectura == NULL){ 
		printf("\nNo se logro abrir el archivo para leer\n");
		return -1; 
	}
	 
	pesolectura = fread(puntero, bytes, bytesmaximo, archivolectura);
	if(pesolectura==0){
		printf("\nEl archivo esta sin datos\n");
		return -1; 
	}
	
	printf("CON %d Bytes\n", pesolectura);


	
	bytes = 1;
	bytesmaximo = (1048576*5);
	nombrearchivoescritura = "copia instantanea.jpg";
	printf("ESCRITURA DE '%s' ",nombrearchivoescritura);
	
	archivoescritura = fopen(nombrearchivoescritura,"wb"); 
	if(archivoescritura == NULL){ 
		printf("\nNo se logro abrir el archivo para escribir\n");
		return -1; 
	} 

	pesoescritura = fwrite(&puntero, sizeof(unsigned char), pesolectura, archivoescritura);
	if(pesoescritura == 0){ 
		printf("\nNo se logro escribir datos\n");
		return -1; 
	} 
	printf("CON %d Bytes\n\n", pesoescritura);
	
	

	
	for(contador = 0; contador < (pesolectura / sizeof(unsigned char)); contador++){

		/*Indice de Bytes, Hexadecimal, Binario*/
		printf("Byte[%d] = 0X%02x ", contador, (int)((unsigned char)puntero[contador])); 
		printbin((int)((unsigned char)puntero[contador]));
		//printf(" %d",(int)puntero[contador]); //ASCII
		printf("\n");
		
		FILE *file = fopen("copia por bytes.jpg","ab+"); 
		if(file == NULL){ 
			printf("\ncopia de byteas a 'copia por bytes.jpg' interrumpida\n");
			return -1; 
		} 
		fwrite(&puntero[contador], 1, 1, file);
		fclose(file); 
		
	}
	printf("\nESCRITURA DE 'copia por bytes.jpg' CON %d Bytes\n\n",pesoescritura);


	
	fclose (archivolectura);	
	fclose (archivoescritura);


	
	return 0;
}
