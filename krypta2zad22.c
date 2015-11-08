#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <unistd.h>

void encrypt(FILE *ifp, FILE *ofp, char ckey[], char ivec[])
{
   
    fseek(ifp, 0L, SEEK_END);
    int fsize = ftell(ifp);
  
    fseek(ifp, 0L, SEEK_SET);

    int outLen1 = 0; int outLen2 = 0;
    unsigned char *indata = malloc(fsize);
    unsigned char *outdata = malloc(fsize*2);
  

  
    fread(indata,sizeof(char),fsize, ifp);

  
    EVP_CIPHER_CTX ctx;
    EVP_EncryptInit(&ctx,EVP_aes_128_cbc(),ckey,ivec);
    EVP_EncryptUpdate(&ctx,outdata,&outLen1,indata,fsize);
    EVP_EncryptFinal(&ctx,outdata + outLen1,&outLen2);
    fwrite(outdata,sizeof(char),outLen1 + outLen2,ofp);
}

char * encrypt2(FILE *ifp, char ckey[], char ivec[])
{
   
    fseek(ifp, 0L, SEEK_END);
    int fsize = ftell(ifp);
  
    fseek(ifp, 0L, SEEK_SET);

    int outLen1 = 0; int outLen2 = 0;
    char *indata = malloc(fsize);
    char *outdata = malloc(fsize*2);
  

  
    fread(indata,sizeof(char),fsize, ifp);

  
    EVP_CIPHER_CTX ctx;
    EVP_EncryptInit(&ctx,EVP_aes_128_cbc(),ckey,ivec);
    EVP_EncryptUpdate(&ctx,outdata,&outLen1,indata,fsize);
    EVP_EncryptFinal(&ctx,outdata + outLen1,&outLen2);
    return outdata;
}


char * decrypt2(FILE *ifp, char ckey[], char ivec[])
{
   
    fseek(ifp, 0L, SEEK_END);
    int fsize = ftell(ifp);
   
    fseek(ifp, 0L, SEEK_SET);

    int outLen1 = 0; int outLen2 = 0;
    unsigned char *indata = malloc(fsize);
    unsigned char *outdata = malloc(fsize);
   

   
    fread(indata,sizeof(char),fsize, ifp);//Read Entire File


    EVP_CIPHER_CTX ctx;
    EVP_DecryptInit(&ctx,EVP_aes_128_cbc(),ckey,ivec);
    EVP_DecryptUpdate(&ctx,outdata,&outLen1,indata,fsize);
    EVP_DecryptFinal(&ctx,outdata + outLen1,&outLen2);
   return outdata;
}


void decrypt(FILE *ifp, FILE *ofp, char ckey[], char ivec[])
{
   
    fseek(ifp, 0L, SEEK_END);
    int fsize = ftell(ifp);
   
    fseek(ifp, 0L, SEEK_SET);

    int outLen1 = 0; int outLen2 = 0;
    unsigned char *indata = malloc(fsize);
    unsigned char *outdata = malloc(fsize);
   

   
    fread(indata,sizeof(char),fsize, ifp);//Read Entire File


    EVP_CIPHER_CTX ctx;
    EVP_DecryptInit(&ctx,EVP_aes_128_cbc(),ckey,ivec);
    EVP_DecryptUpdate(&ctx,outdata,&outLen1,indata,fsize);
    EVP_DecryptFinal(&ctx,outdata + outLen1,&outLen2);
    fwrite(outdata,sizeof(char),outLen1 + outLen2,ofp);
}

char* szukajklucza( char  sciezka[], char id[], char klucz[], char iv[], int n )
{  
 
FILE* keystore1,* fOUT ;  
   keystore1 = fopen(sciezka,"rb");
    static char brak[10];
	 strcpy(brak, "brak");
    if(keystore1==NULL ) {printf("Plik błedny"); return brak;}

    fOUT = fopen("keystore4.txt", "wb");
    decrypt(keystore1,fOUT, klucz, iv);
    fclose(keystore1);
    fclose(fOUT);
	FILE* keystore ;  
	 keystore = fopen("keystore4.txt","rb");
     char idszukane[256];
	 static char szyfr[256];
	 static char wektor[256];
	 
   if (keystore==NULL){printf("Coś z plikiem" ); return 0;}
   else
   {  while (!feof(keystore))   
			{ 
                         fscanf(keystore, "%s", idszukane); 
                           
			  if (feof(keystore))   {printf("Za mało danych1");  return brak;  }
			  fscanf(keystore, "%s", szyfr); 
			  if (feof(keystore))   {printf("Za mało danych2");  return brak;  }
			  fscanf(keystore, "%s", wektor); 
                           // printf( " ff %s  fdddf %s", idszukane, szyfr); 
			  if(strcmp(idszukane,id)==0)  
			          {	
						//fwrite(brak,sizeof(char), sizeof(brak), keystore);
						fclose(keystore);
						
						// keystore = fopen("keystore4.txt","wb");
 						//fwrite(brak,sizeof(char), sizeof(brak), keystore);
							//fclose(keystore);
					
					  
					   if(n==0)
					   return szyfr;
					   else return wektor;
					  
					  }
			  if (feof(keystore))   {printf("Za mało danych3");  return brak;  }
			
			}
      
   }
    
	//fwrite(brak,sizeof(char), sizeof(brak), fOUT);
	fclose(keystore);
	  
						 keystore = fopen("keystore4.txt","wb");
 						fwrite(brak,sizeof(char), sizeof(brak), keystore);
							fclose(keystore);
					
       printf("Brak w keystore potrzebnych danych");
	return brak;
}





int main(int argc, char *argv[])
{   FILE *fIN, *fOUT;  
   FILE* konf,*konf2;
   char kee[255];
		  strcpy(kee, "komiksyeee");
	char wee[255];
		  strcpy(wee, "danemisasa");	  
   konf=fopen("konf.txt","rb");
   if (konf==NULL)
   {   //fclose(konf);
       konf2=fopen("konf2.txt","wb");
	     char cos[255];
		  strcpy(cos, "");
		 strcat(cos,argv[1]);
                 strcat(cos," ");
		 strcat(cos,argv[2]);
                 strcat(cos," ");
		 strcat(cos,argv[3]);
                 strcat(cos," ");
		 strcat(cos,argv[4]);
                 strcat(cos," ");
	  //strcpy(cos, "keystore2.txt mis smutekizal smierctutu");
	   fwrite(cos,sizeof(cos)-1, 1, konf2);
	   fclose(konf2);
	    fIN = fopen("konf2.txt", "rb");
		if(fIN==NULL ) {printf("Plik błedny"); return 0;}
		fOUT = fopen("konf.txt", "wb");
		
			encrypt(fIN, fOUT, "komiksyeee", "danemisasa");
			
     fclose(fIN);
     fclose(fOUT);                     // FILE *keystore;
					//keystore = fopen("konf2.txt","wb");
	                 //char brak[10];
				    // strcpy(brak, "brak");
 					//fwrite(brak,sizeof(char), sizeof(brak), keystore);
					//fclose(keystore);
   
    }
	else {  char * wynik;
                      
	     wynik=decrypt2(konf, "komiksyeee", "danemisasa");
		 printf("dd %s", wynik);
		char *  path1;
		char *  ide1;
		char *  keys1;
		char *  vector1;
		
		path1 = strtok (wynik," ");
		  
				
				ide1 = strtok (NULL, " ");
				keys1= strtok (NULL, " ");
				vector1 = strtok (NULL, " ");
		  char* haslo;
	       printf("dd 7%s7  7%s7   7%s7  7%s7", path1, ide1, keys1, vector1);
               printf("\n");
             
	      haslo=getpass("haslo podaj ");
         if( !strncmp(haslo,"4444",100)==0 ) {printf("Złe hasło"); return 0;}
            char* szyfrek;
		char*  wektor;
           char line[4096];
            sprintf(line,"./krr.exe nie %s %s %s %s", argv[1], argv[2], path1, ide1);
           system(line);
            
	/*        //  szyfrek=szukajklucza("keystore2.txt","mis","smutekizal", "smierctutu",0);
         // wektor=szukajklucza("keystore2.txt","mis","smutekizal", "smierctutu",1);
             

		
			char * key2="smutekizal";
		char * iv2="smierctutu";
       
	 szyfrek=szukajklucza(path1,ide1,keys1, vector1,0);
	 wektor=szukajklucza(path1,ide1,keys1, vector1,1);
         
	printf(" ff %s  jjj  %s ",szyfrek, wektor);
	
          szyfrek=szukajklucza(path1,ide1,keys1, vector1,0);
	 wektor=szukajklucza(path1,ide1,keys1, vector1,1);



    fIN = fopen(argv[1], "rb");
    if(fIN==NULL ) {printf("Plik błedny2"); return 0;}
    fOUT = fopen(argv[2], "wb");
	
			encrypt(fIN, fOUT, "gdzielas", "pasmigas");
			
			
    fclose(fIN);
    fclose(fOUT);		
			
     */
	return 0;	 
	
	}

	
	
	
	printf("Zakończono");
    return 0;
}
