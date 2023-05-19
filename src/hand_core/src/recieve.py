import sys
import socket
import wave
import keyboard

UDP_IP = "192.168.1.117"
UDP_PORT = 3333
srate=16000

WAVE_OUTPUT_FILENAME = "test.wav"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

frames = b''
wav_flag = 0
while True:
    keyboard.read_key()
    while keyboard.is_pressed('space'):
        if wav_flag == 0:
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            sock.bind((UDP_IP, UDP_PORT))
            frames = b''      
        wav_flag = 1
        data, addr = sock.recvfrom(1024) 
        frames = frames+data
    if wav_flag == 1:
        print("Create WAV")
        wav_flag = 0
        sock.close()
        wf = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
        wf.setnchannels(1)
        wf.setsampwidth(4)
        wf.setframerate(srate)
        wf.writeframes(frames)
        wf.close()