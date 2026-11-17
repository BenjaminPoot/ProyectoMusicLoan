/*
 * Archivo: inventario.c
 * Proyecto: MusicLoan - Sistema de Gestion de Prestamos de Instrumentos Musicales
 * Proposito: Implementacion de operaciones CRUD y consultas del catalogo de instrumentos (RF-01 a RF-04).
 * Autor: Angel Benjamin Pat Poot
 * Fecha: Noviembre 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inventario.h"
#include "validaciones.h"

int buscar_indice_instrumento(const Instrumento *inventario, int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (inventario[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int registrar_instrumento(Instrumento *inventario, int *total) {
    Instrumento nuevo;
    int codigo_valido = 0;

    printf("\n=== REGISTRAR INSTRUMENTO ===\n");

    if (*total >= MAX_INSTRUMENTOS) {
        printf("Error: Capacidad maxima del inventario alcanzada (%d).\n", MAX_INSTRUMENTOS);
        return 0;
    }

    /* Captura y validacion de codigo numerico unico */
    while (!codigo_valido) {
        if (!leer_entero("Codigo numerico unico (0 para cancelar): ", &nuevo.codigo)) {
            printf("Error: Debe ingresar un numero entero valido.\n");
            continue;
        }
        if (nuevo.codigo == 0) {
            printf("Registro cancelado.\n");
            return 0;
        }
        if (nuevo.codigo < 0) {
            printf("Error: El codigo debe ser un numero positivo.\n");
            continue;
        }
        if (buscar_indice_instrumento(inventario, *total, nuevo.codigo) != -1) {
            printf("Error: Ya existe un instrumento con el codigo %d. Intente con otro.\n", nuevo.codigo);
            continue;
        }
        codigo_valido = 1;
    }

    /* Captura y validacion de nombre */
    while (1) {
        leer_cadena("Nombre del instrumento: ", nuevo.nombre, LONG_NOMBRE);
        if (es_cadena_vacia(nuevo.nombre)) {
            printf("Error: El nombre no puede estar vacio.\n");
        } else if (contiene_delimitador(nuevo.nombre)) {
            printf("Error: El nombre no puede contener el caracter '|'.\n");
        } else {
            break;
        }
    }

    /* Captura y validacion de categoria */
    while (1) {
        leer_cadena("Categoria (ej. Cuerda, Teclado, Percusion, Viento): ", nuevo.categoria, LONG_NOMBRE);
        if (es_cadena_vacia(nuevo.categoria)) {
            printf("Error: La categoria no puede estar vacia.\n");
        } else if (contiene_delimitador(nuevo.categoria)) {
            printf("Error: La categoria no puede contener el caracter '|'.\n");
        } else {
            break;
        }
    }

    nuevo.estado = ESTADO_DISPONIBLE;
    inventario[*total] = nuevo;
    (*total)++;

    printf("Instrumento registrado correctamente con estado DISPONIBLE.\n");
    return 1;
}

void consultar_inventario(const Instrumento *inventario, int total) {
    printf("\n=== INVENTARIO DE INSTRUMENTOS ===\n");

    if (total == 0) {
        printf("Inventario vacio. No hay instrumentos registrados.\n");
        return;
    }

    printf("%-6s %-26s %-16s %-12s\n", "COD.", "NOMBRE", "TIPO", "ESTADO");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%-6d %-26s %-16s %-12s\n",
               inventario[i].codigo,
               inventario[i].nombre,
               inventario[i].categoria,
               inventario[i].estado == ESTADO_DISPONIBLE ? "Disponible" : "Prestado");
    }
}

void buscar_instrumento(const Instrumento *inventario, int total) {
    char criterio[LONG_NOMBRE];
    char criterio_min[LONG_NOMBRE];
    char nombre_min[LONG_NOMBRE];
    int es_numerico = 1;
    int encontrados = 0;

    printf("\n=== BUSCAR INSTRUMENTO ===\n");

    if (total == 0) {
        printf("Inventario vacio. No hay registros para buscar.\n");
        return;
    }

    leer_cadena("Ingrese codigo o nombre para buscar: ", criterio, LONG_NOMBRE);
    if (es_cadena_vacia(criterio)) {
        printf("Error: Debe ingresar un criterio de busqueda.\n");
        return;
    }

    for (size_t i = 0; criterio[i] != '\0'; i++) {
        if (!isdigit((unsigned char)criterio[i])) {
            es_numerico = 0;
            break;
        }
    }

    if (es_numerico) {
        int codigo_buscado = atoi(criterio);
        int idx = buscar_indice_instrumento(inventario, total, codigo_buscado);
        if (idx != -1) {
            printf("Resultado: %d | %s | %s | %s\n",
                   inventario[idx].codigo,
                   inventario[idx].nombre,
                   inventario[idx].categoria,
                   inventario[idx].estado == ESTADO_DISPONIBLE ? "Disponible" : "Prestado");
            encontrados = 1;
        }
    } else {
        convertir_minusculas(criterio, criterio_min, LONG_NOMBRE);
        for (int i = 0; i < total; i++) {
            convertir_minusculas(inventario[i].nombre, nombre_min, LONG_NOMBRE);
            if (strstr(nombre_min, criterio_min) != NULL) {
                printf("Resultado: %d | %s | %s | %s\n",
                       inventario[i].codigo,
                       inventario[i].nombre,
                       inventario[i].categoria,
                       inventario[i].estado == ESTADO_DISPONIBLE ? "Disponible" : "Prestado");
                encontrados++;
            }
        }
    }

    if (encontrados == 0) {
        printf("No encontrado.\n");
    }
}

int actualizar_instrumento(Instrumento *inventario, int total) {
    int codigo = 0;
    int idx = -1;
    char nuevo_nombre[LONG_NOMBRE];
    char nueva_categoria[LONG_NOMBRE];
    int modificado = 0;

    printf("\n=== ACTUALIZAR INSTRUMENTO ===\n");

    if (total == 0) {
        printf("Inventario vacio.\n");
        return 0;
    }

    if (!leer_entero("Ingrese el codigo del instrumento a actualizar: ", &codigo)) {
        printf("Error: Codigo no valido.\n");
        return 0;
    }

    idx = buscar_indice_instrumento(inventario, total, codigo);
    if (idx == -1) {
        printf("Error: No existe un instrumento con el codigo %d.\n", codigo);
        return 0;
    }

    printf("Datos actuales -> Codigo: %d | Nombre: %s | Categoria: %s | Estado: %s\n",
           inventario[idx].codigo,
           inventario[idx].nombre,
           inventario[idx].categoria,
           inventario[idx].estado == ESTADO_DISPONIBLE ? "Disponible" : "Prestado");
    printf("(Presione Enter sin escribir texto para conservar el dato actual)\n");

    while (1) {
        leer_cadena("Nuevo nombre: ", nuevo_nombre, LONG_NOMBRE);
        if (es_cadena_vacia(nuevo_nombre)) {
            break; /* Conservar nombre original */
        }
        if (contiene_delimitador(nuevo_nombre)) {
            printf("Error: El nombre no puede contener el caracter '|'.\n");
            continue;
        }
        strcpy(inventario[idx].nombre, nuevo_nombre);
        modificado = 1;
        break;
    }

    while (1) {
        leer_cadena("Nueva categoria: ", nueva_categoria, LONG_NOMBRE);
        if (es_cadena_vacia(nueva_categoria)) {
            break; /* Conservar categoria original */
        }
        if (contiene_delimitador(nueva_categoria)) {
            printf("Error: La categoria no puede contener el caracter '|'.\n");
            continue;
        }
        strcpy(inventario[idx].categoria, nueva_categoria);
        modificado = 1;
        break;
    }

    if (modificado) {
        printf("Instrumento actualizado correctamente.\n");
        return 1;
    }

    printf("No se realizaron modificaciones.\n");
    return 0;
}
