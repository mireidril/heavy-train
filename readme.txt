==== INSTALLATION =====
Tout d'abord, j'espère que vous n'avez pas placé le dossier SVN HeavyTrain à un endroit où le chemin est constitué d'un accent (ex : Document/Céline/HeavyTrain) Si c'est le cas, changez son emplacement, car Cmake n'aime pas les accents.

Sous Linux, vous avez besoin des bibliothèques suivantes :
SDL
SDL_image
SDL_ttf
SDL_mixer
SDL_gfx
smpeg
tinyXML

Sous Windows :
1. Installer Cmake : http://www.cmake.org/cmake/resources/software.html et Visual C++ Express 2010 : http://www.microsoft.com/visualstudio/en-us/products/2010-editions/visual-cpp-express
2. Lancez cmake-gui
3. Complétez les deux champs du haut avec :
 - Where is the source code : [chemin du SVN]
 - Where to build the binaries : [chemin du SVN]/windows
4. Cliquez sur "Configure" puis choisissez "Visual Studio 10" puis cliquez sur OK
5. Cliquez une seconde fois sur "Configure" puis ensuite sur "Generate"
6. C'est fini ! Lancez le projet Visual Studio "HeavyTrain.vcproj" du répertoire "windows", puis clic droit sur le projet dans Visual Studio et choisissez "Définir le projet comme projet de démarrage". Heavy Train devrait maintenant être écrit en gras. Faites F7 pour compiler et F5 pour compiler puis lancez le programme.

Sous Linux
1. Avec des apt-get ou avec l'installeur Synaptic, installez Cmake et tinyXml.
2. Installez Box2D en téléchargeant l'archive suivante (http://code.google.com/p/box2d/downloads/detail?name=Box2D_v2.2.1.zip&can=2&q=) et suivez les indications du fichier build.txt
3. Lancez cmake-gui
4. Complétez les deux champs du haut avec :
 - Where is the source code : [chemin du SVN]
 - Where to build the binaries : [chemin du SVN]/linux
5. Cliquez sur "Configure" puis choisissez "Unix Makefile" puis cliquez sur OK
6. Cliquez une seconde fois sur "Configure" puis ensuite sur "Generate"
7. C'est fini ! Le makefile se situe dans le répertoire "linux"

==== CREER SES NIVEAUX =====
Vous voulez créer votre propre niveau ?  Aucun problème, notre jeu le permet et même l'encourage ! Heavy Train permet la création de niveaux grâce au fichier levels.xml
Amusez vous en remplaçant les trois niveaux du jeu par les vôtres !

Exemple de configuration d'un niveau :
<world>
	<island id="1">
		<level id="1">
			<!-- Heure de départ du niveau  -->
			<departure hour="12" minutes="00" seconds="00"/>
			
			<!-- Image de sol de niveau : doit être de dimension 2048x384  -->
			<sprite type="ground" img="../img/levels/level2/niveau2-sol2.png"/>
			
			<!-- Image de fond du niveau à la position posY (par défault à 0) -->
			<sprite type="background" img="../img/levels/level1/niveau1-sky.png" />
			<sprite type="background" posY="518" img="../img/levels/level1/niveau1-mountain.png" />
			
			<!-- Une infobulle de type "type" apparaîtra dans le niveau, après l'évènement "action"
			<infobulle type="standard" action="collision" declenche="false">
				<sprite img="info2.png" />
			</infobulle>
			
			<!--Block de type Gare, de longueur "size"-->
			<station size="200">
				<!-- Horaire d'arrivée à la gare -->
				<option hours="12" minutes="00" leaving="0" entering="10"/>
			</station>
			
			<!-- Block de type Ground, de longueur 1024 -->
			<block type="GROUND" size="1024">
				<obstacle type="animal" nom="vache" posX="800" posY="300" />
			</block>
			
			<block type="TUNNEL" size="200">
			</block>
			
			<block type="GROUND" size="1024">
				<point x="400" y = "600" />
				<point x="600" y = "660" />
			</block>
	
			<station size="200">
				<option hours="12" minutes="30" leaving="5" entering="15"/>
				<infobulle type="aide" declenche="false" posX="800">
					<sprite img="info1.png" />
				</infobulle>
			</station>
			
			<block type="PRECIPICE" size="100">
				<obstacle type="bonus" nom="etoile" posX="3200" posY="300" />
			</block>

			<station size="200">
				<option hours="13" minutes="00" leaving="2" entering="20"/>
			</station>
		</level>
	</island>
</levels>

Pour plus de détails, consultez les cahiers des charges.