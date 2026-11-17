/*
 * Archivo: main.c
 * Proyecto: MusicLoan - Sistema de Gestion de Prestamos de Instrumentos Musicales
 * Proposito: Modulo principal. Gestiona los menus de consola (IU-01 a IU-03) y coordina los modulos.
 * Autor: Angel Benjamin Pat Poot
 * Fecha: Noviembre 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"
#include "prestamos.h"
#include "archivos.h"
#include "validaciones.h"

/*
 * Funcion: menu_estudiantes
 * Proposito: Despliega y gestiona el submenu de consultas publicas para estudiantes (IU-02).
 * Parametros: inventario - arreglo de instrumentos; total_inst - total de instrumentos.
 * Retorno: void
 */
static void menu_estudiantes(const Instrumento *inventario, int total_inst) {
    int opcion = -1;

    while (opcion != 0) {
        printf("\n=== CONSULTA DE INSTRUMENTOS ===\n");
        printf("1. Ver inventario completo\n");
        printf("2. Buscar por codigo o nombre\n");
        printf("0. Regresar\n");

        if (!leer_entero("Opcion: ", &opcion)) {
            printf("Error: Ingrese una opcion numerica valida.\n");
            opcion = -1;
            continue;
        }

        switch (opcion) {
            case 1:
                consultar_inventario(inventario, total_inst);
                break;
            case 2:
                buscar_instrumento(inventario, total_inst);
                break;
            case 0:
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
}

/*
 * Funcion: menu_administracion
 * Proposito: Despliega y gestiona el panel administrativo del encargado (IU-03).
 * Parametros: inventario - arreglo de instrumentos; total_inst - puntero al total de instrumentos;
 *             prestamos - arreglo de prestamos; total_prest - puntero al total de prestamos.
 * Retorno: void
 */
static void menu_administracion(Instrumento *inventario, int *total_inst,
                                Prestamo *prestamos, int *total_prest) {
    int opcion = -1;

    while (opcion != 0) {
        printf("\n=== PANEL DEL ENCARGADO ===\n");
        printf("1. Registrar instrumento\n");
        printf("2. Consultar inventario\n");
        printf("3. Buscar instrumento\n");
        printf("4. Actualizar instrumento\n");
        printf("5. Registrar prestamo\n");
        printf("6. Registrar devolucion\n");
        printf("7. Consultar historial\n");
        printf("0. Regresar\n");

        if (!leer_entero("Opcion: ", &opcion)) {
            printf("Error: Ingrese una opcion numerica valida.\n");
            opcion = -1;
            continue;
        }

        switch (opcion) {
            case 1:
                if (registrar_instrumento(inventario, total_inst)) {
                    guardar_instrumentos(inventario, *total_inst);
                }
                break;
            case 2:
                consultar_inventario(inventario, *total_inst);
                break;
            case 3:
                buscar_instrumento(inventario, *total_inst);
                break;
            case 4:
                if (actualizar_instrumento(inventario, *total_inst)) {
                    guardar_instrumentos(inventario, *total_inst);
                }
                break;
            case 5:
                if (registrar_prestamo(inventario, *total_inst, prestamos, total_prest)) {
                    guardar_instrumentos(inventario, *total_inst);
                    guardar_prestamos(prestamos, *total_prest);
                }
                break;
            case 6:
                if (registrar_devolucion(inventario, *total_inst, prestamos, *total_prest)) {
                    guardar_instrumentos(inventario, *total_inst);
                    guardar_prestamos(prestamos, *total_prest);
                }
                break;
            case 7:
                consultar_historial(prestamos, *total_prest, inventario, *total_inst);
                break;
            case 0:
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
}

/*
 * Funcion: main
 * Proposito: Punto de entrada principal de MusicLoan (IU-01).
 * Parametros: ninguno
 * Retorno: 0 al finalizar correctamente.
 */
int main(void) {
    Instrumento inventario[MAX_INSTRUMENTOS];
    Prestamo prestamos[MAX_PRESTAMOS];
    int total_instrumentos = 0;
    int total_prestamos = 0;
    int opcion = -1;

    /* Carga inicial de persistencia local (RF-08) */
    cargar_instrumentos(inventario, &total_instrumentos);
    cargar_prestamos(prestamos, &total_prestamos);

    while (opcion != 0) {
        printf("\n+------------------------------------+\n");
        printf("|             MUSICLOAN              |\n");
        printf("| 1. Consultas para estudiantes      |\n");
        printf("| 2. Administracion de instrumentos  |\n");
        printf("| 0. Salir                           |\n");
        printf("+------------------------------------+\n");

        if (!leer_entero("Seleccione una opcion: ", &opcion)) {
            printf("Error: Ingrese una opcion numerica valida.\n");
            opcion = -1;
            continue;
        }

        switch (opcion) {
            case 1:
                menu_estudiantes(inventario, total_instrumentos);
                break;
            case 2:
                menu_administracion(inventario, &total_instrumentos, prestamos, &total_prestamos);
                break;
            case 0:
                guardar_instrumentos(inventario, total_instrumentos);
                guardar_prestamos(prestamos, total_prestamos);
                printf("Datos guardados. Saliendo de MusicLoan...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    }

    return 0;
}
