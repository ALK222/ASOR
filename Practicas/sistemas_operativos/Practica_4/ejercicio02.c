#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int p_h[2]; // Tubería padre a hijo
    int h_p[2]; // Tubería hijo a padre
    pid_t pid;

    if (pipe(p_h) == -1 || pipe(h_p) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // Proceso hijo

        close(p_h[1]); // Cerramos el extremo de escritura de p_h
        close(h_p[0]); // Cerramos el extremo de lectura de h_p

        char buffer[256];

        // Leer mensaje del padre
        size_t length = read(p_h[0], buffer, sizeof(buffer));
        buffer[length] = '\0';
        printf("[Hijo] Mensaje recibido: %s", buffer);

        // Esperar 1 segundo
        sleep(1);

        // Enviar el carácter 'l' al padre para indicar que está listo
        write(h_p[1], "l", 1);

        // Leer 10 mensajes y enviar 'q' al padre
        for (int i = 0; i < 10; i++)
        {
            size_t length = read(p_h[0], buffer, sizeof(buffer));
            printf("[Hijo] Mensaje recibido: %s", buffer);
            sleep(1);
            char flag[1] = "l";
            if (i == 9)
            {
                flag[0] = 'q';
            }
            write(h_p[1], flag, 1);
        }
        // sleep(2);
        // write(h_p[1], "q", 1);

        // Limpiar
        close(p_h[0]);
        close(h_p[1]);
    }
    else
    {
        // Proceso padre

        close(p_h[0]); // Cerramos el extremo de lectura de p_h
        close(h_p[1]); // Cerramos el extremo de escritura de h_p

        char buffer[256];

        // Leer mensaje del usuario
        printf("Ingrese un mensaje para el hijo: ");
        fgets(buffer, 256, stdin);

        // Enviar el mensaje al hijo
        write(p_h[1], buffer, strlen(buffer));

        // Esperar la señal del hijo ('l')
        read(h_p[0], buffer, 1);
        printf("[Padre] Hijo listo\n");

        // Enviar 10 mensajes al hijo
        int i = 0;
        while (buffer[0] != 'q')
        {
            sprintf(buffer, "%d\n", i);
            printf("[Padre] Mensaje %d para el hijo\n", i);
            write(p_h[1], buffer, strlen(buffer));
            read(h_p[0], buffer, 1);
            i++;
        }

        sleep(0.5);
        // Esperar 'q' del hijo y finalizar
        printf("[Padre] Hijo ha terminado. Finalizando.\n");

        // Limpiar
        close(p_h[1]);
        close(h_p[0]);

        // Esperar a que el hijo termine
        wait(NULL);
    }

    return 0;
}
