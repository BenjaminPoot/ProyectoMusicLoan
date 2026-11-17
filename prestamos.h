/*
 * Archivo: prestamos.h
 * Proyecto: MusicLoan - Sistema de Gestion de Prestamos de Instrumentos Musicales
 * Proposito: Definicion de la estructura Prestamo y prototipos del modulo de transacciones.
 * Autor: Angel Benjamin Pat Poot
 * Fecha: Noviembre 2026
 */

#ifndef PRESTAMOS_H
#define PRESTAMOS_H

#include "inventario.h"

#define MAX_PRESTAMOS 1000
#define LONG_MATRICULA 20
#define LONG_FECHA 12
#define LONG_FOLIO 10

#define PRESTAMO_DEVUELTO 0
#define PRESTAMO_ACTIVO 1

typedef struct {
    char folio[LONG_FOLIO];
    int codigo_instrumento;
    char matricula[LONG_MATRICULA];
    char fecha_prestamo[LONG_FECHA];
    char fecha_devolucion[LONG_FECHA];
    int estado; /* 1 = Activo, 0 = Devuelto */
} Prestamo;

/*
 * Funcion: registrar_prestamo
 * Proposito: Crea un prestamo activo para un instrumento disponible y actualiza su estado (RF-05, CU-05).
 * Parametros: inventario - arreglo de instrumentos; total_inst - total de instrumentos;
 *             prestamos - arreglo de prestamos; total_prest - puntero al total de prestamos.
 * Retorno: 1 si el prestamo fue registrado, 0 si se cancelo o no cumple reglas de negocio.
 */
int registrar_prestamo(Instrumento *inventario, int total_inst,
                       Prestamo *prestamos, int *total_prest);

/*
 * Funcion: registrar_devolucion
 * Proposito: Cierra un prestamo activo por folio o codigo de equipo y libera el instrumento (RF-06, CU-06).
 * Parametros: inventario - arreglo de instrumentos; total_inst - total de instrumentos;
 *             prestamos - arreglo de prestamos; total_prest - total de prestamos.
 * Retorno: 1 si la devolucion fue registrada, 0 si no existe prestamo activo o falla validacion.
 */
int registrar_devolucion(Instrumento *inventario, int total_inst,
                         Prestamo *prestamos, int total_prest);

/*
 * Funcion: consultar_historial
 * Proposito: Muestra el historial de prestamos filtrado por todos, activos o devueltos (RF-07, CU-07).
 * Parametros: prestamos - arreglo de prestamos; total_prest - total de prestamos;
 *             inventario - arreglo de instrumentos (para mostrar nombre); total_inst - total de instrumentos.
 * Retorno: void
 */
void consultar_historial(const Prestamo *prestamos, int total_prest,
                         const Instrumento *inventario, int total_inst);

#endif /* PRESTAMOS_H */
