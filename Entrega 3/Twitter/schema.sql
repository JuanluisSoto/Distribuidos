CREATE TABLE Users (name varchar(20), email varchar(30), password varchar(20), bio varchar(229), avatar varchar(33), phrase varchar(25), primary key(name));
													
CREATE TABLE Mensajes (id int AUTO_INCREMENT, name_user varchar(20), message varchar(281), dato varchar(40), tipo_dato varchar(10), primary key(id), foreign key(name_user) references Users(name));

## Identificador de mensaje, ID Usuario que lo creó, mensaje, dato adjunto (solo uno), 
## tipo de dato (video/imagen)
