/**
 * @file rom.h
 * @brief plik zawiekaj�cy klase ROM
 */
#pragma once
#include "stdafx.h"
#include "Memory.h"

#define ROM_SIZE 4 * 1024 ///< makrodefinicja rozmiaru pami�ci ROM

/** Klasa pami�ci ROM */
class ROM : public Memory
{
	int instructionSize; ///< Rozmiar instrukcji
public:
	/** Konstruktor klasy RAM
	 * @param size rozmiar pami�ci
	 */
	ROM(const ushort size);
	~ROM();

	/** Funkcja pobrania instrukcji z pliku
	 * @param namefile nazwa pliku
	 */
	void getInstructionsFormFIle(const std::string namefile);

	/** Funkcja zwracjaj�ca warto�� instrukcji z pliku  */
	int getInstructionSize() const;
};

