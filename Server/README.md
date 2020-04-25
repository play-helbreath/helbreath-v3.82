______________________________________
         Fichiers utiles
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

HBmaster.exe:
¯¯¯¯¯¯¯¯¯¯¯¯¯
ftp://ftp.lpmintekz.com/
Pour eclosions, Patch IP journalière, creations de comptes
et bien d'autres choses encore.
NB: Fichier inf pour mettre certaines données ds la base de registre.
NB: Attention à sélectionner HBX sinon .....

Demarrer_Serveur.exe:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
Script compilé pour démarrer le serveur simplement.

FTP:
¯¯¯¯
Il en faudra un pour uploader le LOGIN.CFG très souvent...

Install.iit:
¯¯¯¯¯¯¯¯¯¯¯¯
Document Install creator. Pour créer simplement une install
pour les joueurs. 
(Il faut installer le soft, http://www.clickteam.com/ )


______________________________________
         Fichiers à modifier
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

Server../core/noticement.txt:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
Texte de bienvenue affiché en jeu au démarrage.

Client../Install.inf:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
Mêts à jour les clefs de base de registre nécéssaires
au lanceur pour savoir ou aller chercher LOGIN.CFG.
Il faut y mettre l'URL de ce fichier, avant de le faire
installer par les joueurs.

Client../LOGIN.CFG:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
Le fichier fourni initialement au joueurs a peu d'importance.
Mais il faut placer ce fichier qui contient des données 
importantes pour le lanceur et le client à un emplacement
fixe sur le web.

Lorsqu'on veut jouer, le lanceur va récupérer ce fichier,
pour:
- [Message] Afficher le message du hosteur
- [UPDATES] Effectuer les mises à jour automatiques.
- [PatchIP] Connaitre l'IP du serveur
- [PatchIP] Détecter si le serveur est en route:
            IP fixe: essaye de connecter un Game server.
            IP variable: regarde régulièrement si LOGIN.CFG
                     a été modifié.
- [PatchIP] Pinguer le serveur.
- [PatchIP] Afficher l'URL du site du serveur
- [PatchIP] Afficher le Nom du serveur.

Ce fichier sert également pour configurer le client:
- [CONFIG] IP, port, et mode (Utiliser LAN, sauf multi-host)


Server../HMLServer.cfg, WLserver.cfg, GateServer.cfg, gserver.cfg:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
Fichiers de configuration des serveurs. Il faut modifier ici
les IP selon tes besoins. (IP interne ET externe)
HBMaster est capable de faire celà pour tous les fichiers
à la fois. (A vérifier, fait des sauvegardes avant.)


Server../GameConfigs/*.cfg:
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
Ici sont stocké pas mal de réglages communes à tous les GameServers.
Ce qui date des sources Siementec est envoyé aux Games par le World
(ex: items, potions...)
Mais tout ce qui a été rajouté ultérieurement est ici, car il aurait
fallu reprogramer le World, et les sources n'étaient pas disponibles.

Settings.cfg est très important, il y a une doc qui en parle.



______________________________________
         Ports à forwarder
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
MLS: (HMLServer.cfg)   2981
WLS: (WLserver.cfg):   2881, 2882, 2883 
(il écoute 3 ports, mais le premier devrait suffire sur un serveur privé)
Games: (gserver.cfg):   9900 et +
Pings du lanceur: Ports des Games + 20.




