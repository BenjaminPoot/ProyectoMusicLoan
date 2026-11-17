/*
 * Archivo: inventario.h
 * Proyecto: MusicLoan - Sistema de Gestion de Prestamos de Instrumentos Musicales
 * Proposito: Definicion de constantes, estructura Instrumento y prototipos del modulo de inventario.
 * Autor: Angel Benjamin Pat Poot
 * Fecha: Noviembre 2026
 */

#ifndef INVENTARIO_H
#define INVENTARIO_H

#define MAX_INSTRUMENTOS 200
#define LONG_NOMBRE 60

#define ESTADO_DISPONIBLE 0
#define ESTADO_PRESTADO 1

typedef struct {
    int codigo;
    char nombre[LONG_NOMBRE];
    char categoria[LONG_NOMBRE];
    int estado; /* 0 = Disponible, 1 = Prestado */
} Instrumento;

/*
 * Funcion: buscar_indice_instrumento
 * Proposito: Localiza la posicion en el arreglo de un instrumento dado su codigo unico.
 * Parametros: inventario - arreglo de instrumentos; total - cantidad actual; codigo - ID a buscar.
 * Retorno: Indice (>= 0) si existe, o -1 si no se encuentra.
 */
int buscar_indice_instrumento(const Instrumento *inventario, int total, int codigo);

/*
 * Funcion: registrar_instrumento
 * Proposito: Da de alta un nuevo instrumento validando codigo unico y campos no vacios (RF-01, CU-01).
 * Parametros: inventario - arreglo de instrumentos; total - puntero al total de registros.
 * Retorno: 1 si se registro con exito, 0 si se cancelo o hubo error.
 */
int registrar_instrumento(Instrumento *inventario, int *total);

/*
 * Funcion: consultar_inventario
 * Proposito: Muestra en consola la tabla completa de instrumentos y su disponibilidad (RF-02, CU-02).
 * Parametros: inventario - arreglo de instrumentos; total - cantidad de registros.
 * Retorno: void
 */
void consultar_inventario(const Instrumento *inventario, int total);

/*
 * Funcion: buscar_instrumento
 * Proposito: Busca instrumentos por codigo exacto o coincidencia parcial en el nombre (RF-03, CU-03).
 * Parametros: inventario - arreglo de instrumentos; total - cantidad de registros.
 * Retorno: void
 */
void buscar_instrumento(const Instrumento *inventario, int total);

/*
 * Funcion: actualizar_instrumento
 * Proposito: Modifica nombre o categoria de un instrumento existente sin alterar su codigo (RF-04, CU-04).
 * Parametros: inventario - arreglo de instrumentos; total - cantidad de registros.
 * Retorno: 1 si se actualizo correctamente, 0 si no hubo cambios o no existe.
 */
int actualizar_instrumento(Instrumento *inventario, int total);

#endif /* INVENTARIO_H */
