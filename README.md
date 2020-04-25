# Helbreath v3.82 (from the Equilibrium Project)

This is the source files of Helbreath v3.82 including its client and server. It
contains everything to make a functional release as it was back then. The build
scripts and the C++ code have been modernized, and they have also been ported to
Linux; this is because it's heavily taken as a reference for the rewrite and
extensive testing needs to be done by the developers who use Linux. You will
also find the untouched version of the source files which were taken as a
starting point.

Helbreath has seen many updates coming from different developers since the
source files were leaked. Therefore it's a bit difficult to trace and understand
what is the official version 3.82 of Helbreath. The source files of the
Equilibrium Project were used and they implement features that is not considered
as vanilla Helbreath by most players.

The layout of the repository is organized as followed.

* sources/   - Modernized source files of the client and server (excluding the gate, main and world servers)
* resources/ - Assets used by the client and server; they're bundled with the compiled binaries to create a release
* tools/     - Folder to contain various tools and utilities related to development of Helbreath
* origin/    - Untouched Helbreath source files that were used as starting point

Note that the *Helbreath USA* folder isn't strictly untouched as the
*HelbreathUSAInstaller.exe* and *HelbreathUSA372.exe* files were removed because
they are large binaries and aren't well supported by GitHub without the use of
Git LFS. That said, they're irrelevant as the Helbreath USA folder is simply the
original base game folder on which the Equilibrium Project related files must be
copied on to of it, rendering these two files irrelevant.

For more information, contact dewachter[dot]jonathan[at]gmail[dot]com.
