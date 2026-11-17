/*
 * Archivo: validaciones.c
 * Proyecto: MusicLoan - Sistema de Gestion de Prestamos de Instrumentos Musicales
 * Proposito: Implementacion de funciones de lectura segura y validacion de datos (RNF-01, RNF-04).
 * Autor: Angel Benjamin Pat Poot
 * Fecha: Noviembre 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

void limpiar_salto_linea(char *cadena) {
    size_t longitud = strlen(cadena);
    if (longitud > 0 && cadena[longitud - 1] == '\n') {
        cadena[longitud - 1] = '\0';
    }
}

int contiene_delimitador(const char *cadena) {
    return (strchr(cadena, '|') != NULL) ? 1 : 0;
}

int es_cadena_vacia(const char *cadena) {
    size_t i = 0;
    while (cadena[i] != '\0') {
        if (!isspace((unsigned char)cadena[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

int leer_entero(const char *mensaje, int *destino) {
    char buffer[64];
    char *fin_ptr = NULL;
    long valor = 0;

    printf("%s", mensaje);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    /* Si la entrada excede el buffer, vaciar el resto de la linea en stdin */
    if (strchr(buffer, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* Descartar caracteres excedentes */
        }
    }

    limpiar_salto_linea(buffer);
    if (es_cadena_vacia(buffer)) {
        return 0;
    }

    valor = strtol(buffer, &fin_ptr, 10);
    while (*fin_ptr != '\0') {
        if (!isspace((unsigned char)*fin_ptr)) {
            return 0;
        }
        fin_ptr++;
    }

    *destino = (int)valor;
    return 1;
}

void leer_cadena(const char *mensaje, char *destino, int tamano) {
    printf("%s", mensaje);
    if (fgets(destino, tamano, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }

    /* Limpiar excedente en stdin si el usuario escribio mas caracteres que el limite */
    if (strchr(destino, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* Descartar caracteres excedentes */
        }
    }

    limpiar_salto_linea(destino);
}

int validar_fecha(const char *fecha) {
    int anio = 0;
    int mes = 0;
    int dia = 0;
    int dias_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (strlen(fecha) != 10) {
        return 0;
    }

    if (fecha[4] != '-' || fecha[7] != '-') {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            continue;
        }
        if (!isdigit((unsigned char)fecha[i])) {
            return 0;
        }
    }

    anio = (fecha[0] - '0') * 1000 + (fecha[1] - '0') * 100 +
           (fecha[2] - '0') * 10 + (fecha[3] - '0');
    mes = (fecha[5] - '0') * 10 + (fecha[6] - '0');
    dia = (fecha[8] - '0') * 10 + (fecha[9] - '0');

    if (anio < 2000 || anio > 2100) {
        return 0;
    }
    if (mes < 1 || mes > 12) {
        return 0;
    }

    /* Ajuste de febrero para anio bisiesto */
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
        dias_mes[1] = 29;
    }

    if (dia < 1 || dia > dias_mes[mes - 1]) {
        return 0;
    }

    return 1;
}

int comparar_fechas(const char *fecha_inicio, const char *fecha_fin) {
    /* Al estar en formato ISO AAAA-MM-DD, la comparacion lexicografica es cronologica */
    return strcmp(fecha_inicio, fecha_fin);
}

int leer_confirmacion(const char *mensaje) {
    char respuesta[16];
    while (1) {
        leer_cadena(mensaje, respuesta, sizeof(respuesta));
        if (strlen(respuesta) == 1) {
            if (respuesta[0] == 'S' || respuesta[0] == 's') {
                return 1;
            }
            if (respuesta[0] == 'N' || respuesta[0] == 'n') {
                return 0;
            }
        }
        printf("Entrada no valida. Por favor responda S o N.\n");
    }
}

void convertir_minusculas(const char *origen, char *destino, int tamano) {
    int i = 0;
    while (origen[i] != '\0' && i < tamano - 1) {
        destino[i] = (char)tolower((unsigned char)origen[i]);
        i++;
    }
    destino[i] = '\0';
}
