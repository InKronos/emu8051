/**
 * @file helpFunctions.h
 * @brief plik zawiekaj¹cy funkcjie i zmienne pomocnicze;
 */
#pragma once
#include "stdafx.h"

/** Funkcja zmiejaj¹ca znak na int
 * @param code znak do zamiany
 * @return zmieniony char
 */
ushort getCharToInt(const char code);

/** Funkcja zmiejaj¹ca ³añcuch kodu hex na bajt
 * @param hexcode kod hexa w ³añcuchu do zmienienia
 * @return bajt
 */
uchar stringToByte(const std::string hexcode);

/** Funkcja zwracj¹ca nazwe pliku
 * @param argc iloœæ parametrów
 * @param argv tablica parametrów
 * @return nazwa pliku
 */
std::string getFilename(const int argc, char* argv[]);


//specjalne funkcje mapy pamiêci rejestrów
const uchar p0 = 0x80;		///< ³¹cznik portu 0
const uchar sp = 0x81;		///< wskaŸnik na stos
const uchar dpl = 0x82;		///< adresowanie pamiêci zewnêtrznej
const uchar dph = 0x83;		///< adresowanie pamiêci zewnêtrznej
const uchar p1 = 0x90;		///< ³¹cznik portu 1
const uchar p2 = 0xA0;		///< ³¹cznik portu 2
const uchar p3 = 0xB0;		///< ³¹cznik portu 3
const uchar psw = 0xD0;		///< s³owo statusu programu
const uchar acc = 0xE0;		///< akumulator
const uchar b = 0xF0;		///< rejstr b do obliczeñ arytmetycznych
