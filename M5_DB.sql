DROP DATABASE IF EXISTS M5_DB;
CREATE DATABASE M5_DB;

USE M5_DB;

CREATE TABLE PARTIDA (
    ID INT NOT NULL,
    ESTADO VARCHAR(60),
    FECHA_Y_HORA VARCHAR(60),
    DURACION FLOAT,
    GANADOR VARCHAR(60),
    PARTICIPANTES VARCHAR(200)
)ENGINE=InnoDB;

CREATE TABLE JUGADORES (
    ID INT NOT NULL,
    USUARIO VARCHAR(20),
    CONTRASEÑA VARCHAR(20),
    PUNTUACION_ACTUAL INT,
    IDPARTIDA INT
)ENGINE=InnoDB;

CREATE TABLE RANKING (
    ID_U INT,
    PUNTUACION_MAXIMA INT
)ENGINE=InnoDB;
   
INSERT INTO PARTIDA VALUES (98, 'JUGANDO', 15032021, 456.789, 'NADIE','JAVIER/GUILLERMO');
INSERT INTO PARTIDA VALUES (99, 'FINALIZADA', 14032021, 765.432, 'PAULA','CHUSO/MARTA/OMAR');

INSERT INTO JUGADORES VALUES (1, 'PACO', '12345', 12, 1);
INSERT INTO JUGADORES VALUES (2, 'MANUEL', '67891', 24, 2);
INSERT INTO JUGADORES VALUES (3, 'MARIA', '23456', 36, 1);
INSERT INTO JUGADORES VALUES (4, 'PAULA', '78912', 42, 2);

INSERT INTO RANKING VALUES (1, 59);
INSERT INTO RANKING VALUES (2, 48);
INSERT INTO RANKING VALUES (3, 36);
INSERT INTO RANKING VALUES (4, 73);
