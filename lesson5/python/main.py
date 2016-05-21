#!/usr/bin/python
# -*- coding: utf-8 -*-
#; Creation date [11.06.2016]
#; Author Frzifus

from Lotto import Lotto

def AF(MeinTipp=[5, 3, 15, 42, 33, 17]):
    erg = 0
    Lotto_ = Lotto()
    Lotto_.Tippen(MeinTipp)

    for i in range (0, 1000000):
        if (Lotto_.Spiel() == 3):
            erg += 1.0
    del Lotto_
    return (erg / 10000)


def BF():
    erg = 0
    Lotto_ = Lotto()
    for i in range (0, 1000000):
        if(Lotto_.Abweichung() == 3):
            erg += 1.0
    del Lotto_
    return (erg / 10000)

if __name__ == "__main__":
    print("Wahrscheinlichkeit fuer 3 Richtige: " + str(AF()) + ' %')
    print("Wahrscheinlichkeit fuer 3 bei 2 Ziehungen: " + str(BF()) + ' %')
