******************************************
******************************************

REPOSITORIO DE MODELISMO ESPACIAL

Autores: Alvaro García y Mario Torralba

******************************************
******************************************

Este repositorio contiene modelos y prototipos de cohetes de modelismo espacial diseñados con OpenRocket
y proyectos de software y hardware basados en Arduino y/o tarjetas compatibles.

El repositorio se estructura de la siguiente manera:

	Modelos Construidos		--> Modelos diseñados con OpenRocket. Basandonos en las espectativas que nos da el simulador han sido
								construidos, pero no necesariamente lanzados.
						   
	Modelos en proceso 	    --> Modelos que están en proceso de diseño en OpenRocket. Susceptibles de sufrir cambios en diseño, materiales
						        motores empleados, etc.
						   
	Proyecto Exeo (y otros) --> Proyectos con alguna caracteristica o interés especial
	
	src                     --> Ruta donde estará el software de distintos proyectos que utilicen electrónica
	
	src/ejemplos            --> Ejemplos de algunos códigos
	
	src/librerias           --> Ruta de librerias que pueden ser compartidas por distintos proyectos.
							
			3pl				--> Librerías de terceras partes que publicaremos unicamente cuando la licencia lo permita
			
			propias			--> Nuestras propias librerías. Públicas y de uso libre.
			
	src/proyectos			--> Proceso principal tipo scketch arduino listo para cargar en tu tarjeta preferida
	

COMO UTILIZAR LOS PROYETOS

	Para utilizar un proyecto liberado unicamente necesitarás descargarte el scketch .ino correspondiente y sus librerías asociadas. Luego puedes 
	compilarlo en tu IDE favorito.
	Nosotros utilizamos VS Community 2013 con el plugin VisualMicro que permite desarrollar facilmente tus proyectos y el Arduino IDE.
	
	En caso de utilizar VS2013 puedes estructurar tu proyecto como prefieras.
	
	En caso de utilizar Arduino IDE, necesitarás ubicar las librerías que descargues en las rutas específicas de la instalación del IDE.
	
		Por ejemplo, una librería propia (.h y .cpp), deberá ir en la ruta C:\Program Files (x86)\Arduino\libraries\Name_final
		De esta	forma el IDE encontrará los recursos y compilará el scketch.
		
		Una librería de hardware (sensores, actuadores, etc), iría en la ruta C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\Name_final
		
		
		
IREMOS ACTUALIZANDO