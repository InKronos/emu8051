/**
 * @file helpFunctions.h
 * @brief plik zawiekaj�cy funkcjie i zmienne pomocnicze;
 */
#pragma once
#include "stdafx.h"

/** Funkcja zmiejaj�ca znak na int
 * @param code znak do zamiany
 * @return zmieniony char
 */
ushort getCharToInt(const char code);

/** Funkcja zmiejaj�ca �a�cuch kodu hex na bajt
 * @param hexcode kod hexa w �a�cuchu do zmienienia
 * @return bajt
 */
uchar stringToByte(const std::string hexcode);

/** Funkcja zwracj�ca nazwe pliku
 * @param argc ilo�� parametr�w
 * @param argv tablica parametr�w
 * @return nazwa pliku
 */
std::string getFilename(const int argc, char* argv[]);


//specjalne funkcje mapy pami�ci rejestr�w
const uchar p0 = 0x80;		///< ��cznik portu 0
const uchar sp = 0x81;		///< wska�nik na stos
const uchar dpl = 0x82;		///< adresowanie pami�ci zewn�trznej
const uchar dph = 0x83;		///< adresowanie pami�ci zewn�trznej
const uchar p1 = 0x90;		///< ��cznik portu 1
const uchar p2 = 0xA0;		///< ��cznik portu 2
const uchar p3 = 0xB0;		///< ��cznik portu 3
const uchar psw = 0xD0;		///< s�owo statusu programu
const uchar acc = 0xE0;		///< akumulator
const uchar b = 0xF0;		///< rejstr b do oblicze� arytmetycznych
