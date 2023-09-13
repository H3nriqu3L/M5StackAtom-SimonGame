import serial
import time
import sounddevice as sd
import numpy as np


ser = serial.Serial('COM3', 115200)
first = True

freq_blue = 350  
freq_green = 500
freq_red = 650 
freq_yellow = 800 
duration = 1

def play_tone(frequency):
    # Gera um tom com a frequência especificada
    t = np.linspace(0, duration, int(duration * 44100), False)
    tone = 0.5 * np.sin(2 * np.pi * frequency * t)
    sd.play(tone)
    sd.wait()


def enviar_sequencia(sequencia):
    # envia a sequência para o Arduino
    ser.write(sequencia.encode())
    ser.write(b'\n')  #  indica o fim da sequência

try:
    while True:
        if(not first):
            color_code_seq = ser.readline().decode().strip()
            for color_code in color_code_seq:
                if color_code == 'b':
                    play_tone(freq_blue)
                    time.sleep(0.3)
                elif color_code == 'g':
                    play_tone(freq_green)
                    time.sleep(0.3)
                elif color_code == 'r':
                    play_tone(freq_red)
                    time.sleep(0.3)
                elif color_code == 'y':
                    play_tone(freq_yellow)
                    time.sleep(0.3)

        sequencia = input("Digite a sequência (b - blue, g - green, r - red, y - yellow): ")
        
       
        enviar_sequencia(sequencia)
        
        resposta = ser.readline().decode().strip()
        print(resposta)
        first = False
        time.sleep(1)  

except KeyboardInterrupt:
    ser.close() 
