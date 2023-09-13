#include "M5Atom.h"

const int numColors = 4;
const CRGB colors[numColors] = {CRGB(0x0000FF), CRGB(0x00FF00), CRGB(0xFF0000), CRGB(0xFFFF00)}; // Blue, Green, Red, Yellow

String sequence = "";
String userInput = "";

const char colorCodes[numColors] = {'b', 'g', 'r', 'y'};
void setup() {
    M5.begin(true, false, true);
    delay(50);
    M5.dis.fillpix(CRGB(0, 0, 0)); // Inicializa com a tela apagada
    Serial.begin(115200);
    randomSeed(analogRead(millis()));
}

void loop() {
    if (sequence.length() == userInput.length()) {
        // Gera uma nova cor na sequência
        char nextColor = randomColor();
        sequence += nextColor;
        //Serial.println("Nova sequência: " + sequence);

        displaySequence(sequence);
        userInput = "";
    }

    // Aguarda o jogador digitar as cores
    if (Serial.available() > 0) {
        char inputColor = Serial.read();
        if (inputColor == 'b' || inputColor == 'g' || inputColor == 'r' || inputColor == 'y') {
            userInput += inputColor;
            //Serial.println("Input do jogador: " + userInput);
            checkInput();
        }
    }

    M5.update();
}

char randomColor() {
    int randomIndex = random(numColors);
    return "bgry"[randomIndex]; // Mapeia índices para cores (blue, green, red)
}

void displaySequence(String seq) {
    Serial.println(seq);
    delay(1000);
    for (int i = 0; i < seq.length(); i++) {
        char color = seq[i];
        showColor(color);
        delay(1000); // Tempo mostra cor
        clearScreen();
        delay(400); // Tempo espera
    }
}

void showColor(char color) {
    CRGB rgbColor;
    switch (color) {
        case 'b':
            rgbColor = CRGB(0x0000FF); 
            break;
        case 'g':
            rgbColor = CRGB(0x00FF00); 
            break;
        case 'r':
            rgbColor = CRGB(0xFF0000);
            break;
        case 'y':
            rgbColor = CRGB(0xFFFF00); 
            break;
    }
    M5.dis.fillpix(rgbColor);
}

void clearScreen() {
    M5.dis.fillpix(CRGB(0, 0, 0));
}

void checkInput() {
    if (userInput == sequence) {
        Serial.println("Sequência correta!");
    } else if (sequence.indexOf(userInput) != 0) {
        Serial.println("Sequência incorreta. Tente novamente.");
        sequence = ""; 
    }
}
