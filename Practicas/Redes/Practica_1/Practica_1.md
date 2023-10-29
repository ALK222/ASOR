# Práctica 1: IPv4 y DHCP

**Ejercicio 1: [vm_1]** Determina las interfaces de red que tiene la máquina y las direcciones IP y MAC que tiene asignadas, utiliza los comandos ip address e ip link

```shell
ubuntu@ubuntu-jammy:~$ ip address
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host
       valid_lft forever preferred_lft forever
2: enp0s3: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 02:00:00:00:01:00 brd ff:ff:ff:ff:ff:ff

```

**Ejercicio 2: [vm_1, vm_2, vm_3router]** Activar las interfaces enp0s3 en vm_1, vm_2 y vm_3router y asignar una dirección IP adecuada. Utilizar los comandos ip address e ip link

```shell
ubuntu@ubuntu-jammy:~$ sudo ip address add 192.168.0.3/24 dev enp0s3
ubuntu@ubuntu-jammy:~$ sudo ip link set dev enp0s3 up
```

**Ejercicio 3: [vm_1, vm_2]** Abrir la herramienta whiresark en vm_1 e iniciar una captura de red. Desde vm_1, comprobar la conectividad con vm_2 usando la orden ping. Observar el tráfico generado, especialmente los protocolos encapsulados en cada datagrama y las direcciones origen y destino. Para ver correctamente el tráfico ARP, puede ser necesario eliminar la tabla ARP en vm_1 con la orden ip neigh flush dev enp0s3.

Completar la siguiente tabla para todos los mensajes intercambiados hasta la recepción del primer mensaje ICMP Echo reply

- Para cada protocolo, anotar las características importantes en el campo "Tipo de mensaje".
- Comparar los datos observados durante la captura con el formato de los mensajes estudiados en clase.

| MAC origen        | MAC destino       | Protocolo | IP Origen   | IP destino  | Tipo de mensaje |
| ----------------- | ----------------- | --------- | ----------- | ----------- | --------------- |
| 02:00:00:00:01:00 | ff:ff:ff:ff:ff:ff | ARP       | 192.168.0.1 | Broadcast   | Request         |
| 02:00:00:00:02:00 | 02:00:00:00:01:00 | ARP       | 192.268.0.2 | 192.268.0.1 | Reply           |
| 02:00:00:00:01:00 | 02:00:00:00:02:00 | ICMP      |             |             |                 |
|                   |                   |           |             |             |                 |
