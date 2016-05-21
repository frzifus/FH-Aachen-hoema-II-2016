#!/usr/bin/python
# -*- coding: utf-8 -*-
#; Creation date [11.06.2016]
#; Author Frzifus

from random import randint

class Lotto(object):
    def __init__(self):
        self.TippZettel  = []

    def Tippen(self, tipp):
        self.TippZettel = tipp

    def Spiel(self):
        SpielZahlen = self.Ziehen()
        ergebnis = 0
        for i in SpielZahlen:
            if i in self.TippZettel:
                ergebnis += 1
        return ergebnis

    def Abweichung(self):
        SpielZahlen = self.Ziehen()
        tmp         = self.Ziehen()
        ergebnis    = 0
        for i in SpielZahlen:
            for j in tmp:
                if (i == j):
                    ergebnis += 1
        return ergebnis

    def Ziehen(self, begin = 1, end = 49):
        ergebnis = []
        value    = randint(begin, end)
        for i in range (1, 7):
            while value in ergebnis:
                value = randint(begin, end)
            ergebnis.append(value)
        return ergebnis
