/**
 * @file rom.h
 * @brief plik zawiekaj¹cy klase ROM
 */
#pragma once
#include "stdafx.h"
#include "Memory.h"

#define ROM_SIZE 4 * 1024 ///< makrodefinicja rozmiaru pamiêci ROM

/** Klasa pamiêci ROM */
class ROM : public Memory
{
	int instructionSize; ///< Rozmiar instrukcji
public:
	/** Konstruktor klasy RAM
	 * @param size rozmiar pamiêci
	 */
	ROM(const ushort size);
	~ROM();

	/** Funkcja pobrania instrukcji z pliku
	 * @param namefile nazwa pliku
	 */
	void getInstructionsFormFIle(const std::string namefile);

	/** Funkcja zwracjaj¹ca wartoœæ instrukcji z pliku  */
	int getInstructionSize() const;
};

