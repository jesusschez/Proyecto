#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mosquitto.h>
#include "libconsulta.h"

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    if (message->payloadlen) {
        char *datos = strdup((char *)message->payload);
        char nombre[50], apellido1[50], apellido2[50], matricula[15], carrera[50], materias[500], calificaciones[500];

        sscanf(datos, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]",
               nombre, apellido1, apellido2, matricula, carrera, materias, calificaciones);

        MYSQL *conn = conectar_bd();
        escribir_bd(conn, nombre, apellido1, apellido2, matricula, carrera, materias, calificaciones);
        mysql_close(conn);

        free(datos);
    }
}

int main() {
    struct mosquitto *mosq;
    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error al crear la instancia de Mosquitto\n");
        return 1;
    }

    mosquitto_message_callback_set(mosq, on_message);

    if (mosquitto_connect(mosq, "localhost", 1883, 60)) {
        fprintf(stderr, "No se pudo conectar al broker MQTT\n");
        return 1;
    }

    mosquitto_subscribe(mosq, NULL, "universidad/estudiantes", 0);

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
