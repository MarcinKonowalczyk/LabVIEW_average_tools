# LabVIEW utils
A LabVIEW (Work In Progres) package constructed alingside, and for the purpouse of, writing scientific experiments. Written in LabVIEW 2015 SP1.

The aim of the toolbox is not to duplicate the functionality of any of the other excellent ones out there (GPowr, OpenG, MGI, etc...). Any duplicated functionality is there in order to reduce how dependant this toolbox is on others (e.g. )

## Packages
 - **average_tools** - Tools for taking averrages in a PtByPt manner. These include an extensive data queue and a plot history.
 - **error_tools** - Tools for handling erros in all the other toolboxes + some general error tools.
 - **filter_tools** - Tools for filtering signals. Some in PtByPt fassion, some in Snapshot By Snapshot, and some where each snapshot is independant of one another.
 - **h5_tools** - Tools working with the h5 LabVIEW toolbox which help with saving files.
 - **misc_tools** - Miscalenous. Might get redistributed around other toolboxes.
 - **persist_controls** - Save/Load controls on vi stop/start respectivelly.
 - **recursive_set_cluster_element** - What it says on the tin
 - **ref_tools** - Tools for workign with control and vi references.
 - **robust_set_cursor_busy_state** - Set sursor to busy state but don't thow and error if in a closed vi.
 - **sweep_string_processing** - Tools for working with variable range strings. See README_sweep_string_processing.md for more information.
 - **timing_tools** - Tools for keeping time and asynchronous wait.
 - **xwave** - Extensive data typedef for working with multidimentional data.

## Dependencies
The following are the external packages used by the toolbox.

 - GPower (eventually will become obsolete)
 - OpenG
 - h5 labview (http://h5labview.sourceforge.net/)

## ToDo's
### Easy ToDos
These can be done by alost anyone. Some require LabVIEW, but none require much knowledge about it
 - Prettify README
 - Add assets folder and extract icons from vi's to use as glyphs
 - Fix typos (I do pay attention as I write, but some things go through)
 - Add documentation to each vi describing what it does
 - Make the colors in vis consistent (currently there are two yellows around the place)
 - Prepare design guidelines (Rough list of colors used, block diagram best practises etc.)
 - Add small README to each toolbox describing what it does

### More difficult ToDos
Things I'm not doing because they are not crucial yet, but I will eventually tick them off
 - ECOs in the error handler
 - Make more polys for the average_tools avergage Nth value
 - Look at the code and see what else neeeds doing. Then put it on this very list
 - Write own timing tools based on ones from Gpower to reduce the dependancy of the Gpower toolbox
 - Self: Import filter tools from downstairs (< Note for self. Noone else can do that.)
 - Merge xwav and xywav into a single data class. Update the other tools (e.g. h5_tools accordingly)
 - Write examples for xwav
 - Write examples for sweep_string_processing
 -
### Hard ToDos
Basically things I do not know how to do myslef (either because they are difficult or because I have not spent much time researching how to actually get it done). Please help.
 - Make this into an actuall package on VIPM (When it's actually done of course)
<<<<<<< HEAD
 - Add fancy menu items ??
 - Make help files ??
 - Custom front pannel control set... ?
=======
 - Add fancy menu items
 - Does anyone know good way to write a vi which works with (any) queues?
>>>>>>> documentation
