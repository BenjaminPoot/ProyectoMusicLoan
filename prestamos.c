/*
 * Archivo: prestamos.c
 * Proyecto: MusicLoan - Sistema de Gestion de Prestamos de Instrumentos Musicales
 * Proposito: Implementacion de prestamos, devoluciones e historial de movimientos (RF-05 a RF-07).
 * Autor: Angel Benjamin Pat Poot
 * Fecha: Noviembre 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "prestamos.h"
#include "validaciones.h"

/*
 * Funcion auxiliar interna: buscar_prestamo_activo
 * Proposito: Busca un prestamo activo coincidente con un folio (ej. P-0001) o codigo de instrumento.
 * Parametros: prestamos - arreglo de prestamos; total_prest - total de registros; criterio - folio o codigo.
 * Retorno: Indice del prestamo activo (>= 0) o -1 si no existe.
 */
static int buscar_prestamo_activo(const Prestamo *prestamos, int total_prest, const char *criterio) {
    char criterio_min[LONG_FOLIO];
    char folio_min[LONG_FOLIO];
    int es_numerico = 1;
    int codigo_buscado = -1;

    for (size_t i = 0; criterio[i] != '\0'; i++) {
        if (!isdigit((unsigned char)criterio[i])) {
            es_numerico = 0;
            break;
        }
    }

    if (es_numerico) {
        codigo_buscado = atoi(criterio);
    } else {
        convertir_minusculas(criterio, criterio_min, LONG_FOLIO);
    }

    for (int i = 0; i < total_prest; i++) {
        if (prestamos[i].estado != PRESTAMO_ACTIVO) {
            continue;
        }
        if (es_numerico) {
            if (prestamos[i].codigo_instrumento == codigo_buscado) {
                return i;
            }
        } else {
            convertir_minusculas(prestamos[i].folio, folio_min, LONG_FOLIO);
            if (strcmp(folio_min, criterio_min) == 0) {
                return i;
            }
        }
    }
    return -1;
}

int registrar_prestamo(Instrumento *inventario, int total_inst,
                       Prestamo *prestamos, int *total_prest) {
    int codigo = 0;
    int idx_inst = -1;
    Prestamo nuevo;

    printf("\n=== REGISTRAR PRESTAMO ===\n");

    if (total_inst == 0) {
        printf("Error: No hay instrumentos registrados en el inventario.\n");
        return 0;
    }

    if (*total_prest >= MAX_PRESTAMOS) {
        printf("Error: Capacidad maxima de historial de prestamos alcanzada (%d).\n", MAX_PRESTAMOS);
        return 0;
    }

    if (!leer_entero("Codigo del instrumento: ", &codigo)) {
        printf("Error: Codigo no valido. Operacion cancelada.\n");
        return 0;
    }

    idx_inst = buscar_indice_instrumento(inventario, total_inst, codigo);
    if (idx_inst == -1) {
        printf("Error: No existe un instrumento con el codigo %d. Operacion cancelada.\n", codigo);
        return 0;
    }

    printf("Instrumento: %s\n", inventario[idx_inst].nombre);

    /* Regla de negocio: No prestar si ya se encuentra ocupado */
    if (inventario[idx_inst].estado != ESTADO_DISPONIBLE) {
        printf("Estado: PRESTADO\n");
        printf("Aviso: El instrumento ya tiene un prestamo activo. Operacion cancelada.\n");
        return 0;
    }

    printf("Estado: DISPONIBLE\n");

    /* Captura de matricula no vacia */
    while (1) {
        leer_cadena("Matricula del estudiante: ", nuevo.matricula, LONG_MATRICULA);
        if (es_cadena_vacia(nuevo.matricula)) {
            printf("Error: La matricula no puede estar vacia.\n");
        } else if (contiene_delimitador(nuevo.matricula)) {
            printf("Error: La matricula no puede contener el caracter '|'.\n");
        } else {
            break;
        }
    }

    /* Captura de fecha valida AAAA-MM-DD */
    while (1) {
        leer_cadena("Fecha (AAAA-MM-DD): ", nuevo.fecha_prestamo, LONG_FECHA);
        if (!validar_fecha(nuevo.fecha_prestamo)) {
            printf("Error: Fecha invalida. Use el formato AAAA-MM-DD (ej. 2026-10-21).\n");
        } else {
            break;
        }
    }

    if (!leer_confirmacion("Confirmar prestamo (S/N): ")) {
        printf("Prestamo cancelado por el usuario.\n");
        return 0;
    }

    /* Generar folio consecutivo y actualizar estado */
    snprintf(nuevo.folio, LONG_FOLIO, "P-%04d", (*total_prest + 1) % 10000);
    nuevo.codigo_instrumento = inventario[idx_inst].codigo;
    strcpy(nuevo.fecha_devolucion, "PENDIENTE");
    nuevo.estado = PRESTAMO_ACTIVO;

    prestamos[*total_prest] = nuevo;
    (*total_prest)++;
    inventario[idx_inst].estado = ESTADO_PRESTADO;

    printf("Prestamo registrado. Folio: %s\n", nuevo.folio);
    return 1;
}

int registrar_devolucion(Instrumento *inventario, int total_inst,
                         Prestamo *prestamos, int total_prest) {
    char entrada[LONG_FOLIO];
    char fecha_dev[LONG_FECHA];
    int idx_prest = -1;
    int idx_inst = -1;

    printf("\n=== REGISTRAR DEVOLUCION ===\n");

    if (total_prest == 0) {
        printf("No existen prestamos registrados.\n");
        return 0;
    }

    leer_cadena("Folio o codigo: ", entrada, LONG_FOLIO);
    if (es_cadena_vacia(entrada)) {
        printf("Error: Debe ingresar un folio o codigo de instrumento.\n");
        return 0;
    }

    idx_prest = buscar_prestamo_activo(prestamos, total_prest, entrada);
    if (idx_prest == -1) {
        printf("Aviso: No existe un prestamo activo asociado a '%s' (o ya fue devuelto).\n", entrada);
        return 0;
    }

    idx_inst = buscar_indice_instrumento(inventario, total_inst, prestamos[idx_prest].codigo_instrumento);

    printf("Folio activo: %s\n", prestamos[idx_prest].folio);
    printf("Estudiante: %s\n", prestamos[idx_prest].matricula);
    if (idx_inst != -1) {
        printf("Instrumento: %d %s\n", inventario[idx_inst].codigo, inventario[idx_inst].nombre);
    } else {
        printf("Instrumento: %d\n", prestamos[idx_prest].codigo_instrumento);
    }
    printf("Fecha de prestamo: %s\n", prestamos[idx_prest].fecha_prestamo);

    /* Validar fecha de devolucion >= fecha de prestamo */
    while (1) {
        leer_cadena("Fecha devolucion (AAAA-MM-DD): ", fecha_dev, LONG_FECHA);
        if (!validar_fecha(fecha_dev)) {
            printf("Error: Fecha invalida. Use el formato AAAA-MM-DD.\n");
            continue;
        }
        if (comparar_fechas(prestamos[idx_prest].fecha_prestamo, fecha_dev) > 0) {
            printf("Error: La fecha de devolucion (%s) no puede ser anterior al prestamo (%s).\n",
                   fecha_dev, prestamos[idx_prest].fecha_prestamo);
            continue;
        }
        break;
    }

    strcpy(prestamos[idx_prest].fecha_devolucion, fecha_dev);
    prestamos[idx_prest].estado = PRESTAMO_DEVUELTO;

    if (idx_inst != -1) {
        inventario[idx_inst].estado = ESTADO_DISPONIBLE;
    }

    printf("Devolucion registrada. Instrumento disponible.\n");
    return 1;
}

void consultar_historial(const Prestamo *prestamos, int total_prest,
                         const Instrumento *inventario, int total_inst) {
    int filtro = 0;
    int mostrados = 0;

    printf("\n=== HISTORIAL DE PRESTAMOS ===\n");

    if (total_prest == 0) {
        printf("No hay operaciones de prestamo registradas.\n");
        return;
    }

    printf("1. Mostrar todos\n");
    printf("2. Mostrar solo activos\n");
    printf("3. Mostrar solo devueltos\n");
    printf("0. Regresar\n");

    if (!leer_entero("Seleccione filtro: ", &filtro) || filtro < 0 || filtro > 3) {
        printf("Opcion no valida.\n");
        return;
    }

    if (filtro == 0) {
        return;
    }

    printf("\n%-8s %-6s %-22s %-14s %-12s %-12s %-10s\n",
           "FOLIO", "COD.", "INSTRUMENTO", "MATRICULA", "F.PRESTAMO", "F.DEVOLUC.", "ESTADO");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < total_prest; i++) {
        if (filtro == 2 && prestamos[i].estado != PRESTAMO_ACTIVO) {
            continue;
        }
        if (filtro == 3 && prestamos[i].estado != PRESTAMO_DEVUELTO) {
            continue;
        }

        int idx_inst = buscar_indice_instrumento(inventario, total_inst, prestamos[i].codigo_instrumento);
        const char *nombre_inst = (idx_inst != -1) ? inventario[idx_inst].nombre : "Desconocido";

        printf("%-8s %-6d %-22s %-14s %-12s %-12s %-10s\n",
               prestamos[i].folio,
               prestamos[i].codigo_instrumento,
               nombre_inst,
               prestamos[i].matricula,
               prestamos[i].fecha_prestamo,
               prestamos[i].fecha_devolucion,
               prestamos[i].estado == PRESTAMO_ACTIVO ? "Activo" : "Devuelto");
        mostrados++;
    }

    if (mostrados == 0) {
        printf("No se encontraron registros para el filtro seleccionado.\n");
    }
}
