//
//  main.cpp
//  Juego blob wars
//
//  Created by Alberto Juarez on 11/1/16.
//  Copyright © 2016 Alberto Juarez. All rights reserved.
//

#include <iostream>
using namespace std;

// Funcion que genera todos los datos del tablero, tanto los espacios en blanco ('*'), como los de los jugadores
void empezarJuego(char cArrTablero[6][6]){
    for (int iCR = 0; iCR < 6; iCR++) {
        for (int iCC = 0; iCC < 6; iCC++){
            cArrTablero[iCR][iCC]= '*';
        }
    }
    cArrTablero[0][0]= 'x';
    cArrTablero[0][5]= 'x';
    cArrTablero[5][0]= 'o';
    cArrTablero[5][5]= 'o';
}

// Funcion que muestra el tablero en si y los numeros de las casillas para una facil eleccion de la casilla.
void mostrarTablero(char cArrTablero[6][6]){
    for (int iCont = 0; iCont < 6;iCont++)
    {
        cout << "\t" << iCont;
    }
    cout << endl;
    for (int iCR = 0; iCR < 6; iCR++) {
        cout << iCR << "\t";
        for (int iCC = 0; iCC < 6; iCC++){
            cout << cArrTablero[iCR][iCC] << "\t";
        }
        cout << endl;
    }
}

//Funcion para verificar si el tablero todavia tiene alguna casilla con el caracter '*'
void verificarSeguir (char cArrTablero[6][6], bool &bSeguir){
    
    for (int iCR = 0; iCR < 6; iCR++) {
        for (int iCC = 0; iCC < 6; iCC++){
            if (cArrTablero[iCR][iCC]=='*'){
                bSeguir = true;
            }
            else
                bSeguir = false;
        }
    }
}

// Funcion que lleva el contador del score y muestra al final quien es el ganador o en su caso si se produjo un empate
void verGanador(char cArrTablero[6][6]){
    int iContX, iContO;
    iContO = 0;
    iContX = 0;
    for (int iCR = 0; iCR < 6; iCR++) {
        for (int iCC = 0; iCC < 6; iCC++){
            if (cArrTablero[iCR][iCC]=='x'){
                iContX++;
            }
            else if ( cArrTablero[iCR][iCC]=='o'){
                iContO++;
            }
        }
    }
    
    cout << "El jugador x tiene " << iContX << " casillas" << endl;
    cout << "El jugador o tiene " << iContO << " casillas" << endl;
    
    if (iContO > iContX){
        cout << "El ganador es el jugador o" << endl;
    }
    else if (iContX > iContO){
        cout << "El ganador es el jugador x" << endl;
    }
    else
        cout << "Fue un empate " << endl;
}

// Funcion que determina que turno sigue en el juego, valida que el blob seleccionado si sea de este jugador,
// hace el movimiento del blob y tambien se come a los blobs enemigos si es el caso

void moverJugador (char cArrTablero[6][6], int &iTurno){
    char cCharActual,cCharOponente;
    int iMovReng = -1;
    int iMovCol = -1;
    char cMovimiento = ' ';
    bool bContinuar = false;
    
    if(iTurno % 2 == 0){
        cout << "Turno del jugador 1 x " << endl;
        cCharActual ='x';
        cCharOponente ='o';
    }
    
    else {
        cout << "Turno del jugador 2 o " << endl;
        cCharActual ='o';
        cCharOponente = 'x';
    }
    
    while (bContinuar == false) {
        
        while (iMovReng < 0 || iMovReng > 5 ) {
            cout << "Renglon -> ";
            cin >> iMovReng;
        }
        
        while (iMovCol < 0 || iMovCol > 5 ) {
            cout << "Columna -> ";
            cin >> iMovCol;
        }
        if (cArrTablero[iMovReng][iMovCol] == cCharActual)
            bContinuar = true;
        else {
            bContinuar = false;
            iMovCol = -1;
            iMovReng = -1;
        }
    }
    
    do {
        cout << "a - izq  x - aba  w - arr  d - der" << endl;
        cout << "q - arriba a la izquierda e - arriba a la derecha" << endl;
        cout << "z - abajo a la izquierda c - abajo a la derecha" << endl;
        cin >> cMovimiento;
        cMovimiento = tolower(cMovimiento);
        
    }   while (cMovimiento != 'a' && cMovimiento != 'x' && cMovimiento != 'w' && cMovimiento != 'd' && cMovimiento != 'q' && cMovimiento != 'e' && cMovimiento != 'z' && cMovimiento != 'c');
    
    if (cArrTablero[iMovReng][iMovCol] == cCharActual) {
        switch (cMovimiento) {
            case 'a': {
                iMovCol -=1;
                break;
            }
            case 'x': {
                iMovReng+=1;
                break;
            }
            case 'w': {
                iMovReng-=1;
                break;
            }
            case 'd': {
                iMovCol += 1;
                break;
            }
            case 'q': {
                iMovReng-=1;
                iMovCol -=1;
                break;
            }
            case 'e': {
                iMovReng-=1;
                iMovCol += 1;
                break;
            }
            case 'z': {
                iMovReng+=1;
                iMovCol -=1;
                break;
            }
            case 'c': {
                iMovReng+=1;
                iMovCol += 1;
                break;
            }
        }
        iTurno++;
        cArrTablero[iMovReng][iMovCol] = cCharActual;
    }
    else
        iTurno++;
    
    if (cArrTablero[iMovReng][iMovCol-1] == cCharOponente)
        cArrTablero[iMovReng][iMovCol-1] = cCharActual;
    
    if (cArrTablero[iMovReng+1][iMovCol] == cCharOponente)
        cArrTablero[iMovReng+1][iMovCol] = cCharActual;
    
    if (cArrTablero[iMovReng-1][iMovCol] == cCharOponente)
        cArrTablero[iMovReng-1][iMovCol] = cCharActual;
    
    if (cArrTablero[iMovReng][iMovCol+1] == cCharOponente)
        cArrTablero[iMovReng][iMovCol+1] = cCharActual;
    
    if (cArrTablero[iMovReng-1][iMovCol-1] == cCharOponente)
        cArrTablero[iMovReng-1][iMovCol-1] = cCharActual;
    
    if (cArrTablero[iMovReng-1][iMovCol+1] == cCharOponente)
        cArrTablero[iMovReng-1][iMovCol+1] = cCharActual;
    
    if (cArrTablero[iMovReng+1][iMovCol-1] == cCharOponente)
        cArrTablero[iMovReng+1][iMovCol-1] = cCharActual;
    
    if (cArrTablero[iMovReng+1][iMovCol+1] == cCharOponente)
        cArrTablero[iMovReng+1][iMovCol+1] = cCharActual;
}

int main() {
    bool bSeguir = true;
    char cSeguirUser;
    char cArrTablero[6][6];
    int iTurno = 0;
    
    empezarJuego(cArrTablero);
    
    do {
        
        mostrarTablero(cArrTablero);
        
        moverJugador(cArrTablero, iTurno);
        
        do {
        cout << "Quieres seguir jugando? (s/n)" << endl;
        cin >> cSeguirUser;
        cSeguirUser = tolower(cSeguirUser);
        }
        while (cSeguirUser != 'n' && cSeguirUser != 's');
        
        if (cSeguirUser=='n'){
            verificarSeguir(cArrTablero, bSeguir);
            break;
        }

    } while (bSeguir == true );

    verGanador(cArrTablero);
    
    return 0;
}