;	V2.64 to V3.0.100 (Version 1.0.6)
;	Converted with AutoItV2toV3 [Version 1.0.6]
;	(C) Copyright 2004 J-Paul Mesnage.

; Prologue		; should be renamed (?) and called somewhere if you are converting  an include file
__init()
; End Prologue
TrayTip ( "Equilibrium Project", "Ce script sert à démarrer de façon automatique le serveur.Ne toucher à rien pendant son exécution!", 20 , 1 )
MsgBox(0, "Equilibrium Project", "Démarrer le serveur Equilibrium Project.",0x40000)
ProgressOn("Equilibrium Project", "Démarage automatisé du serveur", "Début",-1,-1,16)
Sleep ( 1000 )
Run ( 'D:\EP_Server\Gate\GateServer[by_Sobame].exe', 'D:\EP_Server\Gate\' )
ProgressSet(5 , "Démarage du Gate server", "Démarage d'Equilibrium Project")
Sleep ( 2000 )
WinShow ( 'Helbreath GateServer 2002-6-20', '', @SW_MINIMIZE )
Sleep ( 1000 )




; Main
Run ( 'D:\EP_Server\Core\MainLServer 496.exe', 'D:\EP_Server\Core\' )
ProgressSet(10 , "Démarage du Main server", "Démarage d'Equilibrium Project")
Sleep ( 3000 )
WinActivate ( 'HB Main-Log-Server v3.51 Extasis fix (Snoopy81)' )
Send ( '{HOME}' )
ProgressSet(15 , "Activation du Main server", "Démarage d'Equilibrium Project")
Sleep ( 2000 )
WinShow ( 'HB Main-Log-Server v3.51 Extasis fix (Snoopy81)', '', @SW_MINIMIZE )
Sleep ( 1000 )


; World
Run ( 'D:\EP_Server\Core\WorldLServer Extasis.exe', 'D:\EP_Server\Core\' )
ProgressSet(20 , "Démarage du World server", "Démarage d'Equilibrium Project")
Sleep ( 8000 )
WinActivate ( 'Helbreath World-Log-Server V2.15' )
Send ( '{HOME}' )
ProgressSet(35 , "Activation du World server", "Démarage d'Equilibrium Project")
Sleep ( 2000 )
WinShow ( 'Helbreath World-Log-Server V2.15', '', @SW_MINIMIZE )
Sleep ( 1000 )


;Exit(0)




Run ( 'D:\EP_Server\GameServers\0_equi\HGserver.exe', 'D:\EP_Server\GameServers\0_equi\' )
ProgressSet(40 , "Démarage des Game  servers", "Démarage d'Equilibrium Project")
Sleep ( 8000 )

Run ( 'D:\EP_Server\GameServers\1_aresden\HGserver.exe', 'D:\EP_Server\GameServers\\1_aresden' )
ProgressSet(55 , "Démarage des Game  servers", "Démarage d'Equilibrium Project")
Sleep ( 8000 )

Run ( 'D:\EP_Server\GameServers\2_elvine\HGserver.exe', 'D:\EP_Server\GameServers\\2_elvine' )
ProgressSet(70 , "Démarage des Game  servers", "Démarage d'Equilibrium Project")
Sleep ( 8000 )

Run ( 'D:\EP_Server\GameServers\3_hunting\HGserver.exe', 'D:\EP_Server\GameServers\\3_hunting' )
ProgressSet(85 , "Démarage des Game  servers", "Démarage d'Equilibrium Project")
Sleep ( 8000 )

Run ( 'D:\EP_Server\GameServers\4_ml\HGserver.exe', 'D:\EP_Server\GameServers\\4_ml' )
ProgressSet(100 , "Démarage des Game  servers", "Démarage d'Equilibrium Project")
Sleep ( 3000 )

ProgressOff()

; Epilogue	Extra Functions needed for Compatibility execution
; 			take care of possible redefinition if you are converting  an include file
;
func __init ()		; to define global variables needed
endfunc
; End Epilogue
