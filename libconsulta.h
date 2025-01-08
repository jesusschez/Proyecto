#ifndef LIBCONSULTA_H
#define LIBCONSULTA_H

#include <mariadb/mysql.h>

// Prototipo para la función que conecta a la base de datos
MYSQL* conectar_bd();

// Prototipo para la función que escribe en la base de datos
void escribir_bd(MYSQL *conn, const char *nombre, const char *apellido1, const char *apellido2, 
                 const char *matricula, const char *carrera, const char *materias, 
                 const char *calificaciones);

#endif // LIBCONSULTA_H
