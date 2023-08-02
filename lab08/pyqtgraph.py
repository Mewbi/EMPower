#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
import pyqtgraph as pg
#from pyqtgraph.Qt import QtGui, QtCore
import numpy as np
import serial
import atexit
import time

def inicia_coleta():
    conexaoSerial.write(b'i')

def ler_intervalo():
    conexaoSerial.write(b't')   ## intervalo
    
def aumenta_intervalo():
    conexaoSerial.write(b'a')  ## aumentar

def diminui_intervalo():
    conexaoSerial.write(b'd')  ## diminuir
    
def para_coleta():
    conexaoSerial.write(b'p')
 
def saindo():
    conexaoSerial.write(b'p')
    print('Saindo')
    

def update():
    global data1, curve1, ptr1, conexaoSerial, x_atual, npontos, previousTime
    if conexaoSerial.inWaiting() > 1:
        dado = conexaoSerial.readline().decode().strip().split("|")
        if len(dado) < 2:
            return

        comando = dado[0]
        valor = float(dado[1])

        if comando == "v":
            novodado = float( (valor*256.0)*5.0/1023.0 )
        
            data1[x_atual] = novodado
            data1[(x_atual+1)%npontos] = np.nan
            x_atual = x_atual+1
            if x_atual >= npontos:
                x_atual = 0
        
            curve1.setData(data1, connect="finite")
            actualTime = time.time()*1000
            taxa = str(round(actualTime-previousTime))
            previousTime = actualTime
            texto.setText("taxa: "+taxa.zfill(3)+"ms" )

        elif comando == "i":
            texto_intervalo.setText("interalo: "+str(valor)+"ms" )

win = pg.GraphicsWindow()
win.setWindowTitle('Coletando dados do Arduino via Porta Serial')

npontos = 800
x_atual = 0
p1 = win.addPlot()
p1.setYRange(0,5,padding=0)
data1 = np.zeros(npontos)
curve1 = p1.plot(data1)
ptr1 = 0

previousTime = time.time()*1000 # pega a hora atual, em milissegundos
texto = pg.TextItem(text="", color=(255,255,0), anchor=(0,1))
p1.addItem(texto)
texto.setPos(0,0) # adiciona o texto na posicao (0,0) do grafico

texto_intervalo = pg.TextItem(text="", color=(255,255,0), anchor=(0,1))
p1.addItem(texto_intervalo)
texto_intervalo.setPos(700,4) # adiciona o texto na posicao (800,5) do grafico


proxy1 = QtGui.QGraphicsProxyWidget()
botao1 = QtGui.QPushButton('Inicia')
proxy1.setWidget(botao1)
botao1.clicked.connect(inicia_coleta)

proxy2 = QtGui.QGraphicsProxyWidget()
botao2 = QtGui.QPushButton('Para')
proxy2.setWidget(botao2)
botao2.clicked.connect(para_coleta)

proxy3 = QtGui.QGraphicsProxyWidget()
botao3 = QtGui.QPushButton('Ler intervalo')
proxy3.setWidget(botao3)
botao3.clicked.connect(ler_intervalo)

proxy4 = QtGui.QGraphicsProxyWidget()
botao4 = QtGui.QPushButton('Aumentar intervalo')
proxy4.setWidget(botao4)
botao4.clicked.connect(aumenta_intervalo)

proxy5 = QtGui.QGraphicsProxyWidget()
botao5 = QtGui.QPushButton('Diminuir intervalo')
proxy5.setWidget(botao5)
botao5.clicked.connect(diminui_intervalo)

p2 = win.addLayout(row=4, col=0)
p2.addItem(proxy1,row=0,col=0)
p2.addItem(proxy2,row=1,col=0)
p2.addItem(proxy3,row=2,col=0)

p2.addItem(proxy4,row=3,col=0)
p2.addItem(proxy5,row=4,col=0)

conexaoSerial = serial.Serial('/dev/ttyUSB0',115200)
conexaoSerial.write(b'i')
        
# inicia timer rodando o mais rápido possível
timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(0)

atexit.register(saindo)

## Start Qt event loop unless running in interactive mode or using pyside.
if __name__ == '__main__':
    QtGui.QApplication.instance().exec_()
