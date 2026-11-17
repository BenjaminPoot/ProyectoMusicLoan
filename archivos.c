/*
 * Archivo: archivos.c
 * Proyecto: MusicLoan - Sistema de Gestion de Prestamos de Instrumentos Musicales
 * Proposito: Implementacion de lectura y escritura persistente en archivos de texto (RF-08, RNF-05).
 * Autor: Angel Benjamin Pat Poot
 * Fecha: Noviembre 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivos.h"
#include "validaciones.h"

int cargar_instrumentos(Instrumento *inventario, int *total) {
    FILE *archivo = fopen(ARCHIVO_INSTRUMENTOS, "r");
    char linea[256];

    *total = 0;
    if (archivo == NULL) {
        /* Si el archivo aun no existe, se inicia con inventario vacio sin abortar */
        printf("Aviso: No se encontro '%s'. Se iniciara con inventario vacio.\n", ARCHIVO_INSTRUMENTOS);
        return 1;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        limpiar_salto_linea(linea);
        if (es_cadena_vacia(linea)) {
            continue;
        }
        if (*total >= MAX_INSTRUMENTOS) {
            printf("Aviso: Se alcanzo el limite de %d instrumentos al cargar.\n", MAX_INSTRUMENTOS);
            break;
        }

        Instrumento temp;
        if (sscanf(linea, "%d|%59[^|]|%59[^|]|%d",
                   &temp.codigo,
                   temp.nombre,
                   temp.categoria,
                   &temp.estado) == 4) {
            inventario[*total] = temp;
            (*total)++;
        }
    }

    if (fclose(archivo) != 0) {
        printf("Advertencia: Error al cerrar '%s'.\n", ARCHIVO_INSTRUMENTOS);
        return 0;
    }
    return 1;
}

int guardar_instrumentos(const Instrumento *inventario, int total) {
    FILE *archivo = fopen(ARCHIVO_INSTRUMENTOS, "w");
    if (archivo == NULL) {
        printf("Error critico: No se pudo abrir '%s' para escritura.\n", ARCHIVO_INSTRUMENTOS);
        return 0;
    }

    for (int i = 0; i < total; i++) {
        if (fprintf(archivo, "%d|%s|%s|%d\n",
                    inventario[i].codigo,
                    inventario[i].nombre,
                    inventario[i].categoria,
                    inventario[i].estado) < 0) {
            printf("Error critico: Fallo la escritura en '%s'.\n", ARCHIVO_INSTRUMENTOS);
            fclose(archivo);
            return 0;
        }
    }

    if (fclose(archivo) != 0) {
        printf("Error: No se pudo cerrar correctamente '%s'.\n", ARCHIVO_INSTRUMENTOS);
        return 0;
    }
    return 1;
}

int cargar_prestamos(Prestamo *prestamos, int *total) {
    FILE *archivo = fopen(ARCHIVO_PRESTAMOS, "r");
    char linea[256];

    *total = 0;
    if (archivo == NULL) {
        printf("Aviso: No se encontro '%s'. Se iniciara historial vacio.\n", ARCHIVO_PRESTAMOS);
        return 1;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        limpiar_salto_linea(linea);
        if (es_cadena_vacia(linea)) {
            continue;
        }
        if (*total >= MAX_PRESTAMOS) {
            printf("Aviso: Se alcanzo el limite de %d prestamos al cargar.\n", MAX_PRESTAMOS);
            break;
        }

        Prestamo temp;
        if (sscanf(linea, "%9[^|]|%d|%19[^|]|%11[^|]|%11[^|]|%d",
                   temp.folio,
                   &temp.codigo_instrumento,
                   temp.matricula,
                   temp.fecha_prestamo,
                   temp.fecha_devolucion,
                   &temp.estado) == 6) {
            prestamos[*total] = temp;
            (*total)++;
        }
    }

    if (fclose(archivo) != 0) {
        printf("Advertencia: Error al cerrar '%s'.\n", ARCHIVO_PRESTAMOS);
        return 0;
    }
    return 1;
}

int guardar_prestamos(const Prestamo *prestamos, int total) {
    FILE *archivo = fopen(ARCHIVO_PRESTAMOS, "w");
    if (archivo == NULL) {
        printf("Error critico: No se pudo abrir '%s' para escritura.\n", ARCHIVO_PRESTAMOS);
        return 0;
    }

    for (int i = 0; i < total; i++) {
        if (fprintf(archivo, "%s|%d|%s|%s|%s|%d\n",
                    prestamos[i].folio,
                    prestamos[i].codigo_instrumento,
                    prestamos[i].matricula,
                    prestamos[i].fecha_prestamo,
                    prestamos[i].fecha_devolucion,
                    prestamos[i].estado) < 0) {
            printf("Error critico: Fallo la escritura en '%s'.\n", ARCHIVO_PRESTAMOS);
            fclose(archivo);
            return 0;
        }
    }

    if (fclose(archivo) != 0) {
        printf("Error: No se pudo cerrar correctamente '%s'.\n", ARCHIVO_PRESTAMOS);
        return 0;
    }
    return 1;
}
