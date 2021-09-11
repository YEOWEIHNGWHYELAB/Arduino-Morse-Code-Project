// There are no official way to separate lowercase and uppercase in Morse Code. 

const int ledPinOut = 13; // Set your desired pin...
const int dotDelay = 200; // Set dot delay. 
const int dashDelay = 600; // Set dash delay. 
const int gapBetweenChar = 600; // Set char gap delay. 

char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."          // S-Z
};

char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

void flashSequence(char* sequence)
{
  int i = 0;
  
  while (sequence[i] != NULL) {
    flashDotOrDash(sequence[i]);
    i++;
  }
  
  delay(gapBetweenChar); // Gaps between letters/numbers
}

void flashDotOrDash(char dotOrDash)
{
  digitalWrite(ledPinOut, HIGH);
  
  if (dotOrDash == '.') {
    delay(dotDelay);           
  }
  else { 
    delay(dashDelay);            
  }
  
  digitalWrite(ledPinOut, LOW);    
  
  delay(dotDelay); // Gaps between flashes
}

void setup() {
  pinMode(ledPinOut, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  char characters;

  // Check Buffer.
  if (Serial.available() > 0) {
    characters = Serial.read();

    // Lower Case
    if (characters >= 'a' && characters <= 'z') {
      flashSequence(letters[characters - 'a']);
    }
    // Upper Case
    else if (characters >= 'A' && characters <= 'Z') {
      flashSequence(letters[characters - 'A']);
    }
    // Numbers
    else if (characters >= '0' && characters <= '9') {
      flashSequence(numbers[characters - '0']);
    }
    // White Space
    else if (characters == ' ') {
      delay(dotDelay * 4);
    }
    
  }
}
