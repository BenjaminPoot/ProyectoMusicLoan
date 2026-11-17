/*
 * Archivo: validaciones.h
 * Proyecto: MusicLoan - Sistema de Gestion de Prestamos de Instrumentos Musicales
 * Proposito: Prototipos de funciones transversales para lectura segura y validacion de entradas.
 * Autor: Angel Benjamin Pat Poot
 * Fecha: Noviembre 2026
 */

#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/*
 * Funcion: limpiar_salto_linea
 * Proposito: Elimina el caracter de nueva linea ('\n') al final de una cadena leida con fgets().
 * Parametros: cadena - arreglo de caracteres a limpiar.
 * Retorno: void
 */
void limpiar_salto_linea(char *cadena);

/*
 * Funcion: contiene_delimitador
 * Proposito: Verifica si una cadena contiene el caracter '|' usado como separador en archivos.
 * Parametros: cadena - cadena de texto a evaluar.
 * Retorno: 1 si contiene '|', 0 en caso contrario.
 */
int contiene_delimitador(const char *cadena);

/*
 * Funcion: es_cadena_vacia
 * Proposito: Comprueba si una cadena esta vacia o contiene unicamente espacios en blanco.
 * Parametros: cadena - cadena de texto a evaluar.
 * Retorno: 1 si esta vacia, 0 si tiene contenido valido.
 */
int es_cadena_vacia(const char *cadena);

/*
 * Funcion: leer_entero
 * Proposito: Lee de forma segura un numero entero desde consola evitando desbordamientos.
 * Parametros: mensaje - texto a mostrar al usuario; destino - puntero donde se guarda el entero.
 * Retorno: 1 si la lectura fue un entero valido, 0 si el formato es invalido.
 */
int leer_entero(const char *mensaje, int *destino);

/*
 * Funcion: leer_cadena
 * Proposito: Lee una linea de texto controlada por longitud y limpia el buffer si excede el tamano.
 * Parametros: mensaje - texto a mostrar; destino - buffer de salida; tamano - capacidad del buffer.
 * Retorno: void
 */
void leer_cadena(const char *mensaje, char *destino, int tamano);

/*
 * Funcion: validar_fecha
 * Proposito: Valida que una fecha cumpla el formato AAAA-MM-DD y corresponda a un dia valido del calendario.
 * Parametros: fecha - cadena con la fecha a validar.
 * Retorno: 1 si la fecha es valida, 0 si es incorrecta.
 */
int validar_fecha(const char *fecha);

/*
 * Funcion: comparar_fechas
 * Proposito: Compara cronologicamente dos fechas previamente validadas en formato AAAA-MM-DD.
 * Parametros: fecha_inicio - primera fecha; fecha_fin - segunda fecha.
 * Retorno: < 0 si fecha_inicio < fecha_fin; 0 si son iguales; > 0 si fecha_inicio > fecha_fin.
 */
int comparar_fechas(const char *fecha_inicio, const char *fecha_fin);

/*
 * Funcion: leer_confirmacion
 * Proposito: Solicita una confirmacion binaria (S/N) al usuario.
 * Parametros: mensaje - pregunta de confirmacion a mostrar.
 * Retorno: 1 si el usuario responde 'S' o 's', 0 si responde 'N' o 'n'.
 */
int leer_confirmacion(const char *mensaje);

/*
 * Funcion: convertir_minusculas
 * Proposito: Convierte una cadena a minusculas en un buffer destino para busquedas sin distincion de mayusculas.
 * Parametros: origen - cadena original; destino - buffer convertido; tamano - longitud maxima.
 * Retorno: void
 */
void convertir_minusculas(const char *origen, char *destino, int tamano);

#endif /* VALIDACIONES_H */
