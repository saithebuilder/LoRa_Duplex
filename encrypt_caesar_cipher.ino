void cesar(char str[], int shift)
{
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      char c = str[i] - 'A';
      c += shift;
      c = c % 26;
      str[i] = c + 'A';
    }
    i++;
  }
  Serial.print( str);
}

void setup() {
  Serial.begin(115200);

}

void loop() {
  char str[] = "HELLO WORLD";
  Serial.print("\n");
  delay(5000);
  cesar(str, 4);
}
