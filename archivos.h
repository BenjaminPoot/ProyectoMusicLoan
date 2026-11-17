/*
 * Archivo: archivos.h
 * Proyecto: MusicLoan - Sistema de Gestion de Prestamos de Instrumentos Musicales
 * Proposito: Definicion de rutas de archivos planos y prototipos de persistencia (RF-08, RNF-05).
 * Autor: Angel Benjamin Pat Poot
 * Fecha: Noviembre 2026
 */

#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "inventario.h"
#include "prestamos.h"

#define ARCHIVO_INSTRUMENTOS "datos/instrumentos.txt"
#define ARCHIVO_PRESTAMOS "datos/prestamos.txt"

/*
 * Funcion: cargar_instrumentos
 * Proposito: Carga los registros de instrumentos desde ARCHIVO_INSTRUMENTOS al arreglo en RAM.
 * Parametros: inventario - arreglo destino; total - puntero al contador de instrumentos.
 * Retorno: 1 si se cargo correctamente o inicio vacio sin error critico, 0 si hubo error.
 */
int cargar_instrumentos(Instrumento *inventario, int *total);

/*
 * Funcion: guardar_instrumentos
 * Proposito: Guarda el arreglo completo de instrumentos en ARCHIVO_INSTRUMENTOS usando '|' como separador.
 * Parametros: inventario - arreglo origen; total - total de registros a escribir.
 * Retorno: 1 si la escritura fue exitosa, 0 si fallo la apertura o escritura del archivo.
 */
int guardar_instrumentos(const Instrumento *inventario, int total);

/*
 * Funcion: cargar_prestamos
 * Proposito: Carga el historial de prestamos desde ARCHIVO_PRESTAMOS al arreglo en RAM.
 * Parametros: prestamos - arreglo destino; total - puntero al contador de prestamos.
 * Retorno: 1 si se cargo correctamente, 0 si hubo error.
 */
int cargar_prestamos(Prestamo *prestamos, int *total);

/*
 * Funcion: guardar_prestamos
 * Proposito: Guarda todos los prestamos (activos y devueltos) en ARCHIVO_PRESTAMOS.
 * Parametros: prestamos - arreglo origen; total - total de registros a escribir.
 * Retorno: 1 si la escritura fue exitosa, 0 si ocurrio un error de archivo.
 */
int guardar_prestamos(const Prestamo *prestamos, int total);

#endif /* ARCHIVOS_H */
