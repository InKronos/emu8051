/**
 * @file CPU.h
 * @brief plik zawiekający klase CPU
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

	RAM ram; ///< Obiekt pamięci RAM
	ROM rom; ///< Obiekt pamięci ROM
	InOut io; ///< Obiekt układu wejścia/wyjścia
public:
	/** Konstruktor klasy CPU
	 * @param filename nazwa pliku instrukcji
	 */
	CPU(std::string filename);

	/** Dekonstruktor klasy CPU */
	~CPU();

	 /** Funkcja uruchamiania procesora */
	void run();

	/** Funkcja zwracająca licznik prgramu
	* @return licznik programu
	*/
	ushort getPC();

private:
	/** Funkcja zwracająca flage przeniesienia Carry
	* @return flaga przeniesienia
	*/
	uchar getPSW_C();		

	/** Funkcja zwracająca dodatkową flage przeniesienia Carry
	* @return dodatkowa flaga przeniesienia
	*/
	uchar getPSW_AC();		

	/** Funkcja zwracająca flage 0
	* @return flaga 0
	*/
	uchar getPSW_F0();		

	/** Funkcja zwracająca Register bank selection bit 1
	* @return Register bank selection bit 1
	*/
	uchar getPSW_RS1();

	/** Funkcja zwracająca Register bank selection bit 0
	* @return Register bank selection bit 0
	*/
	uchar getPSW_RS0();	

	/** Funkcja zwracająca flage Przepełnienia
	* @return flage przepełnienia
	*/
	uchar getPSW_OV();		

	/** Funkcja zwracająca flage przystości
	* @return flage parzystości
	*/
	uchar getPSW_P();		

	/** Funkcja ustawiająca flage przeniesienia Carry
	* @param bit bit zmiany
	*/
	void setPSW_C(const bool bit);

	/** Funkcja ustawiająca flage dodatkowego przeniesienia Carry
	* @param bit bit zmiany
	*/
	void setPSW_AC(const bool bit);

	/** Funkcja ustawiająca flage 0
	* @param bit bit zmiany
	*/
	void setPSW_F0(const bool bit);

	/** Funkcja ustawiająca egister bank selection bit 1
	* @param bit bit zmiany
	*/
	void setPSW_RS1(const bool bit);

	/** Funkcja ustawiająca egister bank selection bit 0
	* @param bit bit zmiany
	*/
	void setPSW_RS0(const bool bit);

	/** Funkcja ustawiająca flage przeniesienia Carry
	* @param bit bit zmiany
	*/
	void setPSW_OV(const bool bit);

	/** Funkcja ustawiająca flage parzystości
	* @param bit bit zmiany
	*/
	void setPSW_P(const bool bit);

	/** Funkcja zwracająca 16-bitowy wskaźnik adresu danych 
	* @return 16-bitowy wskaźnik adresu danych 
	*/
	ushort getDPTR();

	/** Funkcja ustawiająca 16-bitowy wskaźnik adresu danych 
	* @param address adres wskaźnika
	*/
	void setDPTR(const ushort address);

	/** Funkcja zwracająca adres rejestru na podstawie kodu operacji
	* @param opcode kod operacji
	*/
	uchar returnRegisterAddres(uchar opcode);


	/** Funkcja obsługi kodów operacyjnych
	* @param opcode kod operacji
	*/
	void opcodesHandler(const uchar opcode);
};

