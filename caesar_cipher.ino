#define Nchars 96  //  starting at 32 up to 126 in the ascii table 
#define n_shift 3  //  shift desired
//
char plaintext[]=
{   
  'A','r','d','u','i','n','o',' ', 't','o',' ','c','i','p','h','e','r',' ','t','h','i','s', '#'};
//
char ciphered[sizeof(plaintext)];
//

boolean stringComplete = true;  

void setup() {

  Serial.begin(115200);
}

void loop() {
  uint8_t i;
 

  while(Serial)
  {
    if(stringComplete==true){
      Serial.println ("decipher this ");
      Serial.println ("");
      cphr();
 
      Serial.println(" ");
 
    }
  }
}

void cphr()
{
  uint8_t sizeofarray = sizeof(plaintext);
  uint8_t i;
  //
  for(i=0;i<sizeofarray;i++)
  {
    uint16_t retrieved;
    retrieved=plaintext[i];
   
    retrieved -=32; 

    uint16_t c =(retrieved + n_shift)% Nchars; 
  
    c +=32; 

    ciphered[i]=c;

    delay(50);
  }
  displayResults();
  stringComplete = false;
}

void displayResults(){

  uint8_t i;
  uint8_t sizeofarray = sizeof(plaintext);
  Serial.print("plaintext ");
  for(i=0;i<sizeofarray;i++)
  {
    Serial.print(plaintext[i]);
    delay(10);
  }
  Serial.println(" ");
  Serial.print("Ciphertext ");
  for(i=0;i<sizeofarray;i++)
  {
    Serial.print(ciphered[i]);
    delay(50);
  }
}
