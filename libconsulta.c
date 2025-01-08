#include <mariadb/mysql.h>
#include <stdio.h>
#include <stdlib.h>

// Conectar a la base de datos
MYSQL* conectar_bd() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "Error al inicializar MySQL\n");
        exit(1);
    }

    if (!mysql_real_connect(conn, "localhost", "root", "tesoem", "universidad", 0, NULL, 0)) {
        fprintf(stderr, "Error de conexión: %s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

// Escribir en la base de datos
void escribir_bd(MYSQL *conn, const char *nombre, const char *apellido1, const char *apellido2, const char *matricula, const char *carrera, const char *materias, const char *calificaciones) {
    char query[1024];
    snprintf(query, sizeof(query),
             "INSERT INTO estudiantes (nombre, apellido1, apellido2, matricula, carrera, materias, calificaciones) "
             "VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s')",
             nombre, apellido1, apellido2, matricula, carrera, materias, calificaciones);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar datos: %s\n", mysql_error(conn));
    }
}
