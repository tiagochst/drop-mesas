#include "definicoes.h"

int lista_inv_inic(char *SListSec, char *SListPrim) {
	FListSec = open_file_bin(SListSec, 0);
	FListPrim = open_file_bin(SListPrim, -1);
}