[KLKS]'s DupeChecker Utility ReadMe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Made this dupe checker in my free time for eternalHB and now i'm sharing it
to the HB community. Now to use the app.

1.Run "HB 2.20 Dupe Checker.exe"
2.Click Browse and select the character files directory, eg "C:\HB\Characters"
3.Click the Filter Items button and let it parse all the character files, it skips .bak files so dont worry. Wait for it to finish before going on, it should create a file called output.txt
4.Click Start and let the dupe checker scan for duped items. Once its finished hit Save Dupe, it should create a file called DupeItems.txt
5.Close the dupe checker and run "DupItemID cfg Maker.exe" and select the character files directory, eg "C:\HB\Characters" and it should spit out a nice DupItemID.cfg and with that just throw it in ur HB Folder

Side Notes
~~~~~~~~~~
1.Add names u want to ignore dupe check into "ExcludeNames.txt"
2.Add items u wanna skip scanning into "IgnoredItems.txt"
3.Anything with a "1 0 0 0" should go into IgnoredItems.txt cos there is no unique id.
4.When you rename a character, remember to delete the old character file or else it will turn up as dupes
5.HB's hgserver is designed to only do 100 duped items so dont expect everything to dissapear immediately

Have Fun,
[KLKS]