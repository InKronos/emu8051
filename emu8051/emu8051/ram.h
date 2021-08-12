/**
 * @file ram.h
 * @brief plik zawiekaj¹cy obiekt klasy RAM
 */
#pragma once

#include "stdafx.h"
#include "Memory.h"


#define RAM_SIZE 256  ///< makrodefinicja rozmiaru pamiêci RAM

 /** Klasa pamiêci RAM */
class RAM : public Memory
{
public:
	/** Konstruktor klasy RAM
	 * @param size rozmiar pamiêci
	 */
	RAM(const ushort size);

	/** Dekonstruktor klasy RAM	 */
	~RAM();

	/** Funkcja do inicjalizacji pamiêci RAM  */
	void initialize();
};

