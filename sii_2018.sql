-- CREACION DE BASE DE DATOS POR CONSOLA
CREATE DATABASE SII_2018;
-- USO DE BASE DE DATOS SII_2018
USE SII_2018; 
-- Creacion de tabla para sii_2018
CREATE TABLE `IDENTIFICACION_DE_VEHICULO` (
    `vehiculoID` int  NOT NULL ,
    `codigo` varchar(7)  NOT NULL ,
    `ano` int  NOT NULL ,
    `tipo` varchar(50)  NOT NULL ,
    `marca` varchar(50)  NOT NULL ,
    `modelo_raw` varchar(100)  NOT NULL ,
    `modelo` varchar(50)  NOT NULL ,
    `version` varchar(50)  NOT NULL ,
    `ptas` int  NOT NULL ,
    `cilindr` int  NOT NULL ,
    `comb` ENUM('BENC','DIES','ELEC')  NOT NULL ,
    `trans` ENUM('MEC','AUT')  NOT NULL ,
    `equip` ENUM('EQUI','FULL','NORM')  NOT NULL ,
    `tas_2018` int  NOT NULL ,
    `perm_2018` int  NOT NULL 
);

