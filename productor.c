#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include <stdlib.h>

// Estructura para el mensaje
typedef struct {
    char nombre[50];
    char apellido1[50];
    char apellido2[50];
    char matricula[15];
    char carrera[50];
    char materias[500];
    char calificaciones[500];
} Estudiante;

void publicar_mensaje(struct mosquitto *mosq, const Estudiante *estudiante) {
    char mensaje[1024];
    snprintf(mensaje, sizeof(mensaje), "%s;%s;%s;%s;%s;%s;%s",
             estudiante->nombre, estudiante->apellido1, estudiante->apellido2,
             estudiante->matricula, estudiante->carrera,
             estudiante->materias, estudiante->calificaciones);

    mosquitto_publish(mosq, NULL, "universidad/estudiantes", strlen(mensaje), mensaje, 0, false);
}

int main() {
    struct mosquitto *mosq;
    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error al crear la instancia de Mosquitto\n");
        return 1;
    }

    if (mosquitto_connect(mosq, "localhost", 1883, 60)) {
        fprintf(stderr, "No se pudo conectar al broker MQTT\n");
        return 1;
    }

    Estudiante estudiante = {
        "Jesus", "Arroyo", "Sanchez", "123456", "Ingeniería en Sistemas Computacionales", "Base de datos,Sistemas Operativos", "90,100"
    };

    publicar_mensaje(mosq, &estudiante);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
