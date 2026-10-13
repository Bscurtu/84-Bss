Primera syscall:
execve es la primera en todas

2.
brk ajusta la posicion final de la memoria. Empieza en NULL.
mmap crea un nuevo espacio en la posicion virtual, que empieza donde addr le indica.
Mprotect se asegura de que la memoria tenga los permisos que se requieran.

3.
Se usa openat por que permite diferenciar directorios relativos de absolutos.

4.
Al escribir en terminal (sin salto de linea al final), printf acumula los caracteres y luego los escribe en un unico write.
En un archivo se observa que guarda todo en un buffer, y lo mete de una en el archivo.

5.
Descubierdo que read devuelve cuanto lee, se puede usar para no pasarte en el buffer de mas de 1 de tamaño