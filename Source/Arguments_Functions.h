
/*! Contiene funzioni di controllo dei parametri passati al programma !*/

/* ArrayOR esegue uno OR sul vettore booleano e ritorna il risultato,
 * e stato utilizzato per controllare che il programma non ricevesse contemporaneamente
 * argomenti lunghi e corti */

#include "Arguments_Header.h"

bool ArrayOR(bool *ArrayBool) {
    bool result = false;

    for (int i = 0; i < sizeof(ArrayBool); i++) {
        result |= ArrayBool[i];
    }

    return result;
}

void CheckLongCompatibility(int opt) {

    for (int i = 0;
         i < sizeof(CompatibleLongOptions) / sizeof(CompatibleLongOptions[0]);
         i++) {
        if ((LongOptions[i] && !CompatibleLongOptions[i][opt])) {
            Error(ErrorSintax, "");
        }
    }

    LongOptions[opt] = true;

    if (ArrayOR(LongOptions) && ArrayOR(ShortOptions))
        Error(ErrorSintax, "");
}

void CheckShortCompatibility(int opt) {

    for (int i = 0;
         i < sizeof(CompatibleShortOptions) / sizeof(CompatibleShortOptions[0]);
         i++) {
        if ((ShortOptions[i] && !CompatibleShortOptions[i][opt])) {
            Error(ErrorSintax, "");
        }
    }

    ShortOptions[opt] = true;

    if (ArrayOR(LongOptions) && ArrayOR(ShortOptions))
        Error(ErrorSintax, "");
}
