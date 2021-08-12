/**
 * @file CPU.h
 * @brief plik zawiekaj�cy klase CPU
 */
#pragma once
#include "stdafx.h"
#include "ram.h"
#include "rom.h"
#include "InOut.h"

 /** Klasa procesora */
class CPU
{
	ushort pc; ///< licznik programu

	RAM ram; ///< Obiekt pami�ci RAM
	ROM rom; ///< Obiekt pami�ci ROM
	InOut io; ///< Obiekt uk�adu wej�cia/wyj�cia
public:
	/** Konstruktor klasy CPU
	 * @param filename nazwa pliku instrukcji
	 */
	CPU(std::string filename);

	/** Dekonstruktor klasy CPU */
	~CPU();

	 /** Funkcja uruchamiania procesora */
	void run();

	/** Funkcja zwracaj�ca licznik prgramu
	* @return licznik programu
	*/
	ushort getPC();

private:
	/** Funkcja zwracaj�ca flage przeniesienia Carry
	* @return flaga przeniesienia
	*/
	uchar getPSW_C();		

	/** Funkcja zwracaj�ca dodatkow� flage przeniesienia Carry
	* @return dodatkowa flaga przeniesienia
	*/
	uchar getPSW_AC();		

	/** Funkcja zwracaj�ca flage 0
	* @return flaga 0
	*/
	uchar getPSW_F0();		

	/** Funkcja zwracaj�ca Register bank selection bit 1
	* @return Register bank selection bit 1
	*/
	uchar getPSW_RS1();

	/** Funkcja zwracaj�ca Register bank selection bit 0
	* @return Register bank selection bit 0
	*/
	uchar getPSW_RS0();	

	/** Funkcja zwracaj�ca flage Przepe�nienia
	* @return flage przepe�nienia
	*/
	uchar getPSW_OV();		

	/** Funkcja zwracaj�ca flage przysto�ci
	* @return flage parzysto�ci
	*/
	uchar getPSW_P();		

	/** Funkcja ustawiaj�ca flage przeniesienia Carry
	* @param bit bit zmiany
	*/
	void setPSW_C(const bool bit);

	/** Funkcja ustawiaj�ca flage dodatkowego przeniesienia Carry
	* @param bit bit zmiany
	*/
	void setPSW_AC(const bool bit);

	/** Funkcja ustawiaj�ca flage 0
	* @param bit bit zmiany
	*/
	void setPSW_F0(const bool bit);

	/** Funkcja ustawiaj�ca egister bank selection bit 1
	* @param bit bit zmiany
	*/
	void setPSW_RS1(const bool bit);

	/** Funkcja ustawiaj�ca egister bank selection bit 0
	* @param bit bit zmiany
	*/
	void setPSW_RS0(const bool bit);

	/** Funkcja ustawiaj�ca flage przeniesienia Carry
	* @param bit bit zmiany
	*/
	void setPSW_OV(const bool bit);

	/** Funkcja ustawiaj�ca flage parzysto�ci
	* @param bit bit zmiany
	*/
	void setPSW_P(const bool bit);

	/** Funkcja zwracaj�ca 16-bitowy wska�nik adresu danych 
	* @return 16-bitowy wska�nik adresu danych 
	*/
	ushort getDPTR();

	/** Funkcja ustawiaj�ca 16-bitowy wska�nik adresu danych 
	* @param address adres wska�nika
	*/
	void setDPTR(const ushort address);

	/** Funkcja zwracaj�ca adres rejestru na podstawie kodu operacji
	* @param opcode kod operacji
	*/
	uchar returnRegisterAddres(uchar opcode);


	/** Funkcja obs�ugi kod�w operacyjnych
	* @param opcode kod operacji
	*/
	void opcodesHandler(const uchar opcode);
};

