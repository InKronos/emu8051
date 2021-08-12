/**
 * @file InOut.h
 * @brief plik zawiekaj�cy klase bazow� Memory
 */
#pragma once
#include "stdafx.h"

 /** Klasa Uk�adu wej�cia/wyj�cia */
class InOut
{
public:
	/** Konstruktor klasy InOut	*/
	InOut();
	/** Dekonstruktor klasy InOut	*/
	~InOut();
	/** Funkcja drukowania symbolu na ekran
	 * @param data znak do wypisania na ekran
	 * @param mode tryb w jaki znak ma by� wypisany na ekran
	 */
	void print(const uchar data, const char mode);

	/** Funkcja pobierania znaku z klawiatury
	 * @param character znak do pobrania
	 * @return warto�� bitowa sprawdzaj�ca czy jaki� znak zosta� nacisi�ty
	 */
	bool getInput(char& character);
};

